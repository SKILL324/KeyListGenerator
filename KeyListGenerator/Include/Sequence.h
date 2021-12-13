#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Sequence.h"
#define SEQUENCE_SIZE 50
#define NUMBER '0'
#define CHARACTER '1'

enum CASE 
{
	Lower, Upper, BothCase
};

enum Textpos
{
	Start = 1, End, BothPos
};

void Sequence_Conversion(char* sequence, char* buffer);
void Sequence_Loop(char* sequence);
int Sequence_Validate(char* sequence);
void rndCharacter(char* rdChar, unsigned int case_type);
void rndNumber(char* rdChar);
FILE* CreateFile(const char* path, const char* mode);
int FileWriteLine(char* buffer, FILE* hFile);
int GenerateKeys();
int EditFileKeys();
int FileReadLine(const char* path, char* buffer, FILE* hFile);
void ConcatenateText(char* text_edited, char* string1, char* string2, char* string3);