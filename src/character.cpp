#include "character.hpp"

void Character::prompt( void ) {
    
    srand((int)time(NULL));
 
    std::string command;

    while( true ) {


        std::cout << "$> ";
        std::cin  >> command;

        // debugging Statment
        //std::cout << command.find('d') << std::endl;

        // command options
        if( command == "spell" ) {
            std::cin >> command;
            cmd_SPELL( command );
        } else if( command == "stats" ) {
            cmd_STATS();
        } else if( command == "help" ) {
            cmd_HELP();
        } else if( command == "health" ) {
            std::cin >> command;
            cmd_HEALTH( command );
        } else if( command == "mod" ) {
            getline( std::cin, command );
            cmd_MODSTAT( command );
        } else if( command == "add" ) {
            getline( std::cin, command );
            cmd_ADDSTAT( command );
        } else if( command == "remove" ) {
            std::cin >> command;
            cmd_RMVSTAT( command );
        } else if( command == "load" ) {
            std::cin >> command;
            cmd_RMVSTAT( command );
        } else if( command == "store" ) {
            std::cin >> command;
            cmd_RMVSTAT( command );
        } else if( command.find('d') < command.size() ) {
            cmd_ROLL( command );
        } else if( command == "exit") {
            break;
        } else {
            std::cout << "ERR: Unknown Command" << std::endl;
        }

    }

    std::cout << "Save Character? [Y/n] ";
    std::cin  >> command;
    if((command == "Y") || (command == "y")) {
        std::cout << "Path to existing file or create new file: " << std::endl;
        std::cin >> command;
        std::cout << "Saving Character..." << std::endl;
        cmd_STORE( command );
        std::cout << "Character Saved." << std::endl;
    }

    std::cout << "Exiting dndterm..." << std::endl;

}


int Character::cmd_ROLL( std::string command ) {

    if( command.length() == 0 ) {
        std::cout << "Command Incorrect Usage:\n<Total Rolls>d<Dice Type>" << std::endl;
        return 1;
    }
    
    if( command == "exit" ) {
        std::cout << "Exiting command sequence: ROLL" << std::endl;
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
    std::cout << "Rolled: " << roll(rollTimes, rollMod) << std::endl;
    
    
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
