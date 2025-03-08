#include "snake.h"

/*全局变量定义*/
Snake snake;			// 定义蛇结构体变量
Food food;				// 定义食物结构体变量
Barrier barrier;		// 定义障碍物结构体变量
char now_Dir = RIGHT;	// 当前蛇头方向
char direction = RIGHT; // 预期蛇头方向
Data data[100];			// 用户记录
int unknown_food;		// 食物代表的分数
int x = 2;				// 设置判断速度全局变量
/*主菜单实现*/
int Menu()
{
	GotoXY(40, 12); // 定位光标位置
	printf("欢迎来到贪吃蛇小游戏");
	GotoXY(43, 14);
	printf("1.开始游戏");
	GotoXY(43, 16);
	printf("2.帮助");
	GotoXY(43, 18);
	printf("3.关于");
	GotoXY(43, 20);
	printf("4.排行榜");
	GotoXY(43, 22);
	printf("其他任意键退出游戏");

	Hide(); // 隐藏光标
	char ch;
	int result = 0;
	ch = _getch(); // 接收用户输入的菜单选项
	switch (ch)
	{ // 根据选项设置返回结果值
	case '1':
		result = 1;
		break;
	case '2':
		result = 2;
		break;
	case '3':
		result = 3;
		break;
	case '4':
		result = 4;
		break;
	}
	system("cls"); // 调用系统命令cls完成清屏操作
	return result;
}

// 光标定位函数，将光标定位到(x,y)坐标位置
void GotoXY(int x, int y)
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

/*隐藏光标*/
void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = {1, 0};
	SetConsoleCursorInfo(hout, &cor_info);
}

/*关于菜单实现*/
void About()
{
	GotoXY(30, 12);
	printf("杭州电子科技大学--程序设计综合实践案例");
	GotoXY(43, 14);
	printf("贪吃蛇-控制台游戏");
	GotoXY(43, 16);
	printf("按任意键返回上级菜单");
	Hide(); // 隐藏光标
	char ch = _getch();
	system("cls");
}

/*帮助菜单实现*/
void Help()
{
	GotoXY(40, 12);
	printf("w 上");
	GotoXY(40, 14);
	printf("s 下");
	GotoXY(40, 16);
	printf("a 左");
	GotoXY(40, 18);
	printf("d 右");
	GotoXY(40, 20);
	printf("q 加速");
	GotoXY(40, 22);
	printf("e 减速");
	GotoXY(40, 24);
	printf("当蛇撞到自身或撞墙时游戏结束");
	GotoXY(45, 26);
	printf("按任意键返回上级菜单");
	Hide(); // 隐藏光标
	char ch = _getch();
	system("cls");
}

/*初始化地图函数*/
void InitMap()
{
	SetConsoleOutputCP(936);
	Hide(); // 隐藏光标
	// 设置蛇头位置在地图中心
	snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y); // 将光标移动到蛇头位置
	SetColor(11);
	printf("@");	   // 打印蛇头
	snake.length = 3;  // 设置蛇长初始值为3节
	snake.speed = 250; // 设置蛇初始移动速度为250
	now_Dir = RIGHT;   // 当前蛇头方向
	// 显示蛇身
	for (int i = 1; i < snake.length; i++)
	{
		// 设置蛇身的纵坐标位置和蛇头位置相同
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
		// 设置蛇身的横坐标位置，蛇身在蛇头的左边,所以横坐标依次减1
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y); // 移动光标到蛇身位置
		SetColor(rand() % 14 + 2);							// 随机设置颜色
		printf("o");										// 打印蛇身
	}
	// 生成地图上下边界
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		GotoXY(i, 0);
		printf("-");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("-");
	}
	// 生成地图左右边界
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1, i);
		printf("|");
	}
	// 生成食物
	PrintFood();
	// 生成障碍物
	PrintBarrier();
	// 得分说明
	SetColor(15);
	GotoXY(50, 5);
	printf("当前得分:0");
	SpeedControl2(); // 默认慢速
	GotoXY(50, 15);
	printf("  当前速度：慢速  ");
	GotoXY(50, 7);
	printf("*为普通食物,吃到得1分");
	GotoXY(50, 9);
	printf("$为精华食物,吃到得2分");
	GotoXY(50, 11);
	printf("?为未知的食物，吃了可能加分，可能扣分，也可能中毒！");
	GotoXY(50, 13);
	printf("■为障碍物，撞到了会死亡！");
}

