#include <stdio.h>
#include <stdlib.h>
#include "CodeExchange.h"

void initialise(void);//debug


int main(void)
{
    //debug
    initialise();

    //start
    int i,j;
    for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            check_board[i][j]=NONE.num;
    clean_screen();
    system("title Èý×ÓÆåÓÎÏ·");
    show_checkboard();
    putchar('\n');
    while(!check_win())
        user_input();

    //end
    clean_buffer();
    getchar();
    return 0;
}

void initialise(void)
{
    int i,j;
    /*for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            check_board[i][j]=1;*/
    //check_board[1][1]=2;


}
