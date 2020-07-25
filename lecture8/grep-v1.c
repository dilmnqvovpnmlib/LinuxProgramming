#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

static void do_grep(regex_t *pattern, FILE *f);

int main(int argc, char *argv[]) {
  printf("Hello \n");

  // コマンドラインから検索文字列が入力されているかを確認
  if (argc < 2) {
    fputs("No pattern \n", stderr);
    exit(1);
  }

  regex_t pattern;
  int err;

  // 正規表現で適合する文字列があるかを確認
  err = regcomp(&pattern, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
  if (err != 0) {
    char buf[1024];

    regerror(err, &pattern, buf, sizeof(buf));
    puts(buf);
    exit(1);
  }

  if (argc == 2) {
    do_grep(&pattern, stdin);
  } else {
    for (int i = 2; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }

      do_grep(&pattern, f);
      fclose(f);
    }
  }
  regfree(&pattern);
  exit(0);
}

// *pattern は、文字列で表現された正規表現のパターンを専用のデータ型に変換したデータ
static void do_grep(regex_t *pattern, FILE *f) {
  char buf[2048];

  while(fgets(buf, sizeof(buf), f)) {
    if (regexec(pattern, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    } 
  }  
}
  
