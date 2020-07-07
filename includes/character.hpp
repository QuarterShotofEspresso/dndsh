#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <string>
#include <vector>

/*
class CharacterData {
    private:
    std::vector<std::string> data;

    public:
    CharacterData();
    std::string valueByKey( std::string key );

};*/

// data stored as {<attribute tag>.<attribute value/max>:<attribute temporary/current>}
// data stored as {"STRENGTH.5", "Health.25:16", "nAmE.Tywin"}
class Character {
    private:
    std::vector<std::string> data;

    public:
    // initialize and loop command prompter
    void prompt( void ); // launch terminal


    /////// command sequences///////
    // miscillaneous sequences
    int cmd_ROLL    ( std::string command );
    int cmd_STATS   ( void );
    int cmd_HELP    ( void );
    // specialized modifier seqeunce(s)
    int cmd_SPELL   ( std::string level );
    int cmd_HEALTH  ( std::string modifyBy );
    // gerneral modifier seqeunces(s)
    int cmd_MODSTAT ( std::string modifier );
    int cmd_ADDSTAT ( std::string stat );
    int cmd_RMVSTAT ( std::string stat );

    // json load and store
    int cmd_LOAD  ( std::string path );
    int cmd_STORE ( std::string path );

    // helper function(s)
    friend int roll( int times, int modulus );
    friend int valueByKey( std::string key );
    friend std::string upper( std::string input );
    // +<modifier> : increase by <modifier>
    // <modifier>  : set value to <modifier>
    // -<modifier> : substract by <modifier>
    friend int modifyRule( std::string modifyBy );
};

// global helper function(s)


#endif //__CHARACTER_HPP__
