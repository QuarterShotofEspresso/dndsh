#include "dndsh.hpp"
#include <readline/readline.h>


int main( void ) {

    srand((int)time(NULL));

    DnDsh newShell;
    std::string command;
    int returnStatus = 0;


    while( returnStatus >= 0 ) {

        if ( returnStatus == 1 ) {
            command = readline( "\033[31m$> \033[0m" );
        } else {
            command = readline( "\033[32m$> \033[0m" );
        }

        returnStatus = newShell.parse( command );

    }

    std::cout << "Save Character? [Y/n] " << BOLDYELLOW;
    std::cin  >> command;
    if((command == "Y") || (command == "y")) {
        std::cout << RESET << "Path to existing file or create new file: " << BOLDYELLOW;
        std::cin >> command;
        std::cout << RESET << "Saving Character..." << std::endl;
        newShell.cmd_STORE( command );
        std::cout << "Character Saved." << std::endl;
    }

    std::cout << RESET << "Exiting dndterm..." << std::endl;

    return 0;
}

