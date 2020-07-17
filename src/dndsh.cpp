#include "dndsh.hpp"
#include "help_messages.hpp"
#include "error_messages.hpp"
#include <fstream>


// setting color schemes
#define PRIMARY_COLOR RESET << BOLDWHITE
#define SECONDARY_COLOR RESET << CYAN
#define TERTIARY_COLOR RESET << BOLDRED


// sample constructor for debugging
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


int DnDsh::cmd_ROLL( const std::string &command ) {

    if( command == "d" ) {
        std::cout << this->formatErr( UNKNOWN_COMMAND_ERR );
        return 1;
    }
    
    else if( command.find('d') < command.size() ) {

        int locationOfd = command.find('d');

        for( int i = 0; i < locationOfd; i++ ) {
            if( !isdigit(command.at(i)) ) {
                std::cout << this->formatErr( UNKNOWN_COMMAND_ERR );
                return 1;
            }
        }

        for( unsigned int i = (locationOfd + 1); i < command.size(); i++ ) {
            if( !isdigit(command.at(i)) ) {
                std::cout << this->formatErr( UNKNOWN_COMMAND_ERR );
                return 1;
            }
        }

        int rollTimes = 0;
        int rollMod = 1;

        rollTimes = (command.find('d') == 0) ? 1 : stoi(command.substr(0, command.find('d')));
        rollMod = stoi(command.substr(command.find('d') + 1, command.length()));

        std::cout << SECONDARY_COLOR << "rolled: " << PRIMARY_COLOR << roll(rollTimes, rollMod) << RESET << std::endl;
    }

    else if( command.empty() ) {
        return 0;
    }

   else {
        std::cout << this->formatErr( UNKNOWN_COMMAND_ERR );
        return 1;
    }
 
    return 0;
}


// Sample Usage:    stat [<key>]           //NOTE: [<key>] entered empty will print out every stat
int DnDsh::cmd_STATS( const std::string &key ) {

    if( key.empty() ) {
        for( unsigned int i = 0; i < this->characterData.size(); i++ ) {
            std::cout << this->formatStat(this->characterData.at(i));
        }
    }

    else {
        unsigned int locationOfKey = this->locateKey( key );
        if ( locationOfKey < this->characterData.size() ) {
            this->formatStat( this->characterData.at( locationOfKey ) );
        }

        else {
            std::cout << this->formatErr( KEY_NOT_FOUND_ERR ); 
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
    } else if( command == "modifier" ) {
        std::cout << DNDSH_MODIFIER_HELP << std::endl;
    } else {
        std::cout << this->formatErr( UNKNOWN_COMMAND_ERR );
        return 1;
    }

    return 0;
}



// Sample Usage:    spell {<spell_level>|all} [<modifier>]        //NOTE: [<modifier>] is by default assumed as: -1
//                  spell master {<spell_level>|all} [<modifier>]
int DnDsh::cmd_SPELL( std::list<std::string> &spellEntry ) {

    std::string level = spellEntry.front();
    spellEntry.pop_front();  

    if( level.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(spell) );
        return 1;
    }

    bool master = false;
    int locationOfKey;

    if( level == "master" ) {
        master = true;
        level = spellEntry.front();
        spellEntry.pop_front();
    }


    if( isdigit(level.at(0)) ) {
        
        level = "SS" + level;
        locationOfKey = this->locateKey( level );

        if( locationOfKey < 0 ) {
            this->formatErr( KEY_NOT_FOUND_ERR );
            return 1;
        }

        else {
            std::string modifier = spellEntry.front();
            spellEntry.pop_front();
            return this->modifyRule( level, modifier, master );
        }
    }

    else if( level == "all" ) {
        std::string modifier = spellEntry.front();
        spellEntry.pop_front();
        if( modifier.empty() ) {
            modifier = "-1";
        }

        for( int i = 1; i < 10; i++ ) {
            locationOfKey = this->locateKey( "SS" + std::to_string(i) );
            if ( locationOfKey < 0 ) {
                std::cout << "spell slot " << i << " does not exist. stopping..." << std::endl;
                return 0;
            } else {
                if( this->modifyRule( "SS" + std::to_string(i), modifier, master ) ) return 1;
            }
        }
    }

    else {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(spell) );
    }

    return 0;
}



// Sample Usage:    health <modifier>
//                  health master <modifier>
int DnDsh::cmd_HEALTH( std::list<std::string> &healthEntry ) {
   
    // check if health key exists 
    if( this->locateKey( "HEALTH" ) < 0 ) {
        std::cout << this->formatErr( KEY_NOT_FOUND_ERR );
        return 1;
    }

    std::string modifier = healthEntry.front();
    healthEntry.pop_front(); 

    bool master = false;

    // check if master flag has been set
    if( modifier == "master" ) {
        master = true;
        modifier = healthEntry.front();
        healthEntry.pop_front();
    }

    // check that argument exists
    if( modifier.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(heal) );
        return 1;
    }

    // modify health stat by modifier
    return this->modifyRule( "HEALTH", modifier, master );

}



// Sample Usage:    mod <stat> <primary_value> [<secondary_value>]    //NOTE: [<secondary_value>] will by default delete <secondary_value> if it exists
int DnDsh::cmd_MODSTAT( std::list<std::string> &modEntry ) {

    if( modEntry.front() == "" ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(mod) );
        return 1;
    }

    std::string stat = this->upper( modEntry.front() );
    modEntry.pop_front();

    int locationOfKey = this->locateKey( stat );
    if( locationOfKey < 0 ) {
        std::cout << this->formatErr( KEY_NOT_FOUND_ERR );
        return 1;
    }

    if( modEntry.front() == "" ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(mod) );
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



