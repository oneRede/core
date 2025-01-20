#include "type.h"
#include "console.h"
const usize FD_STDOUT = 1;

isize sys_write(usize fd, char* buf, usize len) {
    switch(fd) {
        case 1: {
            print("%s", buf);
            return len;
        }
    }
}