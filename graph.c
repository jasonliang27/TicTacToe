#include <string.h>
#include <math.h>
#include "CodeExchange.h"

//Var
struct templat NONE= {0,"  ",0};
struct templat PLAYER= {1,"√",0};
struct templat AI= {2,"×"};
const int count_func=9;//used:entry_setting;setting_put_tips
int background_colour=0;
int font_colour=7;
int reset=0;
int ischangefirst=0;
enum change_modes {background,font};

const char* MCE[]=
{
    "请输入坐标(Format:x,y;输入 4,4 进入选项页面):x,y\b\b\b",
    "请输入介于 1 和 %d 的坐标或 4,4 (选项指令)!\n",
    "请按格式输入！",
    "此处已有棋子!"
};

//extern const char * PLAYER;
//extern const char * AI;
extern int getch(void);


void show_checkboard()
{
    int i;
    printf("   1   2    3\n");
    for(i=0; i<base; i++)
    {
        printf("%d %s | %s | %s \n",i+1,(!check_board[i][0])?NONE.piece:(check_board[i][0]==1)?PLAYER.piece:AI.piece,(!check_board[i][1])?NONE.piece:(check_board[i][1]==1?PLAYER.piece:AI.piece),(!check_board[i][2])?NONE.piece:(check_board[i][2]==1?PLAYER.piece:AI.piece));
        if(i!=base-1)
            printf("  -------------\n");
    }
}

void clean_screen(void)
{
    system("cls");
}

void user_input(void)
{
    int x,y;
    char temp;
    while(1)
    {

        if(reset)
        {
            reset_checkboard();
            show_default(1,0);
            reset=0;
            continue;
        }

        printf(MCE[0]);

        if(scanf("%d%c%d",&x,&temp,&y)!=3)
        {
            user_input_err();
            puts(MCE[2]);
            continue;
        }

        if(x>base+1 || y>base+1 ||x<1||y<1)
        {
            user_input_err();
            printf(MCE[1],base);
            continue;
        }
        if(x==4&&y==4)
        {
            entry_setting();
            continue;
        }
        else if ((x==4&&y!=4)||(x!=4&&y==4))
        {
            user_input_err();
            printf(MCE[1],base);
            continue;
        }
        if(check_board[x-1][y-1]!=NONE.num)
        {
            user_input_err();
            puts(MCE[3]);
            continue;
        }
        clean_buffer();
        refresh_checkboard(x-1,y-1,PLAYER.num);
        if(check_win())
        {
            reset_checkboard();
            return;
        }
        if(!response_advantages())
            response_danger();
        if(check_win())
        {
            reset_checkboard();
            return;
        }
    }
}


void refresh_checkboard(int x,int y,int value)
{
    check_board[x][y]=value;
    show_default(1,0);
}

void user_input_err(void)
{
    show_default(0,1);
}

int getchr(void)
{
    return putchar(getch());
}

void entry_setting(void)
{
    char input;
    int change_piece_choose;
    clean_screen();
    while(1)
    {
        setting_put_tips(0);
        input=getchr();
        input-='0';
        if(input<1||input>count_func)
        {
            setting_put_tips(1);
            continue;
        }
        else
            break;
    }
    switch(input)
    {
    case 1://重新开始
        clean_buffer();
        reset_checkboard();
        break;

    case 2://重置计分
        AI.points=PLAYER.points=NONE.points=0;
        show_default(1,0);
        break;

    case 3://更改棋子
        putchar('\n');
        setting_put_tips(2);
        printf("请选择:_\b");
        while(!scanf("%d",&change_piece_choose))
        {
            clean_buffer();
            setting_put_tips(1);
            setting_put_tips(2);
            printf("请选择:_\b");
        }
        clean_buffer();
        if(change_piece_choose==3)
            show_default(1,0);
        else
            change_piece(change_piece_choose==1?PLAYER.num:(change_piece_choose==2?AI.num:NONE.num));
        break;
    case 8://返回
        show_default(1,1);
        break;
    case 4://更改颜色
        change_colour();
        break;
    case 9://退出
        exit(0);
        break;
    case 7://关于
        show_about();
        break;
    case 6://使用说明
        show_help();
        break;
    case 5:
        change_first();
        break;
    }

}

