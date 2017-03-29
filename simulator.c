#include<stdio.h>
#include<stdlib.h>

#define MAX_NO_OF_LINES				1000


int main()
{
	FILE *fp;
	int iOpcode;
	int iAddress;
	int iOperand1;
	int iOperand2;
	int iNoOfLines;
	int iRegisterNo;
	int iInstruction;
	int iarrRegister[4];
	char szFileName[50];
	int iProogramCounter;
	long larrMemory[MAX_NO_OF_LINES];

	printf("\n Enter File name:-");
	scanf("%s", szFileName);
	//
	//	Opening file in read mode.
	//
	fp = fopen(szFileName,"r");
	if(NULL == fp)
	{
		printf("\nFile opening Error!!!");
		exit(0);
	}
	else
	{
		iNoOfLines = 0;
		while (!feof(fp))
		{
			//
			//	Copying every instruction from file.
			//
			fscanf(fp,"%ld",&larrMemory[iNoOfLines]);
			iNoOfLines++;
		}

		fclose(fp);
	}

	iProogramCounter = 0;
	while(1)
	{
		//
		//	Getting one instruction at time.
		//
		iInstruction = larrMemory[iProogramCounter++];
		//
		//	Separating operand, opecode from instruction.
		//
		iAddress = iInstruction%1000;
		iInstruction = iInstruction/1000;
		iRegisterNo = iInstruction%10;
		iOpcode = iInstruction/10;
		//
		//	Performing operation according to opcode.
		//
		switch(iOpcode)
		{
			case 1:
				//	ADD
				iarrRegister[iRegisterNo - 1] += larrMemory[iAddress];
				break;
			case 2 :
				//	SUB
				iarrRegister[iRegisterNo - 1] -= larrMemory[iAddress];
				break;
			case 3 :
				//	MULT
				iarrRegister[iRegisterNo - 1] *= larrMemory[iAddress];
				break;
			case 4 :
				//	MOVER
				iarrRegister[iRegisterNo - 1] = larrMemory[iAddress];
				break;
			case 5 :
				//	MOVEM
				larrMemory[iAddress] = iarrRegister[iRegisterNo - 1];
				break;
			case  6 :
				//	COMP
				iOperand1 = iarrRegister[iRegisterNo - 1];
				iOperand2 = larrMemory[iAddress];
				break;
			case 7 :
				//	BC
				switch(iRegisterNo)
				{
					case 0:
						if (iOperand1 < iOperand2)
							iProogramCounter = iAddress;
					break;
					case 1:
						if(iOperand1 <= iOperand2)
							iProogramCounter = iAddress;
					break;
					case 2:
						if(iOperand1 == iOperand2)
							iProogramCounter = iAddress;
						break;
					case 3:
						if(iOperand1 > iOperand2)
							iProogramCounter = iAddress;
						break;
					case 4:
						if(iOperand1 >=iOperand2)
						iProogramCounter = iAddress;
						break;
					case 5:
						iProogramCounter = iAddress;
						break;
					default:printf("\n Invalid Relational operator!!!");
						break;
				}
				break;
			case 8:
				//	DIV
				if(larrMemory[iAddress]==0)
					printf("\n Divide by zero is notdefined!!!");
				else
					iarrRegister[iRegisterNo - 1] /= larrMemory[iAddress];
				break;
			case 9:
				//	READ
				printf("\n Input: ");
				scanf("%ld",&larrMemory[iAddress]);
				break;
			case 10 :
				//	PRINT
				printf("\n Output: %ld \n\n",larrMemory[iAddress]);
				break;
			case 11 :
				//	STOP
				exit(0);
			default:printf("\n Invalid opcode");
				exit(0);
			}
	}
}

