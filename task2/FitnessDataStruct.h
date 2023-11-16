#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

//function to open file
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

//function to find date with fewest steps
int earliest_date(char filename[], char mode[]){
	int count;
	count = count_items(filename,"r");
	FILE *file = open_file(filename, mode);
	FITNESS_DATA my_data[count];
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

	int lowest_steps = my_data[0].steps;
	char lowest_date[15];
	char lowest_time[15];

	//iterate through data
	for (int i = 0; i < count; i++){
		if (my_data[i].steps <= lowest_steps){
			lowest_steps = my_data[i].steps;
			strcpy(lowest_date,my_data[i].date);
			strcpy(lowest_time,my_data[i].time);
		}
	}
	        
	printf("%s %s\n",lowest_date, lowest_time);
	return 0;

}
#endif // FITNESS_DATA_STRUCT_H

