#include<stdio.h>
#include<string.h>
#define MAX_PROC_CNT 	10
struct ProcInfo
{
	char szProcName[10];
    	int iArvlTime;
    	int iBurstTime;
	int iStartTime;	
	int iFinishTime;
	int iWaitTime;
    	int iTAT;
    	int iTBT;	//TempBurstTime (extra line from fcfs)
}procInfo[MAX_PROC_CNT];

int iNoOfProcess;
int iCurrentTime;	//extra line from fcfs


void SortByAT()	//Same function as FCFS	
{
	int i,j;
	struct ProcInfo tempProcInfo;
	for(i=0;i<iNoOfProcess;i++)
	{
		for(j=i+1;j<iNoOfProcess;j++)
		{
			if(procInfo[i].iArvlTime > procInfo[j].iArvlTime)
            		{
				tempProcInfo = procInfo[i];
				procInfo[i] = procInfo[j];
				procInfo[j] = tempProcInfo;
			} 	
		}
	}
}

void AcceptProcInfo()	//Same function as FCFS	with one extra line
{
    int i;
    //printf("Enter the number of processes:");
    //scanf("%d",&iNoOfProcess);
    iNoOfProcess = 3;
    /*for(i=0; i<iNoOfProcess; i++)
    {
        printf("Enter the ProcessName, arriArvlTimeival Time& Burst Time:");
        scanf("%s%d%d",procInfo[i].szProcName,&procInfo[i].iArvlTime, &procInfo[i].iBurstTime);
    }*/

        strcpy(procInfo[0].szProcName, "p1");
        procInfo[0].iArvlTime = 3;
        procInfo[0].iBurstTime = 5;
	procInfo[0].iTBT = procInfo[0].iBurstTime;	//extra line from fcfs

        strcpy(procInfo[1].szProcName, "p2");
        procInfo[1].iArvlTime = 4;
        procInfo[1].iBurstTime = 6; 
	procInfo[1].iTBT = procInfo[1].iBurstTime;	//extra line from fcfs
        
	strcpy(procInfo[2].szProcName, "p3");
        procInfo[2].iArvlTime = 2;
        procInfo[2].iBurstTime = 7;         
	procInfo[2].iTBT = procInfo[2].iBurstTime;	//extra line from fcfs
}

void DisplayProcInfo()	//Same Fucntion as FCFS remove FinishTime
{
    int i;
    printf("\nPName ArivalTime BurstTime WaitTime StartTime TAT Finish");
    for(i=0; i<iNoOfProcess; i++)
    {
        printf("\n%s\t%3d\t%3d\t%3d\t%3d\t%6d\t%6d",procInfo[i].szProcName, procInfo[i].iArvlTime, procInfo[i].iBurstTime,          
	procInfo[i].iWaitTime,procInfo[i].iStartTime,procInfo[i].iTAT,procInfo[i].iFinishTime);
    }
}


int getProcWithMinBT()	//Gives the process with Minimum BurstTime
{
	int i=0;
	int iMin=999;
	int p=-1;

	for(i=0;i<iNoOfProcess;i++)
	{
		if((procInfo[i].iArvlTime <= iCurrentTime) && (procInfo[i].iTBT != 0))
		{
			if(procInfo[i].iBurstTime < iMin)
			{
				iMin = procInfo[i].iBurstTime;
				p=i;				
			}
		}	
	}
	return p;
}

void ComputeProcTimes()
{
	int i,cnt=0;
	printf("\nGantt Chart: ");
	while(cnt != iNoOfProcess)
	{	
		i = getProcWithMinBT();
		if(i == -1)
		{
			printf("|---|",iCurrentTime);	//if CPU is idle
			iCurrentTime = procInfo[cnt].iArvlTime;
		}
		else
		{
			//Calculate the ProcessTimes for the Process with minimum burst time
			printf("%d",iCurrentTime);
				
			procInfo[i].iWaitTime = iCurrentTime - procInfo[i].iArvlTime;	//Modified line from FCFS
			procInfo[i].iStartTime = iCurrentTime;				//Modified line from FCFS

			iCurrentTime = iCurrentTime + procInfo[i].iBurstTime;		//Extra line from FCFS	
			
			procInfo[i].iFinishTime = procInfo[i].iStartTime + procInfo[i].iBurstTime;	//Modified line from FCFS
			procInfo[i].iTAT = procInfo[i].iWaitTime + procInfo[i].iBurstTime;
	
			procInfo[i].iTBT = 0;	
			
			printf(" %s %d|",procInfo[i].szProcName,iCurrentTime);

			cnt++;
		}
	}
	printf("\n");	
}

int main()	//Everything same as FCFS
{
    int i;
    int totwt=0;
    int tottat=0;

    AcceptProcInfo();	//Step 1: Accept All Process Data
    SortByAT();		//Step 2: Sort All The Process By Arrival Time
    
    ComputeProcTimes();	//Step 3: Calculate StartTime, ArrivalTime, TurnAroundTime
    DisplayProcInfo();	//Step 4: Display The ProcInfo Table

    for(i=0; i<iNoOfProcess; i++)	//Calculate Average WaitTime and TAT
    {
        totwt+= procInfo[i].iWaitTime;
        tottat+= procInfo[i].iTAT;
    }
    
    //Display Average WaitTime and TAT
    printf("\nAverage Waiting time:%f",(float)totwt/iNoOfProcess);	
    printf("\nAverage Turn Around Time:%f",(float)tottat/iNoOfProcess);
    getchar();
    return 0;
}
