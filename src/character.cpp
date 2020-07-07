#include "character.hpp"
#include <iostream>


CharacterData() { }


std::string CharacterData::valueByKey( std::string key ) {
    
    std::vector<std::string>::iterator ptr;

    for( ptr = this->data.begin(); ptr < this->data.end(); ptr++ ) {
        if( upper(*ptr.substr(0, *ptr.find('.'))) == upper(key) ) {
            return *ptr.substr(*ptr.find('.') + 1, *ptr.size());
        }
    }

    return "";
}




void Character::prompt( void ) {
    
    srand((int)time(NULL));

    do {

        std::string command;

        std::cout << "$> ";
        std::cin  >> command;

        if( command.find('d') > -1 ) {
            cmd_ROLL( command );
        } else if( command == "spell" ) {
            std::cin >> command;
            cmd_SPELL( command );
        } else {
            std::cout << "ERR: Unknown Command" << std::endl;
        }

    } while( command != "exit" );

    std::cout << "Save Character? [Y/n] ";
    std::cin  >> command;
    if( command.upper() == "Y" ) {
        std::cout << "Saving Character..." << std::endl;
        // TODO: Implement cmd_STORE
        std::cout << "Character Saved." << std::endl;
    }

    std::cout << "Exiting dndterm..." << std::endl;

}


int Character::cmd_ROLL( std::string command ) {

    if (command.length() == 0) {
        std::cout << "Command Incorrect Usage:\n<Total Rolls>d<Dice Type>\n$> ";
        return 1;
    }
    
    if (rollString == "exit") {
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
    std::cout << "Need to implement" << std::endl;
    return 0;
}


int Character::cmd_HELP( void ) {
    std::cout << "Need to implement" << std::endl;
    return 0;
}


int Character::cmd_SPELL( void ) {
    std::cout << "Need to implement" << std::endl;
    return 0;
}


int Character::cmd_HEALTH( void ) {
    std::cout << "Need to implement" << std::endl;
    return 0;
}


int Character::cmd_MODSTAT( void ) {
    std::cout << "Need to implement" << std::endl;
    return 0;
}


int Character::cmd_ADDSTAT( void ) {
    std::cout << "Need to implement" << std::endl;
    return 0;
}


int Character::cmd_RMVSTAT( void ) {
    std::cout << "Need to implement" << std::endl;
    return 0;
}


////// Helper Functions //////
int roll(int times, int modulus) {

    int sum = 0;

    for (int i = 0; i < times; i++) {
        sum += rand() % modulus;
    }

    return sum + 1;
}


std::string upper( std::string input ) {
    
    for( int i = 0; i < input.size(); i++ ) {
        input.at(i) = toupper( input.at(i) );
    }

    return input;
}
