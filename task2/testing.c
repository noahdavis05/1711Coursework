#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int round_float(float number){
	int temp_int = (int)number;
	float temp_float = number - temp_int;
	if (temp_float < 0.5){
		return temp_int;
	} else {
		return temp_int + 1;
	}
}

int main() {
    // Example usage
    int rounded1 = round_float(12.34);
    int rounded2 = round_float(12.5); 
    printf("%d %d",rounded1,rounded2);

    return 0;
}

