#include <iostream>
#include <fstream>
#include <graphics.h>
using namespace std;
int start();
void game();
void help();
void about();
void intro();
void funcpy();
void square();
void classic();
int typeselect();
void gameselect();
void backbutton();
void dsquare(int, int);
int hcheckbox(int, int);
int vcheckbox(int, int);
int getnumber(int, int);
void score(int, int, int);
/*---------------------------- horizontal rectangle class start----------------------*/
class recth
{
protected:
    int x, y, n;

public:
    int color;
    static int w;
    recth() {}
    recth(int x, int y)
    {
        this->x = x;
        this->y = y;
        color = 1;
        n = w;
        w++;
    }
    void draw()
    {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        rectangle(x - 30, y - 10, x + 30, y + 10);
        floodfill(x, y, color);
    }
    inline void selected()
    {
        color = 2;
    }
};
int recth::w;
/*---------------------------- horizontal rectangle class end----------------------*/
/*---------------------------- vertical rectangle class start----------------------*/
class rectv : public recth
{
public:
    static int u;
    rectv() {}
    rectv(int x, int y)
    {

        this->x = x;
        this->y = y;
        color = 1;
        n = u;
        u++;
    }
    void draw()
    {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        rectangle(x - 10, y - 30, x + 10, y + 30);
        floodfill(x, y, color);
    }
    void selected()
    {
        color = 2;
    }
};
int rectv::u;
recth h[29];
rectv v[29];
/*---------------------------- vertical rectangle class end----------------------*/
void board(int p, int q, int flag);
/*----------------------------main() start---------------------------*/
int main()
{
    int select;
    initwindow(700, 700, "", -3, -3);
    setbkcolor(CYAN);
    intro();
    cleardevice();
menu:
    funcpy();
    select = start();
    cleardevice();
    switch (select)
    {
    case 1:
        game();
        goto menu;
    case 2:
        help();
        goto menu;
    case 3:
        about();
        goto menu;
    case 4:
        classic();
        goto menu;
    }
    getch();
    return 0;
}
/*----------------------------main() end--------------------------*/
/*----------------------------game() start-------------------------*/
void game()
{
    int x, y, number, flag = 0;
    POINT cursorpos;

    int i, j, box = 0, a = 0, p = 0, q = 0;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 5; j++)
        {
            h[a] = recth(70 + j * 100, 20 + i * 100);
            v[a] = rectv(20 + i * 100, 70 + j * 100);
            a++;
        }
    }
    while (1)
    {

        for (int a = 0; a < 30; a++)
        {
            if (h[a].color == 2 && v[a].color == 2)
            {
                if (a == 29)
                {
                    if (p > q)
                    {
                        settextstyle(8, 0, 5);
                        outtextxy(100, 600, "Player one is winner");
                    }
                    else
                    {
                        settextstyle(8, 0, 5);
                        outtextxy(100, 600, "player 2 is winner");
                    }
                }
                else
                    continue;
            }
            else
                break;
        }

        board(p, q, flag);
        while (1)
        {
            if (GetAsyncKeyState(VK_LBUTTON))
            {
                GetCursorPos(&cursorpos);
                x = cursorpos.x;
                y = cursorpos.y;
                if (x > 575 && x < 675 && y > 550 && y < 600)
                {
                    goto bac;
                }
                number = getnumber(x, y);
                if (number >= 0 && number <= 29 && h[number].color == 1)
                {
                    h[number].selected();
                    box = hcheckbox(number, flag);
                    if (flag == 0)
                    {
                        p = p + box;
                        if (box == 0)
                        {
                            flag = 1;
                        }
                    }
                    else
                    {
                        q = q + box;
                        if (box == 0)
                        {
                            flag = 0;
                        }
                    }
                    goto iterate;
                }
                if (number >= 30 && number <= 59 && v[number - 30].color == 1)
                {
                    v[number - 30].selected();
                    box = vcheckbox(number - 30, flag);
                    if (flag == 0)
                    {
                        p = p + box;
                        if (box == 0)
                        {
                            flag = 1;
                        }
                    }
                    else
                    {
                        q = q + box;
                        if (box == 0)
                        {
                            flag = 0;
                        }
                    }
                }
                goto iterate;
            }
        }
    iterate:;
    }
