#ifndef PROCESS_H
#define PROCESS_H


void get_process_info();
typedef struct{
char pid[256];
char process_name[100];
char state;
int memory_kb;
}Process;

extern Process process_list[20];
extern int process_count;

#endif
