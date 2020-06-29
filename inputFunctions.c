#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "header.h"

/* Dynamic reading input from the user and check whether it is valid.
   Checking for brackets if starts or ends with operator, if only given 
   a number only, if we use operator after operator (not mentioned in 
   parentheses), if only pressed the Enter key and if you are opening 
   and closing brackets without content above all controlled by special 
   functions. Finally, it returns a pointer to the contents of user input.
*/
char* readInfix(){
    int properFormat;
    int position;
    int size ;
    char* inFix =NULL;
    printf("\nPlease enter a Numeric expression: ");
	
    do{
        properFormat=0;
        position = 0;
        size = 2; // Maximum read length it's 2 because must take and final null-character.
        inFix = (char*)malloc(size);
        /* Fgets(pointer to the string read is stored, max num of chars to be read with 
		   final null-character,the stream where characters are read from). */
		   
        while(fgets((inFix + position), size, stdin) != NULL)
        {
            if(strchr(inFix, '\n')) // if last char is '\n' stop
            {
                break;
            }
            else
            {				
                position = position + 1; // Increase position.
                inFix = (char*)realloc(inFix, position + size);  //Dynamic memory allocation always in pairs.
            }
        }
		
        if (checkValidity(inFix)==0) // Maybe it contains a space and crash the rest checks.
            printf("\nInvalid numeric expression: Use characters that do not belong to a numeric expression.");
        else{
            if (checkParenthesis(inFix)==0) 
                printf("\nInvalid numeric expression: Problem with the number of Parentheses.");
            if (checkStartAndEnd(inFix)==0) 
                printf("\nInvalid numeric expression: Use operands at the beginning or at the end of the numeric expression.");
            if (checkOnlyNumber(inFix)==0) 
                printf("\nInvalid numeric expression: Use only a number and no operators.");
            if (checkOpAfterOp(inFix)==0) 
                printf("\nInvalid numeric expression: Use operator after operator e.g. *-.");
            if (checkParenthesisAfterParenthesis(inFix)==0) //
                printf("\nInvalid numeric expression: Use open and close parentheses without content e.g. ().");

			// ProperFormat MUST BE equal with 6 for have right input format.
            properFormat = properFormat+ checkValidity(inFix);
            properFormat = properFormat+ checkParenthesis (inFix);
            properFormat = properFormat+ checkStartAndEnd(inFix);
            properFormat = properFormat+ checkOnlyNumber(inFix);
            properFormat = properFormat+ checkOpAfterOp(inFix);
            properFormat = properFormat+ checkParenthesisAfterParenthesis(inFix);
        }
		
		// ProperFormat MUST BE equal with 6 for have right input format.
        if((properFormat!=6) || (checkValidity(inFix)==0))
        {
            printf("\nPlease give again a Numeric expression: ");
            free(inFix);
        }
    }while (properFormat!=6);
	
    return inFix;
}


 /* Checking for brackets using the lemma brackets takes as 
    input parameter the user and returns 1 for valid format 
	and 0 for non-valid. */
int checkParenthesis(char* input){
    int count=0;
    int i;
    for (i=0; i<strlen(input); i++)
    {
        if (input[i]=='(')
            count++;
        if (input[i]==')')
            count--;
    }
    if (count==0) 
        return 1; // It's ok !!!!
    else
        return 0; // It's ok !!!!
}

/* Checking if starts or ends with operator takes as input 
   parameter the user and returns 1 for valid format and 0 
   for non-valid. */
int checkStartAndEnd(char* input){
    if ((input[0]=='^')||(input[0]=='*')||(input[0]=='/')||(input[0]=='~')||(input[0]=='+')||(input[0]=='-')||(input[0]==')')||(input[0]=='='))
        return 0;

    if ((input[strlen(input)-2]=='^')||(input[strlen(input)-2]=='*')||(input[strlen(input)-2]=='/')||(input[strlen(input)-2]=='~')||(input[strlen(input)-2]=='+')||(input[strlen(input)-2]=='-')||(input[strlen(input)-2]=='(')||(input[strlen(input)-2]=='='))
        return 0;

    return 1;
}

/* Checking if use non-accept operands and symbol takes as 
   input parameter the user and returns 1 for valid format 
   and 0 for non-valid. */
int checkValidity(char* input){
    int i;
    if(input[0]=='\n')
        return 0;
    for (i=0; i<strlen(input)-1; i++) // Catch op positions.
    {
        if ((input[i]=='^')||(input[i]=='*')||(input[i]=='/')||(input[i]=='~')||(input[i]=='+')||(input[i]=='-')||(input[i]=='(')||(input[i]==')')||(input[i]=='=')||(isdigit(input[i])))
        {
            // Do nothing
        }
        else
        {
            return 0;
        }
    }
    return 1;

}