void setting_put_tips(int code)
{
    int i;
    const char* tips[]=
    {
        "重新开始",
        "重置计分",
        "更改棋子",
        "更改背景或字体颜色",
        "更改先下方",
        "使用说明",
        "关于程序",
        "返回游戏",
        "退出游戏"
    };
    const char change_piece_tip[]="1.玩家 2.计算机 3.返回";
    switch(code)
    {
    case 0:
        for(i=0; i<count_func; i++)
            printf("%d. %s   ",i+1,tips[i]);
        printf("\n请选择:_\b");
        break;
    case 1:
        clean_screen();
        putchar('\a');
        puts("输入错误！请按提示输入！");
        break;
    case 2:
        clean_screen();
        puts(change_piece_tip);
        break;

    }

}

void reset_checkboard(void)
{
    int i,j;
    for(i=0; i<base; i++)
        for(j=0; j<base; j++)
            check_board[i][j]=0;
    if(first==AI.num)
        if(!response_advantages())
            response_danger();
    show_default(1,0);
}

void change_piece(int code)
{
    char input[3];

    clean_screen();
    printf("\n更改前：%s\n更改后：_\b",code==1?PLAYER.piece:(code==2?AI.piece:NONE.piece));
    scanf("%s",input);
    clean_buffer();
    if(input[0]=='\n')
        goto label_end;
    code=(code==1?PLAYER.num:(code==2?AI.num:NONE.num));
    switch(code)
    {
    case 1:
        memset(PLAYER.piece,' ',sizeof(char)*3);
        PLAYER.piece[0]=input[0];
        if(input[1]!='\0')
            PLAYER.piece[1]=input[1];
        PLAYER.piece[2]='\0';
        break;
    case 2:
        memset(AI.piece,' ',sizeof(char)*3);
        AI.piece[0]=input[0];
        if(input[1]!='\0')
            AI.piece[1]=input[1];
        AI.piece[2]='\0';
        break;
    case 3:
        show_default(1,0);
        break;
    }

label_end:
    show_default(1,0);

}

void show_default(int isnewline,int iscleanbuffer)
{
    if(iscleanbuffer)
        clean_buffer();
    clean_screen();
    show_checkboard();
    show_points();
    if(isnewline)
        putchar('\n');
}

void change_colour(void)
{
    int input;
    char cmd[10];
    char unit,ten;

    clean_screen();
    printf("1.字体 2.背景\n请选择:_\b");
    while(!scanf("%d",&input)||input>2||input<1)
    {
        setting_put_tips(1);
        clean_buffer();
        printf("1.字体 2.背景\n请选择:_\b");
    }
    clean_screen();
    if(input==1)
        show_colors(font);
    else
        show_colors(background);
    strcpy(cmd,"color ");
    unit=to_hex(font_colour);
    ten=to_hex(background_colour);
    //printf("%c %c\n",unit,ten);//debug
    *(cmd+6)=ten;
    cmd[7]=unit;
    cmd[8]='\0';
    system(cmd);
    //puts(cmd);//debug
    getchar();
    show_default(1,0);
}

void show_colors(int mode)
{
    int input,i;
    const char* colours[]= {"黑色","蓝色","绿色","浅绿色","红色","紫色","黄色","白色","灰色","淡蓝色","淡绿色","淡浅绿色","淡红色","淡紫色","淡黄色","亮白色"};//used:change_color
    for(i=0; i<16; i++)
        printf("%d. %s   ",i+1,colours[i]);
    printf("\n请选择%s颜色:_\b",mode?"字体":"背景");
    while(!scanf("%d",&input)||input>16||input<1)
    {
        setting_put_tips(1);
        clean_buffer();
        for(i=0; i<16; i++)
            printf("%d. %s   ",i+1,colours[i]);
        printf("\n请选择%s颜色:_\b",mode?"字体":"背景");
    }
    if(mode)
        font_colour=input-1;
    else
        background_colour=input-1;
}

char to_hex(int num)
{
    char ret;
    if (num<10)
        ret='0'+num;
    else
        ret='a'+num-10;
    return ret;
}

