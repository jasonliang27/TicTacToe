#include <string.h>
#include "CodeExchange.h"

void show_checkboard(void);
void refresh_checkboard(int x,int y,int value);
void clean_screen(void);
void user_input(void);
void user_input_err(void);
void entry_setting(void);
void setting_put_tips(int code);
void reset_checkboard(void);
void change_piece(int code);
void show_default(int isnewline,int iscleanbuffer);
void change_colour(void);
void show_colors(int mode);//used:change_color
void show_about(void);
char to_hex(int num);
int getchr(void);

//Var
struct templat NONE= {0,"  ",0};
struct templat PLAYER= {1,"√",0};
struct templat AI= {2,"×"};
const int count_func=7;//used:entry_setting;setting_put_tips
int background_colour=0;
int font_colour=7;
enum change_modes {background,font};
/*char PLAYER[3]="√";
char AI[3]="×";*/
const char* MCE[]=
{
    "请输入坐标(Format:x,y;输入 4,4 设置):x,y\b\b\b",
    "请输入不介于 1 和 %d 的坐标！\n",
    "请按格式输入！",
    "此处已有棋子!"
};

//extern const char * PLAYER;
//extern const char * AI;

void show_checkboard()
{
    int i,j;
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
    int x,y,i;
    int t=0;
    char str[10];

    while(1)
    {
        char temp[9];
        printf(MCE[0]);

        if(scanf("%d,%d",&x,&y)!=2)
        {
            user_input_err();
            puts(MCE[2]);
            continue;
        }
        else
        {
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

            /*Alternative
            char chrx,chry,chrd;
            chrx=(char)getchr();
            chrd=(char)getchr();
            chry=(char)getchr();*/
            refresh_checkboard(x-1,y-1,PLAYER.num);
            break;
        }


    }
}

void refresh_checkboard(int x,int y,int value)
{
    check_board[x][y]=value;
    show_default(1,1);
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


    int i;
    char input;
    int change_piece_choose;
    int change_code;
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
    case 1:
        reset_checkboard();
        break;

    case 2:
        //todo:reset_point
        break;

    case 3:
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
    case 6:
        show_default(1,1);
        break;
    case 4:
        change_colour();
        break;
    case 7:
        exit(0);
        break;
    case 5:
        show_about();
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
        "关于程序",
        "返回游戏",
        "退出游戏"
    };
    const char change_piece_tip[]="1.玩家 2.AI 3.返回";
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
    show_default(1,0);
}

void change_piece(int code)
{
    char input[3];
    int ischagned=0;

    clean_screen();
    printf("\n更改前：%s\n更改后：_\b",code==1?PLAYER.piece:(code==2?AI.piece:NONE.piece));
    scanf("%s",input);
    clean_buffer();
    if(input[0]=='\n')
        goto label_end;
    //clean_buffer();
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
    /*case 3:
        memset(NONE.piece,' ',sizeof(char)*3);
        NONE.piece[0]=input[0];
        if(input[1]!='\0')
            NONE.piece[1]=input[1];
        NONE.piece[2]='\0';
        break;*/
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
    if(isnewline)
        putchar('\n');
}

void change_colour(void)
{
    /*const char* font_colours[]= {"淡绿色", "淡浅绿色", "淡红色", "淡紫色", "淡黄色", "亮白色"};
    const char* background_colours[]={"黑色", "蓝色", "绿色", "浅绿色", "红色", "紫色", "黄色", "白色", "灰色", "淡蓝色"};*/



    int i,input;
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
    //enum change_modes {background,font};
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
    puts("三子棋游戏");
    puts("v1.0.0");
    printf("\n按任意键返回.\n");
    getch();
    show_default(1,0);
}
