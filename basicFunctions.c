#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "header.h"

/* Show Welcome message, Do you want to continue & Rules. */
void TextArt()  {
    char ch;
    printf("\n    _____       __ _        _   _       _        _   _    ");
    printf("\n   |_   _|     / _(_)      | \\ | |     | |      | | (_) ");
    printf("\n     | | _ __ | |_ ___  __ |  \\| | ___ | |_ __ _| |_ _  ___  _ __  ");
    printf("\n     | || '_ \\|  _| \\ \\/ / | . ` |/ _ \\| __/ _` | __| |/ _ \\| '_ \\   ");
    printf("\n    _| || | | | | | |>  <  | |\\  | (_) | || (_| | |_| | (_) | | | |  ");
    printf("\n    \\___/_| |_|_| |_/_/\\_\\ \\_| \\_/\\___/ \\__\\__,_|\\__|_|\\___/|_| |_|  ");
    printf("\n                                 _                                   ");
    printf("\n                                | |                                  ");
    printf("\n                                | |_ ___                             ");
    printf("\n                                | __/ _ \\                             ");
    printf("\n                                | || (_) |                            ");
    printf("\n                                 \\__\\___/                             ");
    printf("\n  ______         _    __ _                    ______          __ _      ");
    printf("\n  | ___ \\       | |  / _(_)          ___      | ___ \\        / _(_)     ");
    printf("\n  | |_/ /__  ___| |_| |_ ___  __    ( _ )     | |_/ / __ ___| |_ ___  __");
    printf("\n  |  __/ _ \\/ __| __|  _| \\ \\/ /    / _ \\/\\   |  __/ '__/ _ \\  _| \\ \\/ /");
    printf("\n  | | | (_) \\__ \\ |_| | | |>  <    | (_>  <   | |  | | |  __/ | | |>  < ");
    printf("\n  \\_|  \\___/|___/\\__|_| |_/_/\\_\\    \\___/\\/   \\_|  |_|  \\___|_| |_/_/\\_\\\n");
    printf("\n                   Infix notation to Postfix & Prefix ");
    printf("\n           (Negative numbers and multi-digit are supported)\n");
    do
    {
        printf("\n                       Do you want to continue, y/n? ");
        ch=getchar();
    }
    while ((ch != 'y') && (ch != 'n')); // Ask the user if want to start Simulation or not!
    if(ch == 'y'){
        printf("\n\n Rules: 1) Insert the infix expression without space, e.g. 5*(((7*9)-(8*7))*4)/7.\n");
        printf("        2) Give the negative numbers with this format (-number), e.g. 5*(-7).\n");
        printf("        3) This program supports only these operators: ^, *, /, ~, +, -, =.\n");
        printf("        4) Output format use parentheses with singed number and operators, e.g. (+5) (-7) (*).\n");
        printf(" All other formats are not supported and appear respectively error messages as the case.\n\n");
    }
    if (ch=='n')
        exit(0);
    getchar();
}


/* Show menu and return a valid choice. */
int Menu() {

    char menu;
    int choice;

    do
    {
        printf("\n\n             +============================================+");
        printf("\n             |                    Menu                    |");
        printf("\n             +============================================+");
        printf("\n             |  Options:                                  |");
        printf("\n             |         1. Insert infix notation           |");
        printf("\n             |         2. Display postfix                 |");
        printf("\n             |         3. Display prefix                  |");
        printf("\n             |         4. Exit                            |");
        printf("\n             +============================================+\n");

        printf("\n                 Please, select a option from 1 to 4: ");
        menu=getchar();
        printf("                           Option %c selected.\n",menu);

        if(!((menu=='1') || (menu=='2') ||(menu=='3')||(menu=='4')))
        {
            getchar();
            printf("\n           *** Try to choice between [1 - 4] next time. ***\n\n");
        }
    }
    while (!((menu=='1') || (menu=='2') ||(menu=='3')||(menu=='4')));
    choice = menu -'0' ;
    getchar();
    return choice;
}