/*生成食物函数*/
void PrintFood()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		// 设置随机的食物坐标位置
		food.x = rand() % (MAP_WIDTH - 2) + 1;
		food.y = rand() % (MAP_HEIGHT - 2) + 1;
		// 循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
		for (int k = 0; k <= snake.length - 1; k++)
		{
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y)
			{
				flag = 1; // 位置有重叠，需要继续循环
				break;
			}
		}

		if (food.x == 0 || food.y == 0 || food.x == MAP_HEIGHT || food.y == MAP_WIDTH)
		{
			flag = 1; // 食物位置与边框位置存在重合
		}
	}
	GotoXY(food.x, food.y);
	int nb = rand() % 3; // 选择随机生成的食物
	if (nb == 0)
	{
		unknown_food = 1;
		SetColor(13);
		printf("*"); // 普通食物
	}
	else if (nb == 1)
	{
		unknown_food = 3;
		SetColor(10);
		printf("$"); // 精华食物
	}
	else if (nb == 2)
	{
		int sb = rand() % 10 + 1;
		if (sb == 1)
		{
			unknown_food = 0;
		}
		else if (sb >= 2 && sb <= 7)
		{
			unknown_food = 3;
		}
		else
		{
			unknown_food = -1;
		}
		SetColor(12);
		printf("?"); // 未知的食物
	}
}

