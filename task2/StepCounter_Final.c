#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {
    // Declare variables
    int cont = 0;
    char my_option[100];
    char option;
    char filename[100];
    int i;
    int count;
    char low_date[15];
    int fewest_steps;
    // make a while loop to contain the switch case statement so that it can be done multiple times
    while (cont == 0){
        // print out options for user to choose
        printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\nEnter choice: ");
        scanf("%s",my_option);
        for (i = 0; my_option[i] != '\0'; ++i); //finds the length of the string to make sure a input was just one character long
        //check length
        if (i == 1){
            option = my_option[0];
        } else {
            option = 'z'; //this will make the switch case default
        }

        
        // switch case statement
        switch (option){
            case 'A':
            case 'a':
                printf("Input filename: ");
                scanf("%s",filename);
                getchar(); // Consume the newline character
                FILE *my_file = open_file(filename,"r");
                if (my_file == NULL){
                    printf("Error: Could not find or open the file.\n");
                    exit(1);
                } else {
                    fclose(my_file);
                }
                break;


            case 'B':
            case 'b':
            // specify the number of lines in the file
                count = count_items(filename,"r");
                printf("%d\n",count);
                break;

            case 'C':
            case 'c':
                //create a structured array
                count = count_items(filename,"r");
                break;

            case 'D':
            case 'd':
                printf("d");
                break;

            case 'E':
            case 'e':
                printf("e");
                break;

            case 'F':
            case 'f':
                printf("f");
                break;

            case 'Q':
            case 'q':
                cont = 1;
                printf("q");
                break;

        // if they type anything else:
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
}


    
   