/* Processes user choice and do the appropriate function. */
void infixToPostAndPre(){
    TextArt();
    struct treeNode* treeRoot= NULL;
    int choice;
    do {
        choice=Menu() ;

        if (choice==1){
			// Initialization of global pointer.
            headInfix=NULL;
            headPostfix=NULL;
            headOperatorStack=NULL;
            treeStackHead=NULL;

			// Create list with infix expession.
            insertInfix ();
			// Create list with the postfix expession of infix expession.
            createPostFixList ();
			// Create Binary Tree from postfix list.
            treeRoot= createBinaryTree();
        } else if (choice==2){
            if(treeRoot!= NULL){
				// Display postfix with postorder print.
                printf("\nPostfix: ");
                postFix(treeRoot);
            }else{
                printf("\nPlease, insert first Infix notation...");
            }
        } else if (choice==3){
            if(treeRoot!= NULL){
				// Display postfix with preorder print.
                printf("\nPrefix: ");
                preFix(treeRoot);
            }else{
                printf("\nPlease, insert first Infix notation...");
            }
        }
    }while (choice!=4);

	// Free all lists & stacks.
    freeList(1);
    freeList(2);
    freeOperatorStack();
    freeTreeNodeStack();
    printf("\n                               Goodbye !!!\n");
    return ;
}


/* I call the function readInfix and take user's input, 
   then stored in an array the positions of operands and call function tokenazationInput.*/
void insertInfix (){
    char* inputExpretion = readInfix();
    int operatorsPositions[100];
    int symbolCount=0;
    int i;

	// Catch all operands positions & increase symbolCount (the real size of operatorsPositions) .
    for (i=0; i<strlen(inputExpretion); i++) // Catch op positions.
    {
        if (inputExpretion[i]=='^'||inputExpretion[i]=='*'||inputExpretion[i]=='/'||inputExpretion[i]=='~'||inputExpretion[i]=='+'||inputExpretion[i]=='-'||inputExpretion[i]=='('||inputExpretion[i]==')'||inputExpretion[i]=='=')
        {
            operatorsPositions[symbolCount]=i;
            symbolCount++;
        }
    }

	// Call tokenazationInput for separate and save ops & numbers in infixList.
    tokenazationInput(inputExpretion,operatorsPositions,symbolCount);
}


/* Create List postfix using operator stack (use addOperatorStack) when reading
   number entered in the list  when entered the operator adds to the stack. 
   Before add operator to the stack check the priorities of top of stack and current
   operator fron infix and do the right push & pop(use popOperatorStack) , when seen 
   close bracket empty the stack until find the opening of bracket and finally empty 
   the stack. */
void createPostFixList (){

    expesionList* temp =headInfix;
	
	// Crossing infix list check every element.
    while(temp!=NULL)
    {
        if (temp->term[0] == '(')
            addOperatorStack(temp->term);
		// From size of element can see if it's number or operator.
        else if (strlen(temp->term)>1)
            addList(2,temp->term);
        else if (temp->term[0] == ')') {
			// Check if operator stack is empty.
            if(headOperatorStack==NULL){
                addOperatorStack(temp->term);
            }
			// Pop and add elemnts to prostfix list until found the open of parenthesis.
            else{
                while (headOperatorStack->op[0] != '(')
                {
                    addList(2,popOperatorStack());
                }
				// Throw '('.
                popOperatorStack();
            }
		// Pop and add elemnts to prostfix list with precedenceOfOperator in headOperatorStack and curentOperator.
        }else {
		// Check if operator stack is empty.
            if(headOperatorStack==NULL){
                addOperatorStack(temp->term);
            }else{
                while(precedenceOfOperator(headOperatorStack->op) >=  precedenceOfOperator(temp->term))
                {
                    addList(2,popOperatorStack());
					// Check if operator stack is empty.
                    if(headOperatorStack==NULL)
                        break;
                }
                addOperatorStack(temp->term);
            }
        }
		// Next element.
        temp=temp->next;
    }
     // Empty stack and add elements to postfix list.
    while (headOperatorStack != NULL) // Pop from stack till empty 
        addList(2,popOperatorStack());
}

/* Returns an integer corresponding to the priority of the operator given as an argument.*/
int precedenceOfOperator(char* oper)
{
    if(oper[0]=='^')
        return 4;
    else if((oper[0]=='*')||(oper[0]=='~')||(oper[0]=='/'))
        return 3;
    else if((oper[0]=='+')||(oper[0]=='-'))
        return 2;
    else if(oper[0]=='(')
        return 1;
    else if (oper[0]=='=')
        return 0;

    exit(0);
}
