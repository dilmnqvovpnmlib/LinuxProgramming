#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

/*
Linux コマンドでシンボリックリンクを貼る際は、以下のコマンドを実行する。
$ ln -s mylist02.txt latest
ファイル mylist02.txt に対し、latest という名前のシンボリックリンクを作成している。この場合、エディタでlatest ファイルを編集したり、閲覧したりすることは、mylist02.txt を編集したり。閲覧したりする結果と同じ操作結果になる。
*/

int main(int argc, char *argv[]) {
  printf("Start \n");

  if (argc != 3) {
    fprintf(stderr, "%s: no arguments \n", argv[0]);
    exit(1);
  }

  if (symlink(argv[1], argv[2]) < 0) {
    perror(argv[1]);
    exit(1);
  }

  exit(0);
}
