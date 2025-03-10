#include "snake.h"
/*全局变量定义*/
Snake snake1 = {.length = 6, .speed = 250, .snake_head = '@', .snake_body = 'o', .x = 1, .Dir = RIGHT};
Snake snake2 = {.length = 6, .speed = 250, .snake_head = '@', .snake_body = 'o', .x = 1, .Dir = RIGHT};
Food foods[MAX_FOOD];		   // 定义食物结构体变量
Barrier barriers[MAX_BARRIER]; // 定义障碍物结构体变量
int foodCount = 1;
int barrierCount = 1;
char direction1 = RIGHT; // 预期蛇头方向
char direction2 = RIGHT;
Data data[100]; // 用户记录

const double updateInterval = 10.0; // 每 10 秒增加一次

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
	GotoXY(50, 12);
	printf("i 上");
	GotoXY(50, 14);
	printf("k 下");
	GotoXY(50, 16);
	printf("j 左");
	GotoXY(50, 18);
	printf("l 右");
	GotoXY(50, 20);
	printf("u 加速");
	GotoXY(50, 22);
	printf("o 减速");
	GotoXY(44, 24);
	printf("当蛇撞墙时游戏结束");
	GotoXY(45, 26);
	printf("按任意键返回上级菜单");
	Hide(); // 隐藏光标
	char ch = _getch();
	system("cls");
}
void Init(int player, int AI)
{
	if (player == 1)
	{
		InitMap(&snake1, player);

		// if (AI) {  AI 蛇,设计AI蛇的函数逻辑;AI蛇的结构体已经给出;

		// }
	}
	else if (player == 2)
	{
		InitMap(&snake1, player);
		InitMap(&snake2, player);
		while (abs(snake2.snakeNode[0].x - snake1.snakeNode[0].x) < 4)
		{
			InitMap(&snake2, player);
		}
		// if (AI) {  AI 蛇,设计AI蛇的函数逻辑;AI蛇的结构体已经给出;将对手作为AI
		// }
	}
};
void InitMap(Snake *snake, int player)
{
	SetConsoleOutputCP(936);
	Hide(); // 隐藏光标

	// 设置蛇头位置随机生成
	snake->snakeNode[0].x = (rand() % (MAP_WIDTH - 5)) + 4;
	snake->snakeNode[0].y = (rand() % (MAP_HEIGHT - 2));
	GotoXY(snake->snakeNode[0].x, snake->snakeNode[0].y); // 将光标移动到蛇头位置
	SetColor(11);
	printf("%c", snake->snake_head); // 打印蛇头
	snake->Dir = RIGHT;				 // 当前蛇头方向
	// 显示蛇身
	for (int i = 1; i < snake->length; i++)
	{
		// 设置蛇身的纵坐标位置和蛇头位置相同
		snake->snakeNode[i].y = snake->snakeNode[i - 1].y;
		// 设置蛇身的横坐标位置，蛇身在蛇头的左边,所以横坐标依次减1
		snake->snakeNode[i].x = snake->snakeNode[i - 1].x - 1;
		GotoXY(snake->snakeNode[i].x, snake->snakeNode[i].y); // 移动光标到蛇身位置
		SetColor(rand() % 14 + 2);							  // 随机设置颜色
		printf("%c", snake->snake_body);					  // 打印蛇身
	}
	// 生成地图上下边界
	Map();
	PrintBarrier(snake);
	PrintFood(snake);
	// 生成食物和障碍物
	// 得分说明
	SetColor(15);
	if (player == 1)
	{
		GotoXY(50, 5);
		printf("当前得分:00");
		GotoXY(50, 15);
		printf("  当前速度：慢速  ");
	}
	else
	{
		GotoXY(50, 5);
		printf("当前得分:00");
		GotoXY(50, 15);
		printf("  当前速度：慢速  ");
		GotoXY(70, 5);
		printf("当前得分:00");
		GotoXY(70, 15);
		printf("  当前速度：慢速  ");
	}
	SpeedControl(snake); // 默认慢速
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
void AddFood()
{
	if (foodCount >= MAX_FOOD)
		return;

	Food food;
	// 设置随机的食物坐标位置
	food.x = rand() % (MAP_WIDTH - 2) + 1;
	food.y = rand() % (MAP_HEIGHT - 2) + 1;

	foods[foodCount] = food;
	foodCount++;
}
void PrintFood(Snake *snake)
{
	int flag = 1;
	for (int i = 0; i <= foodCount - 1; i++)
	{
		while (flag)
		{
			flag = 0;

			// 循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
			for (int k = 0; k <= snake->length - 1; k++)
			{
				if (snake->snakeNode[k].x == foods[i].x && snake->snakeNode[k].y == foods[i].y)
				{
					foods[i].x = rand() % (MAP_WIDTH - 2) + 1;
					foods[i].y = rand() % (MAP_HEIGHT - 2) + 1;
					flag = 1; // 位置有重叠，需要继续循环
					break;
				}
			}

			if (foods[i].x == 0 || foods[i].y == 0 || foods[i].x == MAP_HEIGHT || foods[i].y == MAP_WIDTH)
			{
				foods[i].x = rand() % (MAP_WIDTH - 2) + 1;
				foods[i].y = rand() % (MAP_HEIGHT - 2) + 1;
				flag = 1; // 食物位置与边框位置存在重合
			}
		}
	}
	for (int i = 0; i <= foodCount - 1; i++)
	{
		GotoXY(foods[i].x, foods[i].y);
		int nb = rand() % 3; // 选择随机生成的食物
		if (nb == 0)
		{
			foods[i].score_food = 1;
			SetColor(13);

			printf("*"); // 普通食物
		}
		else if (nb == 1)
		{
			foods[i].score_food = 3;

			SetColor(10);

			printf("$"); // 精华食物
		}
		else if (nb == 2)
		{
			int sb = rand() % 10 + 1;
			if (sb == 1)
			{
				foods[i].score_food = 0;
			}
			else if (sb >= 2 && sb <= 7)
			{
				foods[i].score_food = 3;
			}
			else
			{
				foods[i].score_food = -1;
			}

			SetColor(12);
			printf("?"); // 未知的食物
		}
	}
}

int MoveSnake(Snake *snake, char direction, int player)
{
	SetConsoleOutputCP(936);
	Snakenode temp;
	int flag = 0;
	temp = snake->snakeNode[snake->length - 1]; // 记录蛇尾
	for (int i = snake->length - 1; i >= 1; i--)
		snake->snakeNode[i] = snake->snakeNode[i - 1];	  // 将所有蛇身向前移动一个位置
	GotoXY(snake->snakeNode[1].x, snake->snakeNode[1].y); // 原来蛇头位置为蛇身
	SetColor(rand() % 14 + 2);
	printf("%c", snake->snake_body); // 前进方向打印一节蛇身，其他蛇身不需要打印
	clock_t currentTime = clock();
	double elapsed = (double)(currentTime - lastUpdateTime) / CLOCKS_PER_SEC;
	if (elapsed >= updateInterval)
	{
		AddBarrier();
		AddFood();
		lastUpdateTime = currentTime;
	}
	// 响应键盘修改
	if (_kbhit())
	{
		// 键盘输入返回1，非键盘输入返回0
		direction = _getch();
		if (_kbhit())
		{
			char input = _getch();
			if (input == UP_P1 || input == DOWN_P1 || input == LEFT_P1 || input == RIGHT_P1 ||
				input == Speedup_P1 || input == Speeddown_P1 || input == Speedup_P1 || input == Speeddown_P1)
			{
				if (snake == &snake1)
					direction = input;
			}
			else if (input == UP_P2 || input == DOWN_P2 || input == LEFT_P2 || input == RIGHT_P2 ||
					 input == Speedup_P2 || input == Speeddown_P2 || input == Speedup_P2 || input == Speeddown_P2)
			{
				if (snake == &snake2)
					direction = input;
			}
		}

		switch (direction)
		{ // 因为每次只有一个键盘输入，所以和方向输入放一起了
		case Speedup_P1:
		case Speedup_P2:
			snake->x = 1;
			break; // 速度修改
		case Speeddown_P1:
		case Speeddown_P2:
			snake->x = 2;
			break;
		default:
			break;
		}

		switch (direction)
		{
		case UP_P1:
		case UP_P2:					// 按下w键
			if (snake->Dir != DOWN) // 如果蛇头向下，按向上移动的键w时不起作用
				snake->Dir = direction;
			break;
		case DOWN_P1:
		case DOWN_P2:			  // 按下s键
			if (snake->Dir != UP) // 如果蛇头向上，按向下移动的键s时不起作用
				snake->Dir = direction;
			break;
		case LEFT_P1:
		case LEFT_P2:				 // 按下a键
			if (snake->Dir != RIGHT) // 如果蛇头向右，按向左移动的键a时不起作用
				snake->Dir = direction;
			break;
		case RIGHT_P1:
		case RIGHT_P2:				// 按下d键
			if (snake->Dir != LEFT) // 如果蛇头向左，按向右移动的键d时不起作用
				snake->Dir = direction;
			break;
		}
	}
	switch (snake->Dir)
	{ // 根据现在的方向修改蛇头的位置
	case UP_P1:
	case UP_P2: // 按下w键
		snake->snakeNode[0].y--;
		break; // 向上移动

	case DOWN_P1:
	case DOWN_P2: // 按下s键
		snake->snakeNode[0].y++;
		break; // 向下移动

	case LEFT_P1:
	case LEFT_P2: // 按下a键:
		snake->snakeNode[0].x--;
		break; // 向左移动
	case RIGHT_P1:
	case RIGHT_P2: // 按下d键
		snake->snakeNode[0].x++;
		break; // 向右移动
	}
	// 打印蛇头
	GotoXY(snake->snakeNode[0].x, snake->snakeNode[0].y);
	SetColor(11);
	printf("%c", snake->snake_head);
	if (!ThroughWall(snake))
	{ // 如果撞墙，穿墙
		if (snake->snakeNode[0].x < 1 || snake->snakeNode[0].x > MAP_WIDTH - 2)
		{
			if (snake->snakeNode[0].x < 1)
			{
				snake->snakeNode[0].x = MAP_WIDTH - 2;
			}
			else if (snake->snakeNode[0].x > MAP_WIDTH - 2)
			{
				snake->snakeNode[0].x = 1;
			}
		}
		else if (snake->snakeNode[0].y > MAP_HEIGHT - 2 || snake->snakeNode[0].y < 1)
		{
			if (snake->snakeNode[0].y > MAP_HEIGHT - 2)
			{
				snake->snakeNode[0].y = 1;
			}
			else if (snake->snakeNode[0].y < 1)
			{
				snake->snakeNode[0].y = MAP_HEIGHT - 2;
			}
		}
	}
	// 判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
	for (int i = 0; i < foodCount; i++)
	{
		if (snake->snakeNode[0].x == foods[i].x && snake->snakeNode[0].y == foods[i].y)
		{
			SetConsoleOutputCP(936);

			if (snake->length + foods[i].score_food - 3 < 1 || foods[i].score_food == 0)
			{

				SetColor(15);
				system("cls");
				if (player == 1)
				{
					SetConsoleOutputCP(936);
					GotoXY(45, 14);
					printf("玩家1最终得分:%d", snake1.length - 3);
					GotoXY(45, 16);
					printf("中毒，你死了！");
					GotoXY(45, 18);
					printf("按任意键返回主菜单");
				}
				else
				{
					SetColor(15);
					SetConsoleOutputCP(936);
					GotoXY(45, 14);
					printf("玩家1最终得分:%d", snake1.length - 3);
					GotoXY(45, 16);
					printf("玩家2最终得分:%d", snake2.length - 3);
					GotoXY(45, 18);
					printf("中毒，你死了！");
					GotoXY(45, 20);
					printf("按任意键返回主菜单");
				}
				char c = _getch();
				system("cls");
				return 0;
			}
			else if (foods[i].score_food == -1) // 吃到食物，但是-1
			{
				for (int k = 0; k < barrierCount - 1; k++)
				{
					GotoXY(barriers[k].x, barriers[k].y);
					printf("  ");
				}
				GotoXY(temp.x, temp.y);
				printf(" ");
				GotoXY(snake->snakeNode[snake->length - 2].x, snake->snakeNode[snake->length - 2].y);
				printf(" ");

				snake->length--;
			}
			else
			{
				for (int k = 0; k < barrierCount - 1; k++)
				{
					GotoXY(barriers[k].x, barriers[k].y);
					printf("  ");
				}
				snake->length += foods[i].score_food; // 吃到食物，蛇长增加
			}
			flag = 1;									// flag为1表示吃到食物，为0表示没有吃到食物
			snake->snakeNode[snake->length - 1] = temp; // 吃到食物，蛇尾加一节;实际上是蛇尾不变，蛇头发生了一个位置
		}
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
		for (int k = 0; k < barrierCount - 1; k++)
		{
			GotoXY(barriers[k].x, barriers[k].y);
			printf("  ");
		}
		PrintBarrier(snake);
		PrintFood(snake);

		// 吃到食物，才会更新障碍物,重新更新一个食物
		if (player == 1)
		{
			GotoXY(50, 5);
			printf("当前得分:%d", snake1.length - 3);
		}
		else
		{ // 打印得分，得分为蛇长减原始长度3
			GotoXY(50, 5);
			printf("当前得分:%d", snake1.length - 3);
			GotoXY(70, 5);
			printf("当前得分:%d", snake2.length - 3);
		}
	}
	// 判断是否死亡
	if (!IsCorrect(snake))
	{ // 如果撞障碍物，则清除屏幕，打印最终得分，游戏结束

		SetConsoleOutputCP(936);
		SetConsoleCP(936);
		SetColor(15);
		system("cls");

		if (player == 1)
		{
			SetConsoleOutputCP(936);
			GotoXY(45, 14);
			printf("最终得分：%d", snake1.length - 3);
			GotoXY(45, 16);
			printf("你输了！");
			GotoXY(45, 18);
			printf("按任意键返回主菜单");
		}
		else
		{
			SetConsoleOutputCP(936);
			GotoXY(45, 14);
			printf("玩家1最终得分:%d", snake1.length - 3);
			GotoXY(45, 16);
			printf("玩家2最终得分:%d", snake2.length - 3);
			GotoXY(45, 18);
			printf("你输了！");
			GotoXY(45, 20);
			printf("按任意键返回主菜单");
		}
		char c = _getch();
		system("cls");
		return 0;
	}

	Map();
	if (Overlap(snake)) // 判断是否自撞
	{
		int t = snake->length;
		for (int j = Overlap(snake) + 1; j < t; j++)
		{
			GotoXY(snake->snakeNode[j].x, snake->snakeNode[j].y);
			printf(" ");
			snake->length -= 1;
		}
		if (player == 1)
		{
			GotoXY(50, 5);
			printf("当前得分:%d", snake1.length - 3);
		}
		else
		{ // 打印得分，得分为蛇长减原始长度3
			GotoXY(50, 5);
			printf("当前得分:%d", snake1.length - 3);
			GotoXY(70, 5);
			printf("当前得分:%d", snake2.length - 3);
		}
	}
	if (snake->x == 1) // 调整速度

	{
		SpeedControl(snake); // 慢速
		if (player == 1)
		{
			GotoXY(50, 15);
			printf("  当前速度：慢速  ");
		}
		else
		{
			{
				if (snake1.x == 1)
				{
					GotoXY(50, 15);
					printf("  当前速度：慢速  ");

				} // 慢速
				else if (snake2.x == 1)
				{
					GotoXY(70, 15);
					printf("  当前速度：慢速  ");
				}
			}
		}
	}
	else if (snake->x == 2)
	{
		if (player == 1)
		{
			GotoXY(50, 15);
			printf("  当前速度：快速  ");
		}
		else
		{
			if (snake1.x == 2)
			{
				GotoXY(50, 15);
				printf("  当前速度:快速  ");
			}
			else if (snake2.x == 2)
			{
				GotoXY(70, 15);
				printf("  当前速度:快速  ");
			}
		}
	}
	Sleep(snake->speed); // 把进程挂起一段时间，用于控制蛇移动的速度
	return 1;
}

/*判断是否自撞或撞墙,返回值为0表示自撞或撞墙，否则为1*/

int IsCorrect(Snake *snake)
{
	for (int k = 0; k < barrierCount - 1; k++)
	{
		if (snake->snakeNode[0].x == barriers[k].x && snake->snakeNode[0].y == barriers[k].y || snake->snakeNode[0].x == barriers[k].x + 1 && snake->snakeNode[0].y == barriers[k].y + 1) // 判断蛇头是否撞墙
			return 0;
	}

	return 1;
}
int ThroughWall(Snake *snake)
{
	if (snake->snakeNode[0].x == 0 || snake->snakeNode[0].y == 0 || snake->snakeNode[0].x == MAP_WIDTH - 1 || snake->snakeNode[0].y == MAP_HEIGHT - 1) // 判断蛇头是否撞墙
		return 0;
	return 1;
}

/*判断是否碰到蛇身*/

int Overlap(Snake *snake)
{
	for (int i = 1; i < snake->length; i++)
	{ // 判断蛇头是否和蛇身重叠，重叠表示自撞
		if (snake->snakeNode[0].x == snake->snakeNode[i].x && snake->snakeNode[0].y == snake->snakeNode[i].y)
		{
			return i;
		}
	}
	return 0;
}

/*生成地图函数*/
void Map()
{
	// SetColor(rand() % 10 + 2); 则随机改变边框颜色
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
}
/*慢速调整函数*/

void SpeedControl(Snake *snake)
{
	switch (snake->length)
	{ // 根据蛇长调整蛇的移动速度
	case 8:
		snake->speed = 220;
		break;
	case 12:
		snake->speed = 205;
		break;
	case 14:
		snake->speed = 190;
		break;
	case 17:
		snake->speed = 185;
		break;
	case 20:
		snake->speed = 170;
		break;
	case 23:
		snake->speed = 150;
		break;
	case 26:
		snake->speed = 130;
		break;
	case 30:
		snake->speed = 110;
		break;
	case 33:
		snake->speed = 80;
		break;
	default:
		break;
	}
}

void SpeedControl2(Snake *snake)
{
	switch (snake->length)
	{ // 根据蛇长调整蛇的移动速度
	case 8:
		snake->speed = 115;
		break;
	case 12:
		snake->speed = 110;
		break;
	case 14:
		snake->speed = 105;
		break;
	case 17:
		snake->speed = 100;
		break;
	case 20:
		snake->speed = 95;
		break;
	case 23:
		snake->speed = 90;
		break;
	case 26:
		snake->speed = 70;
		break;
	case 30:
		snake->speed = 50;
		break;
	case 33:
		snake->speed = 20;
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

void Name(int x)
{
	SetConsoleOutputCP(936);
	if (x == 1)
	{
		SetConsoleOutputCP(936);
		GotoXY(48, 12);
		printf("请输入用户名：");
		GotoXY(48, 14);
		scanf("%s", &data[data[0].count].name);
	}
	else if (x == 2)
	{
		SetConsoleOutputCP(936);
		GotoXY(48, 12);
		printf("请输入用户名1:");
		GotoXY(48, 14);
		scanf("%s", &data[data[0].count].name);
		data[0].count++;
		system("cls");
		GotoXY(48, 12);
		SetConsoleOutputCP(936);
		printf("请输入用户名2:");
		GotoXY(48, 14);
		scanf("%s", &data[data[0].count].name);
	}
	data[0].count++;
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

void AddBarrier()
{
	Barrier barrier;
	barrier.x = rand() % (MAP_WIDTH - 2) + 1;
	barrier.y = rand() % (MAP_HEIGHT - 2) + 1;

	barriers[barrierCount] = barrier;
	barrierCount++;
}
/*生成障碍物函数*/
void PrintBarrier(Snake *snake)
{
	int flag = 1;
	for (int i = 0; i <= barrierCount - 1; i++)
	{
		while (flag)
		{
			flag = 0;

			// 循环判断障碍物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
			for (int k = 0; k <= snake->length - 1; k++)
			{
				if (snake->snakeNode[k].x == barriers[i].x && snake->snakeNode[k].y == barriers[i].y)
				{
					barriers[i].x = rand() % (MAP_WIDTH - 2) + 1;
					barriers[i].y = rand() % (MAP_HEIGHT - 2) + 1;
					flag = 1; // 位置有重叠，需要继续循环
					break;
				}
			}
			for (int k = 0; k <= foodCount - 1; k++)
			{
				if (foods[k].x == barriers[i].x && foods[k].y == barriers[i].y)
				{
					barriers[i].x = rand() % (MAP_WIDTH - 2) + 1;
					barriers[i].y = rand() % (MAP_HEIGHT - 2) + 1;
					flag = 1; // 位置有重叠，需要继续循环
					break;
				}
			}
			if (barriers[i].x == 0 || barriers[i].y == 0 || barriers[i].x == MAP_HEIGHT || barriers[i].y == MAP_WIDTH)
			{
				barriers[i].x = rand() % (MAP_WIDTH - 2) + 1;
				barriers[i].y = rand() % (MAP_HEIGHT - 2) + 1;
				flag = 1; // 位置有重叠，需要继续循环
			}
		}
	}
	for (int i = 0; i <= barrierCount - 1; i++)
	{
		GotoXY(barriers[i].x, barriers[i].y);
		printf("■");
	}
}
int Mode()
{
	SetConsoleOutputCP(936);
	GotoXY(40, 12); // 定位光标位置
	printf("选择难度模式");
	GotoXY(43, 14);
	printf("1.普通模式");
	GotoXY(43, 16);
	printf("2.困难模式");

	char ch;
	int result = 0;
	ch = _getch(); // 接收用户输入的菜单选项
	switch (ch)
	{
	case '1':
		result = 1;
		break;

	case '2':
		result = 2;
		break;
	}
	system("cls");
	return result;
}
int Player_Mode()
{
	SetConsoleOutputCP(936);
	GotoXY(40, 12); // 定位光标位置
	printf("选择玩家模式");
	GotoXY(43, 14);
	printf("1.单人模式");
	GotoXY(43, 16);
	printf("2.双人模式");

	char ch;
	int result = 0;
	ch = _getch(); // 接收用户输入的菜单选项
	switch (ch)
	{
	case '1':
		result = 1;
		break;

	case '2':
		result = 2;
		break;
	}
	system("cls");
	return result;
}
int Enable_AI()
{
	SetConsoleOutputCP(936);
	GotoXY(40, 12); // 定位光标位置
	printf("选择是否启用AI");
	GotoXY(43, 14);
	printf("1.启用AI");
	GotoXY(43, 16);
	printf("2.不启用AI");

	char ch;
	int result = 0;
	ch = _getch(); // 接收用户输入的菜单选项
	switch (ch)
	{
	case '1':
		result = 1;
		break;

	case '2':
		result = 2;
		break;
	}
	system("cls");
	return result;
}