/*蛇移动函数实现,返回值为1表示继续移动，为0表示停止移动*/
int MoveSnake()
{
	SetConsoleOutputCP(936);
	SetConsoleCP(936);

	Snakenode temp;
	int flag = 0;
	temp = snake.snakeNode[snake.length - 1]; // 记录蛇尾
	for (int i = snake.length - 1; i >= 1; i--)
		snake.snakeNode[i] = snake.snakeNode[i - 1];	// 将所有蛇身向前移动一个位置
	GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y); // 原来蛇头位置为蛇身
	SetColor(rand() % 14 + 2);
	printf("o"); // 前进方向打印一节蛇身，其他蛇身不需要打印
	// 响应键盘修改
	if (_kbhit())
	{
		// 键盘输入返回1，非键盘输入返回0
		direction = _getch();
		switch (direction)
		{ // 因为每次只有一个键盘输入，所以和方向输入放一起了
		case Speedup:
			x = 1;
			break; // 速度修改
		case Speeddown:
			x = 2;
			break;
		default:
			break;
		}

		switch (direction)
		{
		case UP:				 // 按下w键
			if (now_Dir != DOWN) // 如果蛇头向下，按向上移动的键w时不起作用
				now_Dir = direction;
			break;
		case DOWN:			   // 按下s键
			if (now_Dir != UP) // 如果蛇头向上，按向下移动的键s时不起作用
				now_Dir = direction;
			break;
		case LEFT:				  // 按下a键
			if (now_Dir != RIGHT) // 如果蛇头向右，按向左移动的键a时不起作用
				now_Dir = direction;
			break;
		case RIGHT:				 // 按下d键
			if (now_Dir != LEFT) // 如果蛇头向左，按向右移动的键d时不起作用
				now_Dir = direction;
			break;
		}
	}
	switch (now_Dir)
	{ // 根据现在的方向修改蛇头的位置
	case UP:
		snake.snakeNode[0].y--;
		break; // 向上移动
	case DOWN:
		snake.snakeNode[0].y++;
		break; // 向下移动
	case LEFT:
		snake.snakeNode[0].x--;
		break; // 向左移动
	case RIGHT:
		snake.snakeNode[0].x++;
		break; // 向右移动
	}
	// 打印蛇头
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	SetColor(11);
	printf("@");
	// 判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
	if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y)
	{
		SetConsoleOutputCP(936);
		SetConsoleCP(936);
		if (snake.length + unknown_food - 3 < 1 || unknown_food == 0)
		{
			SetColor(15);
			system("cls");
			data[data[0].count - 1].score = snake.length - 3;
			GotoXY(45, 14);
			printf("最终得分：%d", snake.length - 3);
			GotoXY(45, 16);
			printf("中毒，你死了！");
			GotoXY(45, 18);
			printf("按任意键返回主菜单");
			char c = _getch();
			system("cls");
			return 0;
		}
		else if (unknown_food == -1)
		{
			GotoXY(barrier.x, barrier.y);
			printf("  ");
			GotoXY(temp.x, temp.y);
			printf(" ");
			GotoXY(snake.snakeNode[snake.length - 2].x, snake.snakeNode[snake.length - 2].y);
			printf(" ");
			snake.length--;
		}
		else
		{
			GotoXY(barrier.x, barrier.y);
			printf("  ");
			snake.length += unknown_food; // 吃到食物，蛇长增加
		}
		flag = 1;								  // flag为1表示吃到食物，为0表示没有吃到食物
		snake.snakeNode[snake.length - 1] = temp; // 吃到食物，蛇尾加一节;实际上是蛇尾不变，蛇头发生了一个位置
	}
	// 输出蛇此时状态
	// 没吃到食物时，在原来的蛇尾打印一个空格，去掉原来的蛇尾
	if (!flag)
	{
		GotoXY(temp.x, temp.y);
		printf(" ");
	}
	else
	{
		GotoXY(barrier.x, barrier.y);
		printf("  ");
		PrintBarrier();
		// 吃到食物，才会更新障碍物
		//  吃到食物，则需要在地图上重新更新一个食物
		PrintFood();
		GotoXY(50, 5);
		printf("当前得分:%d", snake.length - 3); // 打印得分，得分为蛇长减原始长度3
	}
	// 判断是否死亡
	if (!IsCorrect())
	{ // 如果撞墙，则清除屏幕，打印最终得分，游戏结束

		SetConsoleOutputCP(936);
		SetConsoleCP(936);
		SetColor(15);
		system("cls");
		data[data[0].count - 1].score = snake.length - 3;
		GotoXY(45, 14);
		printf("最终得分%d  ", snake.length - 3);
		GotoXY(45, 16);
		printf("你输了！");
		GotoXY(45, 18);
		printf("按任意键返回菜单");
		char c = _getch();
		system("cls");
		return 0;
	}

	if (Overlap()) // 判断是否自撞
	{
		int t = snake.length;
		for (int j = Overlap() + 1; j < t; j++)
		{
			GotoXY(snake.snakeNode[j].x, snake.snakeNode[j].y);
			printf(" ");
			snake.length -= 1;
		}
		GotoXY(50, 5);
		printf("当前得分:   %d  ", snake.length - 3); // 打印得分，得分为蛇长减原始长度3
	}
	if (x == 1) // 调整速度
	{
		SpeedControl(); // 快速
		GotoXY(50, 15);
		printf("  当前速度：快速  ");
	}
	else
	{
		SpeedControl2(); // 慢速
		GotoXY(50, 15);
		printf("  当前速度：慢速  ");
	}
	Sleep(snake.speed); // 把进程挂起一段时间，用于控制蛇移动的速度
	return 1;
}

/*判断是否自撞或撞墙,返回值为0表示自撞或撞墙，否则为1*/
int IsCorrect()
{
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 || snake.snakeNode[0].y == MAP_HEIGHT - 1) // 判断蛇头是否撞墙
		return 0;
	if (snake.snakeNode[0].x == barrier.x && snake.snakeNode[0].y == barrier.y) // 判断蛇头是否撞墙
		return 0;

	return 1;
}

/*判断是否碰到蛇身*/
int Overlap()
{
	// int t = snake.length;
	for (int i = 1; i < snake.length; i++)
	{ // 判断蛇头是否和蛇身重叠，重叠表示自撞
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
		{
			//            //表示存在重叠，需要断尾
			//			for (int j = i+1; i < t; j++){
			//              GotoXY(snake.snakeNode[j].x ,snake.snakeNode[j].y);
			//               printf(" ");
			//			snake.length-=1;
			return i;
		}
	}
	return 0;
}

