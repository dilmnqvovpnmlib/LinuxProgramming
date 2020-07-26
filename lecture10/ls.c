#include <stdio.h>
// exit 関数を使うためにinclude する必要がある
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

static void do_ls(char *dir_name);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments \n", argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    do_ls(argv[i]);
  }

  exit(0);
}

void do_ls(char *dir_name) {
  DIR *d;
  struct dirent *ent;

  d = opendir(dir_name);

  if (!d) {
    perror(dir_name);
    exit(1);
  }

  while (ent = readdir(d)) {
    printf("%s \n", ent->d_name);
  }
}
