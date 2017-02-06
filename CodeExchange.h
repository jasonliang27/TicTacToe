#ifndef CODEEXCHANGE_H_INCLUDED
#define CODEEXCHANGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define base 3
#define version "v1.1.2"

int check_board[base][base];
struct templat
{
    const int num;
    char piece[3];
    int points;

}PLAYER,AI,NONE;

//function
//main.c
void initialise(void);//debug
//graph.c
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
void show_points(void);
char to_hex(int num);
int getchr(void);
void show_help(void);
//process.c
void clean_buffer(void);
int check_win(void);
void win(int code);
int response_advantages(void);
int response_danger(void);
int response_default(void);



#endif // CODEEXCHANGE_H_INCLUDED
