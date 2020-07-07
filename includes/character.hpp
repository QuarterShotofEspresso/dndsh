#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <string>
#include <vector>


class CharacterData {
    private:
    std::vector<std::string> data;

    public:
    CharacterData();
    std::string valueByKey( std::string key );

};

// data stored as {<attribute tag>.<attribute value/max>.<attribute temporary/current>}
// data stored as {"STRENGTH.5", "Health.25:16", "nAmE.Tywin"}
class Character {
    private:
    CharacterData *data;

    public:
    // initialize and loop command prompter
    void prompt( void ); // launch terminal


    /////// command sequences///////
    // miscillaneous sequences
    int cmd_ROLL    ( std::string command );
    int cmd_STATS   ( void );
    int cmd_HELP    ( void );
    // specialized modifier seqeunce(s)
    int cmd_SPELL   ( int spellLevel );
    int cmd_HEALTH  ( void );
    // gerneral modifier seqeunces(s)
    int cmd_MODSTAT ( void );
    int cmd_ADDSTAT ( void );
    int cmd_RMVSTAT ( void );

    // json load and store
    int cmd_LOAD  ( std::string path );
    int cmd_STORE ( std::string path );

    // helper functions
    friend int roll( int times, int modulus );
    friend std::string upper( std::string input );
};


#endif //__CHARACTER_HPP__
