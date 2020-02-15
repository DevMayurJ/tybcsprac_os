#include <stdio.h>
#define	COUNT_PROCESS			5
#define	COUNT_RESOURCE			3

int iarrMax[COUNT_PROCESS][COUNT_RESOURCE] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };
int iarrAllocation[COUNT_PROCESS][COUNT_RESOURCE] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int iarrNeed[COUNT_PROCESS][COUNT_RESOURCE];
char chCompletedStatus[COUNT_PROCESS] = {'f','f','f','f', 'f'};
int iarrAvailable[COUNT_RESOURCE] = {3,3,2};
int iarrRequest[COUNT_RESOURCE] = {0,0,2};

void Display(int arr[5][3]);
int isSafeState();
main()
{
	int i;
	int j;

	//
	//	Calculating need.
	//
	for(i = 0; i < COUNT_PROCESS; i++)
	{
		for(j = 0; j < COUNT_RESOURCE; j++)
		{
			iarrNeed[i][j] = iarrMax[i][j] - iarrAllocation[i][j];
		}
	}

	printf("Allocation\n");
	Display(iarrAllocation);

	printf("Max\n");
	Display(iarrMax);

	printf("Need\n");
	Display(iarrNeed);

	if(isSafeState())
	{
		printf("currently system is in a safe state\n");
	}
	else
	{
		printf("currently system is not in a safe state\n");
	}

	getchar();
	getchar();

	for(j = 0; j< COUNT_RESOURCE; j++)
	{
		if (iarrRequest[j] > iarrNeed[1][j] )
			break;
	}

	if( j < COUNT_RESOURCE)
	{
		printf("request cannot be granted as it is greater than need\n");
	}
	else
	{
		for(j = 0; j < COUNT_RESOURCE; j++)
		{
			if (iarrRequest[j] > iarrAvailable[j] )
			break;
		}

		if (j < COUNT_RESOURCE)
		{
			printf("request cannot be granted as it is greater than available\n");
		}
		else
		{
			for(j = 0; j < COUNT_RESOURCE; j++)
			{
				iarrAllocation[1][j] += iarrRequest[j];
			}

			for(j = 0; j < COUNT_RESOURCE; j++)
			{
				iarrNeed[1][j] -= iarrRequest[j];
			}

			for(j = 0; j < COUNT_RESOURCE; j++)
			{
				iarrAvailable[j] -= iarrRequest[j];
			}

			if( isSafeState())
			{
				printf("Request can be granted immediately\n");
			}
			else
			{
				printf("Request cannot be granted immediately\n");
			}
		}
	}
}

int isSafeState()
{
	int i;
	int j;
	char chStockChanged;
	int iarrTemp[COUNT_RESOURCE];

	for(i = 0; i < COUNT_PROCESS; i++)
	{
		chCompletedStatus[i] = 'f';
	}

	for(i = 0; i < COUNT_RESOURCE; i++)
	{
		iarrTemp[i] = iarrAvailable[i];
	}

	printf("<");
	chStockChanged = 't';
	while (chStockChanged == 't' )
	{
		chStockChanged = 'f';
		for(i = 0; i < COUNT_PROCESS; i++)
		{
			if (chCompletedStatus[i] == 'f')
			{
				for (j = 0; j < COUNT_RESOURCE; j++)
				{
					if (iarrNeed[i][j] > iarrTemp[j])
					{
						break;
					}
				}
	
				if (j == COUNT_RESOURCE)
				{
					printf("p%d,",i);
					chCompletedStatus[i] = 't';
					for (j = 0; j < COUNT_RESOURCE; j++)
					{
						iarrTemp[j] += iarrAllocation[i][j];
					}

					chStockChanged = 't';
				}
			}
		}
	}

	printf(">\n");
	for(i = 0; i < COUNT_PROCESS; i++)
	{
		if (chCompletedStatus[i] == 'f' )
		{
			return 0;
		}
	}

	return 1;
}

void Display(int arr[COUNT_PROCESS][COUNT_RESOURCE])
{
	int i;
	int j;

	for(i = 0; i < COUNT_PROCESS; i++)
	{
		for(j = 0; j < COUNT_RESOURCE; j++)
		{
			printf("%2d", arr[i][j]);	
		}

		printf("\n");	
	}
}

