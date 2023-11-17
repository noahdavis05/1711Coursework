#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declaration
void modifyString(char *str);

int main() {
    // Example usage
    char myString[] = "Hello, World!";
    
    // Print the original string
    printf("Original String: %s\n", myString);

    // Call the function to modify the string
    modifyString(myString);

    // Print the modified string
    printf("Modified String: %s\n", myString);

    return 0;
}

// Function definition
void modifyString(char *str) {
    // Modify the string in-place
    strcat(str, " Have a great day!");
}
