#include <string.h>
#include <math.h>
#include "CodeExchange.h"

//Var
struct templat NONE= {0,"  ","  ",0};
struct templat PLAYER= {1,"√","√",0};
struct templat AI= {2,"×","×",0};
const int count_func=9;//used:entry_setting;setting_put_tips
int background_colour=0;
int font_colour=7;
int reset=0;
int ischangefirst=0;
enum change_modes {background,font};

const char* MCE[]=
{
    "请输入坐标(Format:x,y):x,y\b\b\b",
    "请输入介于 1 和 %d 的坐标或键入 4,4 (进入选项页面)!\a\n",
    "请按格式输入！\a",
    "此处已有棋子!\a",
    "请输入数字!\a"
};

//extern const char * PLAYER;
//extern const char * AI;

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
    char ix,iy;
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
        if(!isdigit(ix=getchr()))
        {
            user_input_err();
            puts(MCE[4]);
            continue;
        }
        putchar(',');
        if((iy=getchr())=='\b')
        {
            show_default(1,0);
            continue;
        }

        if(!isdigit(iy))
        {
            user_input_err();
            puts(MCE[4]);
            continue;
        }
        x=ix-'0';
        y=iy-'0';
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
    show_default(0,0);
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
        while(((change_piece_choose=getchr()-'0'),1)&&(change_piece_choose>3||change_piece_choose<1))
        {
            //clean_buffer();
            setting_put_tips(1);
            setting_put_tips(2);
            printf("请选择:_\b");
        }
        //clean_buffer();
        if(change_piece_choose==3)
            show_default(1,0);
        else
        {
            change_piece(change_piece_choose==1?PLAYER.num:(change_piece_choose==2?AI.num:NONE.num));
            show_default(1,0);
        }
        break;
    case 8://返回
        show_default(1,0);
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
            printf("%d. %s\n",i+1,tips[i]);
        printf("\n请选择:_\b");
        break;
    case 1:
        clean_screen();
        putchar('\a');
        puts("输入错误！请按提示输入！\a");
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
    t_s=clock();
    show_default(1,0);
}

