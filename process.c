#include "CodeExchange.h"

void clean_buffer(void);
int check_win(void);
void win(int code);


void clean_buffer(void)
{
    while(getchar()!='\n')
        continue;
}

int check_win(void)
{
    int i,j,current_piece;
    int Pcount=0,Acount=0,Ncount=0;
    int iswin=0;


    /*//row
        for(i=0,Pcount=Acount=Ncount=0; i<base; i++,Pcount=Acount=Ncount=0)
        {
            for(j=0; j<base; j++,current_piece=check_board[i][j])
                if(current_piece==PLAYER.num)
                {
                    if(++Pcount==3)
                    {
                        win(PLAYER.num);
                        iswin=1;
                        break;
                    }
                }

                else if(current_piece==AI.num)
                {
                    if(++Acount==3)
                    {
                        win(AI.num);
                        iswin=1;
                        break;
                    }
                }
                else if(current_piece==NONE.num)
                    Ncount++;
            if(iswin)
                break;
        }

        //col old
        for(i=0,Pcount=0,Acount=0,Ncount=0; i<base; i++)
        {


            for(j=0; j<base; j++,current_piece=check_board[j][i])
                if(current_piece==PLAYER.num)
                {
                    if(++Pcount==3)
                    {
                        win(PLAYER.num);
                        iswin=1;
                        break;
                    }
                }
                else if(current_piece==AI.num)
                {
                    if(++Acount==3)
                    {
                        win(PLAYER.num);
                        iswin=1;
                        break;
                    }
                    else if(current_piece==NONE.num)
                        Ncount++;
                }

            if(iswin)
                break;
        }*/
    /*//col old 22:09
    for(i=0,Pcount=Acount=Ncount=0; i<base; i++,Pcount=Acount=Ncount=0)
    {
        for(j=0; j<base; j++,current_piece=check_board[j][i])
        {
            if(current_piece==PLAYER.num)
            {
                if(++Pcount==3)
                {
                    win(PLAYER.num);
                    iswin=1;
                    break;
                }
            }
            else if(current_piece==AI.num)
            {
                if(++Acount==3)
                {
                    win(AI.num);
                    iswin=1;
                    break;
                }
            }
            else if(current_piece==NONE.num)
                Ncount++;
        }

        if(iswin)
            break;
    }*/

    //col
    for(i=0,Acount=Pcount=Ncount=0; (i<base)||(!iswin); i++,Acount=Pcount=Ncount=0)

    {
        for(j=0; j<base; j++,current_piece=check_board[j][i])
        {
            if(current_piece==PLAYER.num)
            {
                if(++Pcount==3)
                {
                    win(PLAYER.num);
                    iswin=1;
                    break;
                }
            }
            else if(current_piece==AI.num)
            {
                if(++Acount==3)
                {
                    win(AI.num);
                    iswin=1;
                    break;
                }
            }
            else if(current_piece==NONE.num)
                Ncount++;
        }
        if(iswin)
            break;
    }


    return iswin;
}

void win(int code)
{
    getchar();
    clean_screen();
    printf("YOU ARE WINNER!\n");
}
