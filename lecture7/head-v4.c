/*
処理対象は標準入力とファイルからの読み込み
表示したい行数をコマンドライン引数から指定する

この実装では、オプション解析をメインに行う
静的に解析しても構わないが、それ用の API を用いて実装していく

使い方
$ ./head-v3.out -n15 text
$ cat text | ./head-v3.out -n15
$ ./head-v3.out -h
*/

#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

#define DEFAULT_N_LINES 10

static void do_head(FILE *f, long nlines);

static struct option long_options[] = {
  {"lines", required_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
  int opt;
  long nlines = DEFAULT_N_LINES;
  
  while ((opt =  getopt_long(argc, argv, "n", long_options, NULL)) != -1) {
    switch(opt) {
      case 'n':
        nlines = atol(optarg);
        break;
      case 'h':
        fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(0);
      case '?':
        fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(1);
    }
  }

  if (optind == argc) {
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
