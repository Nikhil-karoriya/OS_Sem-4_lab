#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int main()
{
    pid_t p;
    printf("before fork\n");
    p = fork();
    if(p < 0) printf("error");
    if (p == 0) // chid process
    {
        printf("I am child having id %d\n", getpid());
        printf("My parent's id is %d\n", getppid());
    }
    else // p > 0 (parent process)
    {
        // wait(NULL); // it makes parent wait for the child process to complete
        printf("My child's id is %d\n", p);
        printf("I am parent having id %d\n", getpid());
    }
    printf("Common\n");
}