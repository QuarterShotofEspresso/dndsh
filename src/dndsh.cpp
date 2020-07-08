#include "dndsh.hpp"

DnDsh::DnDsh() {
    this->characterData = {
        "NAME.Tywin",
        "STRENGTH.15:10",
        "HEALTH.25:10",
        "DEXTERITY.10"
    };
}

int DnDsh::cmd_REQ( std::string command ) {
    
    int returnStatus = 0;

    // command options
    if( command == "spell" ) {
        returnStatus = cmd_SPELL( command );
    } else if( command == "stats" ) {
        returnStatus = cmd_STATS();
    } else if( command == "help" ) {
        returnStatus = cmd_HELP();
    } else if( command == "health" ) {
        returnStatus = cmd_HEALTH( command );
    } else if( command == "mod" ) {
        returnStatus = cmd_MODSTAT( command );
    } else if( command == "add" ) {
        returnStatus = cmd_ADDSTAT( command );
    } else if( command == "remove" ) {
        returnStatus = cmd_RMVSTAT( command );
    } else if( command == "load" ) {
        returnStatus = cmd_RMVSTAT( command );
    } else if( command == "store" ) {
        returnStatus = cmd_RMVSTAT( command );
    } else if( command.find('d') < command.size() ) {
        returnStatus = cmd_ROLL( command );
    } else if( command == "exit") {
        returnStatus = -1;
    } else {
        std::cout << BOLDRED << "error: " << RESET << RED << "Unknown Command" << RESET << std::endl;
        returnStatus = 1;
    }

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


int DnDsh::cmd_STATS( void ) {

    std::string datum;

    for( unsigned int i = 0; i < this->characterData.size(); i++ ) {
        datum = this->characterData.at(i);
        std::cout << BOLDWHITE << datum.substr(0, datum.find('.')) << RESET << CYAN << ": " << RESET;
        if( datum.find(':') < datum.size() ) {
            std::cout << CYAN << "Max: " << BOLDWHITE << datum.substr(datum.find('.') + 1, datum.find(':') - (datum.find('.') + 1)) << RESET << CYAN << " | ";
            std::cout << "Current: " << BOLDWHITE << datum.substr(datum.find(':') + 1, datum.size()) << RESET;
        } else {
            std::cout << BOLDWHITE << datum.substr(datum.find('.') + 1, datum.size()) << RESET;
        }
    
        std::cout << std::endl;
    }

    return 0;
}


int DnDsh::cmd_HELP( void ) {
    std::cout << "Need to implement HELP" << std::endl;
    return 0;
}


int DnDsh::cmd_SPELL( std::string level ) {
    std::cout << "Need to implement SPELL" << std::endl;
    return 0;
}


int DnDsh::cmd_HEALTH( std::string modifyBy ) {
    std::cout << "Need to implement HEALTH" << std::endl;
    return 0;
}


int DnDsh::cmd_MODSTAT( std::string modifier ) {
    std::cout << "Need to implement MODSTAT" << std::endl;
    return 0;
}


int DnDsh::cmd_ADDSTAT( std::string stat ) {
    std::cout << "Need to implement ADDSTAT" << std::endl;
    return 0;
}


int DnDsh::cmd_RMVSTAT( std::string stat ) {
    std::cout << "Need to implement RMVSTAT" << std::endl;
    return 0;
}


int DnDsh::cmd_LOAD( std::string path ) {
    std::cout << "Need to implement LOAD" << std::endl;
    return 0;
}


int DnDsh::cmd_STORE( std::string path ) {
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


std::string DnDsh::valueByKey( std::string key ) {
    
    std::vector<std::string>::iterator ptr;

    for( ptr = this->characterData.begin(); ptr < this->characterData.end(); ptr++ ) {
        if( upper((*ptr).substr(0, (*ptr).find('.'))) == upper(key) ) {
            return (*ptr).substr((*ptr).find('.') + 1, (*ptr).size());
        }
    }

    return "";
}


std::string DnDsh::upper( std::string input ) {
    
    for( unsigned int i = 0; i < input.size(); i++ ) {
        input.at(i) = toupper( input.at(i) );
    }

    return input;
}


int DnDsh::modifyRule( std::string modifyBy ) {
    if( modifyBy.at(0) == '+' ) {
        //TODO: Increase By
    } else if( modifyBy.at(0) == '-' ) {
        //TODO: Decrease By
    } else {
        //TODO: Set To
    }

    return 0;
}
