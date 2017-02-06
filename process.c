#include "CodeExchange.h"
#include <time.h>


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


    //row
    for(i=0,Pcount=Acount=Ncount=0; i<base; i++,Pcount=Acount=Ncount=0)
    {
        //printf("F   i=%2d   P:%d A:%d N:%d\n",i,Pcount,Acount,Ncount);//debug
        for(j=0,current_piece=check_board[i][0]; j<base; j++,current_piece=check_board[i][j])
        {

            if(current_piece==PLAYER.num)
            {
                //puts("A   PLAYER");//debug
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
            //printf("L   j=%2d   P:%d A:%d N:%d CP=%d\n",j,Pcount,Acount,Ncount,current_piece);//debug
        }
        if(iswin)
            break;
    }

//process 50.txt
    //col
    for(i=0,Pcount=Acount=Ncount=0; i<base; i++,Pcount=Acount=Ncount=0)
    {
        //printf("F   i=%2d   P:%d A:%d N:%d\n",i,Pcount,Acount,Ncount);//debug
        for(j=0,current_piece=check_board[0][i]; j<base; j++,current_piece=check_board[j][i])
        {

            if(current_piece==PLAYER.num)
            {
                //puts("A   PLAYER");//debug
                if(++Pcount==3)
                {
                    win(PLAYER.num);
                    iswin=1;
                    //getchar();//debug
                    break;
                }
            }
            else if(current_piece==AI.num)
            {
                //puts("A   AI");//debug
                if(++Acount==3)
                {
                    win(AI.num);
                    iswin=1;
                    break;
                }
            }
            else if(current_piece==NONE.num)
                Ncount++;
            //printf("L   j=%2d   P:%d A:%d N:%d CP=%d\n",j,Pcount,Acount,Ncount,current_piece);//debug
        }
        //printf("H   i=%2d   P:%d A:%d N:%d\n\n",i,Pcount,Acount,Ncount);//debug
        if(iswin)
            break;
    }
    /*{//Debug
        int k;
        for(k=0; k<base; k++)
            printf("%d  %d  %d\n",check_board[k][0],check_board[k][1],check_board[k][2]);

    }*/

    {
        //1,1 2,2 3,3
        if((!((check_board[0][0]==NONE.num)&&(check_board[1][1]==NONE.num)&&(check_board[2][2]==NONE.num)))&&((check_board[0][0]==check_board[1][1])&&(check_board[1][1]==check_board[2][2])&&(check_board[0][0]==check_board[2][2])))
        {
            win(check_board[0][0]);
            iswin=1;
        }
    }
    {
        //1,3 2,2 3,1
        if((!((check_board[0][2]==NONE.num)&&(check_board[1][1]==NONE.num)&&(check_board[2][0]==NONE.num)))&&((check_board[0][2]==check_board[1][1])&&(check_board[1][1]==check_board[2][0])&&(check_board[0][2]==check_board[2][0])))
        {
            win(check_board[0][2]);
            iswin=1;
        }
    }
    {
        //check tie
        int IAF=1;//Is All Full
        int i,j;
        for(i=0; i<base; i++)
            for(j=0; j<base; j++)
                IAF=((check_board[i][j]!=NONE.num)?IAF:0);
        if(IAF&&(!iswin))
        {
            win(NONE.num);
            iswin=1;
        }
    }
    return iswin;
}

void win(int code)
{


    //clean_screen();
    if(code==PLAYER.num)
    {
        PLAYER.points++;
        printf("你赢了!\n");
    }
    else if(code==AI.num)
    {
        AI.points++;
        printf("计算机赢了!\n");
    }
    else
    {
        NONE.points++;
        printf("平局!\n");
    }
    puts("按任意键以开始下一场...");
    clean_buffer();
}

