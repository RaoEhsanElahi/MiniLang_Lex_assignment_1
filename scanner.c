#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TestFile1.h"
#include "TestFile2.h"
#include "TestFile3.h"

// Define token types
#define INTEGER 1
#define BOOLEAN 2
#define OPERATOR 3
#define ASSIGNMENT 4
#define EQUALITY 5
#define INEQUALITY 6
#define KEYWORD 7
#define IDENTIFIER 8
#define LITERAL 9
#define COMMENT 10
#define ERROR 11

// Function to check if a string is a keyword
int isKeyword(char *lexeme)
{
    char *keywords[] = {"if", "else", "print", "true", "false"};
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(lexeme, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char c)
{
    char operators[] = {'+', '-', '*', '/', '=', '=', '!'};
    for (int i = 0; i < 7; i++)
    {
        if (c == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

// Function to tokenize a line of code
void tokenizeLine(char *line, int line_num)
{
    char *token;
    token = strtok(line, " \t");
    while (token != NULL)
    {
        // Check for comments
        if (strstr(token, "//") != NULL)
        {
            printf("Token Type: COMMENT, Lexeme: %s\n", token);
            return;
        }
        // Check for symbols
        if (isalpha(token[0]) || isdigit(token[0]))
        {
            if (isKeyword(token))
            {
                printf("Token Type: KEYWORD, Lexeme: %s\n", token);
            }
            else if (isOperator(token[0]))
            {
                printf("Token Type: OPERATOR, Lexeme: %s\n", token);
            }
            else if (isdigit(token[0]))
            {
                printf("Token Type: INTEGER, Lexeme: %s\n", token);
            }
            else if (strcmp(token, "true") == 0 || strcmp(token, "false") == 0)
            {
                printf("Token Type: BOOLEAN, Lexeme: %s\n", token);
            }
            else
            {
                printf("Token Type: IDENTIFIER, Lexeme: %s\n", token);
            }
        }
        else
        {
            printf("Token Type: ERROR, Lexeme: %s\n", token);
        }
        token = strtok(NULL, " \t");
    }
}

// Function to scan the file
void scanFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    char line[100];
    int line_num = 1;
    while (fgets(line, sizeof(line), file))
    {
        printf("Line %d:\n", line_num);
        tokenizeLine(line, line_num);
        line_num++;
    }
    fclose(file);
}

int main()
{
    char filename[100] = "file1.h"; // TestFile name.
    scanFile(filename);
    return 0;
}
