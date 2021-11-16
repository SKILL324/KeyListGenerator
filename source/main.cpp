#include "Sequence.h"

int main()
{
	int x = 0;
	do
	{ 
	printf("1.Generate keys\n");
	printf("2.Edit keys\n");
	printf("3.Exit\n");
	printf(">>");
	scanf_s("%d", &x);
	system("cls");
	switch (x)
	{
	case 1:
		
		if (!GenerateKeys())
		{
			printf("Error GenerateKeys.\n");
			return 0;
		}
		break;

	case 2:
		if (!EditFileKeys())
		{
			printf("Error EditFileKeys.\n");
			return 0;
		}
		break;
	}
	system("cls");
	} while (x != 3);
	return 0;
}

