//DFA Driver
#include<stdio.h>
#include<string.h>

char szIpSym[10];

int GetIndexNo(char chSym, int iNoOfIPSym)
{	
	int k;
	for (k = 0; k < iNoOfIPSym; k++)
	{
		if(chSym == szIpSym[k])
		{
			return k;
		}
	}

	return -1;
}

main()
{
	int i;
	int j;
	int iFlag;
	char chSym;
	int iIpLength;
	int iNoOfFinal;
	int iNoOfIPSym;
	int iWantToExit;
	int iNoOfStates;
	int iCurrentState;
	int iUpdatedState;
	char szIpString[50];
	int iCurrentSymIndex;
	int iarrDelta[20][10];
	int iarrFinalState[10];

	//accept no of states.
	iNoOfStates = 0;
	printf("\n How many no of states?");
	scanf("%d",&iNoOfStates);
	
	//accept input symbols as a string.
	printf("\nEnter input symbols:- ");
	scanf("%s",&szIpSym);	
	iNoOfIPSym = strlen(szIpSym);
	
	//accept delta table.
	printf("\n\t\t  ** Enter details of transitions ** \n\n ");
	for (i = 0; i < iNoOfStates; i++)
	{
		for (j = 0; j < iNoOfIPSym; j++)
		{
			printf("\nwhere to go from Q%d on %c : ",i,szIpSym[j]);	
			scanf("%d",&iarrDelta[i][j]);
		}
	}

	//accept no of final states.
	printf("\n How many final states? : ");
	scanf("%d",&iNoOfFinal);

	//accept final states.
	printf("\n Enter final state : ");
	for (i = 0; i < iNoOfFinal; i++)
	{
		scanf("%d",&iarrFinalState[i]);
	}

	//print delta.
	printf("\n*** DELTA ***\n delta |");
	for (j = 0; j < iNoOfIPSym; j++)
	{
		printf(" %c \t", szIpSym[j]);
	}

	printf("\n------------------------------------------\n");	
	for(i = 0; i < iNoOfStates; i++)
	{
		printf("    q%d |",i);
		for(j = 0; j < iNoOfIPSym; j++)
		{	
			printf(" %d\t", iarrDelta[i][j]);		
		}

		printf("\n------------------------------------------\n");
	}

	while(1)
	{
		iCurrentState = 0;
		printf("\n Enter the input string : ");
		scanf("%s", &szIpString);
		iIpLength = strlen(szIpString);
		j=0;
		i=0;

		for (i = 0; i < iIpLength; i++)
		{
			//take current sym from input string.
			chSym = szIpString[i];
			iCurrentSymIndex = GetIndexNo(chSym, iNoOfIPSym);
			if (-1 == iCurrentSymIndex)
			{
				printf("\nInvalid input symbol");
				exit(0);
			}

			iUpdatedState = iarrDelta[iCurrentState][iCurrentSymIndex];
			printf("  \tQ%d\t\t%c\tQ%d\t\t  Q%d\t\n ",iCurrentState,chSym,iUpdatedState,iUpdatedState);
			iCurrentState = iUpdatedState;
		}

		//String over.Check current state in final state.
		iFlag = 0;
		for (i=0; i < iNoOfFinal && 0 == iFlag; i++)
		{
			if(iCurrentState == iarrFinalState[i])
			{
				iFlag = 1;
				break;
			}
		}

		if(1 == iFlag)
		{
			printf("\n%s is Accepted by DFA.\n", szIpString);
		}
		else if(0 == iFlag)
		{	
			printf("\n%s is Rejected by DFA.\n", szIpString);
		}

		printf("\n\nDo you want to check another string?(1/0):-");
		scanf("%d", &iWantToExit);
		
		if(0 == iWantToExit)
		{
			break;
		}
	}//while end

	printf("\nBye\n");
}//main end
