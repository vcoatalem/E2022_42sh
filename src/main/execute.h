#ifndef EXECUTE_H
#define EXECUTE_H

#include "42sh.h"
#include "readline.h"
void sigintHandler(int _);
int execute_stdin(struct execution_bundle *bundle);
int execute_interactive(struct execution_bundle *bundle);
int execute_cmd(struct execution_bundle *bundle, char *cmd);
int execute_script(struct execution_bundle *bundle, char* script);

#endif 
