/* The program consists of the following components:
0: Welcome the user;
1: Create and display the boundary;
2: Initialize the snake;
3: Randomly generate food; Note: The food cannot appear on the snake's body;
4: Control the movement of the snake; Note: The snake cannot turn back;
5: Lengthen the snake when it eats food;
6: End the game if the snake eats itself or hits the boundary;
7: Display the score;
8: There is a target score for each level;
9: Different maps are set for each level;
10: Allow the user to speed up, slow down, pause or quit the game;
11: Ask the user if they want to restart the game. */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define LEN sizeof(Snake)

typedef struct snake {
    int x;
    int y;
    struct snake* next;
} Snake;
Snake* head_snake;
Snake* p_snake;
Snake* Food;

typedef struct obstacle {
    int x;
    int y;
    struct obstacle* next;
} Obs;
Obs* head_wall;
Obs* p_wall;
Obs* q_wall;

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

void Welcome();  // welcome the user

void pos(int, int);  // position the cursor

void goto_print(int x, int y);  // output the cursor

void Level();  // enter the level

// different maps for each level
void wall();

void map();

void map1();

void map2();

void map3();

void map4();

void creat_snake();  // create the snake

void creat_food();  // generate food randomly

void move_snake();  // move the snake

void eat_food();  // eat the food and get longer

void not_eat_food();  // move the snake without eating food

char Redirection();  // determine the key pressed

void Pause();  // pause function

bool Judge();  // determine if the snake is dead

void Clean_snake();  // clear the memory of the snake

void Clean_wall();  // clear the memory of the wall

void Finish();  // end the game and display the animation

char Decide();  // decide whether to restart the level
int main() {    // initialize the data
    Welcome();
    while (decision == 'y') {
        while (!judgement) {
            // initialize different variables for each level
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
                printf("Level %d", level);
                Sleep(2500);
                system("cls");
                Level();
                level++;
            }
        }
        Finish();             // clear the memory
        decision = Decide();  // decide whether to restart the game
        score = 0;
        level = 1;
        speed = 175;
        judgement = false;
        win = false;
        system("cls");
    }
    pos(70, 0);
    printf("Goodbye!");
    return 0;
}

void Welcome() {
    int i;
    pos(0, 0);
    printf("Please maximize the window for the best gaming experience.");

    // This statement waits for 3500ms for the user to press enter or continues to the next statement.
    for (i = 0; i <= 3500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    system("cls");
    pos(70, 1);
    printf("Welcome to the Snake game");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 3);
    printf("You can move the snake using the arrow keys \"↑.↓.←.→\" or \"W.S.A.D\"   ");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }

    pos(60, 5);
    printf("\"F1\" for acceleration, \"F2\" for deceleration, \"Space\" for pause");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 7);
    printf("Do not let the snake bite itself or hit the wall");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 10);
    printf("The snake is ready to go");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 12);
    printf("Let's go! Start playing!");
    for (i = 0; i <= 3000; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(60, 14);
    system("pause");
    system("cls");
}

// Function to set the cursor position on the console screen
void pos(int x, int y) {
    COORD pos;      // create a coordinate array
    HANDLE output;  // create position
    pos.X = x;
    pos.Y = y;
    output = GetStdHandle(STD_OUTPUT_HANDLE);  // standard output
    SetConsoleCursorPosition(output, pos);     // set the cursor position
}

// Function to go to a specific position and print a block character
void goto_print(int x, int y) {
    pos(x, y);
    printf("■");  // print a block character at the position
}

// Function to create the game level, including the snake, food, and obstacles
void Level() {
    map();          // create the game map
    creat_snake();  // create the snake
    creat_food();   // randomly generate food
    while (1) {
        move_snake();         // move the snake
        key = Redirection();  // determine the input direction
        judgement = Judge();  // determine if the snake is dead
        if (judgement)
            break;                    // end the game if the snake is dead
        if (score >= LEVERL_score) {  // if the score is greater than the level score
            system("cls");            // clear the screen
            Clean_snake();            // clean the snake
            Clean_wall();             // clean the obstacles
            break;                    // advance to the next level
        }
    }
}

