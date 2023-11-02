#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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

//function to open my file
FILE *open_file(char filename[], char mode[]) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("");
        exit(1);
    }
    return file;
}

//function to find how many items are in file
int find_items(char filename[], char mode[]){
    FILE *file = open_file(filename, mode);

    //read file and work out how many records there are in the file
    int count = 0;
    int buffer_size = 100;
    char line_buffer[buffer_size];
    while (fgets(line_buffer,buffer_size,file) != NULL){
        count++;
    }
    //close file so it can be opened again from the start
    fclose(file);
    return count;
}

// Complete the main function
int main() {
    //open my file
    char filename[] = "FitnessData_2023.csv";
    char mode[] = "r";

    //read file and work out how many records there are in the file
    int count = find_items(filename,mode);
    //print out the number of records in the file
    printf("%d\n",count);

    //create a structured array
    FITNESS_DATA my_data[count];
    //open file again
    FILE *new_file = open_file(filename, mode);
    //add data to this array
    char date[11];
    char time[6];
    char steps[10];
    //make a counter variable 
    int counter = 0;
    int buffer_size = 100;
    char line_buffer[buffer_size];
    while (fgets(line_buffer,buffer_size,new_file) != NULL){
        tokeniseRecord(line_buffer,",",date,time,steps);
        strcpy(my_data[counter].date, date);
        strcpy(my_data[counter].time,time);
        my_data[counter].steps = atoi(steps);
        counter++;        
    }

    //print out first three rows with the slashes
    for (int i = 0; i < 3; i++){
        printf("%s/%s/%d\n",my_data[i].date, my_data[i].time, my_data[i].steps);
    }

    return 0;
}
