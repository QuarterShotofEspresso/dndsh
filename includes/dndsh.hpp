#ifndef __DNDSH_HPP__
#define __DNDSH_HPP__

#include <string>
#include <vector>
#include <iostream>
#include <readline/readline.h>
#include "linux_color_schemes.hpp"

// data stored as {<attribute tag>.<attribute value/max>:<attribute temporary/current>}
// data stored as {"STRENGTH.5", "Health.25:16", "nAmE.Tywin"}
class DnDsh {

    private:
    std::vector<std::string> characterData;


    public:
    DnDsh();
    // initialize and loop command prompter
    int cmd_REQ( std::string command ); // launch terminal

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


    private:
    // helper function(s)
    int roll( int times, int modulus );
    std::string valueByKey( std::string key );
    std::string upper( std::string input );
    // +<modifier> : increase by <modifier>
    // <modifier>  : set value to <modifier>
    // -<modifier> : substract by <modifier>
    int modifyRule( std::string modifyBy );
};

#endif //__DNDSH_HPP__
