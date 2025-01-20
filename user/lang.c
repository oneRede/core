// #include <signal.h>
// #include <uconsole.h>

// #define EXIT_FAILURE 1
// #define NULL ((void *)0)

// const int BT_BUF_SIZE = 256;

// void sigsegv_handler(int signo)
// {
//   int j, nptrs;
//   void *buffer[BT_BUF_SIZE];
//   char **strings;

//   nptrs = backtrace(buffer, BT_BUF_SIZE);
//   printf("backtrace() returned %d addresses\n", nptrs);

//   strings = backtrace_symbols(buffer, nptrs);
//   if (strings == NULL)
//   {
//     perror("backtrace_symbols");
//     exit(EXIT_FAILURE);
//   }

//   for (j = 0; j < nptrs; j++)
//     printf("%s\n", strings[j]);

//   free(strings);
//   exit(-1);
// }

// int main() {
//   signal(SIGSEGV, sigsegv_handler);
// }