#include<stdio.h>
#include<string.h>
#define MAX_PROC_CNT    10

struct ProcInfo
{
    int iArvlTime;
    int iBurstTime;
    char szProcName[10];
    int iStartTime;
    int iFinishTime;
    int iTAT;
    int iWaitTime;
}procInfo[MAX_PROC_CNT];


 
int iNoOfProcess;

void SortByAT()
{
    int i;
    int j;
    for(i=0; i<iNoOfProcess; i++)
    {
        for(j=0; j<iNoOfProcess; j++)
        {
            if(procInfo[i].iArvlTime < procInfo[j].iArvlTime)
            {
		struct ProcInfo tempProcInfo;
		tempProcInfo = procInfo[i];
		procInfo[i] = procInfo[j];
		procInfo[j] = tempProcInfo;

          }
 
        }
    }
}


void AcceptProcInfo()
{
    int i;
    printf("Enter the number of processes:");
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

        strcpy(procInfo[1].szProcName, "p2");
        procInfo[1].iArvlTime = 4;
        procInfo[1].iBurstTime = 6; 

        strcpy(procInfo[2].szProcName, "p3");
        procInfo[2].iArvlTime = 2;
        procInfo[2].iBurstTime = 7;         
}

void DisplayProcInfo()
{
    int i;
    printf("\nPName ArivalTime Burstime WaitTime StartTime TAT Finish");
    for(i=0; i<iNoOfProcess; i++)
    {
        printf("\n%s\t%3d\t%3d\t%3d\t%3d\t%6d\t%6d",procInfo[i].szProcName, procInfo[i].iArvlTime,
        procInfo[i].iBurstTime, procInfo[i].iWaitTime, procInfo[i].iStartTime,
procInfo[i].iTAT, procInfo[i].iFinishTime);
    }
}

void ComputeProcTimes()
{
    int i;
    // Calculate start time, waiting and turn around time.
    for(i=0; i<iNoOfProcess; i++)
    {
        if(i==0)
        {
            procInfo[i].iStartTime= procInfo[i].iArvlTime;
        }
        else
        {
            procInfo[i].iStartTime= procInfo[i - 1].iFinishTime;
        }

        procInfo[i].iWaitTime = procInfo[i].iStartTime - procInfo[i].iArvlTime;
        procInfo[i].iFinishTime = procInfo[i].iStartTime + procInfo[i].iBurstTime;
        procInfo[i].iTAT = procInfo[i].iFinishTime - procInfo[i].iArvlTime;
    }

}


void main()
{
    int i;
    int totwt=0;
    int tottat=0;

    AcceptProcInfo();
    SortByAT();

    ComputeProcTimes();
    DisplayProcInfo();

    for(i=0; i<iNoOfProcess; i++)
    {
        totwt+= procInfo[i].iWaitTime;
        tottat+= procInfo[i].iTAT;
    }
    
    printf("\nAverage Waiting time:%f",(float)totwt/iNoOfProcess);
    printf("\nAverage Turn Around Time:%f",(float)tottat/iNoOfProcess);
    getchar();
    return 0;
}