void change_piece(int code)
{
    char input[3];
    int i,isctrl=0,issame=0,loop=0;

    clean_screen();
    printf("请输入更改后的棋子。\n如需返回请键入[Ctrl]+B; 如需恢复默认棋子键入[Ctrl]+D\n默认：%s\n更改前：%s\n更改后：_\b",(code==PLAYER.num?PLAYER.default_piece:(code==AI.num?AI.default_piece:NONE.default_piece)),(code==PLAYER.num?PLAYER.piece:(code==AI.num?AI.piece:NONE.piece)));
    scanf("%s",input);
    input[2]='\0';
    for(i=0; i<2; i++)
        if(!(input[i]=='\0'||input[i]=='\002'||input[i]=='\004'))
            isctrl=iscntrl(input[i])?1:isctrl;
    for(i=0; i<2; i++)
        issame=((input[i])==(*((code==PLAYER.num?AI.piece:PLAYER.piece)+i)));
    clean_buffer();
    if(strchr(input,'\004'))
        for(i=0; i<2; i++)
            loop=((!loop)?((code==PLAYER.num?(*(PLAYER.default_piece+i)):(*(AI.default_piece+i)))==(code==AI.num?(*(PLAYER.piece+i)):(*(AI.piece+i)))):loop);
    while(isctrl||issame||loop)
    {
        clean_screen();
        if(issame)
            printf("请不要输入与%s相同的棋子符号！\a\n",code==PLAYER.num?"计算机":"玩家");
        if(isctrl)
            printf("请不要输入提示外的控制字符!\a\n");
        if(loop)
            printf("默认棋子与%s棋子符号相同!\a请输入其他棋子符号。如需恢复%s默认棋子,请先返回,然后把%s的棋子更改为其他棋子符号,再来更改%s的棋子符号。\n",code==PLAYER.num?"计算机":"玩家",code==PLAYER.num?"玩家":"计算机",code==PLAYER.num?"计算机":"玩家",code==PLAYER.num?"玩家":"计算机");

        isctrl=issame=loop=0;
        printf("请输入更改后的棋子。\n如需返回请键入[Ctrl]+B; 如需恢复默认棋子键入[Ctrl]+D\n默认：%s\n更改前：%s\n更改后：_\b",(code==PLAYER.num?PLAYER.default_piece:(code==AI.num?AI.default_piece:NONE.default_piece)),(code==PLAYER.num?PLAYER.piece:(code==AI.num?AI.piece:NONE.piece)));
        scanf("%s",input);
        clean_buffer();
        //code=(code==1?PLAYER.num:(code==2?AI.num:NONE.num));
        for(i=0; i<2; i++)
            if(!(input[i]=='\0'||input[i]=='\002'||input[i]=='\004'))
                isctrl=iscntrl(input[i])?1:isctrl;
        for(i=0; i<2; i++)
            issame=((input[i]==(*(code==PLAYER.num?AI.piece:PLAYER.piece)+i)?1:issame));
        if(strchr(input,'\004'))
            for(i=0; i<2; i++)
                loop=((!loop)?((code==PLAYER.num?(*(PLAYER.default_piece+i)):(*(AI.default_piece+i)))==(code==AI.num?(*(PLAYER.piece+i)):(*(AI.piece+i)))):loop);
    }
    if(input[0]=='\n')
        return;
    if(strchr(input,'\002'))
        return;
    if(strchr(input,'\004'))
        strcpy(input,(code==1?PLAYER.default_piece:AI.default_piece));
        else
    switch(code)
    {
    case 1:
        memset(PLAYER.piece,' ',sizeof(char)*3);
        /*if(input[1]!='\0')
            PLAYER.piece[1]=input[1];*/
            strcpy(PLAYER.piece,input);
        PLAYER.piece[2]='\0';
        break;
    case 2:
        memset(AI.piece,' ',sizeof(char)*3);;
        /*if(input[1]!='\0')
            AI.piece[1]=input[1];*/
            strcpy(AI.piece,input);
        AI.piece[2]='\0';
        break;
    case 3:
        show_default(1,0);
        break;
    }
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
    printf("1.字体\n2.背景\n3.返回\n请选择:_\b");
    while(((input=getchr()-'0'),1)&&(input>3||input<1))
    {
        /*printf("%d",input);//debug
        clean_buffer();//debug
        getchar();//debug*/
        setting_put_tips(1);
        printf("1.字体\n2.背景\n3.返回\n请选择:_\b");
    }
    clean_screen();
    if(input==3)
    {
        show_default(1,0);
        return;
    }
    show_colors(input==1);
    strcpy(cmd,"color ");
    unit=to_hex(font_colour);
    ten=to_hex(background_colour);
    //printf("%c %c\n",unit,ten);//debug
    *(cmd+6)=ten;
    cmd[7]=unit;
    cmd[8]='\0';
    system(cmd);
    //puts(cmd);//debug
    show_default(1,0);
}

void show_colors(int mode)
{
    int input,i,same=0;
    const char* colours[]= {"黑色","蓝色","绿色","浅绿色","红色","紫色","黄色","白色","灰色","淡蓝色","淡绿色","淡浅绿色","淡红色","淡紫色","淡黄色","亮白色","返回"};//used:change_color
    //clean_buffer();
    for(i=0; i<17; i++)
        printf("%c. %s\n",i>9?'a'+i-10:'0'+i,colours[i]);
    printf("\n请选择%s颜色:_\b",mode?"字体":"背景");
    while(((input=getchr()),1)&&((!isalnum(input))||to_dec(input)>17||to_dec(input)<0||(same=(to_dec(input)==(mode?background_colour:font_colour)))))
    {
        if(same)
        {
            clean_screen();
            printf("\a背景颜色和字体颜色不能相同!\n");
            same=0;
        }
        else
        setting_put_tips(1);
        for(i=0; i<17; i++)
            printf("%c. %s\n",i>9?'a'+i-10:'0'+i,colours[i]);
        printf("\n请选择%s颜色:_\b",mode?"字体":"背景");
    }
    if(input!='g')
    {
        if(mode)
            font_colour=to_dec(input);
        else
            background_colour=to_dec(input);
    }
}

