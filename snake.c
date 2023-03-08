/*程序分为一下内容
 0：欢迎用户到来；
 1：创建围墙并显示；
 2：初始化蛇身；
 3：随机产生食物；注意事项：食物不能出现在蛇身；
 4：控制蛇的移动；注意事项：蛇不能回头;
 5：吃食物加长蛇；
 6：吃到自己或撞墙游戏结束；
 7：显示分数；
 8: 每一关存在目标分数；
 9: 每一关设置不同地图；
 10: 让游戏加速减速暂停退出
 11：选择是否重新开始
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#define LEN sizeof(Snake)

typedef struct snake {
    int x;
    int y;
    struct snake *next;
} Snake;
Snake *head_snake;
Snake *p_snake;
Snake *Food;

typedef struct obstacle {
    int x;
    int y;
    struct obstacle *next;
} Obs;
Obs *head_wall;
Obs *p_wall;
Obs *q_wall;

int wall_length;
int wall_width;
int Initial_length;
int level = 1;
int LEVERL_score;
int score = 0;
int SPEED;
int add;
char decision = 'y';
char key;
int addition;
int speed = 175;
bool judgement = false;
bool win = false;
bool move = true;
bool cause;
bool judge1, judge2, judge3, judge4;

void Welcome();  //欢迎用户介绍游戏

void pos(int, int); //定位光标

void goto_print(int x, int y);//输出█

void Level();//进入每一关


//不同的地图
void wall();

void map();

void map1();

void map2();

void map3();

void map4();

void creat_snake(); //创建蛇

void creat_food(); //随机产生食物

void move_snake(); //移动蛇

void eat_food();//吃掉食物加长

void not_eat_food();//没吃食物移动

char Redirection();//判断按键位

void Pause();//暂停函数

bool Judge();//判断蛇有没有死

void Clean_snake();// 清除蛇的内存

void Clean_wall(); //清理墙的内存

void Finish();//结束游戏展现动画

char Decide();//决定是否重新开始关卡

int main() {   //初始化数据；
    Welcome();
    while (decision == 'y') {
        while (!judgement) {

            //每一关初始化不同变量
            switch (level) {
                case 1:
                    judge1 = true, judge2 = true, judge3 = true, judge4 = true;
                    key = 'D';
                    add = 10;
                    SPEED = 250;
                    wall_length = 40;
                    wall_width = 20;
                    Initial_length = 4;
                    LEVERL_score = 250;
                    break;
                case 2:
                    judge1 = true, judge2 = true, judge3 = true, judge4 = true;
                    key = 'D';
                    add = 15;
                    SPEED = 225;
                    wall_length = 60;
                    wall_width = 25;
                    Initial_length = 5;
                    LEVERL_score = 500;
                    break;
                case 3:
                    judge1 = true, judge2 = true, judge3 = true, judge4 = true;
                    key = 'D';
                    add = 15;
                    SPEED = 200;
                    wall_length = 80;
                    wall_width = 30;
                    Initial_length = 5;
                    LEVERL_score = 750;
                    break;
                case 4:
                    judge1 = true, judge2 = true, judge3 = true, judge4 = true;
                    key = 'D';
                    add = 20;
                    SPEED = 150;
                    wall_length = 100;
                    wall_width = 35;
                    Initial_length = 6;
                    LEVERL_score = 1000;
                    break;
                default:
                    win = true;
                    break;
            }
            if (win)
                break;
            else {
                pos(80, 15);
                printf("第 %d 关", level);
                Sleep(2500);
                system("cls");
                Level();
                level++;
            }
        }
        Finish();//清除释放内存
        decision = Decide();//决定是否重新开始游戏
        score = 0;
        level = 1;
        speed = 175;
        judgement = false;
        win = false;
        system("cls");
    }
    pos(70, 0);
    printf("再见!");
    return 0;
}

void Welcome() {
    int i;
    pos(0, 0);
    printf("温馨提示，请将终端窗口最大化，游戏体验最佳");

    //这个语句可以使用户等待3500ms或者直接按下回车进行下一个语句
    for (i = 0; i <= 3500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    system("cls");
    pos(70, 1);
    printf("欢迎来到贪吃蛇小游戏");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 3);
    printf("你可以使用键位 \"↑.↓.←.→\" 或者 \"W.S.A.D\" 来移动蛇   ");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }

    pos(60, 5);
    printf("\"F1\"加速  \"F2\"减速  \"Space\"暂停");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 7);
    printf("不要让蛇咬到自己或者撞到墙");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 10);
    printf("现在小蛇已经准备就绪");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 12);
    printf("冲冲冲！开始吧！");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 14);
    system("pause");
    system("cls");
}


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
    printf("■");//'■'占据1个字符长
}

void Level() {
    map();
    creat_snake();  //创建蛇
    creat_food();  //随机产生食物
    while (1) {
        move_snake(); //移动蛇
        key = Redirection(); //判断输入键位
        judgement = Judge();//判断蛇有无死
        if (judgement) break;
        if (score >= LEVERL_score) {
            system("cls");
            Clean_snake();
            Clean_wall();
            break; //升级关卡
        }
    }

}


void wall() {
    int i;
    pos((80 + wall_length) / 2, 1);
    printf("贪吃蛇");
    pos((80 + wall_length) / 2 - 1, 3);
    printf(" 第 %d 关", level);
    pos(46 + wall_length, 5);
    printf("总分： ");
    pos(46 + wall_length, 6);
    printf("每个食物得分：%d", add);
    pos(46 + wall_length, 7);
    printf("目标分数 ：%d", LEVERL_score);
    pos(46 + wall_length, 9);
    printf("游戏规则");
    pos(46 + wall_length, 11);
    printf("不能穿墙，不能咬到自己\n");
    pos(46 + wall_length, 12);
    printf("用↑.↓.←.→ 或者 W.S.A.D分别控制蛇的移动.");
    pos(46 + wall_length, 13);
    printf("F1:加速   F2:减速 ");
    pos(46 + wall_length, 14);
    printf("ESC:退出游戏  SPACE：暂停游戏.");
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
    for (i = 5; i <= 5 + wall_width; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + wall_length;
        q_wall->y = i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 40 + wall_length; i >= 40; i -= 2) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = i;
        q_wall->y = 5 + wall_width;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    //打印列
    for (i = 5 + wall_width; i >= 5; i--) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40;
        q_wall->y = i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;

    }

}

void map() {
    switch (level) {
        case 1:
            map1();
            break;
        case 2:
            map2();
            break;
        case 3:
            map3();
            break;
        case 4:
            map4();
            break;
        default:
            break;
    }
}

void map1() {

    wall();
    free(p_wall);
    q_wall->next = NULL;
}

void map2() {
    int i;

    //打印行
    wall();
    for (i = 1; i < 16; ++i) {
        if (i == 4 || i == 8 || i == 12) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + 20;
        q_wall->y = 5 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i < 16; i++) {
        if (i == 4 || i == 8 || i == 12) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + 40;
        q_wall->y = 30 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    free(p_wall);
    q_wall->next = NULL;
}

void map3() {
    int i;
    wall();
    for (i = 1; i <= 11; i++) {
        if (i == 6 || i == 7) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + i * 2;
        q_wall->y = 11;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 13; i++) {
        if (i == 9) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 62;
        q_wall->y = 11 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 62 + i * 2;
        q_wall->y = 24;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 7; i++) {
        if (i == 5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 82;
        q_wall->y = 23 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 11; i++) {
        if (i == 6 || i == 7) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + wall_length - i * 2;
        q_wall->y = 29;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 13; i++) {
        if (i == 9) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 98;
        q_wall->y = 29 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 98 - i * 2;
        q_wall->y = 16;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 7; i++) {
        if (i == 5) continue;
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
    wall();
    for (i = 1; i <= 9; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 68;
        q_wall->y = 5 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 20; i++) {
        if (i == 8 || i == 16) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 68 + i * 2;
        q_wall->y = 14;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i++) {
        if (i == 4 || i == 5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 108;
        q_wall->y = 14 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 112;
        q_wall->y = 5 + wall_width - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 20; i++) {
        if (i == 8 || i == 16) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 112 - i * 2;
        q_wall->y = 31;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i++) {
        if (i == 4 || i == 5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 72;
        q_wall->y = 31 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        if (i == 5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + wall_length - 2 * i;
        q_wall->y = 12;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 8; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 120;
        q_wall->y = 12 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 26; i++) {
        if (i == 8 || i == 16 || i == 24) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 120 - i * 2;
        q_wall->y = 20;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        if (i == 5) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + 2 * i;
        q_wall->y = 33;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 8; i++) {
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 60;
        q_wall->y = 33 - i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 26; i++) {
        if (i == 8 || i == 16 || i == 24) continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 60 + i * 2;
        q_wall->y = 25;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }

    free(p_wall);
    q_wall->next = NULL;
    pos(0, 0);
}

void creat_snake() {
    //Snake *head,*p为全局变量
    int i;
    p_snake = malloc(LEN);
    p_snake->next = NULL;

    //头插法
    for (i = 0; i < Initial_length; i++) {
        head_snake = p_snake;
        p_snake = malloc(LEN);
        p_snake->next = head_snake;
        head_snake->x = 40 + wall_length - 10;
        head_snake->y = 6 + i;
        goto_print(head_snake->x, head_snake->y);
    }

    free(p_snake);
}

void creat_snake2() {
    //Snake *head,*p为全局变量
    int i;
    p_snake = malloc(LEN);
    p_snake->next = NULL;
    for (i = 0; i < Initial_length; i++) {
        head_snake = p_snake;
        p_snake = malloc(LEN);
        p_snake->next = head_snake;
        head_snake->x = 40 + wall_length - 10;
        head_snake->y = 5 + wall_width - 1;
        goto_print(head_snake->x, head_snake->y);
    }

    free(p_snake);
}

void creat_food() {   //在墙内随机创建食物
    Snake *food = malloc(LEN);
    bool flag = false;
    while (!flag) {
        flag = true;
        srand((unsigned int) time(NULL));
        food->x = rand() % (wall_length - 4) + 42;//food x坐标范围
        if (food->x % 2) (food->x)++;//保证x坐标为偶数
        food->y = rand() % (wall_width - 1) + 6;//food y坐标范围
        p_snake = head_snake;
        while (p_snake) {//食物不能出现在蛇身
            if (food->x == p_snake->x && food->y == p_snake->y)
                flag = false;
            p_snake = p_snake->next;
        }
        p_wall = head_wall;
        while (p_wall) {//食物不能出现在墙
            if (food->x == p_wall->x && food->y == p_wall->y)
                flag = false;
            p_wall = p_wall->next;
        }
    }

    pos(food->x, food->y);
    printf("⊙");
    Food = food; //返回食物的信息，为后面判断有没有吃到食物做准备

}


void move_snake() {
    Snake *next_head = malloc(LEN);
    int x = head_snake->x;
    int y = head_snake->y;
    next_head->next = head_snake;
    head_snake = next_head;
    switch (key) {
        case 'U':
            y--;   //因为坐标本身与常规坐标反向
            break;
        case 'D':
            y++;
            break;
        case 'R':
            x += 2;
            break;
        case 'L':
            x -= 2;
            break;
        default:
            break;
    }
    head_snake->x = x;
    head_snake->y = y;
    goto_print(head_snake->x, head_snake->y);

    //有没有吃到食物
    if (x == Food->x && y == Food->y) {
        eat_food();

    } else
        not_eat_food();

    //调整速度
    addition = (LEVERL_score - score) / 10;
    if (addition == 10 && judge1) {
        add = add + 5;
        speed = SPEED - 40;
        judge1 = false;
    }
    if (addition == 17 && judge2) {
        add = add + 5;
        speed = SPEED - 30;
        judge2 = false;
    }
    if (addition == 24 && judge3) {
        add = add;
        speed = SPEED;
        judge3 = false;
    }
    /* if (addition == 20 && judge4) {
         add = add+5;
         speed = SPEED - 20;
         judge4=false;
     }*/
    Sleep(speed);
    move = true;
    pos(0, 0);
    //控制得分和速度；

}


