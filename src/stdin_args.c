#include "stdin_args.h"
#include <stdlib.h>

StdinArgs stdin_args_new(int argc, char **argv) {
  return (StdinArgs){.count = argc, .args = argv};
}

char *stdin_args_get_n(StdinArgs *self, size_t n) {
  return (self && n >= 0 && n < self->count) ? self->args[n] : NULL;
}
