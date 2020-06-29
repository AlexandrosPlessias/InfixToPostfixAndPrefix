#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "header.h"

/* Each element of postfix list is checked for whether is number or 
   operator, whether it is a number you create a tree with the number 
   as price and children NULL if operator is again creating a tree to
   value the operator and children in the first 2 values ​​of the stack
   of trees. Finally returns the head of the stack tree is the root of
   the final tree. */
treeNode* createBinaryTree(){
    expesionList* temp ;
    temp =headPostfix;
	// Cross  prostfix list.
    while(temp!=NULL){
	
        treeNode* tree=NULL ; // Utility pointers.
        tree=(treeNode*)malloc(sizeof(treeNode));

        if(strlen(temp->term)>1){ // Number.
			// Create new tree with number, left & right pointer NULL
            tree->data=temp->term;
            tree->firstChildren=NULL;
            tree->secondChildren=NULL;
        }else{ //operator.
			// Create new tree with operator and as left and right pointer the top 2 stack trees.
            tree->data=temp->term;
            tree->firstChildren=popTreeNodeStack();
            tree->secondChildren=popTreeNodeStack();
        }
        addTreeNodeToStack(tree);	// Add tree to the stack of trees.
        temp=temp->next;	// Next element of postfix list.
    }
    struct treeNode * treeRoot=NULL;
    return treeRoot=popTreeNodeStack();		// Return the root of main tree.
}

/* Adds to the stack the tree given as an argument. */
void addTreeNodeToStack(treeNode* tree){
    treeNodeStack *newRoot;
    newRoot = (treeNodeStack*) malloc( sizeof( treeNodeStack ));   // Memory allocation to create new nodes.
	// If space available store the digit in struct.
    if ( newRoot != NULL )      
    {
        newRoot->roots=tree; // Copies of user data at new node.
		// The Memory allocation from before is a node of the stack, which linked in stack with next.
        newRoot->next =treeStackHead ; 
        treeStackHead=newRoot;  // Now this node becomes the new head of the stack.
    }
    else{
        printf("No memory available.\n" );
        exit(0);
    }
}

/* Returns the pointer (treeNode) who is the head of the stack and releases it. */
treeNode* popTreeNodeStack(){
    treeNodeStack* nextTree;	// Utility pointers.
    treeNode* treeData = treeStackHead->roots;	// Get head treeNode.
    nextTree=treeStackHead->next;	// Save treeStackHead->next node.
    free(treeStackHead);	// Free head.
    treeStackHead=nextTree;	// New head is next of previous head.
    return treeData;	// Return head treeNode.
}

/*  Empty the stack. */
void freeTreeNodeStack(){
    // Utility pointers.
    treeNodeStack *nextRoot;
    treeNodeStack *temp=treeStackHead;
    while(temp!=NULL)
    { 
        nextRoot=temp->next;	// nextRoot shows at next node of stack.
        free(temp);	 // Free current node.
        temp=nextRoot;	// Show in next node of stack.
    }
}