//没吃食物移动
void not_eat_food() {
    p_snake = head_snake;
    while (p_snake->next->next) {
        p_snake = p_snake->next;
    }
    pos(p_snake->next->x, p_snake->next->y);
    printf("  ");
    pos(0, 0);
    free(p_snake->next);
    p_snake->next = NULL;
}

//吃了食物加长
void eat_food() {
    p_snake = head_snake;
    score += add;
    creat_food();
    pos(56 + wall_length, 5);
    printf("%d", score);
    pos(46 + wall_length, 6);
    printf("每个食物得分：%d", add);
}

//获取按键；
char Redirection() {
    if (move) {
        if (key != 'D' && (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP))) //W键或↑键
            key = 'U';
        else if (key != 'U' && (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)))  //S键或↓键
            key = 'D';
        else if (key != 'L' && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))) //D键或→键
            key = 'R';
        else if (key != 'R' && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))) //A键或←键
            key = 'L';
        move = false;
    }

    //暂停函数
    if (GetAsyncKeyState(VK_SPACE))
        Pause();

    //退出游戏
    if (GetAsyncKeyState(VK_ESCAPE))
        judgement = true;

    //加速语句
    if (GetAsyncKeyState(VK_F1)) {
        if (SPEED > 50) {
            add += 2;
            pos(46 + wall_length, 6);
            printf("每个食物得分：%d", add);
            SPEED -= 15;
        }
    }

    //减速语句
    if (GetAsyncKeyState(VK_F2)) {
        if (SPEED < 400 && add > 5) {
            add -= 2;
            pos(46 + wall_length, 6);
            printf("每个食物得分：%d", add);
            SPEED += 15;
        }
    }
    //**************************
    //神秘按键“，”：跳关 ；
    if (GetAsyncKeyState(VK_F5))
        score = LEVERL_score;
    return key;
}

