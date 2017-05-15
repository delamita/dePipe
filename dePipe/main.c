//
//  main.c
//  dePipe
//
//  Created by 费克翔 on 2017/5/15.
//  Copyright © 2017年 Crazzy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int pipeDis[2];
    
    int ch1Pid,ch2Pid,ch3Pid;
    
    int *count = (int *)malloc(1);
    *count = 0;
    
    ch1Pid = fork();
    ch2Pid = fork();
    ch3Pid = fork();
    
    if(ch1Pid<0||ch2Pid<0||ch3Pid<0){
        printf("创建子进程失败\n");
        return -1;
    }
    
    if (ch1Pid==1) {
        
        printf("进入子程序1,子程序一开始写入\n");
        
        close(pipeDis[1]);
        
        char *mesg = "this message from children 1\n";
        write(pipeDis[0], mesg, sizeof(mesg));
        
        *count += 1;
        printf("子进程1写入完毕");
    }
    
    
    
    return 0;
}
