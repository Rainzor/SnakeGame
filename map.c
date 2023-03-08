
//
// Created by 17809 on 2020/12/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int wall_length;
int wall_width;
typedef struct obstacle {
    int x;
    int y;
    struct obstacle *next;
} Obs;
Obs *head_wall;
Obs *p_wall;
Obs *q_wall;

void pos(int x, int y) {
    COORD pos; //创建坐标数组
    HANDLE output;//创建位置
    pos.X = x;
    pos.Y = y;
    output = GetStdHandle(STD_OUTPUT_HANDLE);//标准输出
    SetConsoleCursorPosition(output, pos);//决定光标位置
}

void goto_print(int x, int y) {
    pos(x, y);
    printf("█");//'█'占据两个字符长
}

void Clean_wall() {
    p_wall = head_wall;
    while (p_wall) {   //释放墙的内存；
        q_wall = p_wall->next;
        free(p_wall);
        p_wall = q_wall;
    }
}

void wall();

void map1();

void map2();

void map3();

void map4();

int main() {
    pos(70, 10);
    printf("Welcome to look though map");
    do {
        Sleep(100);
    } while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE));
    system("cls");
    pos(60, 1);
    printf("Map1");
    map1();
    do {
        Sleep(100);
    } while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE));
    Clean_wall();
    system("cls");
    pos(60, 1);
    printf("Map2");
    map2();
    do {
        Sleep(100);
    } while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE));
    Clean_wall();
    system("cls");
    pos(60, 1);
    printf("Map3");
    map3();
    do {
        Sleep(100);
    } while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE));
    Clean_wall();
    system("cls");
    pos(60, 1);
    printf("Map4");
    map4();
    do {
        Sleep(100);
    } while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE));
    Clean_wall();
    system("cls");
    return 0;

}

void wall() {
    int i;
    p_wall = malloc(sizeof(Obs));
    head_wall = p_wall;
    for (i = 40; i <= 40 + wall_length; i += 2) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = i;
        q_wall->y = 5;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 40; i <= 40 + wall_length; i += 2) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = i;
        q_wall->y = 5 + wall_width;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    //打印列
    for (i = 5; i <= 5 + wall_width; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40;
        q_wall->y = i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;

    }
    for (i = 5; i <= 5 + wall_width; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + wall_length;
        q_wall->y = i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
}

void map1() {
    wall_length=50;
    wall_width=20;
    wall();
    pos(0, 0);
    free(p_wall);
    q_wall->next = NULL;
}

void map2() {
    int i;
    wall_length = 60;
    wall_width = 25;
    //打印行
    wall();
    for (i = 1; i < 16; ++i) {
        if(i==4||i==8||i==12) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + 20;
        q_wall->y = 5 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i < 16; i++) {
        if(i==4||i==8||i==12) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + 40;
        q_wall->y = 30 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    free(p_wall);
    q_wall->next = NULL;
    pos(0, 0);
}

void map3() {
    int i;
    wall_length = 80;
    wall_width = 30;
    wall();
    for (i = 1; i <= 11; i ++){
        if (i==6||i==7) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + i*2;
        q_wall->y = 11;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 13; i++) {
        if (i==9) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 62;
        q_wall->y = 11 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i ++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 62 + i*2;
        q_wall->y = 24;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 7; i++) {
        if (i==5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 82;
        q_wall->y = 23 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 11; i ++) {
        if (i==6||i==7) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + wall_length - i*2;
        q_wall->y = 29;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 13; i++) {
        if (i==9) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 98;
        q_wall->y = 29 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i ++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 98 - i*2;
        q_wall->y = 16;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 7; i++) {
        if (i==5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 78;
        q_wall->y = 17 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    free(p_wall);
    q_wall->next = NULL;
    pos(0, 0);
}

void map4() {
    int i;
    wall_length = 100;
    wall_width = 35;
    wall();
    for (i = 1; i <= 9; i ++){
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 68;
        q_wall->y = 5+i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 20; i++) {
        if(i==8||i==16) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 68+i*2;
        q_wall->y = 14;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i ++){
        if(i==4||i==5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 108;
        q_wall->y = 14-i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i ++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 112;
        q_wall->y = 5+wall_width-i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 20; i ++) {
        if(i==8||i==16) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 112-i*2;
        q_wall->y = 31;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i ++) {
        if(i==4||i==5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 72;
        q_wall->y = 31+i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        if(i==5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40+wall_length-2*i;
        q_wall->y = 12;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 8; i ++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 120;
        q_wall->y = 12+i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 26; i++) {
        if(i==8||i==16||i==24) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 120-i*2;
        q_wall->y = 20;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        if(i==5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40+2*i;
        q_wall->y = 33;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 8; i ++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 60;
        q_wall->y = 33-i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 26; i++) {
        if(i==8||i==16||i==24) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 60+i*2;
        q_wall->y = 25;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }

    free(p_wall);
    q_wall->next = NULL;
    pos(0, 0);
}
