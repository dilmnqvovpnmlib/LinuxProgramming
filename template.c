#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Start \n");

  if (argc < 2) {
    fprintf(stderr, "%s: no arguments \n", argv[0]);
    exit(1);
  }

  exit(0);
}
