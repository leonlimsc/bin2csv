#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "main.h"
#include "bin_2_csv.h"
#include "input_for_bin.h"


unsigned char buf[1000];

static void write_csv_student(void);
static void write_csv_employee(void);

FILE *fpcsv;

void bin_2_csv(void) {
    dbg();

    FILE *fpbin;
    fpbin = fopen("test.bin", "rb");
    if(fpbin == NULL) {
        printf("!!! ERROR !!! test.bin open error\n\n");
        exit(1);
    }

    fpcsv = fopen("test.csv", "w");
    if(fpcsv == NULL) {
        printf("!!! ERROR !!! test.csv open error\n\n");
        fclose(fpbin);
        exit(1);        
    }

    fseek(fpbin,0,SEEK_SET);
    char len;
    unsigned char ch;

    while(1) {
        fread(&len, 1, 1, fpbin);
        for(int i = 0; i < len; i++) {
            fread(&ch, 1, 1, fpbin);
            if(feof(fpbin)) {
                puts("end of test.bin\n");
                fclose(fpbin);
                fclose(fpcsv);
                puts("\n\n test.bin and test.csv closed. exit...\n");
                exit(0);                
            }
            // printf("0x%x\n", ch);    // show for easy debug
            buf[i] = ch;
        }

        if(buf[0] == MSG_ID_STUDENT) {
            write_csv_student();
        }else if(buf[0] == MSG_ID_EMPLOYEE) {
            write_csv_employee();
        }else{
            printf("!!! ERROR !!! item ID error\n\n");
        }
    }
}

static void write_csv_student(void) {
    dbg();

    fprintf(fpcsv, "%s,", "student");
    fprintf(fpcsv, "%s,", &buf[1]); // name starts from buf[1]

    int pos = 0;
    float *pfloat;
    
    for( ; pos < MAX_STR_LEN; pos++) {
        if(buf[pos] == '\0') {
            break;  // end of the name
        }
    }

    pos++;  // point to maths score
    pfloat = (float *)(&buf[pos]);
    fprintf(fpcsv, "%f,", *pfloat);

    pos += 4; // point to english score
    pfloat = (float *)(&buf[pos]);
    fprintf(fpcsv, "%f\n", *pfloat);
}

static void write_csv_employee(void) {
    dbg();

    fprintf(fpcsv, "%s,", "employee");
    fprintf(fpcsv, "%s,", &buf[1]); // name starts from buf[1]

    int pos = 0;
    float *pfloat;
    
    for( ; pos < MAX_STR_LEN; pos++) {
        if(buf[pos] == '\0') {
            break;  // end of the name
        }
    }

    pos++; // point to dept
    fprintf(fpcsv, "%s,", &buf[pos]);

    for( ; pos < MAX_STR_LEN; pos++) {
        if(buf[pos] == '\0') {
            break;  // end of the dept
        }
    }

    pos++;  // point to salary
    pfloat = (float *)(&buf[pos]);
    fprintf(fpcsv, "%f\n", *pfloat);
}


// =========================================== //
#if 0
reference code

#include <stdio.h>
 
float f = 1032.192
char buffer[32];
 
// 执行以下语句,buffer里面就保存了f转换的结bai果
sprintf(buffer, "%f", f);


    float x = 12.347;
    char a[100];
    int len = sprintf(a, "%f", x);
    printf("%s", a);
    printf("\n%d\n", len);
	
        fprintf(fpcsv, "%f", *pfloat);

  fread(buffer, strlen(c)+1, 1, fp);    
	
 if(feof(stream)) {
     .. end of file
 }

#endif
// =========================================== //



