#include <stdio.h>

#include "QUEUE.h"
//#include "FCFS.h"


int NUM_PROCESSES;
int Process_finished_IO = -1;
int Process_arrived = -1;
int Process_finished_QuantumTime = -1;
void main()
{
	//intialization
	//const unsigned char arrivalTime[NUM_PROCESSES]={0,2,4};//,4,6,8};
	//const unsigned char brustTime[NUM_PROCESSES]={3,6,4};//,20,20,20};
	//const unsigned char interruptTime[NUM_PROCESSES]={2,2,2};//,4,5,2};
	//const unsigned char inout_Time[NUM_PROCESSES]={5,6,3};//,2,2,2};
	unsigned char time=0,current_processId=0,i=0,busy_cpu=0,done_process=0,remaining=0,robin=0,timeslicedone=0,start = 0;
	int temp_id=0,temp = 0,k=0,timeslice,choose = 0; // this "temp" to fix relative arrival time , "K" counter to check if user miss type
    float Average_Waiting_Time=0,Average_Turnaround_Time=0;
   char filename[20];
	Process_info pcb[50];
	Ready_que_ptr Head_ptr = NULL;
	Ready_que_ptr Tail_ptr = NULL;
	//.*.*.*.*.*.*.*.*.Read File
	FILE *cfptr; // pointer to locate the address in the read file.
				// at initiate the pointer point to first address in the read file.
	do{
	printf("Enter file name + its extention:\n");
	scanf("%[^\n]s",&filename);
	printf("%s",filename);
	for (k=0;k<=20;k++)
	{
		if(filename[k]== '.') {start =1;}
	}
	}while(start!=1);

	if((cfptr = fopen(filename,"r"))==NULL)
	{
			printf("file can't be opened");
	}
	else{
		printf("succeffuly opened tha file :D\n");
		while(!feof(cfptr)&&(fscanf(cfptr,"%s%d%d%d%d",pcb[i].acount,&pcb[i].arrival_time,&pcb[i].brust_time,&pcb[i].remaining_time,&pcb[i].inout_time)==5))
		{
		
		temp += pcb[i].arrival_time;
		pcb[i].arrival_time = temp;
		printf("process=%s,arrival time=%d,brust time=%d,interrupt time=%d,in_out time=%d\n",pcb[i].acount,pcb[i].arrival_time,pcb[i].brust_time,pcb[i].remaining_time,pcb[i].inout_time);
		i++;
		NUM_PROCESSES= i;
		}
	}
	printf("number of process:%d\n",NUM_PROCESSES);
	//.*.*.*.*.*.*.*.*.Begin
	printf("Let the game begin ^O^\n");
	printf("Choose Algrorithm: 1 \"FCFS\" , 2 \"RR\"\n");
	scanf("%d",&choose);
	//.*.*.*.*.*.*.*.*..*.*.*.*.*.*.*.*..*.*.*.*.*.*.*.*.
	if(choose == 2)
	{//RR
	//printf("Enter timeslice value:\n");
	//scanf("%d",&timeslice);
		timeslice = 2 ; //constant as the new modification
		for (i=0;i<NUM_PROCESSES;i++)
		{
			pcb[i].process_id = i;
			pcb[i].waiting_time =0;
			pcb[i].done_cpu_time =0;
			pcb[i].done_inout_time =0;
			pcb[i].inout_busy = 0;
			pcb[i].still_remaining_time = 0;
			pcb[i].finished_time=0;
		}
	
		while (done_process < NUM_PROCESSES)
		{
			
			//printf("time:%d\n",time);
			//list_queue(Head_ptr);
			//printf("current_processId:%d\n",current_processId);
			temp_id = check_arrivalTime(pcb,time);
			if (temp_id != -1)
			{
				//printf("id:%d\n",temp_id);
				//enqueue(&Head_ptr,&Tail_ptr,temp_id);
				//list_queue(Head_ptr);
				Process_arrived = temp_id ;
			}

			//check for inout
			/*for(i=0;i<NUM_PROCESSES;i++){
				if(pcb[i].inout_busy == 1) {pcb[i].done_inout_time++;
					if(pcb[i].inout_time == pcb[i].done_inout_time)
					{
						//printf("process just finshed inout :%d doneinouttime %d",i+1,pcb[i].done_inout_time);
						//printf(">>>time:%d\n",time);
						pcb[i].done_inout_time = 0;
						pcb[i].inout_busy=0;
						
						enqueue(&Head_ptr,&Tail_ptr,i);
					}
				}
			}*/
		
			if (busy_cpu ==1 ){
				
							
			// عندك 3 حتمال
			// اول واحد انه فيه بروسيس خلصت كده التايم الانتربت بتاعها و هتروح ع الانبوت اوتبوت 
			// تاني احتمال انها خلاص خلصت خالص كل البرست سي بي يو بتاعها وكده طيبه و اخلعي من هنا
			// تالت احتمال ان لا مفيش حاجة من ديه لسه حصلت ف كمل احاج زي ما انت
				if (remaining  == 0)
					{
						busy_cpu = 0;
						//printf("process end due to no end timeslice:%d",current_processId+1);
						//printf(">>>time:%d\n",time);
						if(pcb[current_processId].done_cpu_time == pcb[current_processId].brust_time){
						done_process++;
						pcb[current_processId].finished_time=time;
						//printf("process[%d] completed at time:%d\n",current_processId+1,time);
						}
						else {
							Process_finished_QuantumTime = current_processId;
							//printf("Process_finished_QuantumTime:%d at time:%d\n",Process_finished_QuantumTime,time);
							//pcb[current_processId].inout_busy = 1;pcb[current_processId].still_remaining_time = 0; 
							//printf("process will go to inout:%d",current_processId+1);
						//printf(">>>time:%d\n",time);
							}
						
						}
				else
					{
						remaining--;
						pcb[current_processId].done_cpu_time +=1;
					}
			}
			order_theInput_readQue (&Head_ptr,&Tail_ptr,&Process_arrived,&Process_finished_QuantumTime);
			//list_queue(Head_ptr);
		/*	else if(busy_cpu ==1 && robin >= timeslice) // time slice ended so we need to switch , the best place to put it is down
			{
				busy_cpu = 0;
				robin = 0;
				//printf("timeslice is done");
				//printf(">>>time:%d\n",time);
				// عندك 3 احتمالات جميل 
				// اول واحد ان فيه بروسيس خلص فعلا علي الحظ مع نهايه التايم سلايز
				// تاني واحد انه لسه ليها وقت ف البروسيسور وهي محتاجاه لسه ف هتروح لل ريدي كيو علشان ترجع ف المره اللي بعدها تكمله
				// الوقت اللي محتاجه من البروسيسور بتاع الانتربت خلص ومحتاجه تروح لل انتبوت اوتبوت
				if (remaining  == 0) 
					{
						// اول احتمالين
						
						// اول احتمال
						if(pcb[current_processId].done_cpu_time == pcb[current_processId].brust_time)
						{
						done_process++;
						//printf("process[%d] completed at time with the end of timeslice:%d\n",current_processId+1,time);
						pcb[current_processId].finished_time=time;
						}
						// تالت احتمال
						else {
							pcb[current_processId].inout_busy = 1;pcb[current_processId].still_remaining_time = 0;
							//printf("process will go to inout at endtimeslice:%d",current_processId+1);
							//printf(">>>time:%d\n",time);
						}
					}
				else 
					{ // تاني احتمال
						//لسه البروسييس محتاجه وقت ف البروسيسور بس التايم سلايز خلصت ف احنا هنحتفظ بهي فضلها كام ثانيه علشان تروح لل انبوت اوتبوت	
					pcb[current_processId].still_remaining_time = remaining;
					enqueue(&Head_ptr,&Tail_ptr,current_processId);
					//printf("process time slice out but still need cpu:%d",current_processId+1);
						//printf("      %d\n",time);  
					remaining--;
					pcb[current_processId].done_cpu_time +=1;
					}
			}*/
		
			 if ((busy_cpu ==0)&&is_empty(Head_ptr) != 1)
			{
				current_processId = dequeue( &Head_ptr,&Tail_ptr);
				//printf("process start:%d",current_processId+1);
				//printf("      %d\n",time);
				busy_cpu =1;
				robin = 0; //start the timeslice
				/*if(pcb[current_processId].still_remaining_time!=0)
					remaining = pcb[current_processId].still_remaining_time;
				else if(pcb[current_processId].brust_time - pcb[current_processId].done_cpu_time > pcb[current_processId].remaining_time)
				remaining = pcb[current_processId].remaining_time;
				else 
					remaining = pcb[current_processId].brust_time - pcb[current_processId].done_cpu_time;
				*/
				if (pcb[current_processId].brust_time - pcb[current_processId].done_cpu_time>timeslice)
				{
					remaining = timeslice;
				}
				else
				{
					remaining = pcb[current_processId].brust_time - pcb[current_processId].done_cpu_time;
				}
				remaining--;
				pcb[current_processId].done_cpu_time +=1;
				
			}
			//printf("remaining_timeofp[%d]:%d\n",current_processId,pcb[current_processId].remaining_time);
			fill_waitingTime(Head_ptr ,pcb );
			time ++;
			//robin++ ; //for next cycle	
			//printf(">>>time:%d  >>> robin:%d\n",time,robin);

		}
	}
	
	//.*.*.*.*.*.*.*.*..*.*.*.*.*.*.*.*..*.*.*.*.*.*.*.*..*.*.*.*.*.*.*.*.
	else if (choose == 1) // FCFS
	{
		for (i=0;i<NUM_PROCESSES;i++)
	{
		pcb[i].process_id = i;
		pcb[i].waiting_time =0;
		pcb[i].done_cpu_time =0;
		pcb[i].done_inout_time =0;
		pcb[i].inout_busy = 0;
		pcb[i].still_remaining_time = 0;
		pcb[i].finished_time=0;
		pcb[i].no_of_IO = 0;
	}
		while (done_process < NUM_PROCESSES)
	{
		
		//printf("time:%d\n",time);
		//list_queue(Head_ptr);
		//printf("current_processId:%d\n",current_processId);
		

		//check for inout
		for(i=0;i<NUM_PROCESSES;i++){
			if(pcb[i].inout_busy == 1) 
			{	
				pcb[i].done_inout_time++;
				if(pcb[i].inout_time == pcb[i].done_inout_time)
				{
						//printf("process  not busy:%d  %d",i,pcb[i].done_inout_time);
						//printf("      %d\n",time);
					pcb[i].done_inout_time = 0;
					pcb[i].inout_busy=0;
					pcb[i].no_of_IO = 1;
					//enqueue(&Head_ptr,&Tail_ptr,i);
					Process_finished_IO = i;
				}
			}
		}
		temp_id = check_arrivalTime(pcb,time);
		if (temp_id != -1)
		{
			//printf("id:%d\n",temp_id);
			//enqueue(&Head_ptr,&Tail_ptr,temp_id);
			Process_arrived = temp_id;
			//list_queue(Head_ptr);
		}
        order_theInput_readQue (&Head_ptr,&Tail_ptr,&Process_arrived,&Process_finished_IO);
		
		if (busy_cpu ==1)
		{

			if (remaining  == 0)
			{
				busy_cpu = 0;
				//printf("process end but not done:%d",current_processId);
				//printf("      %d\n",time);
				if(pcb[current_processId].done_cpu_time == pcb[current_processId].brust_time){
				done_process++;
				pcb[current_processId].finished_time=time;
				//printf("process[%d] completed at time:%d\n",current_processId+1,time);
				}
				else                                      //first I/O operation
				{
					pcb[current_processId].inout_busy = 1;
				
				}
				//printf("process busy:%d",current_processId);
				//printf("      %d\n",time);
			}
			else
			{
				remaining--;
				pcb[current_processId].done_cpu_time +=1;
			}
		}
		
		 if ((busy_cpu ==0)&&is_empty(Head_ptr) != 1)
		{
			current_processId = dequeue( &Head_ptr,&Tail_ptr);
			//printf("process start:%d",current_processId);
			//printf("      %d\n",time);
			busy_cpu =1;
			printf("pcb[%d].no_of_IO:%d,time %d\n",current_processId,pcb[current_processId].no_of_IO,time);
			if((pcb[current_processId].brust_time - pcb[current_processId].done_cpu_time > pcb[current_processId].remaining_time)&&pcb[current_processId].no_of_IO == 0)  // pcb[i].no_of_IO = 0 the first time of running in the CPU
			{
				//printf("enrer :%d\n",current_processId);
				remaining = pcb[current_processId].remaining_time;
			}
			else 
			{	
				//printf("out:%d time:%d\n",current_processId,time);
				remaining = pcb[current_processId].brust_time - pcb[current_processId].done_cpu_time;
			}
			remaining--;
			pcb[current_processId].done_cpu_time +=1;
		}
		//printf("remaining_timeofp[%d]:%d\n",current_processId,pcb[current_processId].remaining_time);
		fill_waitingTime(Head_ptr ,pcb );
		time ++;
	}
	}
    for (i=0;i<NUM_PROCESSES;i++){
			printf("p[%d]:\n",i+1);
			printf("Termination Time = %d\n",pcb[i].finished_time);
			printf("Waiting Time = %d\n",pcb[i].waiting_time);
			printf("Turnaround Time = %d\n",pcb[i].finished_time-pcb[i].arrival_time);
			Average_Waiting_Time += pcb[i].waiting_time;
			Average_Turnaround_Time += (pcb[i].finished_time-pcb[i].arrival_time);
	}
	
	printf("Average Waiting Time = %f\n",Average_Waiting_Time/NUM_PROCESSES);
	printf("Average Turnaround Time = %f\n",Average_Turnaround_Time/NUM_PROCESSES);
}


