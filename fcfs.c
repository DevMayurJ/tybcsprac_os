#include<stdio.h>
#include<string.h>
#include<conio.h>
#define MAX_PROC_CNT    10

struct ProcInfo
{
    int iArvlTime;
    int iBurstTime;
    char szProcName[10];
}procInfo[MAX_PROC_CNT];


 
int iNoOfProcess;

void SortByAT()
{
    int i;
    int j;
    int iTemp;
    char szTempProcName[10];
    for(i=0; i<iNoOfProcess; i++)
    {
        for(j=0; j<iNoOfProcess; j++)
        {
            if(procInfo[i].iArvlTime < procInfo[j].iArvlTime)
            {
                iTemp=procInfo[i].iArvlTime;
                procInfo[i].iArvlTime = procInfo[j].iArvlTime;
                procInfo[j].iArvlTime=iTemp;
            
                iTemp=procInfo[i].iBurstTime;
                procInfo[i].iBurstTime=procInfo[j].iBurstTime;
                procInfo[j].iBurstTime=iTemp;
            
                strcpy(szTempProcName,procInfo[i].szProcName);
                strcpy(procInfo[i].szProcName,procInfo[j].szProcName);
                strcpy(procInfo[j].szProcName,szTempProcName);
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

main()
{
    int i;
    int star[MAX_PROC_CNT],finish[MAX_PROC_CNT],tat[MAX_PROC_CNT],wt[MAX_PROC_CNT];
    int totwt=0,tottat=0;
//clrscr();

    AcceptProcInfo();
    SortByAT();
    // Calculate start time, waiting and turn around time.
    for(i=0; i<iNoOfProcess; i++)
    {
        if(i==0)
        {
            star[i]= procInfo[i].iArvlTime;
        }
        else
        {
            star[i]=finish[i-1];
        }

        wt[i]=star[i]- procInfo[i].iArvlTime;
        finish[i]=star[i]+ procInfo[i].iBurstTime;
        tat[i]=finish[i]- procInfo[i].iArvlTime;
    }

    printf("\nPName ArivalTime Burstime WaitTime StartTime TAT Finish");
    for(i=0; i<iNoOfProcess; i++)
    {
        printf("\n%s\t%3d\t%3d\t%3d\t%3d\t%6d\t%6d",procInfo[i].szProcName, procInfo[i].iArvlTime,
        procInfo[i].iBurstTime, wt[i],star[i],tat[i],finish[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
    
    printf("\nAverage Waiting time:%f",(float)totwt/iNoOfProcess);
    printf("\nAverage Turn Around Time:%f",(float)tottat/iNoOfProcess);
    getch();
    return 0;
}
