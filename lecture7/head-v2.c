/*
処理対象は標準入力のみ
表示したい行数をコマンドライン引数から指定する
ファイル名をコマンドライン引数から受け取れるようにする

使い方
$ ./head-v2.out 10 text
*/

#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int main(int argc, char *argv[]) {
  // 行数が指定されていない時は、エラーを吐く
  if (argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    exit(1);
  }

  long nlines = atol(argv[1]);

  if (argc == 2) {
    do_head(stdin, nlines);
  } else {
    int i;

    for(i = 2; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      // f == NULL と同義 
      if(!f) {
        perror(argv[i]);
        exit(1);
      }

      do_head(f, nlines);

      fclose(f);
    }
  }
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