void wall() {
    int i;
    pos((80 + wall_length) / 2, 1);
    printf("Snake Game");
    pos((80 + wall_length) / 2 - 1, 3);
    printf("Level %d", level);
    pos(46 + wall_length, 5);
    printf("Total Score: ");
    pos(46 + wall_length, 6);
    printf("Each Food Score: %d", add);
    pos(46 + wall_length, 7);
    printf("Target Score: %d", LEVERL_score);
    pos(46 + wall_length, 9);
    printf("Game Rules");
    pos(46 + wall_length, 11);
    printf("Do not go through walls or bite yourself.");
    pos(46 + wall_length, 12);
    printf("Use arrows or W.S.A.D to control the snake.");
    pos(46 + wall_length, 13);
    printf("F1: Increase speed F2: Decrease speed");
    pos(46 + wall_length, 14);
    printf("ESC: Quit Game SPACE: Pause Game.");
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
    // Print columns
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

    // print the wall
    wall();
    for (i = 1; i < 16; ++i) {
        if (i == 4 || i == 8 || i == 12)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + 20;
        q_wall->y = 5 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i < 16; i++) {
        if (i == 4 || i == 8 || i == 12)
            continue;
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
        if (i == 6 || i == 7)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + i * 2;
        q_wall->y = 11;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 13; i++) {
        if (i == 9)
            continue;
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
        if (i == 5)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 82;
        q_wall->y = 23 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 11; i++) {
        if (i == 6 || i == 7)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 40 + wall_length - i * 2;
        q_wall->y = 29;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 13; i++) {
        if (i == 9)
            continue;
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
        if (i == 5)
            continue;
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
        if (i == 8 || i == 16)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 68 + i * 2;
        q_wall->y = 14;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i++) {
        if (i == 4 || i == 5)
            continue;
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
        if (i == 8 || i == 16)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 112 - i * 2;
        q_wall->y = 31;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 9; i++) {
        if (i == 4 || i == 5)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 72;
        q_wall->y = 31 + i;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        if (i == 5)
            continue;
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
        if (i == 8 || i == 16 || i == 24)
            continue;
        q_wall = p_wall;
        p_wall = malloc(sizeof(Obs));
        q_wall->x = 120 - i * 2;
        q_wall->y = 20;
        goto_print(q_wall->x, q_wall->y);
        q_wall->next = p_wall;
    }
    for (i = 1; i <= 10; i++) {
        if (i == 5)
            continue;
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
        if (i == 8 || i == 16 || i == 24)
            continue;
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
    // Snake *head,*p is global variable
    int i;
    p_snake = malloc(LEN);
    p_snake->next = NULL;

    // 头插法
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
    // Snake *head,*p is global variable
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

void creat_food() {  // random food
    Snake* food = malloc(LEN);
    bool flag = false;
    while (!flag) {
        flag = true;
        srand((unsigned int)time(NULL));
        food->x = rand() % (wall_length - 4) + 42;  // food x
        if (food->x % 2)
            (food->x)++;                          // x coordinate must be even
        food->y = rand() % (wall_width - 1) + 6;  // food y 
        p_snake = head_snake;
        while (p_snake) {  // food cannot appear on the snake
            if (food->x == p_snake->x && food->y == p_snake->y)
                flag = false;
            p_snake = p_snake->next;
        }
        p_wall = head_wall;
        while (p_wall) {  // food cannot appear on the wall
            if (food->x == p_wall->x && food->y == p_wall->y)
                flag = false;
            p_wall = p_wall->next;
        }
    }

    pos(food->x, food->y);
    printf("⊙");
    Food = food;  // return food information
}

void move_snake() {
    Snake* next_head = malloc(LEN);
    int x = head_snake->x;
    int y = head_snake->y;
    next_head->next = head_snake;
    head_snake = next_head;
    switch (key) {
        case 'U':
            y--;  // Because the coordinate system is different
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

    // Judge if eat food
    if (x == Food->x && y == Food->y) {
        eat_food();

    } else
        not_eat_food();

    // Velocity Control
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
    // Collision detection
}

// Function to move snake without eating food
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

// Function to increase snake length after eating food
void eat_food() {
    p_snake = head_snake;
    score += add;
    creat_food();
    pos(56 + wall_length, 5);
    printf("%d", score);
    pos(46 + wall_length, 6);
    printf("Each food scores: %d", add);
}
// 获取按键；
// Function to get the direction from user input
char Redirection() {
    // Check if movement is allowed
    if (move) {
        // If key is not 'D' and 'W' or Up arrow key is pressed
        if (key != 'D' && (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)))
            key = 'U';  // Set direction to 'U'
        // If key is not 'U' and 'S' or Down arrow key is pressed
        else if (key != 'U' && (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)))
            key = 'D';  // Set direction to 'D'
        // If key is not 'L' and 'D' or Right arrow key is pressed
        else if (key != 'L' && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)))
            key = 'R';  // Set direction to 'R'
        // If key is not 'R' and 'A' or Left arrow key is pressed
        else if (key != 'R' && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)))
            key = 'L';  // Set direction to 'L'
        move = false;   // Movement is not allowed
    }
    // Pause the game if spacebar is pressed
    if (GetAsyncKeyState(VK_SPACE))
        Pause();

    // Quit the game if escape key is pressed
    if (GetAsyncKeyState(VK_ESCAPE))
        judgement = true;

    // Increase game speed if F1 key is pressed
    if (GetAsyncKeyState(VK_F1)) {
        if (SPEED > 50) {                            // Only increase speed if current speed is greater than 50
            add += 2;                                // Increase score for each food
            pos(46 + wall_length, 6);                // Set cursor position to print score
            printf("Score for each food: %d", add);  // Print score for each food
            SPEED -= 15;                             // Decrease game speed
        }
    }

    // Decrease game speed if F2 key is pressed
    if (GetAsyncKeyState(VK_F2)) {
        if (SPEED < 400 && add > 5) {                // Only decrease speed if current speed is less than 400 and score is greater than 5
            add -= 2;                                // Decrease score for each food
            pos(46 + wall_length, 6);                // Set cursor position to print score
            printf("Score for each food: %d", add);  // Print score for each food
            SPEED += 15;                             // Increase game speed
        }
    }

    // Secret key to skip a level
    if (GetAsyncKeyState(VK_F5))
        score = LEVERL_score;  // Set score to level score

    return key;  // Return the updated direction value
}

