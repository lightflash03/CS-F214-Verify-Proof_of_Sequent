#include <stdio.h>
#include <string.h> //Included to accomodate the strcpy() fucntion
#include <stdlib.h> //Included to call malloc
#include <time.h>   //Included to clock the time that the program takes to run
// The time.h function is used to accurately find the time the program takes to run, from start to end
#define MAX 100 // Maximum size of the input expression & the stack

char prec[4] = ">+*~"; // Allowed operators, in increasing order of precedence

// This function returns the precedence of any input character
// The assigned precedence is 4 for '~', 3 for '*', 2 for '+' and 1 for '>'
// The function returns 0 if the input character is an operand(alphabet) or a parenthesis
int precedence(char c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '(' || c == ')'))
  {
    return 0;
  }
  for (int i = 4; i > 0; i--)
  {
    if (prec[i - 1] == c)
    {
      return i;
    }
  }
  printf("Invalid character: %c\n", c);
  // Illegal symbols in the input expression will terminate the program
  // In that case , we directly exit the program after alerting the user what the error causing character is
  exit(1);
}

// Functions to manipulate Stacks

void Push(char Item, int *Top, char *Stack)
{ // This function adds an Item, in this case a character to the top of the stack
  if (*Top == MAX - 1)
    // This if condition indicates the base case when the stack is full
    return;
  (*Top)++;
  // We do top++ to change the reference of the previous top to the new one
  *(Stack + *Top) = Item;
}

char Pop(int *Top, char *Stack)
{                 // This function removes the topmost element from the stack and returns it
  if (*Top == -1) // This if condition indicates the base case when stack is empty
    return '\0';
  return *(Stack + (*Top)--); // stack[top--];
  // We do Top-- to assign a new top to the stack, which was previously the second element
}

char Peek(int *Top, char *Stack)
{                 // This function reads the topmost element of the stack but doesn't remove it
  if (*Top == -1) // Base case when the stack is empty
    return '\0';
  return *(Stack + *Top);
}

// This function obtains the Postfix Expression for the parameter passed, which is a character pointer, pointing to a character array
void getPostfix(char *expression)
{
  int i, j;
  int top = -1;
  char stack[MAX];
  for (i = 0, j = -1; expression[i]; ++i)
  {
    // Here we are checking is the character we scanned is operand or not
    // and this adding to to output.
    if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z'))
      expression[++j] = expression[i];
    // Here, if we scan character ‘(‘, we need push it to the stack.
    else if (expression[i] == ')')
      Push(expression[i], &top, stack);
    // Here, if we scan character is an ‘)’, we need to pop and print from the stack
    // we need to do this until an ‘(‘ is encountered in the stack.
    else if (expression[i] == '(')
    {
      while ((top != -1) && Peek(&top, stack) != ')')
        expression[++j] = Pop(&top, stack);
      if ((top != -1) && Peek(&top, stack) != ')')
      {
        printf("Invalid Expression.\n");
        exit(1); // For an invalid expression, we exit out of the program after printing an error code
      }
      else
        Pop(&top, stack);
    }
    else
    { // if the character is an operator
      while ((top != -1) && precedence(expression[i]) <= precedence(Peek(&top, stack)))
        expression[++j] = Pop(&top, stack);
      Push(expression[i], &top, stack);
    }
  }
  // Once all inital expression characters are traversed
  // we can add all the remaining characters in the stack to the expression
  while ((top != -1))
    expression[++j] = Pop(&top, stack);
  expression[++j] = '\0';
}

// This function simply reverses a given string(character array) and over-writes the initial one
void reverseString(char *exp)
{
  int size = strlen(exp);
  int j = size, i = 0;
  char temp[size];
  temp[j--] = '\0';
  while (exp[i] != '\0')
  {
    temp[j] = exp[i];
    j--;
    i++;
  }
  strcpy(exp, temp);
}

// Function to rewrite an Infix Expression into Prefix form
// In this function, we call the getPostfix function between 2 reversal functions
// We do so because it is more readable code when we convert a function to postfix
// The conversion to prefix can be achieved by first getting the postfix of the reverse of the input expression, and then reversing the output again
void InfixtoPrefix(char *exp)
{
  // reverse string
  reverseString(exp);
  // get postfix
  getPostfix(exp);
  // reverse string again
  reverseString(exp);
}

// The standard TreeNode structure that constitutes the parse tree
typedef struct TreeNode
{
  char data;
  struct TreeNode *left, *right;
} TreeNode;

