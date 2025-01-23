#include "type.h"

typedef enum TaskStatus
{
    UnInit,
    Ready,
    Running,
    Exited,
}TaskStatus;

typedef struct TaskContext
{
    usize ra;
    usize sp;
    usize s[12];
} TaskContext;

TaskContext task_zero_init();
TaskContext goto_restore(usize kstack_ptr);