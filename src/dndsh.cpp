#include "dndsh.hpp"
#include "help_messages.hpp"

DnDsh::DnDsh() {
    this->characterData = {
        "NAME.Tywin",
        "STRENGTH.15:10",
        "HEALTH.25:10",
        "DEXTERITY.10"
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

    // command options
    if( commandTokens.front() == "spell" ) {
        commandTokens.pop_front();
        returnStatus = cmd_SPELL( commandTokens );
    } else if( commandTokens.front() == "stats" ) {
        commandTokens.pop_front();
        returnStatus = cmd_STATS( commandTokens.front() );
    } else if( commandTokens.front() == "help" ) {
        commandTokens.pop_front();
        returnStatus = cmd_HELP( commandTokens.front() );
    } else if( commandTokens.front() == "health" ) {
        commandTokens.pop_front();
        returnStatus = cmd_HEALTH( commandTokens );
    } else if( commandTokens.front() == "mod" ) {
        commandTokens.pop_front();
        returnStatus = cmd_MODSTAT( commandTokens );
    } else if( commandTokens.front() == "add" ) {
        commandTokens.pop_front();
        returnStatus = cmd_ADDSTAT( commandTokens );
    } else if( commandTokens.front() == "rm" ) {
        commandTokens.pop_front();
        returnStatus = cmd_RMVSTAT( commandTokens.front() );
    } else if( commandTokens.front() == "ld" ) {
        commandTokens.pop_front();
        returnStatus = cmd_LOAD( commandTokens.front() );
    } else if( commandTokens.front() == "st" ) {
        commandTokens.pop_front();
        returnStatus = cmd_STORE( commandTokens.front() );
    } else if( input.find('d') < input.size() ) {
        returnStatus = cmd_ROLL( input );
    } else if( commandTokens.front() == "exit") {
        returnStatus = -1;
    } else if( input == "" ) {
        returnStatus = 0;
    } else {
        std::cout << BOLDRED << "error: " << RESET << RED << "Unknown Command" << RESET << std::endl;
        returnStatus = 1;
    }

    commandTokens.clear();

    return returnStatus;

}


int DnDsh::cmd_ROLL( std::string command ) {

    if( command.length() == 1 ) {
        std::cout << BOLDRED << "error: " << RESET << RED << "Incorrect Command Usage: " << RESET << CYAN << " <total_rolls>d<dice_type>" << RESET << std::endl;
        return 1;
    }


    int rollTimes = 0;
    int rollMod = 1;

    if (command.find('d') == 0) {
        rollTimes = 1;
    } else {
        rollTimes = stoi(command.substr(0, command.find('d')));
    }
    
    rollMod = stoi(command.substr(command.find('d') + 1, command.length()));
    std::cout << CYAN << "Rolled: " << BOLDWHITE << roll(rollTimes, rollMod) << RESET << std::endl;
    
    
    return 0;
}


// Sample Usage:    stats [<key>]           //NOTE: [<key>] entered empty will print out every stat
int DnDsh::cmd_STATS( const std::string &key ) {

    std::string datum;

    for( unsigned int i = 0; i < this->characterData.size(); i++ ) {
        datum = this->characterData.at(i);
        std::cout << BOLDWHITE << datum.substr(0, datum.find('.')) << RESET << CYAN << ":\t" << RESET;
        if( datum.find(':') < datum.size() ) {
            std::cout << BOLDWHITE << datum.substr(datum.find('.') + 1, datum.find(':') - (datum.find('.') + 1)) << RESET 
            << CYAN << "/" << BOLDRED << datum.substr(datum.find(':') + 1, datum.size()) << RESET;
        } else {
            std::cout << BOLDWHITE << datum.substr(datum.find('.') + 1, datum.size()) << RESET;
        }
    
        std::cout << std::endl;
    }

    return 0;
}



// Sample Usage:    help [<command>]    //NOTE: absent [<command>] prints all available commands
int DnDsh::cmd_HELP( const std::string &command ) {
    
    int returnStatus = 0;

    if( command == "" ) {
        std::cout << DNDSH_COMMAND_HELP_LIST << std::endl;
    }

    else if( command == "roll" ) {
        std::cout << DNDSH_ROLL_CMD_HELP << std::endl;
    }
    
    else if( command == "stats" ) {
        std::cout << DNDSH_STATS_CMD_HELP << std::endl;
    }

    else if( command == "spell" ) {
        std::cout << DNDSH_SPELL_CMD_HELP << std::endl;
    }

    else if( command == "health" ) {
        std::cout << DNDSH_HEALTH_CMD_HELP << std::endl;
    }

    else if( command == "mod" ) {
        std::cout << DNDSH_MOD_CMD_HELP << std::endl;
    }

    else if( command == "add" ) {
        std::cout << DNDSH_ADD_CMD_HELP << std::endl;
    }

    else if( command == "rm" ) {
        std::cout << DNDSH_RM_CMD_HELP << std::endl;
    }

    else if( command == "ld" ) {
        std::cout << DNDSH_LD_CMD_HELP << std::endl;
    }
    
    else if( command == "st" ) {
        std::cout << DNDSH_ST_CMD_HELP << std::endl;
    }

    else {
        std::cout << BOLDRED << "error: " << RESET << RED << "Unknown command type \'help\' for a list of commands" << std::endl;
        returnStatus = 1;
    }

    return returnStatus;

}

// Sample Usage:    spell <1-9> [<modifier>]        //NOTE: [<modifier>] is by default assumed as: -1
//                  spell reset all
//                  spell reset <1-9>
//                  spell master <1-9> <modifier>
int DnDsh::cmd_SPELL( std::list<std::string> &level ) {
    std::cout << "Need to implement SPELL" << std::endl;
    return 0;
}



// Sample Usage:    health <modifier>
//                  heatlh reset
//                  heatlh master <modifer>
int DnDsh::cmd_HEALTH( std::list<std::string> &modifyBy ) {
   
    int returnStatus = 0;

    if( this->locateKey( "HEALTH" ) < 0 ) {
        std::cout << CYAN << "Key: " << BOLDWHITE << "HEALTH" << RESET << CYAN 
        << " does not exist." << std::endl 
        << "Please add the key using the \'add\' command" << RESET << std::endl;
        returnStatus = 1;
    } 

    else if( modifyBy.front() == "" ) {
        std::cout << BOLDRED << "error: " << RESET << RED << "Incorrect Usage: "
        "Type \'help health\' to learn more" << RESET << std::endl;
        returnStatus = 1;
    }

    else if( modifyBy.front() == "master" ) {
        modifyBy.pop_front();
        returnStatus = this->modifyRule( "HEALTH", modifyBy.front() );
    }

    else {
        returnStatus = this->modifyRule( "HEALTH", modifyBy.front() );
    }

    return returnStatus;
}



// Sample Usage:    mod <key> <new_value> [<new_temp_value>]    //NOTE: [<new_temp_value>] will by default leave everything unchanged
int DnDsh::cmd_MODSTAT( std::list<std::string> &modifier ) {
    std::cout << "Need to implement MODSTAT" << std::endl;
    return 0;
}



// Sample Usage:    add <new_key> <new_value> [<new_temp_value>]    //NOTE: [<new_temp_value>] will by deafult skip appending a new_temp_value to new_key
int DnDsh::cmd_ADDSTAT( std::list<std::string> &stat ) {
    std::cout << "Need to implement ADDSTAT" << std::endl;
    return 0;
}



// Sample Usage:    rm  <key>
int DnDsh::cmd_RMVSTAT( const std::string &stat ) {
    std::cout << "Need to implement RMVSTAT" << std::endl;
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
        if( this->characterData.at(i).substr(0, characterData.at(i).find('.')) == capKey ) {
            return i;
        }
    }

    return -1;
}


