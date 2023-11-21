#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    } else {
        printf("1");
        exit(1);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    } else{
        printf("2");
        exit(1);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    } else {
        printf("3");
        exit(1);
    }
    
    // Free the duplicated string
    free(inputCopy);

    }


//funciton to open a file
FILE *open_file(char filename[], char mode[]) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("");
        exit(1);
    }
    return file;
}

//function to find how many items are in file
int count_items(char filename[], char mode[]){
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



int main() {
    char filename[100];
    printf("Enter Filename: ");
    scanf("%s",filename);
    FILE *file = open_file(filename,"r");
    int count = count_items(filename,"r");

    FitnessData my_data[count];
	//add data to this array
	char date[11];
	char time[6];
	char steps[10];
	//make a counter variable 
	int counter = 0;
	int buffer_size = 100;
	char line_buffer[buffer_size];
	//adding data
	while (fgets(line_buffer,buffer_size,file) != NULL){
		tokeniseRecord(line_buffer,",",date,time,steps);
		strcpy(my_data[counter].date, date);
		strcpy(my_data[counter].time,time);
		my_data[counter].steps = atoi(steps);
		counter++;
	}   

    printf("  got hjere");

    
}
