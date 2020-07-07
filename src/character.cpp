#include "character.hpp"
#include "linux_color_schemes.hpp"
#include <readline/readline.h>
#include <readline/history.h>

void Character::prompt( void ) {
    
    srand((int)time(NULL));
 
    std::string command;
    int returnStatus = 0;

    while( true ) {

        if ( returnStatus ) {
            command = readline( "\033[31m$> \033[0m" );
        } else {
            command = readline( "\033[32m$> \033[0m" );
        }


        // command options
        if( command == "spell" ) {
            std::cin >> command;
            returnStatus = cmd_SPELL( command );
        } else if( command == "stats" ) {
            returnStatus = cmd_STATS();
        } else if( command == "help" ) {
            returnStatus = cmd_HELP();
        } else if( command == "health" ) {
            std::cin >> command;
            returnStatus = cmd_HEALTH( command );
        } else if( command == "mod" ) {
            getline( std::cin, command );
            returnStatus = cmd_MODSTAT( command );
        } else if( command == "add" ) {
            getline( std::cin, command );
            returnStatus = cmd_ADDSTAT( command );
        } else if( command == "remove" ) {
            std::cin >> command;
            returnStatus = cmd_RMVSTAT( command );
        } else if( command == "load" ) {
            std::cin >> command;
            returnStatus = cmd_RMVSTAT( command );
        } else if( command == "store" ) {
            std::cin >> command;
            returnStatus = cmd_RMVSTAT( command );
        } else if( command.find('d') < command.size() ) {
            returnStatus = cmd_ROLL( command );
        } else if( command == "exit") {
            break;
        } else {
            std::cout << BOLDRED << "error: " << RESET << RED << "Unknown Command" << RESET << std::endl;
            returnStatus = 1;
        }

    }

    std::cout << "Save Character? [Y/n] ";
    std::cin  >> command;
    if((command == "Y") || (command == "y")) {
        std::cout << "Path to existing file or create new file: ";
        std::cin >> command;
        std::cout << "Saving Character..." << std::endl;
        cmd_STORE( command );
        std::cout << "Character Saved." << std::endl;
    }

    std::cout << "Exiting dndterm..." << std::endl;

}


int Character::cmd_ROLL( std::string command ) {

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
    std::cout << MAGENTA << "Rolled: " << BOLDWHITE << roll(rollTimes, rollMod) << RESET << std::endl;
    
    
    return 0;
}


int Character::cmd_STATS( void ) {
    std::cout << "Need to implement STATS" << std::endl;
    return 0;
}


int Character::cmd_HELP( void ) {
    std::cout << "Need to implement HELP" << std::endl;
    return 0;
}


int Character::cmd_SPELL( std::string level ) {
    std::cout << "Need to implement SPELL" << std::endl;
    return 0;
}


int Character::cmd_HEALTH( std::string modifyBy ) {
    std::cout << "Need to implement HEALTH" << std::endl;
    return 0;
}


int Character::cmd_MODSTAT( std::string modifier ) {
    std::cout << "Need to implement MODSTAT" << std::endl;
    return 0;
}


int Character::cmd_ADDSTAT( std::string stat ) {
    std::cout << "Need to implement ADDSTAT" << std::endl;
    return 0;
}


int Character::cmd_RMVSTAT( std::string stat ) {
    std::cout << "Need to implement RMVSTAT" << std::endl;
    return 0;
}


int Character::cmd_LOAD( std::string path ) {
    std::cout << "Need to implement LOAD" << std::endl;
    return 0;
}


int Character::cmd_STORE( std::string path ) {
    std::cout << "Need to implement STORE" << std::endl;
    return 0;
}

////// Helper Functions //////
int Character::roll(int times, int modulus) {

    int sum = 0;

    for (int i = 0; i < times; i++) {
        sum += rand() % modulus;
    }

    return sum + 1;
}


std::string Character::valueByKey( std::string key ) {
    
    std::vector<std::string>::iterator ptr;

    for( ptr = this->data.begin(); ptr < this->data.end(); ptr++ ) {
        if( upper((*ptr).substr(0, (*ptr).find('.'))) == upper(key) ) {
            return (*ptr).substr((*ptr).find('.') + 1, (*ptr).size());
        }
    }

    return "";
}


std::string Character::upper( std::string input ) {
    
    for( int i = 0; i < input.size(); i++ ) {
        input.at(i) = toupper( input.at(i) );
    }

    return input;
}


int Character::modifyRule( std::string modifyBy ) {
    if( modifyBy.at(0) == '+' ) {
        //TODO: Increase By
    } else if( modifyBy.at(0) == '-' ) {
        //TODO: Decrease By
    } else {
        //TODO: Set To
    }

    return 0;
}