int response_advantages(void)
{
    {
        //row
        int i;
        for(i=0; i<base; i++)
        {
            if((check_board[i][0]==AI.num)&&(check_board[i][1]==AI.num)&&(check_board[i][2]==NONE.num))
            {
                refresh_checkboard(i,2,AI.num);
                return 1;
                break;
            }
            if((check_board[i][0]==AI.num)&&(check_board[i][2]==AI.num)&&(check_board[i][1]==NONE.num))
            {
                refresh_checkboard(i,1,AI.num);
                return 1;
                break;
            }
            if((check_board[i][1]==AI.num)&&(check_board[i][2]==AI.num)&&(check_board[i][0]==NONE.num))
            {
                refresh_checkboard(i,0,AI.num);
                return 1;
                break;
            }
        }
    }
    {
        //col

        int i;
        for(i=0; i<base; i++)
        {
            if((check_board[0][i]==AI.num)&&(check_board[1][i]==AI.num)&&(check_board[2][i]==NONE.num))
            {
                refresh_checkboard(2,i,AI.num);
                return 1;
                break;
            }
            if((check_board[0][i]==AI.num)&&(check_board[2][i]==AI.num)&&(check_board[1][i]==NONE.num))
            {
                refresh_checkboard(1,i,AI.num);
                return 1;
                break;
            }
            if((check_board[1][i]==AI.num)&&(check_board[2][i]==AI.num)&&(check_board[0][i]==NONE.num))
            {
                refresh_checkboard(0,i,AI.num);
                return 1;
                break;
            }
        }
    }
    {
        //0,0 1,1 2,2
        if((check_board[0][0]==AI.num)&&(check_board[1][1]==AI.num)&&(check_board[2][2]==NONE.num))
        {
            refresh_checkboard(2,2,AI.num);
            return 1;
        }
        if((check_board[0][0]==AI.num)&&(check_board[2][2]==AI.num)&&(check_board[1][1]==NONE.num))
        {
            refresh_checkboard(1,1,AI.num);
            return 1;
        }
        if((check_board[1][1]==AI.num)&&(check_board[2][2]==AI.num)&&(check_board[0][0]==NONE.num))
        {
            refresh_checkboard(0,0,AI.num);
            return 1;
        }
    }
    {
        //0,2 1,1 2,0
        if((check_board[0][2]==AI.num)&&(check_board[1][1]==AI.num)&&(check_board[2][0]==NONE.num))
        {
            refresh_checkboard(2,0,AI.num);
            return 1;
        }
        if((check_board[0][2]==AI.num)&&(check_board[2][0]==AI.num)&&(check_board[1][1]==NONE.num))
        {
            refresh_checkboard(1,1,AI.num);
            return 1;
        }
        if((check_board[1][1]==AI.num)&&(check_board[2][0]==AI.num)&&(check_board[0][2]==NONE.num))
        {
            refresh_checkboard(0,2,AI.num);
            return 1;
        }
    }
    return 0;
}

