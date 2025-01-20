#include <stdio.h>
#include <string.h>

// 定义一个结构体
typedef struct {
    char name[50];
    int age;
    float height;
} Person;

int main() {
    extern void _num_app();

    long int nuum = *((long int *) (_num_app+8));
    printf("num app: %lx\n", nuum);
    // 在栈上声明结构体变量
    Person person;

    // 初始化结构体成员
    strcpy(person.name, "张三");
    person.age = 25;
    person.height = 1.75;

    // 打印结构体变量的地址
    printf("结构体 person 的地址: %lx\n", (unsigned long int)&person);

    // 打印结构体成员的值
    printf("姓名: %s\n", person.name);
    printf("年龄: %d\n", person.age);
    printf("身高: %.2f\n", person.height);


    int num = 1000;
    int* np = &num;
    int* np2 = np;

    printf("np: %d\n", *np);
    printf("np: %d\n", *np2);

    return 0;
}