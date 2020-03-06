#include<stdio.h>
#include<string.h>
#include<conio.h>

char szProcName[10][10];
int arriArvlTime[10], bur[10];
char t[10];
int iNoOfProcess;

void SortByAT()
{
    int i,j;
    int temp;
    for(i=0; i<iNoOfProcess; i++)
    {
        for(j=0; j<iNoOfProcess; j++)
        {
            if(arriArvlTime[i]<arriArvlTime[j])
            {
                temp=arriArvlTime[i];
                arriArvlTime[i]=arriArvlTime[j];
                arriArvlTime[j]=temp;
                temp=bur[i];
                bur[i]=bur[j];
                bur[j]=temp;
                strcpy(t,szProcName[i]);
                strcpy(szProcName[i],szProcName[j]);
                strcpy(szProcName[j],t);
            }
 
        }
    }
}

main()
{
    int star[10],finish[10],tat[10],wt[10],i;
    int totwt=0,tottat=0;
//clrscr();
    printf("Enter the number of processes:");
    //scanf("%d",&iNoOfProcess);
    iNoOfProcess = 3;
    //for(i=0; i<iNoOfProcess; i++)
    //{
        //printf("Enter the ProcessName, arriArvlTimeival Time& Burst Time:");
        //scanf("%s%d%d",&szProcName[i],&arriArvlTime[i],&bur[i]);
    //}

        strcpy(szProcName[0], "p1");
        arriArvlTime[0] = 3;
        bur[0] = 5;

        strcpy(szProcName[1], "p2");
        arriArvlTime[1] = 4;
        bur[1] = 6; 

        strcpy(szProcName[2], "p3");
        arriArvlTime[2] = 2;
        bur[2] = 7;         


    SortByAT();
    // Calculate waiting and turn around time.
    for(i=0; i<iNoOfProcess; i++)
    {
        if(i==0)
            star[i]=arriArvlTime[i];
        else
            star[i]=finish[i-1];
        wt[i]=star[i]-arriArvlTime[i];
        finish[i]=star[i]+bur[i];
        tat[i]=finish[i]-arriArvlTime[i];
    }

    printf("\nPName arriArvlTimetime Burtime WaitTime StartTime TAT Finish");
    for(i=0; i<iNoOfProcess; i++)
    {
        printf("\n%s\t%3d\t%3d\t%3d\t%3d\t%6d\t%6d",szProcName[i],arriArvlTime[i],bur[i],wt[i],star[i],tat[i],finish[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
    
    printf("\nAverage Waiting time:%f",(float)totwt/iNoOfProcess);
    printf("\nAverage Turn Around Time:%f",(float)tottat/iNoOfProcess);
    getch();
    return 0;
}