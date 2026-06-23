#include<stdio.h>
#include"cpu.h"
#include<unistd.h>
#include<pthread.h>

extern pthread_mutex_t print_mutex;
double cpu_usage;

void get_cpu_info(){
FILE *fp;
char cpu_label[20];
long user_time;
long nice_time;
long system_time;
long idle_time;
long user1, system1, idle1;
long user2, system2, idle2;
long user_delta, system_delta, idle_delta, total_delta;

fp=fopen("/proc/stat", "r");

if(fp==NULL){
printf("Failed to open /proc/stat\n");
return;
}
//printf("opened file\n");
/*
fscanf(fp,"%s %ld %ld %ld %ld", cpu_label, &user_time, &nice_time, &system_time, &idle_time);
printf("CPU time:%ld\nUser time:%ld\nSystem time:%ld\nIdle time:%ld\n", user_time, system_time, idle_time );
//printf("CPU Model working\n");*/
fscanf(fp, "%s %ld %ld %ld %ld", cpu_label,&user1,&nice_time,&system1,&idle1);
//printf("read file\n");
fclose(fp);
sleep(1);
//printf("user1:%ld\nsystem1:%ld\nidle:%ld\n", user1, system1, idle1);
fp=fopen("/proc/stat", "r");
if(fp==NULL){
printf("failed opening /proc/stat\n");
return;
}
fscanf(fp,"%s %ld %ld %ld %ld",cpu_label,&user2,&nice_time,&system2,&idle2);
fclose(fp);
//printf("user1:%ld user2:%ld\nsystem1:%ld system2:%ld\nidle1:%ld idle2:%ld\n", user1, user2, system1, system2, idle1, idle2);
user_delta=user2-user1;
system_delta=system2-system1;
idle_delta=idle2-idle1;
total_delta=user_delta+system_delta+idle_delta;
if(total_delta==0){
printf("can't calculate CPU usage!\n");
return;
}
cpu_usage=((double)(user_delta+system_delta)/total_delta)*100;
pthread_mutex_lock(&print_mutex);
//printf("CPU Usage:%.2f%%\n", cpu_usage);
pthread_mutex_unlock(&print_mutex);
}
