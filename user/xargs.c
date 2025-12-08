#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// 统一风格与流程：预置固定参数，按行分隔读取，行完即 exec
static void run(char *prog, char **args) {
  int pid = fork();
  if (pid == 0) {
    exec(prog, args);
    fprintf(2, "xargs: exec %s failed\n", prog);
    exit(1);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(2, "usage: xargs command [args...]\n");
    exit(1);
  }

  char buf[2048];
  char *p = buf;      // 缓冲写指针
  char *tok = buf;    // 当前 token 起点

  char *argsbuf[128]; // 参数指针数组
  char **pa = argsbuf;

  // 先写入固定参数（xargs 后面的命令及其参数）
  for (int i = 1; i < argc; i++)
    *pa++ = argv[i];
  char **fixed_end = pa; // 记录固定参数尾

  // 逐字节读取 stdin，遇空格/换行切分
  char ch;
  while (read(0, &ch, 1) == 1) {
    if (ch == ' ' || ch == '\n') {
      *p = '\0';
      *pa++ = tok;      // 收集一个参数
      tok = p + 1;      // 下个 token 起点

      if (ch == '\n') { // 行结束，立即执行
        *pa = 0;
        run(argv[1], argsbuf);
        pa = fixed_end; // 恢复到固定参数之后
        tok = p + 1;
      }
    } else {
      *p = ch;
    }
    p++;
  }

  // EOF 后如有残余参数（最后一行无换行）
  if (tok != p) {
    *p = '\0';
    *pa++ = tok;
    *pa = 0;
    run(argv[1], argsbuf);
  }

  // 回收所有子进程
  while (wait(0) != -1);
  exit(0);
}