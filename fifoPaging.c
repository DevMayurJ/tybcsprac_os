#include <stdio.h>
#include <stdlib.h>


struct PAGETABLE
{
	int fno;
	int valid;
};

int *frameTable;
int iarrPageString[] = {9,14,10,11,15,9,11,9,15,10,9,15,10,12,15};

struct node
{
	int iPageNo;
	struct node *next;
} *head, *end;

void Append(int iPageNo)
{	
	struct node *newnode;
	newnode = malloc(sizeof(struct node));
	newnode->iPageNo = iPageNo;
	newnode->next = NULL;
	if( head == NULL )
		head = end = newnode;
	else
	{
		end->next = newnode;
		end = newnode;
	}
}

int SelectVictim()
{
	struct node *temp = head;
	int iPageNo = temp->iPageNo;

	head = temp->next;
	free(temp);
	return iPageNo;		
}

int GetFreeFrame(int iNoOfFrames)
{
	int i;
	for(i=0; i<iNoOfFrames; i++)
	{
		if( frameTable[i] == -1 )
			return i;
	}

	return -1;
}

int GetMaxPageNoFromPageString()
{
	int iCnt = 0;
	int iMax = 0;
	for(iCnt=0; iCnt < sizeof(iarrPageString)/sizeof(int); ++iCnt)
	{	
		if( iarrPageString[iCnt] > iMax)
			iMax = iarrPageString[iCnt];
	}

	return iMax;	
}

int main()
{
	int i;
	int iFrameCnt;
	int iFreeFrame;
	int iMaxPageNo;
	int iVictimPage;
	int iDemandedPage;
	int iPageFault = 0;
	int iNoOfFrames = 0;
	struct PAGETABLE *pageTable;

	printf("Enter number of frames : ");
	scanf("%d",&iNoOfFrames);
	system("clear");

	iMaxPageNo = GetMaxPageNoFromPageString();
	
	pageTable = malloc(sizeof(struct PAGETABLE) * (iMaxPageNo+1));
	frameTable = malloc(sizeof(int) * iNoOfFrames);
	
	for(i=0; i<= iMaxPageNo; i++)
		pageTable[i].valid = 0;	

	for(i=0; i<iNoOfFrames; i++)
		frameTable[i] = -1;

	for(i=0; i<sizeof(iarrPageString)/sizeof(int); i++)
	{
		iDemandedPage = iarrPageString[i];	
		printf("\nCurrent page: %2d",iDemandedPage);
		if( pageTable[iDemandedPage].valid == 0 )		
		{
			iPageFault++;
			iFreeFrame = GetFreeFrame(iNoOfFrames);
			if( iFreeFrame != -1 )
			{

				// free frame found for page.
				pageTable[iDemandedPage].fno = iFreeFrame;
				pageTable[iDemandedPage].valid = 1;
				frameTable[iFreeFrame] = iDemandedPage;
			}
			else
			{
				//
				//	Free frame not availabe. Select and remove victim page.
				//
				iVictimPage = SelectVictim();
				pageTable[iDemandedPage].fno = pageTable[iVictimPage].fno;
				pageTable[iVictimPage].valid = 0;
				pageTable[iDemandedPage].valid = 1;
				frameTable[ pageTable[iVictimPage].fno] = iDemandedPage;
			}

			Append(iDemandedPage);
			printf ("\nFrame Table:-\n");
			for(iFrameCnt  =0; iFrameCnt < iNoOfFrames; iFrameCnt++)
			{

				if( frameTable[iFrameCnt] != -1 )
					printf("%2d ",frameTable[iFrameCnt]);

			}

			getchar();
			getchar();
		}
	}

	printf("Total Page Faults Observed : %d\n", iPageFault);
}