// Function to pause the game
void Pause() {
    while (1) {
        Sleep(300);
        if (GetAsyncKeyState(VK_SPACE))
            break;
    }
}

bool Judge() {
    // Judge if snake hits the wall
    p_wall = head_wall;
    while (p_wall) {
        if (head_snake->x == p_wall->x && head_snake->y == p_wall->y) {
            cause = false;  // this is a wall
            return true;
        }
        p_wall = p_wall->next;
    }

    // Judge if snake hits itself
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

// Clear Mem
void Clean_snake() {
    Snake* q;
    p_snake = head_snake;
    pos(Food->x, Food->y);
    printf("  ");
    free(Food);        // Release the memory of food
    while (p_snake) {  // Release the memory of snake
        q = p_snake->next;
        pos(p_snake->x, p_snake->y);
        printf("  ");
        free(p_snake);
        p_snake = q;
    }
}

void Clean_wall() {
    p_wall = head_wall;
    while (p_wall) {  // 释放墙的内存；
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
        // If the player has won
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 - 2);
        printf("Congratulations, you have completed the game!");
        Sleep(5000);
        system("cls");
    } else {
        // If the player has lost Display animation
        Snake* q;
        p_snake = head_snake;
        pos(Food->x, Food->y);
        printf("  ");
        free(Food);
        pos(0, 1);
        if (cause)
            printf("The snake bit itself");
        else
            printf("Collided with a wall");
        while (p_snake) {  // Release memory and show animation
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
        printf("Game Over");
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 + 2);
        printf("You Lost");
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 + 4);
        printf("Your Final Score is %d", score);
        Sleep(2000);
        pos((60 + wall_length) / 2, (5 + wall_width) / 2 + 6);
        system("pause");
        system("cls");
    }
}

// Decide whether to restart the game
char Decide() {
    int i;
    char d;
    pos(70, 3);
    printf("Do you want to restart the game?");
    for (i = 0; i <= 1500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(65, 5);
    printf("Enter YES to continue or NO to exit");
    pos(70, 7);
    while (isspace(d = getchar()))
        continue;
    while (getchar() != '\n')
        continue;
    if (isupper(d))
        d = tolower(d);
    return d;
}
