#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

/*
ハードリンクの作成 (シンボリックリンクと区別)
rm コマンドは、ファイル名を削除する。実体を指す名前が全て何区なった時点で、すなはちリンクカウントが 0 になった時点で、初めて実体が削除される。
*/

/*
$ ./ln.out old_file new_file
*/

int main(int argc, char *argv[]) {
  printf("Start \n");

  if (argc != 3 ) {
    fprintf(stderr, "%s: no arguments \n", argv[0]);
    exit(1);
  }

  if (link(argv[1], argv[2]) < 0) {
    perror(argv[1]);
    exit(1);
  }

  exit(0);
}