std::string DnDsh::upper( std::string input ) {
    
    for( unsigned int i = 0; i < input.size(); i++ ) {
        input.at(i) = toupper( input.at(i) );
    }

    return input;
}


int DnDsh::modifyRule( std::string key, std::string modifyBy ) {

    int returnStatus = 0;

    int locationOfKey = this->locateKey( key );
    std::string datum = this->characterData.at(locationOfKey);
    int locationOfTempValue = datum.find(':');
    bool tempValueExists = ( locationOfTempValue < datum.size() );
    int maxValue = std::stoi(datum.substr(datum.find('.') + 1, datum.find(':')));
    std::string partDatum;
    int newTempValue;

    if( tempValueExists ) {
        partDatum = datum.substr(0, locationOfTempValue);
        newTempValue = std::stoi(datum.substr(datum.find(':') + 1, datum.size()));
    } else {
        partDatum = datum.substr(0, datum.size());
        newTempValue = std::stoi(datum.substr(datum.find('.') + 1, datum.size()));
    }


    if( (modifyBy.at(0) == '+') && tempValueExists ) {
        newTempValue += std::stoi(modifyBy.substr(1, modifyBy.size())); 
    }

    else if( modifyBy.at(0) == '-' ) {
        newTempValue -= std::stoi(modifyBy.substr(1, modifyBy.size()));
    }

    else if( isdigit(modifyBy.at(0)) ) {
        newTempValue = std::stoi(modifyBy);
    }

    else if( modifyBy == "reset" ) {
        newTempValue = std::stoi(partDatum.substr(partDatum.find('.') + 1, partDatum.size()));
    }

    else {
        std::cout << BOLDRED << "error: " << RESET << RED << "modifier unknown" << RESET << std::endl;
        returnStatus = 1;
    }    

    if( newTempValue < 0 ) { 
        newTempValue = 0;
    } else if( newTempValue > maxValue ) {
        newTempValue = maxValue;
    }

    this->characterData.at(locationOfKey) = partDatum + ":" + std::to_string( newTempValue );        

    return returnStatus;
}






