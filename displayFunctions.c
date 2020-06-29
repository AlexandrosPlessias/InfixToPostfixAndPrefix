#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "header.h"

/* Displays recursively calling the same itself and 
   visits to the method tree Value Left Right. */
void preFix(treeNode* root)
{
    if(root != NULL)
    {
        printf("(%s) ",root->data);
        preFix(root->secondChildren);
        preFix(root->firstChildren);
    }
}

/* Displays recursively calling the same itself and 
   visits to the method tree Left Right Value. */
void postFix(treeNode* root)
{
    if(root != NULL)
    {
        postFix(root->secondChildren);
        postFix(root->firstChildren);
        printf("(%s) ",root->data);
    }
}
