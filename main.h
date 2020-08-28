#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#if 1
#define dbg() \
static int _dbg_cnt_asdf = 0; \
printf("\n--->dbg: %s, %s, %d\n\n", __FILE__, __func__, ++_dbg_cnt_asdf)
#else
#define dbg()
#endif

#define MAX_STR_LEN 50





