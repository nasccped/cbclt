#include "app_name.h"
#include <string.h>

// when dealing with null pointers.
#define APP_NAME_NULL_PLACEHOLDER "<NULL POINTER BEING USED>"

// path separator according to OS.
#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

AppName app_name_new(StdinArgs *args) {
  return (AppName){.kind = FROM_STDIN, .args = args};
}

AppName *app_name_set_custom_name(AppName *self, char *name) {
  if (!self)
    return NULL;
  if (name) {
    // use negat: func returns 0 if success
    if (!strncpy_s(self->custom, APP_NAME_MAX_LENGTH, name, strlen(name) + 1)) {
      self->kind = CUSTOM;
    }
  }
  return self;
}

AppName *app_name_set_from_stdin(AppName *self, StdinArgs *args) {
  if (!self)
    return NULL;
  if (args) {
    self->kind = FROM_STDIN;
    self->args = args;
  }
  return self;
}

char *app_name_get_name(AppName *self) {
  char *name = APP_NAME_NULL_PLACEHOLDER;
  if (!self)
    return name;
  switch (self->kind) {
  case FROM_STDIN:
    name = (!self->args || !self->args->args[0]) ? name : self->args->args[0];
    break;
  case CUSTOM:
    name = self->custom;
    break;
  }
  return name;
}
