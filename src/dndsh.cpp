#include "dndsh.hpp"
#include "help_messages.hpp"

DnDsh::DnDsh() {
    this->characterData = {
        "NAME.Tywin",
        "STRENGTH.15",
        "HEALTH.25:6",
        "DEXTERITY.10",
        "SS1.5",
        "SS2.10",
        "SS3.4"
    };
}


int DnDsh::cmd_REQ( std::string input ) {
   
    std::istringstream inputStream(input);
    std::string token;
    std::list<std::string> commandTokens;
    int returnStatus = 0;


    while( inputStream >> token ) {
        commandTokens.push_back( token );
    }
    commandTokens.push_back("");

    std::string command = commandTokens.front();
    commandTokens.pop_front();

    // command options
    if( command == "spell" || command == "sp" ) {
        returnStatus = cmd_SPELL( commandTokens );
    } else if( command == "ls" || command == "l" ) {
        returnStatus = cmd_STATS( commandTokens.front() );
    } else if( command == "help" ) {
        returnStatus = cmd_HELP( commandTokens.front() );
    } else if( command == "health" || command == "hp" ) {
        returnStatus = cmd_HEALTH( commandTokens );
    } else if( command == "mod" ) {
        returnStatus = cmd_MODSTAT( commandTokens );
    } else if( command == "add" ) {
        returnStatus = cmd_ADDSTAT( commandTokens );
    } else if( command == "remove" || command == "rm" ) {
        returnStatus = cmd_RMVSTAT( commandTokens.front() );
    } else if( command == "load" || command == "ld" ) {
        returnStatus = cmd_LOAD( commandTokens.front() );
    } else if( command == "store" || command == "st" ) {
        returnStatus = cmd_STORE( commandTokens.front() );
    } else if( command == "exit") {
        returnStatus = -1;
    } else {
        returnStatus = cmd_ROLL( input );
    }

    commandTokens.clear();

    return returnStatus;

}


int DnDsh::cmd_ROLL( std::string command ) {

    if( command == "d" ) {
        std::cout << this->format_err( "unknown command. Type \'help\' for a list of commands" );
        return 1;
    }
    
    else if( command.find('d') < command.size() ) {

        int locationOfd = command.find('d');

        for( int i = 0; i < locationOfd; i++ ) {
            if( !isdigit(command.at(i)) ) {
                std::cout << this->format_err( "unknown command. Type \'help\' for a list of commands" );
                return 1;
            }
        }

        for( unsigned int i = (locationOfd + 1); i < command.size(); i++ ) {
            if( !isdigit(command.at(i)) ) {
                std::cout << this->format_err( "unknown command. Type \'help\' for a list of commands" );
                return 1;
            }
        }

        int rollTimes = 0;
        int rollMod = 1;

        rollTimes = (command.find('d') == 0) ? 1 : stoi(command.substr(0, command.find('d')));
        rollMod = stoi(command.substr(command.find('d') + 1, command.length()));

        std::cout << CYAN << "rolled: " << BOLDWHITE << roll(rollTimes, rollMod) << RESET << std::endl;
    }

    else if( command.size() == 0 ) {
        return 0;
    }

   else {
        std::cout << this->format_err( "unknown command. Type \'help\' for a list of commands" );
        return 1;
    }
 
    return 0;
}


// Sample Usage:    stat [<key>]           //NOTE: [<key>] entered empty will print out every stat
int DnDsh::cmd_STATS( const std::string &key ) {

    if( key == "" ) {
        for( unsigned int i = 0; i < this->characterData.size(); i++ ) {
            this->printStat(this->characterData.at(i)); 
            std::cout << std::endl;
        }
    }

    else {
        unsigned int locationOfKey = this->locateKey( key );
        if ( locationOfKey < this->characterData.size() ) {
            this->printStat( this->characterData.at( locationOfKey ) );
            std::cout << std::endl;
        }

        else {
            std::cout << this->format_err( "stat: stat not found. Type \'ls\' for a list of stats" ); 
            return 1;
        }
    }

    return 0;
}



