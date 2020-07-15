#ifndef __DNDSH_HELP_MESSAGES__
#define __DNDSH_HELP_MESSAGES__

#define DNDSH_COMMAND_HELP_LIST     "Command List:\n"\
                                    "roll(d<dice_type>):    rolls a dice of type <dice_type>\n"\
                                    "ls/l:                  list all stats or specific stat\n"\
                                    "spell/sp:              modify available spell slots\n"\
                                    "health/hp:             modify master hp and/or current hp\n"\
                                    "mod:                   modify a stat\n"\
                                    "add:                   create a new stat\n"\
                                    "remove/rm:             delete a stat\n"\
                                    "load/ld:               load stats in xml file\n"\
                                    "store/st:              store stats in xml file\n"\
                                    "modifier:              valid modifiers\n"\
                                    "type \'help <command>\' for more information"


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


#define DNDSH_SPELL_CMD_HELP        "Sample Usage:\tsp {<spell_level>|all} [<modifier>]\n"\
                                    "\t\tsp reset [<spell_level>]\n"\
                                    "\t\tsp master {<spell_level>|all} <modifier>\n"\
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


#define DNDSH_HEALTH_CMD_HELP       "Sample Usage:\thp <modifier>\n"\
                                    "\t\thp reset\n"\
                                    "\t\thp master <modifer>\n"\
                                    "Description:\n"\
                                    "Health will adjust <ancillary_value> according to <modifer>. If <ancillary_value>\n"\
                                    "does not exist, health will create one and adjust it according to <modifer>. The reset\n"\
                                    "option operates on <ancillary_value> only and sets it equal to <master_value>.\n"\
                                    "To adjust <master_value> the \'master\' option must be provided before <modifer>."


#define DNDSH_MOD_CMD_HELP          "Sample Usage:\tmod <key> <master_value> [<new_ancillary_value>]\n"\
                                    "NOTE:\t[<new_ancillary_value>] will by default leave everything unchanged."

#define DNDSH_ADD_CMD_HELP          "Sample Usage:\tadd <new_key> <master_value> [<new_ancillary_value>]\n"\
                                    "NOTE:\t[<new_ancillary_value>] will, by default, append nothing to <new_key> after <master_value>."

#define DNDSH_RM_CMD_HELP           "Sample Usage:\trm <key>\n"\
                                    "Deletes character data entry identified by <key>."

#define DNDSH_LD_CMD_HELP           "Sample Usagae:\tld <file_path>\n"\
                                    "NOTE:\t<file_path> must be in the working directory, otherwise the absolute path must be provided."

#define DNDSH_ST_CMD_HELP           "Sample Usage:\tst <file_path>\n"\
                                    "NOTE:\t<file_path> must be in the working directory, otherwise the absolute path must be provided."

#define DNDSH_MODIFIER_HELP         "+<modifier> : increase by <modifier>\n"\
                                    "<modifier>  : set value to <modifier>\n"\
                                    "-<modifier> : substract by <modifier>\n"\
                                    "reset       : set <ancillary_value> to <master_value>"

#endif //__DNDSH_HELP_MESSAGES__
