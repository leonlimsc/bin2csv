#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "main.h"
#include "input_for_bin.h"
#include "bin_2_csv.h"


int main(int argc, char *argv[]) {
	printf("var len of data demo. data to bin, then bin to csv\n");
	printf("build on %s, %s\n\n", __DATE__, __TIME__);

	char input;
	printf("\n\nclear test.bin? 'y' for yes, others for no\n");
	input = getche();
	if(input == 'y' || input == 'Y') {
		FILE *fp;
		fp = fopen("test.bin", "w");
		fclose(fp);
		puts("\ntest.bin cleared\n");
	}

	while(1) {
		
		printf("\n\n\nselect what to do:\n'i' for input data to get bin,\n'c' for convert bin to csv:\n'x' to exit: ");
		input = getche();		
		switch (input) {
			case 'i':
			case 'I':
				{
					input_for_bin();
					break;
				}
			case 'c':
			case 'C':
				{
					bin_2_csv();
					break;
				}
			case 'x':
			case 'X':
				{
					puts("\nbye\n");
					return 0;	
				}
		}	
	}

	return 0;
}

// =========================================== //
#if 0



#endif
// =========================================== //