char to_hex(int num)
{
    return (num<10?'0'+num:'a'+num-10);
}

int to_dec(char num)
{
    num=tolower(num);
    return (num>='a'?num-'a'+10:num-'0');
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
        printf("玩家胜 %d 局,负 %d 局   计算机胜 %d 局,负 %d 局   平局 %d 局   %s %d 局   总共 %d 局\n如需进入选项页面,请键入 4,4\n",PLAYER.points,AI.points,AI.points,PLAYER.points,NONE.points,(PLAYER.points>AI.points)?"玩家领先计算机":"计算机领先玩家",abs(PLAYER.points-AI.points),total);
    else
        printf("玩家胜 %d 局,负 %d 局   计算机胜 %d 局,负 %d 局   和棋 %d 局   玩家和计算机暂时打平   总共 %d 局\n如需进入选项页面,请键入 4,4\n",PLAYER.points,AI.points,AI.points,PLAYER.points,NONE.points,total);

}

void show_help()
{
    clean_screen();
    puts("井字棋帮助");
    putchar('\n');
    puts("按任意键退出帮助。");
    putchar('\n');
    puts("对弈方法:");
    puts("    输入横纵坐标以定位棋子落位置。先输入行号，分隔符半角逗号(,)自动添加，然后输入列号，程序将会自动落子。");
    putchar('\n');
    puts("   1    2    3");
    puts("1  √ |    |   ");
    puts("  --------------");
    puts("2  × | × | 〇");
    puts("  --------------");
    puts("3     |    | √");
    puts("       图1");
    putchar('\n');
    puts("    如图1，如果您想落子于圆圈(〇)处，您应单击键盘上的数字2，程序会自动添加半角逗号(,)，然后单击键盘上的数字3，程序自动落子。");
    putchar('\n');
    puts("游戏规则：");
    puts("    与现实中的井字棋规则相同。如有一方横、纵或斜的棋子形成一条线即可胜利。");
    putchar('\n');
    puts("按任意键退出帮助。");
    getch();
    show_default(0,0);
    puts("输入横纵坐标，逗号(,)自动添加");
}

int change_first(void)
{
    int select;
    clean_screen();
    puts("更改先下方可能会重置棋盘。是否继续?");
    puts("1.是 2.否");
    printf("请选择:_\b");
    while(((select=getchr()-'0'),1)&&((select>2)||(select<1)))
    {
        clean_screen();
        //clean_buffer();
        puts("输入错误!请按提示输入!\a");
        puts("更改先下方将重置棋盘。是否继续?");
        puts("1.是 2.否");
        printf("请选择:_\b");
    }
    //clean_buffer();
    clean_screen();
    if(select==1)
    {
        printf("现在先下方: %s \n默认先下方: %s\n",((first==PLAYER.num)?"玩家":"计算机"),"玩家");
        puts("1.玩家 2.计算机 3.返回");
        printf("您想把先下方更改为:_\b");
        while(((select=getchr()-'0'),1)&&((select>3)||(select<1)))
        {
            //clean_buffer();
            clean_screen();
            puts("输入错误!请按提示输入!\a");
            printf("现在先下方: %s \n 默认先下方: %s\n",((first==PLAYER.num)?"玩家":"计算机"),"玩家");
            puts("1.玩家 2.计算机 3.返回");
            printf("您想把先下方更改为:_\b");
        }
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
