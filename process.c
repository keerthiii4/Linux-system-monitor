#include<stdio.h>
#include"process.h"
#include<dirent.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>

extern pthread_mutex_t print_mutex;
Process process_list[20];
int process_count;

int is_pid(char *name){
int i=0;
while(name[i]!='\0'){
if(!isdigit(name[i])){
return 0;
}
i++;
}
return 1;
}


void get_process_info(){
//printf("Process model working\n");
char path[256];
char line[256];
char state;
char process_name[100];
char memory_label[50];
int memory_kb = 0;
int count = 0;
DIR *dir;
struct dirent *entry;
dir=opendir("/proc");

if(dir==NULL){
printf("Failed to open /proc\n");
return;
}
//printf("%-8s %-20s %-5s %s\n", "PID", "Name", "State", "Memory(KB)");
//printf("opened /proc\n");
while((entry=readdir(dir))!=NULL){
if(is_pid(entry->d_name)){
sprintf(path, "/proc/%s/status", entry->d_name);
FILE *fp;
fp = fopen(path, "r");
fgets(line, sizeof(line), fp);
sscanf(line,"Name:\t%s", process_name);
fgets(line, sizeof(line), fp);
sscanf(line, "State:\t%c", &state);
while(fgets(line, sizeof(line), fp)){
sscanf(line, "%s %d", memory_label, &memory_kb);
if(strcmp(memory_label, "VmRSS:")== 0){
break;
}
}
pthread_mutex_lock(&print_mutex);
//printf("%-8s %-20s %-5c %d\n", entry->d_name, process_name, state, memory_kb);
strcpy(process_list[count].pid,entry->d_name);
strcpy(process_list[count].process_name, process_name);
process_list[count].state=state;
process_list[count].memory_kb=memory_kb;
pthread_mutex_unlock(&print_mutex);
count++;
if(count >20){
break;
}
if(fp == NULL){
continue;
}
fclose(fp);
//printf("%s\n", entry->d_name);
//printf("%s\n", path);
}}
process_count=count;
printf("-------------------------------\n");
closedir(dir);
}