/*慢速调整函数*/
void SpeedControl()
{
	switch (snake.length)
	{ // 根据蛇长调整蛇的移动速度
	case 8:
		snake.speed = 220;
		break;
	case 12:
		snake.speed = 205;
		break;
	case 14:
		snake.speed = 190;
		break;
	case 17:
		snake.speed = 185;
		break;
	case 20:
		snake.speed = 170;
		break;
	case 23:
		snake.speed = 150;
		break;
	case 26:
		snake.speed = 130;
		break;
	case 30:
		snake.speed = 110;
		break;
	case 33:
		snake.speed = 80;
		break;
	default:
		break;
	}
}

/*高速调整函数*/
void SpeedControl2()
{
	switch (snake.length)
	{ // 根据蛇长调整蛇的移动速度
	case 8:
		snake.speed = 115;
		break;
	case 12:
		snake.speed = 110;
		break;
	case 14:
		snake.speed = 105;
		break;
	case 17:
		snake.speed = 100;
		break;
	case 20:
		snake.speed = 95;
		break;
	case 23:
		snake.speed = 90;
		break;
	case 26:
		snake.speed = 70;
		break;
	case 30:
		snake.speed = 50;
		break;
	case 33:
		snake.speed = 20;
		break;
	default:
		break;
	}
}

void Read()
{
	FILE *file;
	file = fopen("scores.txt", "rb");
	fscanf(file, "%d", &data[0].count);
	for (int i = 0; i < data[0].count; i++)
	{
		fscanf(file, "%s", &data[i].name);
		fscanf(file, "%d", &data[i].score);
		data[i].count = data[0].count;
	}
	fclose(file);
}

void List()
{
	SetConsoleOutputCP(936);
	GotoXY(48, 12);
	printf("用户名");
	GotoXY(58, 12);
	printf("分数");
	int i;
	for (i = 0; i < 3; i++)
	{
		GotoXY(48, 12 + (i + 1) * 2);
		printf("%s", data[i].name);
		GotoXY(58, 12 + (i + 1) * 2);
		printf("%d", data[i].score);
	}
	GotoXY(48, 12 + (i + 1) * 2);
	printf("按任意键返回菜单");
	Hide();
	char ch = _getch();
	system("cls");
}

void Name()
{
	SetConsoleOutputCP(936);
	GotoXY(48, 12);
	printf("请输入用户名：");
	GotoXY(48, 14);
	scanf("%s", &data[data[0].count].name);
	data[0].count++;
	char ch = _getch();
	system("cls");
}

void Rank()
{
	int max_index;
	char a[50];

	for (int i = 0; i < data[0].count; i++) // 选择排序
	{
		max_index = i;
		for (int j = i + 1; j < data[0].count; j++)
		{
			if (data[j].score > data[i].score)
			{
				max_index = j;
			}
		}
		strcpy(a, data[i].name);
		strcpy(data[i].name, data[max_index].name);
		strcpy(data[max_index].name, a);
		int temp = data[i].score;
		data[i].score = data[max_index].score;
		data[max_index].score = temp;
	}
	List();
}

void Write()
{
	FILE *file;
	file = fopen("scores.txt", "wb");
	fprintf(file, "%d\n", data[0].count);
	for (int i = 0; i < data[0].count; i++)
	{
		fprintf(file, "%s ", data[i].name);
		fprintf(file, "%d", data[i].score);
		fprintf(file, "\n");
	}
	fclose(file);
}

void SetColor(int c)
{
	// 颜色设置
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/*生成障碍物函数*/
void PrintBarrier()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		// 设置随机的障碍物坐标位置
		barrier.x = rand() % (MAP_WIDTH - 2) + 1;
		barrier.y = rand() % (MAP_HEIGHT - 2) + 1;
		// 循环判断障碍物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
		for (int k = 0; k <= snake.length - 1; k++)
		{
			if (snake.snakeNode[k].x == barrier.x && snake.snakeNode[k].y == barrier.y && food.x == barrier.x && food.y == barrier.y)
			{
				flag = 1; // 位置有重叠，需要继续循环
				break;
			}
		}
		if (barrier.x == 0 || barrier.y == 0 || barrier.x == MAP_HEIGHT || barrier.y == MAP_WIDTH)
		{
			flag = 1;
		}
	}
	GotoXY(barrier.x, barrier.y);
	printf("■");
}
