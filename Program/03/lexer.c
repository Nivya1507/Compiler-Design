#include <stdio.h>

int main() {
    char ch;

    printf("Enter an operator: ");
    scanf(" %c", &ch);   // space avoids newline issue

    switch (ch) {
        case '+':
            printf("Valid Operator: PLUS (+)\n");
            break;
        case '-':
            printf("Valid Operator: MINUS (-)\n");
            break;
        case '*':
            printf("Valid Operator: MULTIPLY (*)\n");
            break;
        case '/':
            printf("Valid Operator: DIVIDE (/)\n");
            break;
        default:
            printf("Invalid Operator\n");
    }

    return 0;
}