// Sample Usage:    help [<command>]    //NOTE: absent [<command>] prints all available commands
int DnDsh::cmd_HELP( const std::string &command ) {
    
    if( command == "" ) {
        std::cout << DNDSH_COMMAND_HELP_LIST << std::endl;
    } else if( command == "roll" ) {
        std::cout << DNDSH_ROLL_CMD_HELP << std::endl;
    } else if( command == "ls" || command == "l" ) {
        std::cout << DNDSH_STATS_CMD_HELP << std::endl;
    } else if( command == "spell" || command == "sp" ) {
        std::cout << DNDSH_SPELL_CMD_HELP << std::endl;
    } else if( command == "health" || command == "hp" ) {
        std::cout << DNDSH_HEALTH_CMD_HELP << std::endl;
    } else if( command == "mod" ) {
        std::cout << DNDSH_MOD_CMD_HELP << std::endl;
    } else if( command == "add" ) {
        std::cout << DNDSH_ADD_CMD_HELP << std::endl;
    } else if( command == "remove" || command == "rm" ) {
        std::cout << DNDSH_RM_CMD_HELP << std::endl;
    } else if( command == "load" || command == "ld" ) {
        std::cout << DNDSH_LD_CMD_HELP << std::endl;
    } else if( command == "store" || command == "st" ) {
        std::cout << DNDSH_ST_CMD_HELP << std::endl;
    } else {
        std::cout << this->format_err( "unknown command: type \'help\' for a list of commands" );
        return 1;
    }

    return 0;
}



// Sample Usage:    spell {<spell_level>|all} [<modifier>]        //NOTE: [<modifier>] is by default assumed as: -1
//                  spell reset [<spell_level>]                   //NOTE: [<spell_level>] is by default 'all'
//                  spell master {<spell_level>|all} <modifier>
int DnDsh::cmd_SPELL( std::list<std::string> &spellEntry ) {

    if( spellEntry.front() == "" ) {
        std::cout << this->format_err( "incorrect usage: type \'help spell\' to learn more." );
        return 1;
    }


    int returnStatus = 0;
   
    bool master = false;
    int locationOfKey;
    std::string level = spellEntry.front();
    spellEntry.pop_front();

    if( level == "master" ) {
        master = true;
        level = spellEntry.front();
        spellEntry.pop_front();
    }


    if( isdigit(level.at(0)) ) {
        
        level = "SS" + level;
        locationOfKey = this->locateKey( level );

        if( locationOfKey < 0 ) {
            this->format_err( "key not found: \'" + level + "\' does not exist. Add key using \'add\' command." );
            return 1;
        }

        else {
            return this->modifyRule( level, spellEntry.front(), master );
        }
    }

    else if( level == "all" ) {
        for( int i = 1; i < 10; i++ ) {
            locationOfKey = this->locateKey( "SS" + std::to_string(i) );
            if ( locationOfKey < 0 ) {
                std::cout << "spell slot " << i << " does not exist. stopping..." << std::endl;
                return 0;
            } else {
                returnStatus = this->modifyRule( "SS" + std::to_string(i), spellEntry.front(), master );
                if( returnStatus ) return 1;
            }
        }
    }

    else if( level == "reset" ) {
        if( spellEntry.front() == "" ) {
            for( int i = 1; i < 10; i++ ) {
                locationOfKey = this->locateKey( "SS" + std::to_string(i) );
                if ( locationOfKey < 0 ) {
                    std::cout << "spell slot " << i << " does not exist. stopping..." << std::endl;
                    return 0;
                }
                else {
                    returnStatus = this->modifyRule( "SS" + std::to_string(i), "reset", master );
                    if( returnStatus ) return 1;
                }
            }
        }

        else if( isdigit(spellEntry.front().at(0)) ) {
            level = "SS" + spellEntry.front();
            locationOfKey = this->locateKey( level );
            if( locationOfKey < 0 ){
                std::cout << this->format_err( "key not found: \'" + level + "\' does not exist. Add key using \'add\' command." );
                return 1;
            }

            else {
                return this->modifyRule( level, "reset", master );
            }
        }

        else {
            std::cout << this->format_err( "incorrect usage: type \'help spell\' to learn more" );
            return 1;
        }
    }

    else {
        std::cout << this->format_err( "incorrect usage: type \'help spell\' to learn more" );
    }

    return 0;
}



