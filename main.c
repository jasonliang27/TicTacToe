#include <stdio.h>
#include <stdlib.h>
#include "CodeExchange.h"

extern clock_t t_s;
int first_t=1;//first for timing(process.c)

int main(void)
{

    /*int x;
    while(1)
    {
        x=getchr();
        printf("\nx=%d %c todec(x)=%d %c num>='a' %d 'a' %d xsalnum(x)=%d tolower(x)=%d %c isalpha(x)=%d isalpha(x)?tolower(x):x=%d\n\n",x,x,to_dec(x),to_dec(x),x>='a','a',isalnum(x),tolower(x),tolower(x),isalpha(x),isalpha(x)?tolower(x):x);
    }*/


    //start
    int i,j;
    first=PLAYER.num;
    for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            check_board[i][j]=NONE.num;
    //initialise(); //debug
    clean_screen();
    system("title TicTacToe");
    show_default(0,0);
    putchar('\n');
    t_s=clock();
    while(1)
        user_input();




    //end
    //clean_buffer();
    //getchar();

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
