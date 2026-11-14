#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
int stack[MAX] = {0};
int top = -1; // to make sure that the first element is 0

void push(char input);
int compute(char op);
int pop(void);

int main()
{
    char buffer[20] = {0};
    printf("Enter the equation\n");
    if (fgets(buffer, sizeof buffer, stdin) != NULL) 
    {
        buffer[strcspn(buffer, "\n")] = '\0';   // strip trailing newline
        printf("You typed: %s\n", buffer);
    }

    // for(int i = 0; i < 20; i++) printf("%d\n", buffer[i]);


    for (int i = 0; i < 20; i++)
    {
        if (isspace(buffer[i])) continue;
        if (isdigit(buffer[i])) push(buffer[i]);
        else if (ispunct(buffer[i])) 
        {
            printf("result %d\n", compute(buffer[i]));
        }
    }
    
    // printf("Buffer array\n");
    
    // for(int i = 0; i < 20; i++) printf("%d\n", buffer[i]);

    // printf("data in stack \n");
    
    // for(int i = 0; i < MAX; i++) printf("%d\n", stack[i]);

    return 0;
}

void push(char input)
{
    printf("numero %c\n", input);
    if(top >= MAX - 1) return;
    top++;
    stack[top] = input;
    return;
}

int pop(void)
{
    if (top < 0) return 0;
    int temp = stack[top];
    stack[top] = 0;
    top--;
    return temp;
}

int compute(char op) 
{
    printf("operator %c\n", op);
    int operand1 = pop();
    int operand2 = pop();
    switch (op) 
    {
        case '+': return operand1 + operand2;
        case '-': return operand2 - operand1;
        case '*': return operand1 * operand2;
        case '/': 
            if (operand2 == 0) 
            {
                printf("Error: division by zero\n");
                return 0;
            }
            return operand1 / operand2;
    }
    return 0; 
}
