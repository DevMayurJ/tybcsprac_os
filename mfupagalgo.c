#include<stdio.h>
//#include<conio.h>

#define MAX_FRAME_CNT 20 
struct node
{
  int iPageNo;
  int iFreq;
}frames[MAX_FRAME_CNT];

int iNoOFFrames;

int CheckPageFault(int iPageNo)
{
  int iFrameIndex;
  for(iFrameIndex = 0; iFrameIndex < iNoOFFrames; iFrameIndex++)
  {
    if(frames[iFrameIndex].iPageNo == iPageNo)
    {
       return iFrameIndex;
    }
  }
   
    return -1;
}

int GetFreeFrame()
{  
    int iFrameIndex;
    for (iFrameIndex = 0; iFrameIndex <= iNoOFFrames; iFrameIndex++)
    {
        if (frames[iFrameIndex].iPageNo == -1)
        {
            return(iFrameIndex);
        }
    }

    return(-1);
}

int get_mfu_frame()
{
  int iFrameIndex;
  int iMfuFrame = 0;
  // select frame number with maximum ref count
  for (iFrameIndex = 1; iFrameIndex < iNoOFFrames; iFrameIndex++)
  {
    if(frames[iFrameIndex].iFreq > frames[iMfuFrame].iFreq)
    {
        iMfuFrame = iFrameIndex;
    }
  }
  
  return iMfuFrame;
}

void Display(int iCurrPage, char *szPageFaultStr)
{
    int iFrameIndex;
    printf("\n%4d\t ", iCurrPage);
    for (iFrameIndex = 0; iFrameIndex < iNoOFFrames; iFrameIndex++)
    {
        printf("%4d:%2d",frames[iFrameIndex].iPageNo, frames[iFrameIndex].iFreq);
    }

    printf(" : %s", szPageFaultStr);
}

int main()
{
    int iFrameNo;
    int iCurrPage;
    int iPageIndex;
    int iFreeFrameNo;
    int iCurrFrameNo;
    int iPageFaults = 0;
    
    int p_request[]={8,5,10,12,10,9,5,10,8,5,1,10,8,1,10};
    int iSize = 15;
   //clrscr();

    printf("\nHow many frames:");
    scanf("%d", &iNoOFFrames);
    //initialize frames
    for (iFrameNo = 0; iFrameNo < iNoOFFrames; iFrameNo++)
    {
        frames[iFrameNo].iPageNo = -1;
        frames[iFrameNo].iFreq = 0;
    }

   printf("\nPageNo     Page Frames              Page Fault");
   printf("\n---------------------------------------------------");
   for(iPageIndex = 0; iPageIndex < iSize; iPageIndex++)
   {
     iCurrPage = p_request[iPageIndex];
     iFrameNo = CheckPageFault(iCurrPage);
     if(iFrameNo ==-1)  
     {
       //page fault occurs
       iFreeFrameNo = GetFreeFrame();
       if (-1 == iFreeFrameNo)
        { 
            //no free frame - do page replacement
            iFreeFrameNo =  get_mfu_frame();
        }

       iPageFaults++;
       frames[iFreeFrameNo].iPageNo = iCurrPage;
       frames[iFreeFrameNo].iFreq = 1;
       Display(iCurrPage, "Yes");
     }
    else 
    {
        //page found in frametable at iFrameNo
       frames[iFrameNo].iFreq++;
       Display(iCurrPage, "NO");
    }
   }

  printf("\n-------------------------------------------------------");
  printf("\n Number of Page Faults=%d", iPageFaults);
  //getch();
}