// Sample Usage:    add <new_key> <new_value> [<new_ancillary_value>]    //NOTE: [<new_ancillary_value>] will by default skip appending a new_ancillary_value to new_key
int DnDsh::cmd_ADDSTAT( std::list<std::string> &addEntry ) {

    std::string newKey = addEntry.front();
    addEntry.pop_front();

    if( newKey.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(add) );
        return 1;
    }

    newKey = this->upper( newKey );
    std::string newMasterValue = addEntry.front();
    addEntry.pop_front();

    if( newMasterValue.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(add) );
        return 1;
    }

    std::string newAncillaryValue = addEntry.front();
    addEntry.pop_front();

    std::string newStat = newKey + "." + newMasterValue;
    if( newAncillaryValue.empty() ) {
        newStat += ":" + newAncillaryValue;
    }

    // std::cout << "Added: " << newStat << std::endl; // dbg

    this->characterData.push_back( newStat );

    return 0;
}



// Sample Usage:    rm  <key>
int DnDsh::cmd_RMVSTAT( const std::string &stat ) {
    
    if( stat.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(remove) );
        return 1;
    }

    int locationOfKey = this->locateKey( stat );
    if ( locationOfKey < 0 ) {
        std::cout << this->formatErr( KEY_NOT_FOUND_ERR );
        return 1;
    }

    else {
        this->characterData.erase( characterData.begin() + locationOfKey );
    }

    return 0;
}



// Sample Usage:   ld <file_path>
int DnDsh::cmd_LOAD( const std::string &path ) {

    if( path.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(load) );
        return 1;
    }


    std::ifstream file( path );

    if( !file.is_open() ) {
        std::cout << this->formatErr( FILE_ACCESS_FAIL_ERR );
        return 1;
    }


    this->characterData.clear();
    std::string inputDatum;
    while( file >> inputDatum ) {
        if( inputDatum != "" ) {
            this->characterData.push_back(inputDatum);
        }
    }

    file.close();
    
    std::cout << "Successfully loaded data from: " << path << std::endl;

    return 0;
}



// Sample Usage:    st <file_path>
int DnDsh::cmd_STORE( const std::string &path ) {
    
    if( path.empty() ) {
        std::cout << this->formatErr( INCORRECT_USAGE_ERR(store) );
        return 1;
    }

    std::ofstream file;
    file.open( path );
 
    if( !file.is_open() ) {
        std::cout << this->formatErr( FILE_ACCESS_FAIL_ERR );
        return 1;
    }

    for( std::string outputDatum : this->characterData ) {
        file << outputDatum << std::endl;
    }

    file.close();

    std::cout << "Successfully stored data to: " << path << std::endl;

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


int DnDsh::locateKey( const std::string &key ) {
    
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


int DnDsh::modifyRule( const std::string &key, const std::string &modifyBy, bool master ) {

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
        masterValue = std::stoi(datum.substr(datum.find('.') + 1, datum.size() - datum.find('.') - 1));
        ancillaryValue = masterValue;
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
            std::cout << this->formatErr( "modifier rule: cannot reset master value" );
            return 1;
        }

        ancillaryValue = masterValue;
    }

    else {
        for( char i : modifyBy ) {
            if( !isdigit(i) ) {
                std::cout << this->formatErr( "modifier rule: unknown modifier" );
                return 1;
            }
        }

        valueToAdjust = std::stoi(modifyBy);
    }


    // adjust ancillary value and master value to respected bounds
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


std::string DnDsh::formatStat( const std::string &datum ) {

    unsigned int locationOfTempValue = datum.find(':');
    bool ancillaryValueExists = ( locationOfTempValue < datum.size() );

    std::string stat = datum.substr(0, datum.find('.'));
    std::string masterValue;
    std::string ancillaryValue;


    // load variables with default master and ancillary values
    if( ancillaryValueExists ) {
        masterValue = datum.substr(datum.find('.') + 1, locationOfTempValue - datum.find('.') - 1);
        ancillaryValue = datum.substr(locationOfTempValue + 1, datum.size() - locationOfTempValue);
    } else {
        masterValue = datum.substr(datum.find('.') + 1, datum.size() - datum.find('.') - 1);
        ancillaryValue = "";
    }
 

    // if masterValue is a path, find and load content from path to document
    bool masterValueIsFile = masterValue.find(".csv") < datum.size();
    if( masterValueIsFile ) {
        masterValue.clear();
        std::ifstream file( masterValue );
        std::string fileContent;
        while( getline(file, fileContent) ) {
            masterValue += "\n" + fileContent;
        }
    }


    // print content
    std::ostringstream formatStream;
    formatStream << PRIMARY_COLOR << stat << SECONDARY_COLOR << ": " << RESET;

    if( ancillaryValueExists ) {
        formatStream << PRIMARY_COLOR << masterValue << SECONDARY_COLOR << "(" << TERTIARY_COLOR << ancillaryValue << SECONDARY_COLOR << ")" << RESET;
    } else {
        formatStream << PRIMARY_COLOR << masterValue << RESET;
    }

    formatStream << std::endl;

    return formatStream.str();
}



std::string DnDsh::formatErr( const std::string &message ) {

    std::ostringstream formatStream;
    std::string formattedString;

    formatStream << BOLDRED << "error: " << RESET << RED << message << RESET << std::endl;
    formattedString = formatStream.str();

    return formattedString;
}





