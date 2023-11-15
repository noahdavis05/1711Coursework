#include <stdio.h>
#include <stdlib.h>

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

#endif // FITNESS_DATA_STRUCT_H

