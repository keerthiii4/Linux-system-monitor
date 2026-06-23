#include<stdio.h>
#include"memory.h"
#include<string.h>
#include<pthread.h>

extern pthread_mutex_t print_mutex;

long total_memory=0;
long free_memory=0;
long used_memory=0;
double memory_usage=0;

void get_memory_info(){
FILE *fp;

char label[50];
long value;
char unit[20];

fp = fopen("/proc/meminfo", "r");

if(fp == NULL){
printf("Failed to open file\n");
return;
}

while(fscanf(fp, "%s %ld %s", label, &value, unit) != EOF){
if(strcmp(label, "MemTotal:")==0){
total_memory=value;
}
if(strcmp(label, "MemFree:")==0){
free_memory=value;
}
//printf("%s %ld %s\n", label, value, unit);
}
used_memory=total_memory-free_memory;
memory_usage=((double)used_memory/total_memory)*100;
pthread_mutex_lock(&print_mutex);
//printf("Total Memory : %ld kb\n",total_memory);
//printf("Free Memory : %ld kb\n",free_memory);
//printf("Used Memory : %ld kb\n",used_memory);
//printf("Memory used : %.2f%%\n",memory_usage);
pthread_mutex_unlock(&print_mutex);
/*
fscanf(fp, "%s %ld", label, &value);
printf("Label: %s\n", label);
printf("Value: %ld\n", value);
printf("file opened successfully\n");*/
fclose(fp);
}
