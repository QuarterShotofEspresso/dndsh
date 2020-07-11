#ifndef __DNDSH_HPP__
#define __DNDSH_HPP__

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <readline/readline.h>
#include "linux_color_schemes.hpp"
#include <sstream>

// data stored as {<stat_key>.<primary_value>[:<secondary_value>]}
// data stored as {"STRENGTH.5", "HEALTH.25:16", "NAME.Tywin", "SAVING:~/dnd/tywin.sd"}
class DnDsh {

    private:
    std::vector<std::string> characterData;


    public:
    DnDsh();
    // initialize and loop command prompter
    int cmd_REQ( std::string input ); // launch terminal

    /////// command sequences///////
    // miscillaneous sequences
    int cmd_ROLL    ( std::string command );
    int cmd_STATS   ( const std::string &key );
    int cmd_HELP    ( const std::string &command );
    // specialized modifier seqeunce(s)
    int cmd_SPELL   ( std::list<std::string> &spellEntry );
    int cmd_HEALTH  ( std::list<std::string> &modifyBy );
    // gerneral modifier seqeunces(s)
    int cmd_MODSTAT ( std::list<std::string> &modifier );
    int cmd_ADDSTAT ( std::list<std::string> &addEntry );
    int cmd_RMVSTAT ( const std::string &stat );

    // json load and store
    int cmd_LOAD  ( const std::string &path );
    int cmd_STORE ( const std::string &path );


    private:
    // helper function(s)
    int roll( int times, int modulus );
    int locateKey( std::string key );
    std::string upper( std::string input );
    // +<modifier> : increase by <modifier>
    // <modifier>  : set value to <modifier>
    // -<modifier> : substract by <modifier>
    // reset       : set <temp_value> to <master_value>
    int modifyRule( std::string key, std::string modifyBy, bool master );
    void printStat( std::string datum );
    std::string format_err( std::string message );
};


constexpr unsigned int dndsh_hash( const char input[] );

#endif //__DNDSH_HPP__