bac:
    cleardevice();
}
/*----------------------------game() end------------------------------*/
/*----------------------------checkbox() start------------------------------*/
int hcheckbox(int n, int flag)
{
    settextstyle(8, 0, 8);
    int leftup, rightup, leftdown, rightdown, top, down;
    top = n - 5;
    down = n + 5;
    leftup = 5 * (n % 5) + (n / 5) - 1;
    rightup = leftup + 5;
    leftdown = leftup + 1;
    rightdown = rightup + 1;
    if (n == 1 || n == 2 || n == 3 || n == 4 || n == 0)
    {
        if (h[down].color == 2 && v[leftdown].color == 2 && v[rightdown].color == 2)
        {
            if (flag == 0)
            {
                outtextxy(40 + (n % 5) * 100, (n / 5) * 100 + 30, "o");
            }
            else
            {
                outtextxy(40 + (n % 5) * 100, (n / 5) * 100 + 30, "x");
            }
            return 1;
        }
        else
            return 0;
    }
    else if (n == 26 || n == 27 || n == 28 || n == 29 || n == 25)
    {
        if (h[top].color == 2 && v[leftup].color == 2 && v[rightup].color == 2)
        {
            if (flag == 0)
            {
                outtextxy(40 + (n % 5) * 100, (n / 5) * 100 - 70, "o");
            }
            else
            {
                outtextxy(40 + (n % 5) * 100, (n / 5) * 100 - 70, "x");
            }
            return 1;
        }
        else
            return 0;
    }
    else
    {
        if (h[top].color == 2 && v[leftup].color == 2 && v[rightup].color == 2)
        {
            if (h[down].color == 2 && v[leftdown].color == 2 && v[rightdown].color == 2)
            {
                if (flag == 0)
                {
                    outtextxy(40 + (n % 5) * 100, (n / 5) * 100 + 30, "o");
                    outtextxy(40 + (n % 5) * 100, (n / 5) * 100 - 70, "o");
                }
                else
                {
                    outtextxy(40 + (n % 5) * 100, (n / 5) * 100 + 30, "x");
                    outtextxy(40 + (n % 5) * 100, (n / 5) * 100 - 70, "x");
                }
                return 2;
            }
            else
            {
                if (flag == 0)
                {
                    outtextxy(40 + (n % 5) * 100, (n / 5) * 100 - 70, "o");
                }
                else
                {
                    outtextxy(40 + (n % 5) * 100, (n / 5) * 100 - 70, "x");
                }
                return 1;
            }
        }
        else if (h[down].color == 2 && v[leftdown].color == 2 && v[rightdown].color == 2)
        {
            if (flag == 0)
            {
                outtextxy(40 + (n % 5) * 100, (n / 5) * 100 + 30, "o");
            }
            else
            {
                outtextxy(40 + (n % 5) * 100, (n / 5) * 100 + 30, "x");
            }
            return 1;
        }
        else
            return 0;
    }
}
int vcheckbox(int n, int flag)
{
    settextstyle(8, 0, 8);
    int leftup, rightup, leftdown, rightdown, top, down;
    top = n - 5;
    down = n + 5;
    rightup = 5 * (n % 5) + (n / 5) - 1;
    leftup = rightup + 5;
    leftdown = leftup + 1;
    rightdown = rightup + 1;
    if (n == 1 || n == 2 || n == 3 || n == 4 || n == 0)
    {
        if (v[down].color == 2 && h[leftdown].color == 2 && h[rightdown].color == 2)
        {
            if (flag == 0)
            {
                outtextxy(40 + (n / 5) * 100, 30 + (n % 5) * 100, "o");
            }
            else
            {
                outtextxy(40 + (n / 5) * 100, 30 + (n % 5) * 100, "x");
            }
            return 1;
        }
        else
            return 0;
    }
    else if (n == 26 || n == 27 || n == 28 || n == 29 || n == 25)
    {
        if (v[top].color == 2 && h[leftup].color == 2 && h[rightup].color == 2)
        {
            if (flag == 0)
            {
                outtextxy((n / 5) * 100 - 60, 30 + (n % 5) * 100, "o");
            }
            else
            {
                outtextxy((n / 5) * 100 - 60, 30 + (n % 5) * 100, "x");
            }
            return 1;
        }
        else
            return 0;
    }
    else
    {
        if (v[top].color == 2 && h[leftup].color == 2 && h[rightup].color == 2)
        {
            if (v[down].color == 2 && h[leftdown].color == 2 && h[rightdown].color == 2)
            {
                if (flag == 0)
                {
                    outtextxy(40 + (n / 5) * 100, 30 + (n % 5) * 100, "o");
                    outtextxy((n / 5) * 100 - 60, 30 + (n % 5) * 100, "o");
                }
                else
                {
                    outtextxy(40 + (n / 5) * 100, 30 + (n % 5) * 100, "x");
                    outtextxy((n / 5) * 100 - 60, 30 + (n % 5) * 100, "x");
                }
                return 2;
            }
            else
            {
                if (flag == 0)
                {
                    outtextxy((n / 5) * 100 - 60, 30 + (n % 5) * 100, "o");
                }
                else
                {
                    outtextxy((n / 5) * 100 - 60, 30 + (n % 5) * 100, "x");
                }
                return 1;
            }
        }
        else if (v[down].color == 2 && h[leftdown].color == 2 && h[rightdown].color == 2)
        {
            if (flag == 0)
            {
                outtextxy(40 + (n / 5) * 100, 30 + (n % 5) * 100, "o");
            }
            else
            {
                outtextxy(40 + (n / 5) * 100, 30 + (n % 5) * 100, "x");
            }
            return 1;
        }
        else
            return 0;
    }
}
/*----------------------------checkbox() end------------------------------*/
/*----------------------------getnumber() start-------------------------*/
int getnumber(int x, int y)
{
    int xco, yco, n = 100;
    for (int i = 0; i < 6; i++)
    {
        if (y > (10 + 100 * i) && y < (30 + 100 * i))
        {
            int yco = 20 + 100 * i;
            for (int j = 0; j < 5; j++)
            {
                if (x > (40 + 100 * j) && x < (100 + 100 * j))
                {
                    xco = 70 + 100 * j;
                    n = (xco / 100 + yco / 100 * 5);
                    break;
                }
            }
            break;
        }
        if (x > (10 + 100 * i) && x < (30 + 100 * i))
        {
            int xco = 20 + 100 * i;
            for (int j = 0; j < 5; j++)
            {
                if (y > (40 + 100 * j) && y < (100 + 100 * j))
                {
                    yco = 70 + 100 * j;
                    n = (yco / 100 + xco / 100 * 5) + 30;
                    break;
                }
            }
            break;
        }
    }
    return n;
}
/*----------------------------getnumber() end-------------------------*/
/*----------------------------backbutton() start-------------------------*/
void backbutton()
{
    settextstyle(8, 0, 2);
    rectangle(575, 550, 675, 600);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(595, 575, BLUE);
    settextstyle(8, 0, 5);
    outtextxy(576, 551, "BACK ");
}
/*----------------------------backbutton() end-------------------------*/
/*----------------------------score() start-------------------------*/
void score(int p, int q, int flag)
{
    char r[5], s[5], t[5];
    sprintf(r, "%d", p);
    sprintf(s, "%d", q);
    sprintf(t, "%d", flag + 1);
    setcolor(BLUE);
    settextstyle(8, 0, 1);
    outtextxy(560, 10, "Score ");
    outtextxy(560, 50, "player 1:");
    outtextxy(560, 90, "player 2:");
    outtextxy(660, 50, r);
    outtextxy(660, 90, s);
    outtextxy(560, 130, "turn :");
    outtextxy(580, 170, "player");
    outtextxy(660, 170, t);
}
/*----------------------------start() end-------------------------*/
/*----------------------------board() start----------------------*/
void board(int p, int q, int flag)
{
    for (int i = 0; i < 30; i++)
    {
        h[i].draw();
        v[i].draw();
        square();
        funcpy();
    }
    score(p, q, flag);
    backbutton();
}
/*----------------------------board() end-------------------------*/
/*----------------------------square() start-------------------------*/
void square()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            dsquare(20 + 100 * i, 20 + 100 * j);
        }
    }
}
/*----------------------------square() end-------------------------*/
/*----------------------------dsquare() start------------------------*/
void dsquare(int x, int y)
{
    setcolor(0);
    rectangle(x - 10, y - 10, x + 10, y + 10);
    setfillstyle(SOLID_FILL, 0);
    floodfill(x, y, 0);
}
/*----------------------------dsquare() end-------------------------*/
void funcpy()
{
    setcolor(1);
    settextstyle(8, 0, 1);
    outtextxy(100, 650, "Copyright 2022© team D-DMA.All rights reserved.");
}
/*-----------------------------About() start---------------------------*/
void about()
{
    int x, y;
    string str;
    char *about;
    POINT cursorpos;
    funcpy();
    settextstyle(8, 0, 2);
    ifstream in("Assets./about.txt");
    for (int i = 0; i < 20; i++)
    {
        getline(in, str);
        about = &str[0];
        outtextxy(100, 100 + i * 20, about);
    }
    readimagefile("Assets./fwulogo.jpg", 75, 125, 150, 200);
   readimagefile("Assets./anuu.jpeg", 80, 210, 150, 280);
    readimagefile("Assets./deep.jpg", 80, 285, 150, 355);
   readimagefile("Assets./akki.jpg", 80, 360, 150, 430);
 readimagefile("Assets./menu.jpeg", 80, 435, 150, 505);
    backbutton();
    while (1)
    {
        GetCursorPos(&cursorpos);
        x = cursorpos.x;
        y = cursorpos.y;
        if (GetAsyncKeyState(VK_LBUTTON) && x > 575 && x < 675 && y > 550 && y < 600)
        {
            cleardevice();
            break;
        }
    }
}
/*-----------------------------About end---------------------------*/
/*-----------------------------Help---------------------------*/
void help()
{
    int x, y;
    POINT cursorpos;
    funcpy();
    settextstyle(8, 0, 2);
    string str;
    char *rule;
    ifstream in("Assets./gamerule.txt");
    for (int i = 0; i < 20; i++)
    {
        getline(in, str);
        rule = &str[0];
        outtextxy(30, 50 + i * 30, rule);
    }
    backbutton();
    while (1)
    {
        GetCursorPos(&cursorpos);
        x = cursorpos.x;
        y = cursorpos.y;
        if (GetAsyncKeyState(VK_LBUTTON) && x > 575 && x < 675 && y > 550 && y < 600)
        {
            cleardevice();
            break;
        }
    }
}
/*-----------------------------help end-----------------------*/
/*-----------------------------start menu-----------------------*/
int start()
{
    int x, y, s;
    POINT cursorpos;
    setcolor(BLUE);
    rectangle(250, 190, 380, 240);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(275, 225, BLUE);
    settextstyle(8, 0, 5);
    outtextxy(251, 191, "START");

    rectangle(250, 250, 380, 300);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(275, 275, BLUE);
    settextstyle(8, 0, 5);
    outtextxy(251, 251, "HELP ");

    rectangle(250, 310, 380, 360);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(275, 325, BLUE);
    settextstyle(8, 0, 5);
    outtextxy(251, 311, "ABOUT");

    rectangle(250, 370, 430, 420);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(275, 375, BLUE);
    settextstyle(8, 0, 5);
    outtextxy(251, 371, "CLASSIC");
    while (1)
    {
        GetCursorPos(&cursorpos);
        x = cursorpos.x;
        y = cursorpos.y;
        if (GetAsyncKeyState(VK_LBUTTON) && x > 250 && x < 380 && y > 190 && y < 240)
        {
            s = 1;
            break;
        }
        else if (GetAsyncKeyState(VK_LBUTTON) && x > 250 && x < 380 && y > 250 && y < 300)
        {
            s = 2;
            break;
        }
        else if (GetAsyncKeyState(VK_LBUTTON) && x > 250 && x < 380 && y > 310 && y < 360)
        {

            s = 3;
            break;
        }
        else if (GetAsyncKeyState(VK_LBUTTON) && x > 250 && x < 430 && y > 370 && y < 420)
        {

            s = 4;
            break;
        }
    }
    return s;
}
/*--------------------------start menu end----------------------*/
/*----------------Welcome Animation  Start----------------------*/
void intro()
{
    for (int i = 10; i < 200; i++)
    {
        setcolor(4);
        outtextxy(250, 400 - i, "Welcome to GameBlocks");
        outtextxy(250, 420 - i, "Loading....");
        delay(1);
        cleardevice();
    }
}
/*----------------Welcome Animation  end------------------------*/
/*---------------------classic game start--------------------*/
class classcircle : public recth
{
public:
    classcircle() {}
    classcircle(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void draw()
    {
        setcolor(BLUE);
        circle(x, y, 2);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(x, y, BLUE);
    }
};
void classic()
{
    int x, y;
    POINT cursorpos;
    funcpy();
    backbutton();
    square();
    delay(1000);
    while (1)
    {
        GetCursorPos(&cursorpos);
        x = cursorpos.x;
        y = cursorpos.y;
        if (GetAsyncKeyState(VK_LBUTTON) && x > 575 && x < 675 && y > 550 && y < 600)
        {
            cleardevice();
            goto backk;
        }
        else if (GetAsyncKeyState(VK_LBUTTON))
        {
            classcircle cir(x, y);
            cir.draw();
        }
    }
backk:
    cleardevice();
}
/*---------------------classic game end--------------------*/