void show_about(void)
{
    clean_screen();
    printf("井字棋游戏 %s\n\n",STATUS);
    printf("版本    : v%s_%s\n",FULLVERSION_STRING,STATUS_SHORT);
    printf("更新日期: %s.%s.%s\n",YEAR,MONTH,DATE);
    printf("\n按任意键返回.\n");
    getch();
    show_default(1,0);
}

void show_points(void)
{
    int total=PLAYER.points+AI.points+NONE.points;

    if(PLAYER.points!=AI.points)
        printf("玩家胜 %d 局,负 %d 局   计算机胜 %d 局,负 %d 局   平局 %d 局   %s %d 局   总共 %d 局\n",PLAYER.points,AI.points,AI.points,PLAYER.points,NONE.points,(PLAYER.points>AI.points)?"玩家领先计算机":"计算机领先玩家",abs(PLAYER.points-AI.points),total);
    else
        printf("玩家胜 %d 局,负 %d 局   计算机胜 %d 局,负 %d 局   和棋 %d 局   玩家和计算机暂时打平   总共 %d 局\n",PLAYER.points,AI.points,AI.points,PLAYER.points,NONE.points,total);

}

void show_help()
{
    int i;
    clean_screen();
    puts("井字棋帮助");
    putchar('\n');
    puts("按任意键退出帮助。");
    putchar('\n');
    puts("对弈方法:");
    puts("    输入横纵坐标以定位棋子落位置。先输入行号，然后输入分隔符(默认半角逗号(,))，再输入列号，最后单击回车(Enter)。");
    putchar('\n');
    puts("   1    2    3");
    puts("1  √ |    |   ");
    puts("  --------------");
    puts("2  × | × | 〇");
    puts("  --------------");
    puts("3     |    | √");
    puts("       图1");
    putchar('\n');
    puts("    如图1，如果您想落子于圆圈(〇)处，您应输入:");
    putchar('\n');
    puts("                   2,3");
    putchar('\n');
    printf("按任意继续显示余下内容");
    getch();
    for(i=1; i<60; i++)
        printf("\b");
    puts("一般地，您也可以输入:");
    putchar('\n');
    puts("                   2-3");
    putchar('\n');
    puts("但这种方法我们不推荐您使用。");
    putchar('\n');
    puts("游戏规则：");
    puts("    与现实中的井字棋规则相同。如有一方横、纵或斜的棋子形成一条线即可胜利。");
    putchar('\n');
    puts("按任意键退出帮助。");
    getch();
    show_default(0,0);
    puts("先输入横纵坐标，再单击回车(Enter)");
}

int change_first(void)
{
    int select;
    clean_screen();
    puts("更改先下方可能会重置棋盘。是否继续?");
    puts("1.是 2.否");
    printf("请选择:_\b");
    while((!scanf("%d",&select))||(select>3)||(select<1))
    {
        clean_screen();
        clean_buffer();
        puts("输入错误!请按提示输入!");
        puts("更改先下方将重置棋盘。是否继续?");
        puts("1.是 2.否");
        printf("请选择:_\b");
    }
    clean_buffer();
    clean_screen();
    if(select==1)
    {
        printf("现在先下方: %s \n默认先下方: %s\n",((first==PLAYER.num)?"玩家":"计算机"),"玩家");
        puts("1.玩家 2.计算机 3.返回");
        printf("您想把先下方更改为:_\b");
        while((!scanf("%d",&select))||(select>4)||(select<1))
        {
            clean_buffer();
            clean_screen();
            puts("输入错误!请按提示输入!");
            printf("现在先下方: %s \n 默认先下方: %s\n",((first==PLAYER.num)?"玩家":"计算机"),"玩家");
            puts("1.玩家 2.计算机 3.返回");
            printf("您想把先下方更改为:_\b");
        }
        clean_buffer();
        switch(select)
        {
        case 1:
            if(first!=PLAYER.num)
                ischangefirst=reset=1;
            first=PLAYER.num;
            break;
        case 2:
            if(first!=AI.num)
                ischangefirst=reset=1;
            first=AI.num;
            break;
        case 3:
            show_default(1,0);
            return 0;
        }
        show_default(1,0);
    }
    else
    {
        show_default(1,0);
        return 0;
    }
    return 1;
}