int response_danger(void)
{
    {
        //row
        int i;
        for(i=0; i<base; i++)
        {
            if((check_board[i][0]==PLAYER.num)&&(check_board[i][1]==PLAYER.num)&&(check_board[i][2]==NONE.num))
            {
                refresh_checkboard(i,2,AI.num);
                return 1;
                break;
            }
            if((check_board[i][0]==PLAYER.num)&&(check_board[i][2]==PLAYER.num)&&(check_board[i][1]==NONE.num))
            {
                refresh_checkboard(i,1,AI.num);
                return 1;
                break;
            }
            if((check_board[i][1]==PLAYER.num)&&(check_board[i][2]==PLAYER.num)&&(check_board[i][0]==NONE.num))
            {
                refresh_checkboard(i,0,AI.num);
                return 1;
                break;
            }
        }
    }
    {
        //col

        int i;
        for(i=0; i<base; i++)
        {
            if((check_board[0][i]==PLAYER.num)&&(check_board[1][i]==PLAYER.num)&&(check_board[2][i]==NONE.num))
            {
                refresh_checkboard(2,i,AI.num);
                return 1;
                break;
            }
            if((check_board[0][i]==PLAYER.num)&&(check_board[2][i]==PLAYER.num)&&(check_board[1][i]==NONE.num))
            {
                refresh_checkboard(1,i,AI.num);
                return 1;
                break;
            }
            if((check_board[1][i]==PLAYER.num)&&(check_board[2][i]==PLAYER.num)&&(check_board[0][i]==NONE.num))
            {
                refresh_checkboard(0,i,AI.num);
                return 1;
                break;
            }

        }
    }
     {
        //0,0 1,1 2,2
        if((check_board[0][0]==PLAYER.num)&&(check_board[1][1]==PLAYER.num)&&(check_board[2][2]==NONE.num))
        {
            refresh_checkboard(2,2,AI.num);
            return 1;
        }
        if((check_board[0][0]==PLAYER.num)&&(check_board[2][2]==PLAYER.num)&&(check_board[1][1]==NONE.num))
        {
            refresh_checkboard(1,1,AI.num);
            return 1;
        }
        if((check_board[1][1]==PLAYER.num)&&(check_board[2][2]==PLAYER.num)&&(check_board[0][0]==NONE.num))
        {
            refresh_checkboard(0,0,AI.num);
            return 1;
        }
    }
    {
        //0,2 1,1 2,0
        if((check_board[0][2]==PLAYER.num)&&(check_board[1][1]==PLAYER.num)&&(check_board[2][0]==NONE.num))
        {
            refresh_checkboard(2,0,AI.num);
            return 1;
        }
        if((check_board[0][2]==PLAYER.num)&&(check_board[2][0]==PLAYER.num)&&(check_board[1][1]==NONE.num))
        {
            refresh_checkboard(1,1,AI.num);
            return 1;
        }
        if((check_board[1][1]==PLAYER.num)&&(check_board[2][0]==PLAYER.num)&&(check_board[0][2]==NONE.num))
        {
            refresh_checkboard(0,2,AI.num);
            return 1;
        }
    }
    return response_default();
//label_end2:
    ;
    //return 0;
}

int response_default(void)
{
    /*int i,j;
    if(check_board[i=1][j=1]==NONE.num)
    {
        refresh_checkboard(i,j,AI.num);
        return 1;
    }
    if(check_board[i=0][j=0]==NONE.num)
    {
        refresh_checkboard(i,j,AI.num);
        return 1;
    }
    if(check_board[i=0][j=2]==NONE.num)
    {
        refresh_checkboard(i,j,AI.num);
        return 1;
    }
    if(check_board[i=2][j=0]==NONE.num)
    {
        refresh_checkboard(i,j,AI.num);
        return 1;
    }
    if(check_board[i=2][j=2]==NONE.num)
    {
        refresh_checkboard(i,j,AI.num);
        return 1;
    }
    for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            if(check_board[i][j]==NONE.num)
            {
                refresh_checkboard(i,j,AI.num);
                return 1;
            }*/

    int x,y/*,isres=0*/,i,j;
    srand(time(0));
    if(check_board[1][1]==NONE.num)
    {
        refresh_checkboard(1,1,AI.num);
        return 1;
    }
    else if(rand()%2)
    {
        for(x=rand()%3,y=rand()%3;; x=rand()%3,y=rand()%3)
            if(check_board[x][y]==NONE.num)
            {
                refresh_checkboard(x,y,AI.num);
                return 1;
            }
    }
    else
    {
        switch(rand()%4)
        {
        case 0:
            if(check_board[i=0][j=0]==NONE.num)
            {
                refresh_checkboard(i,j,AI.num);
                return 1;
            }
            break;
        case 1:
            if(check_board[i=0][j=2]==NONE.num)
            {
                refresh_checkboard(i,j,AI.num);
                return 1;
            }
            break;
        case 2:
            if(check_board[i=2][j=0]==NONE.num)
            {
                refresh_checkboard(i,j,AI.num);
                return 1;
            }
            break;
        case 3:
            if(check_board[i=2][j=2]==NONE.num)
            {
                refresh_checkboard(i,j,AI.num);
                return 1;
            }
        }
    }


        for(i=0; i<base; i++)
            for(j=0; j<base; j++)
                if(check_board[i][j]==NONE.num)
                {
                    refresh_checkboard(i,j,AI.num);
                    return 1;
                }

    return 0;
}

