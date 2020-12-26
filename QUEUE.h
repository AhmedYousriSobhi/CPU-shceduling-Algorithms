#include <stdio.h>


typedef struct ready_que{
	int process_id;
	struct ready_que * next_ptr;
}Ready_que;




typedef Ready_que * Ready_que_ptr;


void enqueue (Ready_que_ptr * head_ptr,Ready_que_ptr * tail_ptr,int p_id );

unsigned char dequeue(Ready_que_ptr * head_ptr,Ready_que_ptr * tail_ptr);

unsigned char is_empty(Ready_que_ptr head_prt); //return 1 if is empty 


// FCFS .header
//#define NUM_PROCESSES 3

typedef struct {
	char *acount[10];
	int process_id;
	int remaining_time;
	int waiting_time;
	int arrival_time;
	int inout_time;
	int done_cpu_time;
	int done_inout_time;
	int brust_time;
	int inout_busy;
	int still_remaining_time; // the rest of interrupt io time needed to go to i/o devices
	int finished_time;
	int no_of_IO;
	
}Process_info;

int check_arrivalTime(Process_info * pcb,unsigned char time);

void fill_waitingTime(Ready_que_ptr const head_ptr ,Process_info * pcb );
void list_queue(Ready_que_ptr const head_ptr);
void order_theInput_readQue (Ready_que_ptr * head_ptr,Ready_que_ptr * tail_ptr,int* process_1,int* process_2);