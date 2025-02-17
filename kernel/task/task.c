#include "type.h"
#include "console.h"
#include "sbi.h"
#include "task/task.h"
#include "loader.h"

extern void __switch(TaskContext *current_task_cx_ptr, TaskContext *next_task_cx_ptr);

TaskManager TM;

void run_first_task()
{
    init_task_manager();
    println("Init Task Manager Done!!!");
    TaskControlBlock task0 = TM.inner.tasks[0];
    task0.task_status = Running;
    println("Init Task Status Done!!!");
    TaskContext *next_task_cx_ptr = &task0.task_cx;
    TaskContext tc = task_zero_init();
    println("Zero Task Status Done!!!");
    println("RA:%x", next_task_cx_ptr->ra);
    println("SP:%x", next_task_cx_ptr->sp);
    __switch(&tc, next_task_cx_ptr);
    println("First Task Done!!!");
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

void init_task_manager()
{
    println("Init Task Manager!!!!");
    usize num_app = get_num_app();

    for (i32 i = 0; i < MAX_APP_NUM; i++)
    {
        TM.inner.tasks[i].task_cx = goto_restore(init_app_cx(i));
        TM.inner.tasks[i].task_status = Ready;
    }
    
    TM.num_app = num_app;
    TM.inner.current_task = 0;
}