//暂停函数
void Pause() {
    while (1) {
        Sleep(300);
        if (GetAsyncKeyState(VK_SPACE))
            break;
    }
}

bool Judge() {
    //判断是否撞墙
    p_wall = head_wall;
    while (p_wall) {
        if (head_snake->x == p_wall->x && head_snake->y == p_wall->y) {
            cause = false;//意义在于让蛇撞到墙后，头位置不会把墙撞破
            return true;
        }
        p_wall = p_wall->next;
    }

    //判断是否咬到自己
    p_snake = head_snake->next;
    while (p_snake) {
        if (head_snake->x == p_snake->x && head_snake->y == p_snake->y) {
            cause = true;
            return true;
        } else
            p_snake = p_snake->next;
    }
    return false;
}

//清除内存
void Clean_snake() {
    Snake *q;
    p_snake = head_snake;
    pos(Food->x, Food->y);
    printf("  ");
    free(Food);//释放食物的内存；
    while (p_snake) {   //释放蛇的内存；
        q = p_snake->next;
        pos(p_snake->x, p_snake->y);
        printf("  ");
        free(p_snake);
        p_snake = q;
    }
}

void Clean_wall() {
    p_wall = head_wall;
    while (p_wall) {   //释放墙的内存；
        if (judgement) {
            pos(p_wall->x, p_wall->y);
            printf("  ");
            pos(0, 0);
            Sleep(5);
        }
        q_wall = p_wall->next;
        free(p_wall);
        p_wall = q_wall;
    }
}

