#ifndef _APP_NAME_H_
#define _APP_NAME_H_

#include "stdin_args.h"
#define APP_NAME_MAX_LENGTH 64

typedef struct {
  enum { FROM_STDIN, CUSTOM } kind;
  union {
    StdinArgs *args;
    char custom[APP_NAME_MAX_LENGTH];
  };
} AppName;

AppName app_name_new(StdinArgs *);
AppName *app_name_set_custom_name(AppName *, char *);
AppName *app_name_set_from_stdin(AppName *, StdinArgs *);
char *app_name_get_name(AppName *);

#endif // !_APP_NAME_H_
