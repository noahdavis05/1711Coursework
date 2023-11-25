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
int tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    int i;
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        for (i = 0; token[i] != '\0'; ++i);
        if (i == 10){ 
            strcpy(date, token);
        } else {
            printf("Error: invalid file\n");
            return 1;
        }
    } else {
        printf("Error: invalid file\n");
        return 1;
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        for (i = 0; token[i] != '\0'; ++i);
        if (i == 5){ 
        strcpy(time, token);
        } else {
            printf("Error: invalid file\n");
            return 1;
        }
    } else{
        printf("Error: invalid file\n");
        return 1;
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
            strcpy(steps, token);
        }
    else {
        printf("Error: invalid file\n");
        return 1;
    }
    
    if (*steps == '\r'){
        printf("Error: invalid file\n");
        return 1;
    }
    // Free the duplicated string
    free(inputCopy);

    return 0;
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
    int success;
    char filename[100];
    printf("Enter Filename: ");
    scanf("%s",filename);
    //check filename is valid and return 1 if not
    FILE *temp_file = fopen(filename,"r");
    if (temp_file == NULL){
        printf("Error: invalid file\n");
        return 1;
    }
    fclose(temp_file);
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
		success = tokeniseRecord(line_buffer,",",date,time,steps);
        if (success == 1){
            return 1;
        }
		strcpy(my_data[counter].date, date);
		strcpy(my_data[counter].time,time);
		my_data[counter].steps = atoi(steps);
		counter++;
	}   
    fclose(file);

    //sort the data
    FitnessData temp;
    for (int i = 0; i < count - 1; i ++){
        for (int j = 0; j < count - i; j ++){
            if (my_data[j].steps < my_data[j + 1].steps){
                temp = my_data[j + 1];
                my_data[j + 1] = my_data[j];
                my_data[j] = temp;
            }
        }
    }



    //open new file so that it can be written to
    strcat(filename,".tsv");
    FILE *new_file = open_file(filename,"w");

    char temp_string[300];
    char temp_num[40];
    for (int i = 0; i < count; i ++){
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