void Finish() {
    if (win) {
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 - 2);
        printf("恭喜你通关了！");
        Sleep(5000);
        system("cls");
    } else {

        //展现动画
        Snake *q;
        p_snake = head_snake;
        pos(Food->x, Food->y);
        printf("  ");
        free(Food);
        pos(0, 1);
        if (cause)
            printf("蛇咬到了自己");
        else
            printf("撞到了墙");
        while (p_snake) {   //释放内存 展示动画
            if (cause) {
                pos(p_snake->x, p_snake->y);
                printf("  ");
            }
            cause = true;
            Sleep(60);
            q = p_snake->next;
            free(p_snake);
            p_snake = q;
        }
        Clean_wall();
        system("cls");
        pos((60 + wall_length) / 2, (5 + wall_width) / 2);
        printf("游戏结束");
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 + 2);
        printf("你输了");
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 + 4);
        printf("你最终的分数是 %d", score);
        Sleep(2000);
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 + 6);
        system("pause");
        system("cls");
    }
}
//决定是否重新开始
char Decide() {
    int i;
    char d;
    pos(70, 3);
    printf("是否重新开始游戏？");
    for (i = 0; i <= 1500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(65, 5);
    printf("输入YES继续     或者输入NO退出");
    pos(70, 7);
    while (isspace(d = getchar())) continue;
    while (getchar() != '\n') continue;
    if (isupper(d))
        d = tolower(d);
    return d;
}
