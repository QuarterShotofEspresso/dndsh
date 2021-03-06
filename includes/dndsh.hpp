#ifndef __DNDSH_HPP__
#define __DNDSH_HPP__

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "linux_color_schemes.hpp"

// data stored as {<stat_key>.<primary_value>[:<secondary_value>]}
// data stored as {"STRENGTH.5", "HEALTH.25:16", "NAME.Tywin", "SAVING:~/dnd/tywin.sd"}
class DnDsh {

    private:
    std::vector<std::string> characterData;


    public:
    DnDsh() { }
    // initialize and loop command prompter
    int parse( std::string input ); // launch terminal

    /////// command sequences///////
    // miscillaneous
    int cmd_ROLL    ( const std::string &command );
    int cmd_HELP    ( const std::string &command );
    // special modifier
    int cmd_SPELL   ( std::list<std::string> &spellEntry );
    int cmd_HEALTH  ( std::list<std::string> &modifyBy );
    // gerneral modifier
    int cmd_MODSTAT ( std::list<std::string> &modifier );
    // speical modifier
    int cmd_ADDSTAT ( std::list<std::string> &addEntry );
    int cmd_RMVSTAT ( const std::string &stat );
    // visualizer commands
    int cmd_LIST    ( const std::string &key );
    // load and store
    int cmd_LOAD  ( const std::string &path );
    int cmd_STORE ( const std::string &path );


    private:
    // helper function(s)
    int roll( int times, int modulus );
    int locateKey( const std::string &key );
    std::string upper( std::string input );
    // +<modifier> : increase by <modifier>
    // <modifier>  : set value to <modifier>
    // -<modifier> : substract by <modifier>
    // reset       : set <temp_value> to <master_value>
    int modifyRule( const std::string &key, const std::string &modifyBy, bool master );
    std::string formatStat( const std::string &datum );
    std::string formatErr( const std::string &message );
};


#endif //__DNDSH_HPP__
