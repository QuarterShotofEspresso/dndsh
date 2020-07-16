#ifndef __ERROR_MESSAGES_HPP__
#define __ERROR_MESSAGES_HPP__

#define UNKNOWN_COMMAND_ERR         "unknown command: Type \'help\' for a list of commands"

#define INCORRECT_USAGE_ERR(CMD)    "incorrect usage: type \'help " #CMD "\' to learn more."

#define KEY_NOT_FOUND_ERR           "stat not found: type \'ls\' for a list of available stat and \'help add\' to learn more about adding stats"

#define FILE_ACCESS_FAIL_ERR        "file access failure: enter absolute path if file is not in working directory"

#endif //__ERROR_MESSAGES_HPP__
