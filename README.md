# 贪吃蛇程序设计

> 本文主要讲述了一个简单的贪吃蛇程序设计，适合初学者，我将一步步的编写程序，并配上详细描述。

## 简介

本文的代码比较简单，只涉及一些的控制台知识，适合初学者学习。

## 1.光标移动函数

先写一个光标移动函数。

```c++
1. void Goto(short x, short y)
   {
   	COORD pos = { x,y };
   	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获得输出设备的句柄
   	SetConsoleCursorPosition(hOut, pos);//设置控制台光标位置
   }
```

## 2.地图函数

在写地图地图之前，我们先确定好地图的大小，我就简单的设置长宽都为30。

```c++
const int h = 30, w = 30;
```

然后用一个二维数组来作为地图。

```c++
int Map[h + 1][w + 1];
```

接着我们用两个循环，将地图的边框画出来。

```c++
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
		cout<<"\n";
	}
}
```

这时候，我们就拥有了最基本的地图。

## 3.贪吃蛇身体

有了地图之后，我们就需要进入主角的设计了。想一下，一个贪吃蛇的身体是由x轴和y轴上的点来确定的，这和我们之后要设计的食物是一样的，共同点是他们都需要一个坐标来确定位置，不同的是贪吃蛇由玩家控制，而食物是随机生成的。因此我们先写一个确定xy点的类。

```c++
class Node
{
public:
	int x;
	int y;
}body[MAX_len],food;
```

之后是贪吃蛇的长度变量和贪吃蛇最大的长度，注意是全局变量。

```c++
int len;
const int MAX_len = 200;
```

接着就可以绘制贪吃蛇。我们把蛇头设置为数组[1]，然后初始长度设置为2。之后，len会因为吃到食物而不断增加，当然这是后面讨论的问题。用Goto函数将贪吃蛇画出来，注意最后一句话，这是把光标移到地图之外。

```c++
void Body()
{
    len=2;
	body[1].x = 3;
	body[1].y = 3;
	body[len].x = 2;
	body[len].y = 3;
	Goto(body[1].x, body[1].y), cout << "*";
	Goto(body[len].x, body[len].y), cout << "*";
	Goto(0, h+5);
}
```

## 4.食物的重要性

最后就是地图上最后一个物体，食物，也是整个贪吃蛇的目标。食物的生成就通过随机函数来完成。

```c++
void Food()
{
	srand((unsigned)time(NULL));
	food.x = rand() % (h-1)+1, food.y = rand() % (w-1)+1;
	Goto(food.x, food.y), cout<<"@";
	Goto(0, h+5);
}
```

## 5.可以开始操纵方向了

操作方向过程，先是玩家输入按键，然后判断输入的方向，接着贪吃蛇转身，完成动作。我们一步步来完成这些工序。

第一步，先给一个方向的全局变量：

```c++
int dir;
```

第二步，先判断输入按键：

```c++
char ch;
int temp;
if (kbhit()) ch = getch();
{

}
```

第三步，我们判断玩家输入的方向，然后将方向赋予一个数值：

```c++
switch (ch)
{
	case 'd': temp = 0; break;
	case 's': temp = 1; break;
	case 'a': temp = 2; break;
	case 'w': temp = 3; break;
}
```

第四步，这些方向还不能出现180度的反转，比如说正在向右走，它只能再向上或者向下掉头。

```c++
if ((temp + dir) % 2 != 0) dir = temp;
```

这样我们就可以操作贪吃蛇的方向了。

## 6.让贪吃蛇动起来

要知道，一整条贪吃蛇，其实就是一小点一小点累计起来。我们的主要思路就是让头向前移动。只需要判断，头部的移动模式。

头部向前移动，有三种情况：

1.撞上墙

2.吃到食物

3.前面是空的

之后头后面的身体覆盖头部的位置，其他身体也是一样的，后面的顶替前面的位置。

```c++
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
		Goto(body[len].x, body[len].y), cout << " ";
		Map[body[len].x][body[len].y] = 0;
	}
	Goto(next_move.x, next_move.y), cout << "*";
	Goto(0, h + 5);
	Map[next_move.x][next_move.y] = 1;
	for (int i = len; i > 1; i--)body[i] = body[i - 1];
	body[1] = next_move;
	Sleep(100);
	return 1;
}
```

