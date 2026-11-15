#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
int stack[MAX] = {0};
int top = -1; // to make sure that the first element is 0

int push(int input);
int compute(char op);
int pop(void);

int main()
{
    char buffer[20] = {0};// where the input is stored temporary
    //char data type to accommodate arithmetic symbols
    printf("Enter the equation\n");
    if (fgets(buffer, sizeof buffer, stdin) != NULL) 
    {
        buffer[strcspn(buffer, "\n")] = '\0';   // ??
        printf("You typed: %s\n", buffer);
    }

    for (int i = 0; i < 20; i++)
    {
        if (isspace((unsigned char)buffer[i])) continue; // space gets ignored
        if (isdigit((unsigned char)buffer[i])) push(buffer[i] - '0');// buffer[i] - '0' is to convert the ascii value to its regular value 
        else if (ispunct((unsigned char)buffer[i])) compute(buffer[i]);
    }
    printf("result %d\n", pop());
    
    return 0;
}

int push(int input)
{
    // printf("\n\n");
    // for (int i = 0; i < MAX; i++) printf("%d\n", stack[i]);
    // printf("\n\n");
    if(top >= MAX - 1) return 0; // fallback
    top++;
    stack[top] = input;
    return 0;
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
    int operand1 = pop();
    int operand2 = pop();
    switch (op) 
    {
        case '+':  push(operand2 + operand1); break;
        case '-':  push(operand2 - operand1); break;
        case '*':  push(operand2 * operand1); break;
        case '/': 
            if (operand2 == 0) 
            {
                printf("Error: division by zero\n");
                return 0;
            }
            push(operand2 / operand2); break;
    }
    return 0; 
}
