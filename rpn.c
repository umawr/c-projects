#include <stdio.h> // for printf() and scanf() and fgets()
#include <string.h> // for strcspn()
#include <ctype.h> // for istype()
#include <stdlib.h> //fro strtol() - string to long
#include <math.h>

#define MAX 20
int stack[MAX] = {0};
int top = -1; // to make sure that the first element is 0
// stack is LIFO so the top most index is "0"
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

    for (char *buffer_string = buffer; *buffer_string; )
    {
        if (isdigit((unsigned char)*buffer_string) || (*buffer_string == '-' && isdigit((unsigned char)*(buffer_string + 1))))
            push((int)strtol(buffer_string, &buffer_string, 10));   // (string to read from, , base 10)
        else
        {
            if (ispunct((unsigned char)*buffer_string)) compute(*buffer_string);
            buffer_string++;
        }
    }
    printf("Result is %d\n", pop());
    
    return 0;
}

int push(int input)
{
    if(top >= MAX - 1) return 0; // fallback
    top++;
    stack[top] = input;
    return 0;
}

int pop(void)
{
    if (top < 0) return 0; // fallback
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
            if (operand1 == 0) 
            {
                printf("!!Error - division by zero!!\n");
                return 0;
            }
            push(operand2 / operand1); break;
    }
    return 0; 
}
