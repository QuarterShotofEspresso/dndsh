#ifndef __DNDSH_HELP_MESSAGES__
#define __DNDSH_HELP_MESSAGES__

#define DNDSH_COMMAND_HELP_LIST     "Command List:\n"\
                                    "d<dice_type> (roll):   rolls a dice of type <dice_type>\n"\
                                    "ls/l:                  list all stats or specific stat\n"\
                                    "spell/sp:              modify available spell slots\n"\
                                    "health/hp:             modify master hp and/or current hp\n"\
                                    "mod:                   modify a stat\n"\
                                    "add:                   create a new stat\n"\
                                    "remove/rm:             delete a stat\n"\
                                    "load/ld:               load stats in xml file\n"\
                                    "store/st:              store stats in xml file\n"\
                                    "type \'help <command>\' for more information\n\n"\
                                    "Specialized Details:\n"\
                                    "modifier:              input that adjusts values of existing stats\n"\
                                    "type \'help modifier\' for more information on modifiers"


#define DNDSH_ROLL_CMD_HELP         "Sample Usage:\t[<roll_times>]d<dice_type>\n"\
                                    "Description:\n"\
                                    "Rolls a dice of type <dice_type> a total of [<roll_times>] times\n"\
                                    "NOTE:\t[<roll_times>] left empty assumes 1"


#define DNDSH_STATS_CMD_HELP        "Sample Usage:\tls [<stat>]\n"\
                                    "Description:\n"\
                                    "Stats will be listed as <stat>: <master_value>. If a stat has a ancillary value, the stat\n"\
                                    "will be displayed as <stat>: <ancillary_value>/<master_value>. Where <ancillary_value> will\n"\
                                    "have a unique color distinction.\n"\
                                    "NOTE:\t[<stat>] left empty will print out every stat"


#define DNDSH_SPELL_CMD_HELP        "Sample Usage:\tspell {<spell_level>|all} [<modifier>]\n"\
                                    "\t\tspell master {<spell_level>|all} <modifier>\n"\
                                    "Description:\n"\
                                    "Spell will adjust <ancillary_value> of <spell_level> according to <modifier>.\n"\
                                    "If <ancillary_value> does not exist, spell will create one and adjust it according\n"\
                                    "to <modifier>. After a rest, spell slot\'s <ancillary_value> can be\n"\
                                    "set to their <master_value> by providing the reset option. The <master_value> of a\n"\
                                    "spell slot can be adjusted by providing the master option\n"\
                                    "IMPORTANT:\tSpell slots must have the following stat format in order for spell\n"\
                                    "\t\tto locate them: SS<spell_level>. For instance, creating a new spell slot in level 4\n"\
                                    "\t\twill look like: \'add SS4 1\'.\n"\
                                    "NOTE:\t[<modifier>] left empty assumes -1.\n"\
                                    "NOTE:\t[<spell_level>] left empty assumes all"


#define DNDSH_HEALTH_CMD_HELP       "Sample Usage:\thealth <modifier>\n"\
                                    "\t\thealth master <modifier>\n"\
                                    "Description:\n"\
                                    "Health will adjust <ancillary_value> according to <modifier>. If <ancillary_value>\n"\
                                    "does not exist, health will create one and adjust it according to <modifier>. The reset\n"\
                                    "option operates on <ancillary_value> only and sets it equal to <master_value>.\n"\
                                    "To adjust <master_value> the \'master\' option must be provided before <modifier>."


#define DNDSH_MOD_CMD_HELP          "Sample Usage:\tmod <key> <master_value> [<new_ancillary_value>]\n"\
                                    "NOTE:\t[<new_ancillary_value>] will by default leave everything unchanged."

#define DNDSH_ADD_CMD_HELP          "Sample Usage:\tadd <new_key> <master_value> [<new_ancillary_value>]\n"\
                                    "NOTE:\t[<new_ancillary_value>] will, by default, append nothing to <new_key> after <master_value>."

#define DNDSH_RM_CMD_HELP           "Sample Usage:\tremove <key>\n"\
                                    "Description:\n"\
                                    "Remove deletes character stat identified by <key>."

#define DNDSH_LD_CMD_HELP           "Sample Usage:\tload <file_path>\n"\
                                    "NOTE:\t<file_path> must be in the working directory, otherwise the absolute path must be provided."

#define DNDSH_ST_CMD_HELP           "Sample Usage:\tst <file_path>\n"\
                                    "NOTE:\t<file_path> must be in the working directory, otherwise the absolute path must be provided."

#define DNDSH_MODIFIER_HELP         "Format:\t+<modifier> : increase by <modifier>\n"\
                                    "\t<modifier>  : set value to <modifier>\n"\
                                    "\t-<modifier> : subtract by <modifier>\n"\
                                    "\treset       : set <ancillary_value> to <master_value>\n"\
                                    "Ex:    spell all reset         expl: resets all spell slots\n"\
                                    "       hp master +4            expl: increases master health by 4\n"\
                                    "       hp master -7            expl: decreases master health by 7\n"\
                                    "       hp master 21            expl: sets master health to 21\n"\
                                    "       hp reset                expl: ancillary_value of health is set to master_value\n"\
                                    "NOTE:\tthe reset modifier cannot be applied to master values\n"\
                                    "NOTE:\tmodifiers are always the last data entered"

#endif //__DNDSH_HELP_MESSAGES__
