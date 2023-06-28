#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100], ntail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

struct termios stored_settings;

void Setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void Draw()
{
    system("clear"); // 清空屏幕

    for (int i = 0; i < width + 2; i++) // 画出上边缘
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) // 画出每一行的内容
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // 左边缘
            if (i == y && j == x)
                cout << "O"; // 蛇头位置
            else if (i == fruity && j == fruitx)
                cout << "F"; // 果实位置
            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#"; // 右边缘
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) // 画出下边缘
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input()
{
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
    {
        switch (c)
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void Logic()
{
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    // 撞墙
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    // 撞到自己
    for (int i = 0; i < ntail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
            gameover = true;
    }

    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;
    }
}

int main()
{
    Setup();
    struct termios new_settings;
    tcgetattr(STDIN_FILENO, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        usleep(50000); // 蛇的速度限制
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &stored_settings);
    return 0;
}
