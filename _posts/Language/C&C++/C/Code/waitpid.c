/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2022-02-23 21:44:57
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-28 23:42:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    // child
    if (pid == 0) {
        printf("a");
        // 刷新缓冲区
        fflush(stdout);
    } else {
        printf("b");
        fflush(stdout);
        // 等待父进程的所有子进程结束
        waitpid(-1, NULL, 0);
    }
    
    printf("c");
    fflush(stdout);
    return 0;
}

// acbc
// bacc