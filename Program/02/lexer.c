#include <stdio.h>
#include <string.h>

int main() {
    char line[200];

    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);

    // Remove newline character
    line[strcspn(line, "\n")] = '\0';

    // Check for single-line comment
    if (line[0] == '/' && line[1] == '/') {
        printf("It is a single-line comment.\n");
    }
    // Check for multi-line comment
    else if (line[0] == '/' && line[1] == '*') {
        if (strstr(line, "*/") != NULL) {
            printf("It is a multi-line comment.\n");
        } else {
            printf("It is NOT a valid comment.\n");
        }
    }
    else {
        printf("It is NOT a comment.\n");
    }

    return 0;
}
