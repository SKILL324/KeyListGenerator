#include "Sequence.h"

void Sequence_Conversion(char* sequence, char* buffer)
{
	for (int i = 0; i < SEQUENCE_SIZE; i++)
	{
		if (sequence[i] == LOWERCASE)
		{
			rndCharacter(&buffer[i], Lower);
		}
		else if(sequence[i] == UPPERCASE)
		{
			rndCharacter(&buffer[i], Upper);
		}
		else if (sequence[i] == NUMBER)
		{
			rndNumber(&buffer[i]);
		}
	}
}

void Sequence_Loop(char* sequence)
{
	printf("UPPERCASE = 2, LOWERCASE = 1, NUMBER = 0, MAX = 50, Ex: 100101010010 \n");
	printf("Sequence: ");
	scanf_s("%s", sequence, 20);
	int validate = 1;
	for (int i = 0; i < 20; i++)
	{
		if (sequence[i] == '2' || sequence[i] == '1' || sequence[i] == '0')
			continue;
		else if (sequence[i] == '\0')
		{
			break;
		}
		else
		{
			validate = 0;
			break;
		}
	}
	if (validate == 0)
		Sequence_Loop(sequence);
}

int Sequence_Validate(char* sequence)
{
	int j = strlen(sequence);

	for (int i = 0; i <= j; i++)
	{
		if (isalpha(sequence[i]))
		{
			printf("Invalid sequence. (Type only '0' , '1' , '2')\n");
			return(0);
		}
	}
	return(1);
}
void rndCharacter(char* rdChar, unsigned int case_type)
{
	switch (case_type)
	{
	case Lower:
		*rdChar = (char)(rand() % (122 + 1 - 97) + 97);
		break;
	case Upper:
		*rdChar = (char)(rand() % (90 + 1 - 65) + 65);
		break;
	case BothCase:
		if ((rand() % (10 + 1 - 0) + 0) >= 5)
			*rdChar = (char)(rand() % (122 + 1 - 97) + 97);
		else
			*rdChar = (char)(rand() % (90 + 1 - 65) + 65);
		break;
	}

}

void rndNumber(char* rdChar)
{
	*rdChar = (char)(rand() % (57 + 1 - 48) + 48);
}

FILE* CreateFile(const char* path, const char* mode)
{
	FILE* hFile;
	fopen_s(&hFile, path, mode);
	if (!hFile)
		return NULL;
	else
		return hFile;
}

int FileWriteLine(char* buffer, FILE* hFile)
{
	if (fprintf(hFile, "%s\n", buffer))
		return 1;
	else
		return 0;
}

