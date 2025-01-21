#include "type.h"
#include "console.h"

#define FD_STDOUT 1

isize sys_write(usize fd, char* buf, usize len) {
    switch(fd) {
        case FD_STDOUT: {
            print("[User] ");
            print("%s", buf);
            return len;
        }
        default:
            break;
    }
}