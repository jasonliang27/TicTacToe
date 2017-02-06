#include <stdio.h>
#include <stdlib.h>
#include "CodeExchange.h"




int main(void)
{


    //start
    int i,j;
    for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            check_board[i][j]=NONE.num;
    //initialise(); //debug
    clean_screen();
    system("title TicTacToe");
    show_default(0,0);
    putchar('\n');
    while(1)
        user_input();




    //end
    clean_buffer();
    getchar();

    return 0;
}

 //debug
void initialise(void)
{
    //int i,j;
    /*for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            check_board[i][j]=1;*/
    //check_board[1][1]=2;
    /*//Tie
    check_board[0][0]=2;
    check_board[1][0]=2;
    check_board[0][2]=2;
    check_board[2][1]=2;*/
    /*//AI win
    check_board[1][0]=2;
    check_board[1][1]=2;
    check_board[1][2]=2;*/
}
