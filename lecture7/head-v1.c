/*
処理対象は標準入力のみ
表示したい行数をコマンドライン引数から指定する

使い方
$ cat text | ./head-v1.out 5
*/

#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int main(int argc, char *argv[]) {
  // 行数が指定されていない時は、エラーを吐く
  if (argc != 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    exit(1);
  }

  do_head(stdin, atol(argv[1]));
  exit(0);
}

static void do_head(FILE *f, long nlines) {
  int c;

  // 行数が 0 以下の値の時は終了
  if (nlines <= 0) return;

  while ((c = getc(f)) != EOF) {
    if (putchar(c) < 0) exit(1);

    if (c == '\n') {
      nlines--;
      if (nlines == 0) return;
    }
  }
}