// Sample Usage:    health <modifier>
//                  heatlh reset
//                  heatlh master <modifer>
int DnDsh::cmd_HEALTH( std::list<std::string> &modifyBy ) {
   
    int returnStatus = 0;
    
    if( this->locateKey( "HEALTH" ) < 0 ) {
        std::cout << this->format_err( "key not found: \'HEALTH\' does not exist. Add key using \'add\' command." );
        return 1;
    } 

    else if( modifyBy.front() == "" ) {
        std::cout << this->format_err( "incorrect usage: type \'help health\' to learn more" );
        return 1;
    }

    else if( modifyBy.front() == "master" ) {
        modifyBy.pop_front();
        returnStatus = this->modifyRule( "HEALTH", modifyBy.front(), true );
    }

    else {
        returnStatus = this->modifyRule( "HEALTH", modifyBy.front(), false );
    }

    return returnStatus;
}



// Sample Usage:    mod <stat> <primary_value> [<secondary_value>]    //NOTE: [<secondary_value>] will by default delete <secondary_value> if it exists
int DnDsh::cmd_MODSTAT( std::list<std::string> &modEntry ) {

    if( modEntry.front() == "" ) {
        std::cout << this->format_err( "incorrect usage: missing <stat>. Type \'help mod\' to learn more" );
        return 1;
    }

    std::string stat = this->upper( modEntry.front() );
    modEntry.pop_front();

    int locationOfKey = this->locateKey( stat );
    if( locationOfKey < 0 ) {
        std::cout << this->format_err( "stat not found: type \'ls\' for a list of available stats" );
        return 1;
    }

    if( modEntry.front() == "" ) {
        std::cout << this->format_err( "incorrect usage: missing <new_value>. Type \'help mod\' to learn more" );
        return 1;
    }

    // load primary_value
    stat += '.' + modEntry.front();
    modEntry.pop_front();

    std::string secondaryValue = modEntry.front();
    modEntry.pop_front();

    // check for <secondary_value>
    if( secondaryValue != "" ) {
        stat += ":" + secondaryValue;
    }
    
    // load secondaryValue
    this->characterData.at( locationOfKey ) = stat;

    return 0;
}



// Sample Usage:    add <new_stat> <new_value> [<new_ancillary_value>]    //NOTE: [<new_ancillary_value>] will by deafult skip appending a new_ancillary_value to new_key
int DnDsh::cmd_ADDSTAT( std::list<std::string> &addEntry ) {

    if( addEntry.front() == "" ) {
        std::cout << this->format_err( "incorrect usage: missing <new_stat>. Type \'help add\' to learn more" );
        return 1;
    }

    std::string newStat = this->upper(addEntry.front());
    addEntry.pop_front();

    if( addEntry.front() == "" ) {
        std::cout << this->format_err( "incorrect usage: missing <new_primary_value>. Type \'help add\' to learn more" );
        return 1;
    }
    
    newStat += "." + addEntry.front();
    addEntry.pop_front();

    if( addEntry.front() != "" ) {    
        newStat += ":" + addEntry.front();
    }

    std::cout << "Added: " << newStat << std::endl;

    this->characterData.push_back( newStat );

    return 0;
}



// Sample Usage:    rm  <key>
int DnDsh::cmd_RMVSTAT( const std::string &stat ) {
    
    if( stat == "" ) {
        std::cout << this->format_err( "incorrect usage: type \'help remove\' to learn more" );
        return 1;
    }

    else {
        int locationOfKey = this->locateKey( stat );
        if ( locationOfKey < 0 ) {
            std::cout << this->format_err( "stat not found: type \'ls\' for a list of available stats" );
            return 1;
        }

        else {
            this->characterData.erase( characterData.begin() + locationOfKey );
        }
    }

    return 0;
}



// Sample Usagae:   ld <file_path>
int DnDsh::cmd_LOAD( const std::string &path ) {
    std::cout << "Need to implement LOAD" << std::endl;
    return 0;
}



// Sample Usage:    st <file_path>
int DnDsh::cmd_STORE( const std::string &path ) {
    std::cout << "Need to implement STORE" << std::endl;
    return 0;
}



////// Helper Functions //////
int DnDsh::roll(int times, int modulus) {

    int sum = 0;

    for (int i = 0; i < times; i++) {
        sum += rand() % modulus;
    }

    return sum + 1;
}