int GenerateKeys()
{
	char* sequence = (char*)calloc(SEQUENCE_SIZE, sizeof(char));
	char* buffer = (char*)calloc(SEQUENCE_SIZE, sizeof(char));
	FILE* hFile;

	do
	{
		Sequence_Loop(sequence);
	} while (!Sequence_Validate(sequence));

	int number_words = 0;
	do
	{
		printf("Number of words: ");
		scanf_s("%d", &number_words);
		printf("\n");
	} while (isalnum(number_words) != 0 || number_words <= 1);
	
	
	if (!(hFile = CreateFile("Sequence.txt","w+")))
	{
		printf("Failed To Create/Write on hFile.\n");
		return 0;
	}

	static char** file_words;
	int sequence_size = (int)strlen(sequence);
	if (file_words = (char**)calloc(number_words + 1, sizeof(*file_words)))
	{
		for (int i = 0; i < number_words; i++)
		{
			Sequence_Conversion(sequence, buffer);
			*(file_words + i) = (char*)calloc(sequence_size + 1, sizeof(*(file_words + i)));
			if (*(file_words + i) != NULL)
			{
				strcpy_s(*(file_words + i), sizeof(*(file_words + i)) * sequence_size, buffer);
			}
		}
	}
	else
	{
		fprintf(stdout, "Error file_words malloc!\n");
		return;
	}
	*(file_words + number_words) = (char*)calloc(sequence_size, sizeof(char));
	*(file_words + number_words) = '\0';

	int j = 0;
	int cmp_result;
	char* temp = (char*)calloc(sequence_size, sizeof(temp));
	if (!temp)
	{
		fprintf(stdout, "Error temp calloc!\n");
		return;
	}

	int loop = 1, word_changed = 0;
	while (loop)
	{
		cmp_result = strcmp(*(file_words + j + 1), *(file_words + j));
		if (cmp_result < 0)
		{
			strcpy_s(temp, sizeof(temp) * sequence_size, file_words[j]);
			strcpy_s(file_words[j], sizeof(file_words[j]) * sequence_size, file_words[j + 1]);
			strcpy_s(file_words[j + 1], sizeof(file_words[j + 1]) * sequence_size, temp);
			word_changed = 1;

		}

		j++;

		if (file_words[j + 1] == NULL && word_changed == 0)
		{
			loop = 0;
			break;
		}

		if (file_words[j + 1] == NULL)
		{
			j = 0;
			word_changed = 0;
		}
	}

	int i = 0;
	while (file_words[i] != NULL)
	{
		if (file_words[i + 1] != NULL)
		{
			if (strcmp(*(file_words + i), *(file_words + i + 1)) != 0)
			{
				FileWriteLine(*(file_words + i), hFile);
				printf("%s\n", *(file_words + i));
			}
				
		}
		else
		{
			FileWriteLine(*(file_words + i), hFile);
			printf("%s\n", *(file_words + i));
		}
		i++;
	}

	i = 0;
	while (*(file_words + i) != NULL)
	{
		//realloc(0,*(file_words + i++));
		free(*(file_words + i++));
	}
	printf("\nSucess!\n");
	printf("Data Saved on Sequence.txt.\n");
	system("pause");
	fclose(hFile);
	free(buffer);
	free(sequence);
	return 1;
}

int EditFileKeys()
{
	char* text1 = (char*)calloc(SEQUENCE_SIZE, sizeof(char));
	char* text2 = (char*)calloc(SEQUENCE_SIZE, sizeof(char));
	int text_index = 0;
	FILE* hFile;
	FILE* hNFile;

	char* buffer = (char*)calloc(SEQUENCE_SIZE*2, sizeof(char));
	char* text_edited = (char*)calloc(SEQUENCE_SIZE * 2, sizeof(char));

	if (!(hFile = CreateFile("Sequence.txt", "r")))
	{
		printf("Failed To Read file.\n");
		return 0;
	}
	if (!(hNFile = CreateFile("Sequence_Edited.txt", "w")))
	{
		printf("Failed To Create file.\n");
		return 0;
	}

	printf("Response = '0' (skip)\n\n");
	printf("(Start) Text to concatenate: ");
	scanf_s("%s", text1, SEQUENCE_SIZE);
	if (text1[0] == '0')
		text1[0] = '\0';
	printf("(End) Text to concatenate: ");
	scanf_s("%s", text2, SEQUENCE_SIZE);
	if (text2[0] == '0')
		text2[0] = '\0';
	printf("\n");
	

	for (int i = 0; !feof(hFile); i++) //i <= 100
	{
		FileReadLine("Sequence.txt", buffer, hFile);
		if (buffer[strlen(buffer) - 1] == '\n')
			buffer[strlen(buffer) - 1] = '\0';

		ConcatenateText(text_edited, text1, text2, buffer);
		FileWriteLine(text_edited, hNFile);
	}
	printf("Sucess!\n");
	printf("Data Saved on Sequence_Edited.txt\n");
	system("pause");
	fclose(hFile);
	free(text1);
	free(buffer);
	free(text_edited);
	return 1;
}

int FileReadLine(const char* path, char* buffer, FILE* hFile)
{
	fgets(buffer, SEQUENCE_SIZE, hFile);
	return 0;
}

void ConcatenateText(char* text_edited, char* string1, char* string2, char* string3)
{
	memset(text_edited, 0, sizeof(char) * SEQUENCE_SIZE * 2);
	strcpy_s(text_edited, sizeof(char) * SEQUENCE_SIZE * 2, string1);
	strcat_s(text_edited, sizeof(char) * SEQUENCE_SIZE * 2, string3);
	strcat_s(text_edited, sizeof(char) * SEQUENCE_SIZE * 2, string2);
}