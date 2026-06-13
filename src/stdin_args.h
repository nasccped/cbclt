#ifndef _STDIN_ARGS_H_
#define _STDIN_ARGS_H_

typedef struct {
  int count;
  char **args;
} StdinArgs;

StdinArgs stdin_args_new(int, char **);
char *stdin_args_get_n(StdinArgs *, size_t);

#endif // !_STDIN_ARGS_H_
