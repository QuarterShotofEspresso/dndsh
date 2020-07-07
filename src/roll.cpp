#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>

struct Multi_Dict {

    void *key;
    void *value;

};

int roll(int times, int modulus) {

    int sum = 0;

    for (int i = 0; i < times; i++) {
        sum += rand() % modulus;
    }

    return sum + 1;
}

int commandEntry( std::string command ) {
    int exitCode = 1;

    switch( command ) {
        case "exit":
            exitCode = 0;
            break;

        case ""


void command() {

    std::string command;
    int noExit;

    while( noExit ) {
        std::cin >> command;
        noExit = commandEntry( command );
    }

}

int main (void) {
    
    srand((int)time(NULL));

    std::string rollString;
    int rollTimes = 0;
    int rollMod = 1;
    int rollStringLen = 0;
    
    while (true) {

        do {
            std::cin >> rollString;
        } while (rollString.length() == 0);

        if (rollString == "exit") {
            break;
        }

        rollStringLen = rollString.length();
    
        if (rollString.find('d') == 0) {
            rollTimes = 1; 
        } else {
            rollTimes = stoi(rollString.substr(0, rollString.find('d')));
        }
    
        rollMod = stoi(rollString.substr(rollString.find('d') + 1, rollString.length()));
        std::cout << "Rolled: " << roll(rollTimes, rollMod) << std::endl;
    }
    
    return 0;
}
