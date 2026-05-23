#include <stdio.h>

void print_green(const char *item) {
  if (!item) return;
  printf("\x1b[92m%s\x1b[0m", item);
}

int main(int argc, char *argv[]) {
  printf("Hello, ");
  print_green("commander");
  printf("!\n");
  return 0;
}
