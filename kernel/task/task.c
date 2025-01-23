#include "type.h"
#include "console.h"
#include "sbi.h"
#include "task/task.h"

extern void __switch(TaskContext *current_task_cx_ptr, TaskContext *next_task_cx_ptr);

TaskManager TM;

void run_first_task()
{
    TaskControlBlock task0 = TM.inner.tasks[0];
    task0.task_status = Running;
    TaskContext *next_task_cx_ptr = &task0.task_cx;
    TaskContext tc = task_zero_init();
    __switch(&tc, next_task_cx_ptr);
}

void mark_current_suspended()
{
    usize current = TM.inner.current_task;
    TM.inner.tasks[current].task_status = Ready;
}

void mark_current_exited()
{
    usize current = TM.inner.current_task;
    TM.inner.tasks[current].task_status = Exited;
}

isize find_next_task()
{
    usize current = TM.inner.current_task;
    for (usize i = current; i < TM.num_app; i++)
    {
        if (TM.inner.tasks[i].task_status == Ready)
        {
            return i;
        }
    }
    return -1;
}

void run_next_task()
{
    isize next = find_next_task();
    if (next > -1)
    {
        usize current = TM.inner.current_task;
        TM.inner.tasks[next].task_status = Running;
        TM.inner.current_task = next;
        TaskContext *current_task_cx_ptr = &TM.inner.tasks[current].task_cx;
        TaskContext *next_task_cx_ptr = &TM.inner.tasks[next].task_cx;

        __switch(current_task_cx_ptr, next_task_cx_ptr);
    }
    else
    {
        println("All applications completed!");
        shutdown();
    }
}

void suspend_current_and_run_next()
{
    mark_current_suspended();
    run_next_task();
}

void exit_current_and_run_next()
{
    mark_current_exited();
    run_next_task();
}
