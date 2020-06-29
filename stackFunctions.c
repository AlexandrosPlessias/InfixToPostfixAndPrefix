#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "header.h"

/* Adds to the stack operator given as an argument. */
void addOperatorStack(char* oper){
    operatorStack *newOperator;
    newOperator = (operatorStack*) malloc( sizeof( operatorStack ));   // Memory allocation to create new nodes.

	 // If space available.
    if ( newOperator != NULL )      {
        newOperator->op=oper;	// Copies of user data at new node.
		// The Memory allocation from before is a node of the stack, which linked in stack with next. 
        newOperator->next = headOperatorStack; 
        headOperatorStack=newOperator;  // Now this node becomes the new head of the stack.
    }else{
        printf("No memory available.\n" );
        exit(0);
    }
}

/* Returns the value (operator) who is the head of the stack and releases it. */
char* popOperatorStack(){
	
    operatorStack *nextOperator=NULL;	// Utility pointers.
    char * headOperator=headOperatorStack->op;	// Get head operator.
    nextOperator=headOperatorStack->next;	// Save headOperatorStack->next node.
    free(headOperatorStack);	// Free head.
    headOperatorStack=nextOperator;	// New head is next of previous head.
    return headOperator;	// Return head operator.
}

/* Empty the stack. */
void freeOperatorStack(){
    // Utility pointers.
    operatorStack *nextOperator;
    operatorStack *temp=headOperatorStack;
    while(temp!=NULL)
    {     
        nextOperator=temp->next;	// NextOperator shows at next node of stack.  
        free(temp);					// Free current node.
        temp=nextOperator;	 		// Show in next node of stack.
    }
}