int DnDsh::locateKey( std::string key ) {
    
    std::string capKey = this->upper( key );

    for( int i = 0; i < this->characterData.size(); i++ ) {
        if( this->characterData.at(i).substr(0, characterData.at(i).find('.')) == capKey ) return i;
    }

    return -1;
}


std::string DnDsh::upper( std::string input ) {
    
    for( unsigned int i = 0; i < input.size(); i++ ) {
        if(isalpha( input.at(i) )) input.at(i) = toupper( input.at(i) );
    }

    return input;
}


int DnDsh::modifyRule( std::string key, std::string modifyBy, bool master ) {

    int returnStatus = 0;

    int locationOfKey = this->locateKey( key );
    std::string datum = this->characterData.at(locationOfKey);
    unsigned int locationOfTempValue = datum.find(':');
    bool ancillaryValueExists = ( locationOfTempValue < datum.size() );
    int masterValue;
    int ancillaryValue;

    // initialize ancillaryValue and masterValue from available ancillary else master
    if( ancillaryValueExists ) {
        masterValue = std::stoi(datum.substr(datum.find('.') + 1, datum.find(':') - datum.find('.') - 1));
        ancillaryValue = std::stoi(datum.substr(datum.find(':') + 1, datum.size() - datum.find(':') - 1));
    } else {
        masterValue = ancillaryValue = std::stoi(datum.substr(datum.find('.') + 1, datum.size() - datum.find('.') - 1));
    }

    
    int &valueToAdjust = ( master ) ? masterValue : ancillaryValue;

    // begin manipulation of data
    // manipulate data by modifier and update ancillaryValue
    if( modifyBy.at(0) == '+' ) {
        valueToAdjust += std::stoi(modifyBy.substr(1, modifyBy.size() - 1));
    }

    else if( modifyBy.at(0) == '-' ) {
        valueToAdjust -= std::stoi(modifyBy.substr(1, modifyBy.size() - 1));
    }

    else if( modifyBy == "reset" ) {
        if( master ){
            std::cout << this->format_err("modifier rule: cannot reset master value");
            return 1;
        }

        ancillaryValue = masterValue;
    }

    else {
        for( char i : modifyBy ) {
            if( !isdigit(i) ) {
                std::cout << this->format_err( "modifier rule: unknown modifer" );
                return 1;
            }
        }

        valueToAdjust = std::stoi(modifyBy);
    }


    // adjust ancillary value and max value to respected bounds
    if( ancillaryValue < 0 ) { 
        ancillaryValue = 0;
    } else if( ancillaryValue > masterValue ) {
        ancillaryValue = masterValue;
    }

    if( masterValue < 0 ) {
        masterValue = 0;
    }

    this->characterData.at(locationOfKey) = this->upper(key) + "." + std::to_string(masterValue) + ":" + std::to_string( ancillaryValue );        

    return returnStatus;
}




void DnDsh::printStat( std::string datum ) {

    unsigned int locationOfTempValue = datum.find(':');
    bool ancillaryValueExists = ( locationOfTempValue < datum.size() );

    std::string stat = datum.substr(0, datum.find('.'));
    std::string masterValue;
    std::string ancillaryValue;
    
    if( ancillaryValueExists ) {
        masterValue = datum.substr(datum.find('.') + 1, locationOfTempValue - datum.find('.') - 1);
        ancillaryValue = datum.substr(locationOfTempValue + 1, datum.size() - locationOfTempValue);
    } else {
        masterValue = datum.substr(datum.find('.') + 1, datum.size() - datum.find('.') - 1);
        ancillaryValue = "";
    }

    std::cout << BOLDWHITE << stat << RESET << CYAN << ": " << RESET;

    if( ancillaryValueExists ) {
        std::cout << BOLDRED << ancillaryValue << RESET << CYAN << "/" << BOLDWHITE << masterValue << RESET;
    } else {
        std::cout << BOLDWHITE << masterValue << RESET;
    }

    return;
}



std::string DnDsh::format_err( std::string message ) {

    std::ostringstream formatStream;
    std::string formattedString;

    formatStream << BOLDRED << "error: " << RESET << RED << message << RESET << std::endl;
    formattedString = formatStream.str();

    return formattedString;
}





