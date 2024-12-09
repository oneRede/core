#include <usyscall.h>
#include <uconsole.h>

isize write(int fd, char *s, usize len)
{
    sys_write(fd, s, len);
};

isize exit(int exit_code) {
    sys_exit(exit_code);
}

int __attribute__((weak)) main() {
    print("this code should excute!!!");
}

void _start() {
    exit(main());
    print("unreachable after sys_exit!");
}