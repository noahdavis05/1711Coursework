#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // iterate through string and check if there are enough commas
    int i;
    for (i = 0; inputCopy[i] != '\0'; ++i);
    //iterate through list and count commas
    int comma_count = 0;
    for (int j = 0; j < i; j++){
        if (inputCopy[j] == ','){
            comma_count ++;
        }
    }
    
    if (comma_count != 2){
        printf("Invalid data in file\n");
        exit(1);
    }

    //iterate through list and check that there are elements inbetween the commas
    for (int j = 0; j < (i-1); j++){
        if (inputCopy[j] == ','){
            if (inputCopy[j+1] == ','){
                printf("Invalid data in file\n");
                exit(0);
            }
        }
    }
    
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

//funciton to open a file
FILE *open_file(char filename[], char mode[]) {
    FILE *file = fopen(filename, mode);
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

//converts my string into an int
//copied from stack overflow
char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}





int main() {
    //ask the user to enter the filename and check if correct
    char filename[100];
    printf("Enter Filename: ");
    scanf("%s",filename);
    //check filename
    FILE *my_file = open_file(filename,"r");
    if (my_file == NULL){
        printf("Error: invalid file\n");
        return 1;
    } else {
        fclose(my_file);
    }

    //work out the number of lines in the file.
    int line_count;
    line_count = count_items(filename,"r");

    //make an array of structs the size of line count
    FitnessData my_data[line_count];

    //open file again so it can be read and checked for validity.
    FILE *file = open_file(filename,"r");
    //make variables to store temp values from tokenise record function
    char date[11];
	char time[6];
	char steps[10];
	//make a counter variable 
	int counter = 0;
	int buffer_size = 100;
	char line_buffer[buffer_size];
    int i;

    //add data to the file
    while (fgets(line_buffer,buffer_size,file) != NULL){
		tokeniseRecord(line_buffer,",",date,time,steps);
        //check the values of date, time, and steps
        //check date
        if (date == NULL){
            printf("Invalid data in file\n");
            return 1;
        }
        for (i = 0; date[i] != '\0'; ++i);
        if (i != 10){
            printf("Invalid data in file\n");
            return 1;
        }
        //check time
        if (time == NULL){
            printf("Invalid data in file\n");
            return 1;
        }
        for (i = 0; time[i] != '\0'; ++i);
        if (i != 5){
            printf("Invalid data in file\n");
            return 1;
        }
        //check steps
        if (steps == NULL){
            printf("Invalid data in file\n");
            return 1;
        }
        if (*steps == '\r'){
            printf("Invalid data in file\n");
            return 1;
        }
		strcpy(my_data[counter].date, date);
		strcpy(my_data[counter].time,time);
		my_data[counter].steps = atoi(steps);
		counter++;
	}   
    fclose(file);

    // sort my data
        FitnessData temp;
    for (int i = 0; i < line_count - 1; i ++){
        for (int j = 0; j < line_count - i; j ++){
            if (my_data[j].steps < my_data[j + 1].steps){
                temp = my_data[j + 1];
                my_data[j + 1] = my_data[j];
                my_data[j] = temp;
            }
        }
    }

    //write the data to my file

    //open new file so that it can be written to
    strcat(filename,".tsv");
    FILE *new_file = open_file(filename,"w");

    char temp_string[300];
    char temp_num[40];
    for (int i = 0; i < line_count; i ++){
        fprintf(new_file, "%s",my_data[i].date);
        fprintf(new_file, "\t");
        fprintf(new_file,"%s",my_data[i].time);
        fprintf(new_file,"\t");
        my_itoa(my_data[i].steps,temp_num);
        fprintf(new_file,"%s",temp_num);
        fprintf(new_file,"\n");
        
    }

    fclose(new_file);

    printf("Data sorted and written to %s\n",filename);
    return(0);

    
    
}
