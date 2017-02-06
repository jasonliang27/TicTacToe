#ifndef CODEEXCHANGE_H_INCLUDED
#define CODEEXCHANGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define base 3


int check_board[base][base];
struct templat
{
    const int num;
    char piece[3];
    int win;

}PLAYER,AI,NONE;

#endif // CODEEXCHANGE_H_INCLUDED
