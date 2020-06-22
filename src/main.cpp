#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>

std::string toString(char *characterString, int length) {
    
    std::string stringString = "";

    for (int i = 0; i < length; i++) {
        stringString += characterString[i];
    }

    return stringString;
}


int roll(int times, int modulus) {

    int sum = 0;

    for (int i = 0; i < times; i++) {
        sum += rand() % modulus;
    }

    return sum;
}



int main(int argc, char **argv) {

    srand((int)time(NULL));

    int rollStringLen = sizeof(argv) / sizeof(char);
    std::string rollString = toString(argv[1], rollStringLen);
    int rollTimes = 0;
    int rollMod = 1;

    if (rollString.find('d') == 0) {
        rollTimes = 1; 
    }
    else {
        rollTimes = stoi(rollString.substr(0, rollString.find('d')));
    }
    
    rollMod = stoi(rollString.substr(rollString.find('d') + 1, rollString.length()));
    std::cout << "Rolled: " << roll(rollTimes, rollMod) << std::endl;

    return 0;
}
