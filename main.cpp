#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

const int h = 30, w = 30;
int Map[h + 1][w + 1];
int len;
const int MAX_len = 200;
int dir;

class Node
{
public:
	int x;
	int y;
}body[MAX_len],food;

void Goto(short x,  short y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获得输出设备的句柄
	SetConsoleCursorPosition(hOut, pos);//设置控制台光标位置
}

void MAP()
{
	for (int i = 0; i <= h; i++)
	{
		for (int j = 0; j <= w; j++)
		{
			if (i == 0 || j == 0 || i == h || j == w)
			{
				Map[i][j] = 1;
				cout << "#";
			}
			else
			{
				Map[i][j] = 0;
				cout << " ";
			}
		}
		cout << "\n";
	}
}

void Body()
{
	len = 2;
	body[1].x = 3;
	body[1].y = 3;
	body[len].x = 2;
	body[len].y = 3;
	Goto(body[1].x, body[1].y), cout << "*";
	Goto(body[len].x, body[len].y), cout << "*";
	Goto(0, h+5);
	Map[body[1].x][body[1].y] = Map[body[len].x][body[len].y] = 1;
}

void Food()
{
	srand((unsigned)time(NULL));
	food.x = rand() % (h-1)+1, food.y = rand() % (w-1)+1;
	Goto(food.x, food.y), cout<<"@";
	Goto(0, h+5);
}

int Move()
{
	Node next_move = body[1];
	switch (dir)
	{
	case 0: next_move.x++; break; //向右
	case 1: next_move.y++; break; //向下
	case 2: next_move.x--; break; //向左
	case 3: next_move.y--; break; //向上
	}
	if (Map[next_move.x][next_move.y]) return 0;
	if (next_move.x == food.x && next_move.y == food.y)
	{
		len++;
		Food();
	}
	else
	{
		Goto(body[len].x, body[len].y), cout <<" ";
		Map[body[len].x][body[len].y] = 0;
	}
	Goto(next_move.x, next_move.y), cout << "*";
	Goto(0, h + 5);
	Map[next_move.x][next_move.y] = 1;
	for (int i = len; i > 1; i--)body[i] = body[i - 1];
	body[1] = next_move;
	Sleep(200);
	return 1;
}

int main()
{
	MAP();
	Body();
	Food();
	dir = 0;
	while (1)
	{
		if (_kbhit())
		{
			char ch = _getch();
			int temp = dir;
			switch (ch)
			{
			case 'd': temp = 0; break;
			case 's': temp = 1; break;
			case 'a': temp = 2; break;
			case 'w': temp = 3; break;
			}
			if ((temp + dir) % 2 != 0) dir = temp;
		}
		if (Move()==0)
		{
			return 0;
		}
	}
}