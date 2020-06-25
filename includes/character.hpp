#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <string>
#include <list>

struct Spell {
    int spellLevel;
    int currentSpellSlots;
    int maxSpellSlots;
};


struct HitPoints {
    int maxHitPoints;
    int currentHitPoints;
};

struct Stats {
    int Strength;
    int Dexterity;
    int Constitution;
    int Intelligence;
    int Wisdom;
    int Charisma;
};

struct Dictionary {
    std::string key;
    std::string value;
};

struct BasicStats {
    int 

class Character {

    private:
        std::string name;
        struct HitPoints myHP;
        list<struct Spell> mySpells; 

    public:
        Character();
        roll();
        

};

#endif //__CHARACTER_HPP__
