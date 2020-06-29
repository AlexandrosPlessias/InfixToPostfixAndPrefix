
typedef struct expesionList
{
    char* term ;
    struct expesionList * next;
} expesionList;


typedef struct operatorStack
{
    char* op ;
    struct operatorStack * next;
} operatorStack;


typedef struct treeNode
{
    char* data;
    struct treeNode * firstChildren, * secondChildren;
} treeNode;


typedef struct treeNodeStack
{
    treeNode* roots;
    struct treeNodeStack * next;
} treeNodeStack;

struct expesionList *headInfix;    // GLOBAL Head pointer.
struct expesionList *headPostfix;    // GLOBAL Head pointer.
struct operatorStack *headOperatorStack;    // GLOBAL Head pointer.
struct treeNodeStack* treeStackHead;   // GLOBAL Head pointer.

// --------------------basicFunction.c -------------------

/* Show Welcome message, Do you want to continue & Rules. */
void TextArt();

/* Show menu and return a valid choice. */
int Menu();

/* Processes user choice and do the appropriate function. */
void infixToPostAndPre();

/* I call the function readInfix and take user's input, 
   then stored in an array the positions of operands and call function tokenazationInput.*/
void insertInfix ();

/* Create List postfix using operator stack (use addOperatorStack) when reading
   number entered in the list  when entered the operator adds to the stack. 
   Before add operator to the stack check the priorities of top of stack and current
   operator fron infix and do the right push & pop(use popOperatorStack) , when seen 
   close bracket empty the stack until find the opening of bracket and finally empty 
   the stack. */
void createPostFixList ();

/* Returns an integer corresponding to the priority of the operator given as an argument.*/
int precedenceOfOperator(char* oper);


// --------------------inputFunction.c -------------------

/* Dynamic reading input from the user and check whether it is valid.
   Checking for brackets if starts or ends with operator, if only given 
   a number only, if we use operator after operator (not mentioned in 
   parentheses), if only pressed the Enter key and if you are opening 
   and closing brackets without content above all controlled by special 
   functions. Finally, it returns a pointer to the contents of user input.
*/
char* readInfix();

/* Checking for brackets using the lemma brackets takes as 
    input parameter the user and returns 1 for valid format 
	and 0 for non-valid. */
int checkValidity(char* input);

/* Checking for brackets using the lemma brackets takes as 
    input parameter the user and returns 1 for valid format 
	and 0 for non-valid. */
int checkParenthesis (char* input);

/* Checking if starts or ends with operator takes as input 
   parameter the user and returns 1 for valid format and 0 
   for non-valid. */
int checkStartAndEnd (char* input);

/* Checking if only given a number only takes as input 
   parameter the user and returns 1 for valid format 
   and 0 for non-valid. */
int checkOnlyNumber(char* input);

/* Checking if we use operator after operator (not mentioned 
   in parentheses) takes as input parameter the user and 
   returns 1 for valid format and 0 for non-valid. */
int checkOpAfterOp (char* input);

/* Checking if  open and close brackets without content takes 
   as input parameter the user and returns 1 for valid format 
   and 0 for non-valid. */
int checkParenthesisAfterParenthesis (char* input);

/* Separates the user input to numbers (positive and negative) & operator's 
   and stores them in infix list. Accepts as parameters the user input, the 
   table with the positions of operators and the size of the table of 
   operators positions.*/
void tokenazationInput(char* input,int* operatorsPositions, int size );

/* Returns the number of digits in the number given as argument 
   through a mathematical formula(floor(log10(abs(numberCheck))) 
   + 1). */
int numberOfDigits(int numberCheck);


// --------------------listFunction.c -------------------

/* Add the element of expression list (simple) with the 
   corresponding code (1 for infix & 2 for postfix). */
void addList (int expesionCode, char* term);

/* Converts operators on char * and also converts the 
   numbers on char* but with sign. */
void setExpetionElement (int expesionCode ,char type, char signOrOperator, int number);

/* Empty the list (singlet) with the corresponding code 
   (1 for infix & 2 for postfix). */
void freeList(int expesionCode);


// --------------------stackFunction.c -------------------

/* Adds to the stack operator given as an argument. */
void addOperatorStack(char*oper);

/* Returns the value (operator) who is the head of the stack and releases it. */
char* popOperatorStack();

/* Empty the stack. */
void freeOperatorStack();


//Tree Stack Management.

/* Each element of postfix list is checked for whether is number or 
   operator, whether it is a number you create a tree with the number 
   as price and children NULL if operator is again creating a tree to
   value the operator and children in the first 2 values ​​of the stack
   of trees. Finally returns the head of the stack tree is the root of
   the final tree. */
treeNode* createBinaryTree();

/* Adds to the stack the tree given as an argument. */
void addTreeNodeToStack(treeNode* left);

/* Returns the pointer (treeNode) who is the head of the stack and releases it. */
treeNode* popTreeNodeStack();

/*  Empty the stack. */
void freeTreeNodeStack();

// --------------------displayFunction.c -------------------

/* Displays recursively calling the same itself and 
   visits to the method tree Value Left Right. */
void preFix(treeNode* root);

/* Displays recursively calling the same itself and 
   visits to the method tree Left Right Value. */
void postFix(treeNode* root);
