#ifndef __HELP_MESSAGES__
#define __HELP_MESSAGES__

#define DNDSH_COMMAND_HELP_LIST     "Command List:\n"\
                                    "d<dice_type>:    rolls a dice of type <dice_type>\n"\
                                    "stats:           display all stats or specific stat\n"\
                                    "spell:           display available spell slots\n"\
                                    "health:          modify and display max hp and current hp\n"\
                                    "mod:             modify a stat\n"\
                                    "add:             create a new stat\n"\
                                    "rm:              delete a stat\n"\
                                    "ld:              load stats in xml file\n"\
                                    "st:              store stats in xml file\n\n"\
                                    "type \'help <command>\' for more information"


#define DNDSH_ROLL_CMD_HELP         "Sample Useage:\t[<roll_times>]d<dice_type>\tNote: [<roll_times>] left empty will assume roll_times of 1\n"\
                                    "Rolls a dice of type <dice_type> a total of [<roll_times>] times"


#define DNDSH_STATS_CMD_HELP        "Sample Usage:\tstats [<stat>]\tNOTE: [<stat>] left empty will print out every stat"


#define DNDSH_SPELL_CMD_HELP        "Sample Usage:\tspell <1-9> [<modifier>]\tNOTE: [<modifier>] left empty assumes -1\n"\
                                    "\t\tspell reset all\n"\
                                    "\t\tspell reset <1-9>\n"\
                                    "\t\tspell master <1-9> <modifier>"

#define DNDSH_HEALTH_CMD_HELP       "Sample Usage:\thealth <modifier>\n"\
                                    "\t\theatlh reset\n"\
                                    "\t\theatlh master <modifer>"


#define DNDSH_MOD_CMD_HELP          ""

#define DNDSH_ADD_CMD_HELP          ""

#define DNDSH_RM_CMD_HELP           ""

#define DNDSH_LD_CMD_HELP           ""

#define DNDSH_ST_CMD_HELP           ""


#endif //__HELP_MESSAGES__
