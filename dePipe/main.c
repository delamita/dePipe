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
#include <sys/wait.h>
#define size 30

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //声明管道的描述文件
    //pipeDis[0]为读取管道，pipeDis[1]为写入管道
    int pipeDis[2];
    
    int ch1Pid,ch2Pid,ch3Pid;
    
    //先建立管道，再建立子进程,子进程就会继承父进程的管道描述文件
    pipe(pipeDis);
    
    //利用forK()函数建立子进程
    ch1Pid = fork();
    //当ch1Pid==0时为子进程
    if (ch1Pid==0) {
        
//        if (*count!=0) {
//            sleep(1);
//        }
        printf("进入子程序1,子程序1开始写入\n");
        
        //子进程进行写入前先关闭读取管道
        close(pipeDis[0]);
        
        char mesg[size] = "this message from children 1";
        //write函数写入失败时返回-1，成功时返回写入的字节数
        int re = (int)write(pipeDis[1], mesg, size);
        if(  re != -1 ){
            printf("子进程1写入完毕,写入的字节数为%d\n",re);
        }
        else{
            printf("子程序1写入失败\n");
        }
        
        exit(0);
    }
    //子程序建立失败返回-1
    else if(ch1Pid==-1){
        printf("创建子进程1失败\n");
        return -1;
    }
    
    sleep(1);

    ch2Pid = fork();
    if (ch2Pid==0) {
        
        
        //如果子进程1写入未完成，则子进程2等待
//        for(;*count!=1;){
//            sleep(1);
//        }

        printf("进入子程序2,子程序2开始写入\n");
        
        close(pipeDis[0]);
        
        char mesg[size] = "this message from children 2";
        int re = (int)write(pipeDis[1], mesg, size);
        if(  re != -1){
            printf("子进程2写入完毕,写入的字节数为%d\n",re);
        }
        else{
            printf("子程序2写入失败\n");
        }
        
        exit(0);
    }
    else if(ch2Pid==-1){
        printf("创建子进程2失败\n");
        return -1;
    }
    
    sleep(1);
    
    ch3Pid = fork();
    if (ch3Pid==0) {
        
        //如果子进程2写入未完成，则子进程3等待
//        for(;*count!=2;){
//            sleep(1);
//        }

        printf("进入子程序3,子程序3开始写入\n");
        
        close(pipeDis[0]);
        
        char mesg[size] = "this message from children 3";
        int re = (int)write(pipeDis[1], mesg, size);
        if(  re != -1){
            printf("子进程3写入完毕,写入的字节数为%d\n",re);
        }
        else{
            printf("子程序3写入失败\n");
        }
        
        exit(0);
    }
    else if(ch3Pid==-1){
        printf("创建子进程3失败\n");
        return -1;
    }
    
    
    char getMesg[30];
    
//    for(;count!=3;){
//        sleep(1);
//    }
    
    sleep(1);

    //读取前关闭写入管道
    close(pipeDis[1]);
    
    printf("父进程开始读取\n");
    
    for (int i=0; i<3; i++) {
        
        if ( read(pipeDis[0], getMesg, size) != -1 ) {
            printf("%s\n",getMesg);
        }
        else{
            printf("读取子进程%d的失败\n",i);
        }
        
    }
    wait(0);
    
    return 0;
}
