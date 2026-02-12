#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 32

void skipWhitespace(FILE *fp) {
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (!isspace(ch)) {
            ungetc(ch, fp);
            break;
        }
    }
}

void skipComment(FILE *fp) {
    char ch, next;

    ch = fgetc(fp);
    next = fgetc(fp);

    // Single-line comment
    if (ch == '/' && next == '/') {
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    }
    // Multi-line comment
    else if (ch == '/' && next == '*') {
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '*' && (next = fgetc(fp)) == '/')
                break;
            else
                ungetc(next, fp);
        }
    }
    else {
        ungetc(next, fp);
        ungetc(ch, fp);
    }
}

void recognizeTokens(FILE *fp) {
    char ch;

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore whitespace
        if (isspace(ch)) {
            skipWhitespace(fp);
            continue;
        }

        // Handle comments
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/' || next == '*') {
                ungetc(next, fp);
                ungetc(ch, fp);
                skipComment(fp);
                continue;
            }
            ungetc(next, fp);
        }

        // Identifier
        if (isalpha(ch) || ch == '_') {
            char id[MAX_ID_LEN];
            int i = 0;

            id[i++] = ch;
            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {
                if (i < MAX_ID_LEN - 1)
                    id[i++] = ch;
            }
            id[i] = '\0';
            ungetc(ch, fp);

            printf("Identifier: %s\n", id);
        }

        // Constant (number)
        else if (isdigit(ch)) {
            char num[32];
            int i = 0, isFloat = 0;

            num[i++] = ch;
            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.')) {
                if (ch == '.')
                    isFloat = 1;
                num[i++] = ch;
            }
            num[i] = '\0';
            ungetc(ch, fp);

            if (isFloat)
                printf("Float Constant: %s\n", num);
            else
                printf("Integer Constant: %s\n", num);
        }

        // Operators
        else if (strchr("+-*/%=<>!", ch)) {
            char op[3];
            op[0] = ch;
            op[1] = '\0';

            char next = fgetc(fp);
            if ((ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '!' && next == '=')) {
                op[1] = next;
                op[2] = '\0';
            } else {
                ungetc(next, fp);
            }

            printf("Operator: %s\n", op);
        }
    }
}

int main() {
    FILE *fp;
    char filename[100];

    printf("Enter source file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    recognizeTokens(fp);
    fclose(fp);

    return 0;
}
