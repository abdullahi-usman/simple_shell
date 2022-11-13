#ifndef __MAIN_H__
#define __MAIN_H__
extern char **environ;

int super_simple_shell(char **env);
char *find_command(char *command);

#endif
