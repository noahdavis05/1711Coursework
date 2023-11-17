#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
int high_low_date(char filename[], int mode){
	int count;
	count = count_items(filename,"r");
	FILE *file = open_file(filename, "r");
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
	if (mode == 0){
	for (int i = 0; i < count; i++){
		if (my_data[i].steps <= lowest_steps){
			lowest_steps = my_data[i].steps;
			strcpy(lowest_date,my_data[i].date);
			strcpy(lowest_time,my_data[i].time);
		}
	}
	printf("Fewest steps: %s %s\n",lowest_date, lowest_time);
	} else {
		for (int i = 0; i < count; i++){
		if (my_data[i].steps >= lowest_steps){
			lowest_steps = my_data[i].steps;
			strcpy(lowest_date,my_data[i].date);
			strcpy(lowest_time,my_data[i].time);
		}
	}
	printf("Largest steps: %s %s\n",lowest_date, lowest_time);
	}
	        
	
	return 0;
}

int calc_mean(char filename[]){
	int count;
	count = count_items(filename,"r");
	FILE *file = open_file(filename, "r");
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

	int total_sum = 0;
	for (int i = 0; i < count; i ++){
		total_sum += my_data[i].steps;
	}
	double myDouble1 = (double)total_sum;
	double myDouble2 = (double)count;
	double mean = myDouble1/ myDouble2;
	int rounded = round(mean);
	return rounded;
}



int longest_period(char filename[]){
	char my_string[300];
	int count;
	count = count_items(filename,"r");
	FILE *file = open_file(filename, "r");
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

	char start[100];
	char end[100];
	int pointers[100];
	int pointers_pointer = 0;
	for (int i =0; i < count; i ++) {
		if (my_data[i].steps >= 500){
			pointers[pointers_pointer] = i;
			pointers_pointer += 1;
		}
	}

	int longest_streak = 0;
	int temp_streak = 1;
	int start_pos;
	int end_pos;
	int temp_pos;



	for (int i = 0; i < pointers_pointer -1 ; i++){
		if (pointers[i] + 1 == pointers[i + 1]){
			if (temp_streak == 1){
				temp_pos = pointers[i];
			}
			temp_streak += 1;
			if (i == pointers_pointer -2 ){
				end_pos = pointers[pointers_pointer -1];
			}
		} else{
			if (temp_streak >= longest_streak){
				longest_streak = temp_streak;
				temp_streak = 1;
				end_pos = pointers[i];
				start_pos = temp_pos;

			}
		}
	}

	printf("%d %d \n",start_pos, end_pos);
	
	return 0;
}


#endif // FITNESS_DATA_STRUCT_H