/* Checking if only given a number only takes as input 
   parameter the user and returns 1 for valid format 
   and 0 for non-valid. */
int checkOnlyNumber(char* input){
    int i;
    int count=0;

    for (i=0; i<strlen(input)-1; i++) // Catch op positions.
    {
        if (isdigit(input[i])!=0)
            count++;
    }

    if(count==(strlen(input)-1))
        return 0;
    else
        return 1;
}

/* Checking if we use operator after operator (not mentioned 
   in parentheses) takes as input parameter the user and 
   returns 1 for valid format and 0 for non-valid. */
int checkOpAfterOp (char* input){
    int i;
    int first;
    int after;

    for (i=0; i<strlen(input)-2; i++) // Catch op positions.
    {
        first=0;
        after=0;
        if ((input[i]=='^')||(input[i]=='*')||(input[i]=='/')||(input[i]=='~')||(input[i]=='+')||(input[i]=='-')||(input[i]=='='))
            first=1;
        if ((input[i+1]=='^')||(input[i+1]=='*')||(input[i+1]=='/')||(input[i+1]=='~')||(input[i+1]=='+')||(input[i+1]=='-')||(input[i+1]=='='))
            after=1;

        if((first==1)&&(after==1))
            return 0;
    }

    return 1;
}

/* Checking if  open and close brackets without content takes 
   as input parameter the user and returns 1 for valid format 
   and 0 for non-valid. */
int checkParenthesisAfterParenthesis (char* input){
    int i;
    int first;
    int after;

    for (i=0; i<strlen(input)-2; i++) // Catch op positions.
    {
        first=0;
        after=0;
        if (input[i]=='(')
            first=1;
        if (input[i+1]==')')
            after=1;

        if((first==1)&&(after==1))
            return 0;
    }
    return 1;
}

/* Returns the number of digits in the number given as argument 
   through a mathematical formula(floor(log10(abs(numberCheck))) 
   + 1). */
int numberOfDigits(int numberCheck){
    if(numberCheck==0)
        return 1;
    else
        return  (floor(log10(abs(numberCheck))) + 1);
}

 /* Separates the user input to numbers (positive and negative) & operator's 
    and stores them in infix list. Accepts as parameters the user input, the 
	table with the positions of operators and the size of the table of 
	operators positions.*/
void tokenazationInput(char* input,int* operatorsPositions, int size ){
    int i,j;
    int tempNumber;
    int power;

	// Check all operators.
    for(i=0; i<=size; i++) 
    {
        power=-1;
        tempNumber=0;

        if(i<size-2) //Look @ 2 position fRONT.
        {
            if((input[operatorsPositions[i]]=='(')&&(input[operatorsPositions[i+1]]=='-')&&(input[operatorsPositions[i+2]]==')'))  //paretn(...-...) || (...-) || (-...).
            {
				// patern (-...)
                if((input[operatorsPositions[i]]=='(')&&(input[operatorsPositions[i]+1]=='-'))
                {
                    for(j=operatorsPositions[i+2]-1; j>operatorsPositions[i+1]; j--)
                    {
                        power++;
                        tempNumber =tempNumber + (input[j]-'0')*ceil((pow(10,power)));
                    }
                    setExpessionElement(1,'#','-',tempNumber);
                    i=i+2;
                    continue;
                }
            }

        }

        if(i==0)
        {
            if(input[operatorsPositions[i]]=='(')
            {
                setExpessionElement(1,'$',input[operatorsPositions[i]],' ');
                continue;
            }
            for(j=operatorsPositions[i]-1; j>=0; j--)
            {
                power++;
                tempNumber =tempNumber + (input[j]-'0')*ceil((pow(10,power)));
            }
            setExpessionElement(1,'#','+',tempNumber);
        }
        else if(i==size)
        {
            if(input[operatorsPositions[size-1]]==')')
            {
                //Do nothing.
            }
            else if(strlen(input)-operatorsPositions[size-1]>=2)
            {
                for(j=strlen(input)-2; j>operatorsPositions[size-1]; j--)
                {
                    power++;
                    tempNumber =tempNumber + (input[j]-'0')*ceil((pow(10,power)));
                }

                setExpessionElement(1,'#','+',tempNumber);
            }
        }
        else
        {
            if((operatorsPositions[i]-operatorsPositions[i-1]>=2))
            {
                for(j=operatorsPositions[i]-1; j>operatorsPositions[i-1]; j--)
                {
                    power++;
                    tempNumber =tempNumber + (input[j]-'0')*ceil((pow(10,power)));
                }
                setExpessionElement(1,'#','+',tempNumber);

            }
        }
        if(i!=size)
            setExpessionElement(1,'$',input[operatorsPositions[i]],' ');
    }
}

