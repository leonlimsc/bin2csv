#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "main.h"
#include "bin_2_csv.h"
#include "input_for_bin.h"

static void input_student(void);
static void input_employee(void);

FILE *fp;

void input_for_bin(void) {
	dbg();

	while(1) {
		char action;
		printf("\n\n===============\n");
		printf("'s' to input a student info,\n");
		printf("'e' to input an employee info,\n");
		printf("'x'' to exit:\n");
		action = getche();
		
		switch(action) {
			case 's':
			case 'S':
				{
					input_student();
					break;
				}
			case 'e':
			case 'E':
				{
					input_employee();
					break;
				}
			case 'x':
			case 'X': 
				{
					exit(0);
				}					
		}
	}
}

static void input_student(void) {
/*
student

Item	Type	len(bytes)
-------------------------
name	string	variable (end by 0)
maths	float	4
english	float	4
*/
	dbg();

	char name[MAX_STR_LEN];
	int namelen;
	
	puts("\n\n===========\ninput student name:");
	fflush(stdin);
	char c;
	for(namelen = 0; namelen < (MAX_STR_LEN - 1); namelen++) {
		scanf("%c", &c);
		if(c == '\n') { // enter
			name[namelen] = '\0';
			namelen++; // include '\0'
			break;
		}else{
			name[namelen] = c;
		}
	}
	name[MAX_STR_LEN -1] = '\0'; // for safe

	puts("\ninput maths score: ");
	float maths;
	scanf("%f", &maths);

	puts("\ninput english score: ");
	float english;
	scanf("%f", &english);

	// about to write to bin
	char tmp = 1+namelen+4+4; // ID, namelen, maths, english
	printf("\nabout to write %d(0x%x) bytes to bin...\n", tmp+1, tmp+1);
	fp = fopen("test.bin", "a");
	fwrite(&tmp, 1, 1, fp); // total len

	tmp = MSG_ID_STUDENT;
	fwrite(&tmp, 1, 1, fp);
	
	fwrite(name, namelen, 1, fp);
	fwrite(&maths, 4, 1, fp);
	fwrite(&english, 4, 1, fp);

	fclose(fp);
	printf("\nbin writing done.\n");
}

static void input_employee(void) {
/*
employee

Item	Type	len(bytes)
-------------------------
name	string	variable (end by 0)
dept.	string  variable (end by 0)
salay	float	4
*/
	dbg();

	#define MAX_STR_LEN 50
	char name[MAX_STR_LEN];
	int namelen;

	char dept[MAX_STR_LEN];
	int deptlen;

	char c;

	puts("\n\n===========\ninput employee name:");
	fflush(stdin);
	for(namelen = 0; namelen < (MAX_STR_LEN - 1); namelen++) {
		scanf("%c", &c);
		if(c == '\n') { // enter
			name[namelen] = '\0';
			namelen++; // include '\0'
			break;
		}else{
			name[namelen] = c;
		}
	}
	name[MAX_STR_LEN -1] = '\0'; // for safe

	puts("\n===========\ninput employee department:");
	fflush(stdin);
	for(deptlen = 0; deptlen < (MAX_STR_LEN - 1); deptlen++) {
		scanf("%c", &c);
		if(c == '\n') { // enter
			dept[deptlen] = '\0';
			deptlen++; // include '\0'
			break;
		}else{
			dept[deptlen] = c;
		}
	}
	dept[MAX_STR_LEN -1] = '\0'; // for safe


	puts("\ninput salary: ");
	float salary;
	scanf("%f", &salary);

	// about to write to bin
	char tmp = 1+namelen+deptlen+4; // ID, namelen, deptlen, salary
	printf("\nabout to write %d(0x%x) bytes to bin...\n", tmp+1, tmp+1);
	fp = fopen("test.bin", "a");
	fwrite(&tmp, 1, 1, fp); // total len

	tmp = MSG_ID_EMPLOYEE;
	fwrite(&tmp, 1, 1, fp);
	
	fwrite(name, namelen, 1, fp);
	fwrite(dept, deptlen, 1, fp);
	fwrite(&salary, 4, 1, fp);

	fclose(fp);
	printf("\nbin writing done.\n");
}


// =========================================== //
#if 0

	reference code

	char fbuf[] = {1, 2, 3, 6, 8, 'a'};
	#define LEN sizeof(fbuf)
	
	FILE *fp;
	fp = fopen("test.bin", "w");
	fwrite(fbuf, LEN, 1, fp);
	fclose(fp);
	
#endif
// =========================================== //

