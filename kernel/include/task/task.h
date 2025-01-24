#include "task/context.h"

#define MAX_APP_NUM 16

typedef struct TaskControlBlock
{
    TaskStatus task_status;
    TaskContext task_cx;
}TaskControlBlock;

typedef struct TaskManagerInner
{
    TaskControlBlock tasks[MAX_APP_NUM];
    usize current_task;
}TaskManagerInner;

typedef struct TaskManager
{
    usize num_app;
    TaskManagerInner inner;
}TaskManager;

void run_first_task();
void mark_current_suspended();
void mark_current_exited();
isize find_next_task();
void run_next_task();
void suspend_current_and_run_next();
void exit_current_and_run_next();

void init_task_manager();