// This is a function to create a TreeNode with Dynamic Memory Allocation(malloc)
// We use malloc to optimise memory usage in C
TreeNode *createNode(char val)
{
  TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
  newNode->data = val;
  newNode->left = newNode->right = NULL;
  // Initially when we create a node(here, root), we need to assign the left and right values to NULL
  // We do so to avoid garbage values being assigned to the left and right
  // Therefore, we start at a common ground when we are verifying if there already exist a left and right to the node
  return newNode;
}

// This function  recursively builds the expression tree
char *makeSubTree(TreeNode **root, char *ch)
{
  if (*ch == '\0')
  { // For a valid prefix expression, the end of the expression should never be encountered
    printf("Invalid Expression.\n");
    exit(1); // Hence we exit the program after printing an error code
  }
  while (1)
  {                       // We use a while loop because we want both conditional statements inside to execute
    char *temp = "dummy"; // We create a dummy variable to traverse the prefix expression to traverse the tree as we add the required variables in order to the tree
    if (*root == NULL)
    {
      // Create a node with *ch as the data and
      // both the children set to null
      *root = createNode(*ch);
    }
    else
    {
      // If the character is an operand, do not recurse further
      if (precedence(*ch) == 0)
        return ch;
      else if (precedence(*ch) == 4)
      { // If the character is a negation(precedence = 4), we know that in regular parse trees, the negation operator is a unary operator
        // Evidently, it shouldn't have a left subtree, rather, only a right one
        temp = makeSubTree(&(*root)->right, ch + 1);
      }
      else
      { // For any other operator not a negation,
        // We first call the recursive function to make a subtree to the left of the operator node
        temp = makeSubTree(&(*root)->left, ch + 1);
        // Then we call the recursive function to build the subtree to the right of the operator node
        temp = makeSubTree(&(*root)->right, temp + 1);
      }
      return temp;
    }
  }
}

// This function does inOrder traversal of the parse tree, to get the infix notation that represents the tree
void getInfix(TreeNode *root)
{
  // The infix notation involves the traversal from the left subtree, to the root, to the right subtree
  // The easiest way to code inOrder traversal is to recursively call it in the mentioned order
  if (root == NULL)
  {
    return;
  }
  else
  {
    getInfix(root->left);
    printf("%c", root->data);
    getInfix(root->right);
  }
}

// The following function returns the height of the parse tree
// We use recursion to calculate the left height first, and the right height too
// The requirement of the height function is to get the maximum distance to be travelled from the root node to the furthest leaf of the tree
int getHeight(TreeNode *root)
{
  if (root == NULL)
    return 0;
  int leftHeight = getHeight(root->left);
  int rightHeight = getHeight(root->right);
  return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

// This function performs the binary operation for the given list of operators
int operate(char operator, int pre, int post)
{
  if (operator== '+')
    return pre | post;
  // This '+' operator performs the bitwise "OR" operation on the propositional atoms
  else if (operator== '*')
    return pre & post;
  // This '*' operator performs the bitwise "AND" operation on the propositonal atoms
  else if (operator== '>')
    // This '>' is the impliation operator whose function is defined by:
    //(a>b) = ~a | b
    return (!pre) | post;
  return 0;
}

// This function evaluates the truth value of the parse tree
// This can be explained as a method called bottom up traversal
int evaluateSubTree(TreeNode *root)
{
  if (root->left == NULL && root->right != NULL)
  {
    // This is the case where the operator in discussion is the "NEGATION"(~) operator
    // Since for this operator, we don't have a left node, we directly return the negation of the child node, which is the right
    return !(evaluateSubTree(root->right));
  }
  else if (root->left == NULL && root->right == NULL)
  {
    // This case indicates that we have reached a leaf node, which surely contains an operand
    // Therfore, the program asks us to assign it some truth values
    printf("Enter Truth Value (0 or 1) of %c: ", root->data);
    int c;
    scanf("%d", &c);
    return c;
  }
  else
  {
    // In this else case we are checking if the present node is an operator, we recursively call the evalute function for its left and right
    return operate(root->data, evaluateSubTree(root->left), evaluateSubTree(root->right));
  }
}

// The main function
int main()
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  char expr[MAX];
  printf("Enter the Infix Expression: ");
  scanf("%[^\n]c", expr);
  InfixtoPrefix(expr);
  printf("The Prefix Expression is: %s\n", expr);
  TreeNode *n = NULL;
  makeSubTree(&n, expr);
  printf("The Infix Expression is: ");
  getInfix(n);
  printf("\nHeight of the Parse Tree: %d\n", getHeight(n));
  printf("Truth Value of Expression: %d\n", evaluateSubTree(n));
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("This program took %f seconds to execute", cpu_time_used);
  return 0;
}