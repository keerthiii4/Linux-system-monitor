#include<stdio.h>
#include"memory.h"
#include"cpu.h"
#include"process.h"
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t print_mutex;

void* cpu_thread_function(void* arg){
while(1){
//printf("cpu thread working\n");
get_cpu_info();
}
return NULL;
}

void* memory_thread_function(void* arg){
while(1){
//printf("memory thread working\n");
get_memory_info();
sleep(1);
}
return NULL;
}

void* process_thread_function(void* arg){
while(1){
//printf("process thread working\n");
get_process_info();
sleep(1);
}
return NULL;
}

void display_system_info()
{
system("clear");
printf("CPU Usage: %.2f%%\n", cpu_usage);
printf("Memory Usage: %.2f%%\n", memory_usage);
printf("Total Memory: %ld KB\n", total_memory);
printf("Free Memory: %ld KB\n", free_memory);
printf("Used Memory: %ld KB\n", used_memory);

printf("\nPID\tNAME\tSTATE\tMEMORY(KB)\n");
for(int i=0;i<process_count;i++){
printf("%s\t%s\t%c\t%d\n", process_list[i].pid, process_list[i].process_name, process_list[i].state, process_list[i].memory_kb);
}
}

int main()
{
pthread_mutex_init(&print_mutex, NULL);
pthread_t cpu_thread;
pthread_t memory_thread;
pthread_t process_thread;
pthread_create(
&cpu_thread,
NULL,
cpu_thread_function,
NULL
);
pthread_create(
&memory_thread,
NULL,
memory_thread_function,
NULL
);
pthread_create(
&process_thread,
NULL,
process_thread_function,
NULL
);
system("clear");
printf("-----Linux system monitor-----\n");
//while(1){
//get_memory_info();
//get_cpu_info();
//get_process_info();
//sleep(1);
//}
//pthread_join(cpu_thread, NULL);
//pthread_join(memory_thread, NULL);
//pthread_join(process_thread, NULL);
while(1){
display_system_info();
sleep(1);
}
return 0;
}
