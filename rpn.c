#include <stdio.h> // for printf() and scanf() and fgets()
#include <string.h> // for strcspn()
#include <ctype.h> // for istype()
#include <stdlib.h> //fro strtol() - string to long
#include <math.h> // doesnt do anythong for now

#define MAX 888
// int stack[MAX] = {0};
int *stack = NULL;
int capacity = 0;
int top = -1; // to make sure that the first element is 0
// stack is LIFO so the top most index is "0"
int push(int input);
int compute(char op);
int pop(void);

int main()
{
    char buffer[MAX] = {0};// where the input is stored temporary
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

    free(stack);
    return 0;
}

int push(int input)
{
    if (top + 1 >= capacity)// top + 1 is the number of items in items and capacity is the number of slots
    {
        int new_capacity = (capacity == 0) ? 8 : capacity * 2;// doubling by two instead of increasing by one
        int *temp = realloc(stack, new_capacity * sizeof *stack);// realloc to grow the existing array dynamically
        if (temp == NULL) return 0;
        stack = temp;
        capacity = new_capacity;
    }
    stack[++top] = input;
    // printf("capacity %d, stack at %p top is %d\n", capacity, (void *)stack, top);
    return 1;
}

int pop(void)
{
    if (top < 0) return 0; // fallback
    return stack[top--];
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
