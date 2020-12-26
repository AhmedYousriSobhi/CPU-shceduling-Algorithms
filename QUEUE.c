#include <stdio.h>
#include <stdlib.h>

#include "QUEUE.h"
extern int NUM_PROCESSES;
void enqueue (Ready_que_ptr * head_ptr,Ready_que_ptr * tail_ptr,int p_id )
{
	Ready_que_ptr new_ptr;  //address of the new node

	new_ptr = malloc(sizeof(Ready_que));

	if (new_ptr != NULL)
	{
		new_ptr->process_id = p_id;
		new_ptr->next_ptr = NULL;

		if (*head_ptr == NULL) //start node
		{
			*head_ptr = new_ptr;
			*tail_ptr = new_ptr;
		}
		else
		{
			(*tail_ptr)->next_ptr= new_ptr;
			*tail_ptr = new_ptr;
		}

	}
	else
	{
		printf("there is no space in the heap");
	}

}


unsigned char is_empty(Ready_que_ptr head_prt)
{
	return (head_prt == NULL);
}


unsigned char dequeue(Ready_que_ptr * head_ptr,Ready_que_ptr * tail_ptr)
{
	Ready_que_ptr temp_ptr= *head_ptr;
	unsigned char r_data;
	if (is_empty(*head_ptr) != 1)
	{
		*head_ptr=(*head_ptr)->next_ptr;
		r_data = temp_ptr->process_id;
		if (temp_ptr == *tail_ptr)
		{
			*tail_ptr = NULL;

		}

		free(temp_ptr);
	}
	else
	{
		printf("queue is empty");
	}

	return r_data;
}


void list_queue(Ready_que_ptr const head_ptr)
{
	Ready_que_ptr current_ptr=head_ptr;
	if (is_empty(head_ptr))
	{
		printf("empty queue\n");
	}
	else
	{
		while (current_ptr != NULL)
		{
			printf("queue data:%d\n",current_ptr->process_id);
			current_ptr=current_ptr->next_ptr;

		}
	}

}

//-------------------------------------------------------------------------

// FCFS.c

 int check_arrivalTime(Process_info * pcb_ptr,unsigned char time)
{

	unsigned i=0;

	while((pcb_ptr[i].arrival_time != time)&&(i != NUM_PROCESSES))
		i++;

	if (i == NUM_PROCESSES)
		i=-1; //if no matching return -1

	return i;

}

void fill_waitingTime(Ready_que_ptr const head_ptr ,Process_info * pcb )
{
	Ready_que_ptr temp_ptr = head_ptr;
	while (temp_ptr != NULL)
	{
		//printf("in fill waiting_time p_Id is %d\n",temp_ptr->process_id);
		pcb[temp_ptr->process_id].waiting_time ++;
		temp_ptr = temp_ptr->next_ptr;
	}

}

void order_theInput_readQue (Ready_que_ptr * head_ptr,Ready_que_ptr * tail_ptr,int * process_1,int * process_2)
{
	if (*process_1 > *process_2)
	{
		if (*process_2 != -1)
		{
			enqueue(head_ptr,tail_ptr,*process_2);
			enqueue(head_ptr,tail_ptr,*process_1);
		
		}
		else
			enqueue(head_ptr,tail_ptr,*process_1);
			
	}
	else if (*process_2 > *process_1)
	{
		if (*process_1 != -1)
		{
			enqueue(head_ptr,tail_ptr,*process_1);
			enqueue(head_ptr,tail_ptr,*process_2);
		
		}
		else
			enqueue(head_ptr,tail_ptr,*process_2);
			
	}
	*process_1 =*process_2=-1;
}
