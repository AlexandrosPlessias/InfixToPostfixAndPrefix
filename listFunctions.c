#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "header.h"

/* Add the element of expression list (simple) with the 
   corresponding code (1 for infix & 2 for postfix). */
void addList (int expesionCode, char* termIn){
    // Utility pointers.
    expesionList *newTerm;
    expesionList *temp;
    newTerm = (expesionList*) malloc( sizeof( expesionList ));   // Memory allocation to create new node.

    if ( newTerm != NULL )    // If space available.
    {
        newTerm->term=termIn; // Copies of user data at new node.
        newTerm->next=NULL;

        if(expesionCode==1)
        {
            if(headInfix==NULL) 
            {
                headInfix=newTerm;
            }
            else
            {
				// Utility shows at the head.
                temp=headInfix;
                while(temp->next!= NULL)
                {
                    temp=temp->next;
                }
                temp->next=newTerm; // Add @ end of list.
            }
        }
        else if(expesionCode==2)
        {
            if(headPostfix==NULL)
            {
                headPostfix=newTerm;
            }
            else
            {
				// Utility shows at the head.
                temp=headPostfix;
                while(temp->next!= NULL)
                {
                    temp=temp->next;
                }
                temp->next=newTerm; // Add @ end of list.
            }
        }
        else
        {
            printf("WRONG LIST CODE !!!\n");
            exit(0);
        }
    }
    else
    {
        printf("No memory available.\n" );
        exit(0);
    }
}

/* Empty the list (singlet) with the corresponding code 
   (1 for infix & 2 for postfix). */
void freeList(int expesionCode){
	 // Utility pointers.
    expesionList *temp;
    expesionList *nextTerm;

	 // Utility shows at the head.
    if(expesionCode==1)
    {
        temp=headInfix;
    }
    else if(expesionCode==2)
    {
        temp=headPostfix;
    }
    else
    {
        printf("WRONG LIST CODE !!!\n");
        exit(0);
    }
	
	
    while(temp!=NULL)
    {
        nextTerm=temp->next; // NextTerm shows at next node of list.
        free(temp);			 // Free current node.
        temp=nextTerm;    	 // Show in next node of list.
    }
}

/* Converts operators on char * and also converts the 
   numbers on char* but with sign. */
void  setExpessionElement (int expesionCode ,char type, char signOrOperator, int number){
    if(type=='$') // OPERATOR
    {
        char* sign=NULL;
        sign=(char*)malloc((sizeof(char))); // Memory allocation.
        *sign=signOrOperator;
        sign[1]='\0'; 
        addList(1,sign); // Add singed number to infix list.

    }
    else  // NUMBER{
    {
        char* sig=NULL;
        char* num=NULL;
        char* numWithSign=NULL;
		
        int sizeNum=0;
        sig=(char*)malloc((2*sizeof(char))); 			// Memory allocation.
        sig[0]=signOrOperator;

        sizeNum = numberOfDigits(number); 				// Get number size of digits.
        num=(char*)malloc((sizeNum+1)*(sizeof(char))); //Memory allocation.
        sprintf(num, "%d", number);                    //Can also use and itoa(number,num,10).
     
		
        numWithSign= (char*)malloc((1+sizeNum+1)*(sizeof(char))); // Memory allocation.
        memcpy(numWithSign,sig,1); 				// numWithSign= sign.
        memcpy(&numWithSign[1],num,sizeNum);	// numWithSign= signNumber.
        numWithSign[1+sizeNum]='\0';			// numWithSign= signNumber\0.
        addList(1,numWithSign);					// Add singed number to infix list.
    }

}


