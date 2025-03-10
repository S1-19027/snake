#include "snake.h"
/*ȫ�ֱ�������*/
Snake snake1 = {.length = 6, .speed = 250, .snake_head = '@', .snake_body = 'o', .x = 1, .Dir = RIGHT};
Snake snake2 = {.length = 6, .speed = 250, .snake_head = '@', .snake_body = 'o', .x = 1, .Dir = RIGHT};
Food foods[MAX_FOOD];		   // ����ʳ��ṹ�����
Barrier barriers[MAX_BARRIER]; // �����ϰ���ṹ�����
int foodCount = 1;
int barrierCount = 1;
char direction1 = RIGHT; // Ԥ����ͷ����
char direction2 = RIGHT;
Data data[100]; // �û���¼

const double updateInterval = 10.0; // ÿ 10 ������һ��

/*���˵�ʵ��*/
int Menu()
{
	GotoXY(40, 12); // ��λ���λ��
	printf("��ӭ����̰����С��Ϸ");
	GotoXY(43, 14);
	printf("1.��ʼ��Ϸ");
	GotoXY(43, 16);
	printf("2.����");
	GotoXY(43, 18);
	printf("3.����");
	GotoXY(43, 20);
	printf("4.���а�");
	GotoXY(43, 22);
	printf("����������˳���Ϸ");

	Hide(); // ���ع��
	char ch;
	int result = 0;
	ch = _getch(); // �����û�����Ĳ˵�ѡ��
	switch (ch)
	{ // ����ѡ�����÷��ؽ��ֵ
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
	system("cls"); // ����ϵͳ����cls�����������
	return result;
}

// ��궨λ����������궨λ��(x,y)����λ��
void GotoXY(int x, int y)
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

/*���ع��*/
void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = {1, 0};
	SetConsoleCursorInfo(hout, &cor_info);
}

/*���ڲ˵�ʵ��*/
void About()
{
	GotoXY(30, 12);
	printf("���ݵ��ӿƼ���ѧ--��������ۺ�ʵ������");
	GotoXY(43, 14);
	printf("̰����-����̨��Ϸ");
	GotoXY(43, 16);
	printf("������������ϼ��˵�");
	Hide(); // ���ع��
	char ch = _getch();
	system("cls");
}

/*�����˵�ʵ��*/
void Help()
{
	GotoXY(40, 12);
	printf("w ��");
	GotoXY(40, 14);
	printf("s ��");
	GotoXY(40, 16);
	printf("a ��");
	GotoXY(40, 18);
	printf("d ��");
	GotoXY(40, 20);
	printf("q ����");
	GotoXY(40, 22);
	printf("e ����");
	GotoXY(50, 12);
	printf("i ��");
	GotoXY(50, 14);
	printf("k ��");
	GotoXY(50, 16);
	printf("j ��");
	GotoXY(50, 18);
	printf("l ��");
	GotoXY(50, 20);
	printf("u ����");
	GotoXY(50, 22);
	printf("o ����");
	GotoXY(44, 24);
	printf("����ײǽʱ��Ϸ����");
	GotoXY(45, 26);
	printf("������������ϼ��˵�");
	Hide(); // ���ع��
	char ch = _getch();
	system("cls");
}
void Init(int player, int AI)
{
	if (player == 1)
	{
		InitMap(&snake1, player);

		// if (AI) {  AI ��,���AI�ߵĺ����߼�;AI�ߵĽṹ���Ѿ�����;

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
		// if (AI) {  AI ��,���AI�ߵĺ����߼�;AI�ߵĽṹ���Ѿ�����;��������ΪAI
		// }
	}
};
void InitMap(Snake *snake, int player)
{
	SetConsoleOutputCP(936);
	Hide(); // ���ع��

	// ������ͷλ���������
	snake->snakeNode[0].x = (rand() % (MAP_WIDTH - 5)) + 4;
	snake->snakeNode[0].y = (rand() % (MAP_HEIGHT - 2));
	GotoXY(snake->snakeNode[0].x, snake->snakeNode[0].y); // ������ƶ�����ͷλ��
	SetColor(11);
	printf("%c", snake->snake_head); // ��ӡ��ͷ
	snake->Dir = RIGHT;				 // ��ǰ��ͷ����
	// ��ʾ����
	for (int i = 1; i < snake->length; i++)
	{
		// ���������������λ�ú���ͷλ����ͬ
		snake->snakeNode[i].y = snake->snakeNode[i - 1].y;
		// ��������ĺ�����λ�ã���������ͷ�����,���Ժ��������μ�1
		snake->snakeNode[i].x = snake->snakeNode[i - 1].x - 1;
		GotoXY(snake->snakeNode[i].x, snake->snakeNode[i].y); // �ƶ���굽����λ��
		SetColor(rand() % 14 + 2);							  // ���������ɫ
		printf("%c", snake->snake_body);					  // ��ӡ����
	}
	// ���ɵ�ͼ���±߽�
	Map();
	PrintBarrier(snake);
	PrintFood(snake);
	// ����ʳ����ϰ���
	// �÷�˵��
	SetColor(15);
	if (player == 1)
	{
		GotoXY(50, 5);
		printf("��ǰ�÷�:00");
		GotoXY(50, 15);
		printf("  ��ǰ�ٶȣ�����  ");
	}
	else
	{
		GotoXY(50, 5);
		printf("��ǰ�÷�:00");
		GotoXY(50, 15);
		printf("  ��ǰ�ٶȣ�����  ");
		GotoXY(70, 5);
		printf("��ǰ�÷�:00");
		GotoXY(70, 15);
		printf("  ��ǰ�ٶȣ�����  ");
	}
	SpeedControl(snake); // Ĭ������
	GotoXY(50, 15);
	printf("  ��ǰ�ٶȣ�����  ");
	GotoXY(50, 7);
	printf("*Ϊ��ͨʳ��,�Ե���1��");
	GotoXY(50, 9);
	printf("$Ϊ����ʳ��,�Ե���2��");
	GotoXY(50, 11);
	printf("?Ϊδ֪��ʳ����˿��ܼӷ֣����ܿ۷֣�Ҳ�����ж���");
	GotoXY(50, 13);
	printf("��Ϊ�ϰ��ײ���˻�������");
}
void AddFood()
{
	if (foodCount >= MAX_FOOD)
		return;

	Food food;
	// ���������ʳ������λ��
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

			// ѭ���ж�ʳ��λ���Ƿ���ߵ�λ���ص�������ص�����Ҫ��������ʳ��λ��
			for (int k = 0; k <= snake->length - 1; k++)
			{
				if (snake->snakeNode[k].x == foods[i].x && snake->snakeNode[k].y == foods[i].y)
				{
					foods[i].x = rand() % (MAP_WIDTH - 2) + 1;
					foods[i].y = rand() % (MAP_HEIGHT - 2) + 1;
					flag = 1; // λ�����ص�����Ҫ����ѭ��
					break;
				}
			}

			if (foods[i].x == 0 || foods[i].y == 0 || foods[i].x == MAP_HEIGHT || foods[i].y == MAP_WIDTH)
			{
				foods[i].x = rand() % (MAP_WIDTH - 2) + 1;
				foods[i].y = rand() % (MAP_HEIGHT - 2) + 1;
				flag = 1; // ʳ��λ����߿�λ�ô����غ�
			}
		}
	}
	for (int i = 0; i <= foodCount - 1; i++)
	{
		GotoXY(foods[i].x, foods[i].y);
		int nb = rand() % 3; // ѡ��������ɵ�ʳ��
		if (nb == 0)
		{
			foods[i].score_food = 1;
			SetColor(13);

			printf("*"); // ��ͨʳ��
		}
		else if (nb == 1)
		{
			foods[i].score_food = 3;

			SetColor(10);

			printf("$"); // ����ʳ��
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
			printf("?"); // δ֪��ʳ��
		}
	}
}

int MoveSnake(Snake *snake, char direction, int player)
{
	SetConsoleOutputCP(936);
	Snakenode temp;
	int flag = 0;
	temp = snake->snakeNode[snake->length - 1]; // ��¼��β
	for (int i = snake->length - 1; i >= 1; i--)
		snake->snakeNode[i] = snake->snakeNode[i - 1];	  // ������������ǰ�ƶ�һ��λ��
	GotoXY(snake->snakeNode[1].x, snake->snakeNode[1].y); // ԭ����ͷλ��Ϊ����
	SetColor(rand() % 14 + 2);
	printf("%c", snake->snake_body); // ǰ�������ӡһ����������������Ҫ��ӡ
	clock_t currentTime = clock();
	double elapsed = (double)(currentTime - lastUpdateTime) / CLOCKS_PER_SEC;
	if (elapsed >= updateInterval)
	{
		AddBarrier();
		AddFood();
		lastUpdateTime = currentTime;
	}
	// ��Ӧ�����޸�
	if (_kbhit())
	{
		// �������뷵��1���Ǽ������뷵��0
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
		{ // ��Ϊÿ��ֻ��һ���������룬���Ժͷ��������һ����
		case Speedup_P1:
		case Speedup_P2:
			snake->x = 1;
			break; // �ٶ��޸�
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
		case UP_P2:					// ����w��
			if (snake->Dir != DOWN) // �����ͷ���£��������ƶ��ļ�wʱ��������
				snake->Dir = direction;
			break;
		case DOWN_P1:
		case DOWN_P2:			  // ����s��
			if (snake->Dir != UP) // �����ͷ���ϣ��������ƶ��ļ�sʱ��������
				snake->Dir = direction;
			break;
		case LEFT_P1:
		case LEFT_P2:				 // ����a��
			if (snake->Dir != RIGHT) // �����ͷ���ң��������ƶ��ļ�aʱ��������
				snake->Dir = direction;
			break;
		case RIGHT_P1:
		case RIGHT_P2:				// ����d��
			if (snake->Dir != LEFT) // �����ͷ���󣬰������ƶ��ļ�dʱ��������
				snake->Dir = direction;
			break;
		}
	}
	switch (snake->Dir)
	{ // �������ڵķ����޸���ͷ��λ��
	case UP_P1:
	case UP_P2: // ����w��
		snake->snakeNode[0].y--;
		break; // �����ƶ�

	case DOWN_P1:
	case DOWN_P2: // ����s��
		snake->snakeNode[0].y++;
		break; // �����ƶ�

	case LEFT_P1:
	case LEFT_P2: // ����a��:
		snake->snakeNode[0].x--;
		break; // �����ƶ�
	case RIGHT_P1:
	case RIGHT_P2: // ����d��
		snake->snakeNode[0].x++;
		break; // �����ƶ�
	}
	// ��ӡ��ͷ
	GotoXY(snake->snakeNode[0].x, snake->snakeNode[0].y);
	SetColor(11);
	printf("%c", snake->snake_head);
	if (!ThroughWall(snake))
	{ // ���ײǽ����ǽ
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
	// �ж��Ƿ�Ե�ʳ������ͷ��λ�ú�ʳ���λ����ͬ��ʾ�Ե�ʳ��
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
					printf("���1���յ÷�:%d", snake1.length - 3);
					GotoXY(45, 16);
					printf("�ж��������ˣ�");
					GotoXY(45, 18);
					printf("��������������˵�");
				}
				else
				{
					SetColor(15);
					SetConsoleOutputCP(936);
					GotoXY(45, 14);
					printf("���1���յ÷�:%d", snake1.length - 3);
					GotoXY(45, 16);
					printf("���2���յ÷�:%d", snake2.length - 3);
					GotoXY(45, 18);
					printf("�ж��������ˣ�");
					GotoXY(45, 20);
					printf("��������������˵�");
				}
				char c = _getch();
				system("cls");
				return 0;
			}
			else if (foods[i].score_food == -1) // �Ե�ʳ�����-1
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
				snake->length += foods[i].score_food; // �Ե�ʳ��߳�����
			}
			flag = 1;									// flagΪ1��ʾ�Ե�ʳ�Ϊ0��ʾû�гԵ�ʳ��
			snake->snakeNode[snake->length - 1] = temp; // �Ե�ʳ���β��һ��;ʵ��������β���䣬��ͷ������һ��λ��
		}
	}
	// ����ߴ�ʱ״̬
	// û�Ե�ʳ��ʱ����ԭ������β��ӡһ���ո�ȥ��ԭ������β
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

		// �Ե�ʳ��Ż�����ϰ���,���¸���һ��ʳ��
		if (player == 1)
		{
			GotoXY(50, 5);
			printf("��ǰ�÷�:%d", snake1.length - 3);
		}
		else
		{ // ��ӡ�÷֣��÷�Ϊ�߳���ԭʼ����3
			GotoXY(50, 5);
			printf("��ǰ�÷�:%d", snake1.length - 3);
			GotoXY(70, 5);
			printf("��ǰ�÷�:%d", snake2.length - 3);
		}
	}
	// �ж��Ƿ�����
	if (!IsCorrect(snake))
	{ // ���ײ�ϰ���������Ļ����ӡ���յ÷֣���Ϸ����

		SetConsoleOutputCP(936);
		SetConsoleCP(936);
		SetColor(15);
		system("cls");

		if (player == 1)
		{
			SetConsoleOutputCP(936);
			GotoXY(45, 14);
			printf("���յ÷֣�%d", snake1.length - 3);
			GotoXY(45, 16);
			printf("�����ˣ�");
			GotoXY(45, 18);
			printf("��������������˵�");
		}
		else
		{
			SetConsoleOutputCP(936);
			GotoXY(45, 14);
			printf("���1���յ÷�:%d", snake1.length - 3);
			GotoXY(45, 16);
			printf("���2���յ÷�:%d", snake2.length - 3);
			GotoXY(45, 18);
			printf("�����ˣ�");
			GotoXY(45, 20);
			printf("��������������˵�");
		}
		char c = _getch();
		system("cls");
		return 0;
	}

	Map();
	if (Overlap(snake)) // �ж��Ƿ���ײ
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
			printf("��ǰ�÷�:%d", snake1.length - 3);
		}
		else
		{ // ��ӡ�÷֣��÷�Ϊ�߳���ԭʼ����3
			GotoXY(50, 5);
			printf("��ǰ�÷�:%d", snake1.length - 3);
			GotoXY(70, 5);
			printf("��ǰ�÷�:%d", snake2.length - 3);
		}
	}
	if (snake->x == 1) // �����ٶ�

	{
		SpeedControl(snake); // ����
		if (player == 1)
		{
			GotoXY(50, 15);
			printf("  ��ǰ�ٶȣ�����  ");
		}
		else
		{
			{
				if (snake1.x == 1)
				{
					GotoXY(50, 15);
					printf("  ��ǰ�ٶȣ�����  ");

				} // ����
				else if (snake2.x == 1)
				{
					GotoXY(70, 15);
					printf("  ��ǰ�ٶȣ�����  ");
				}
			}
		}
	}
	else if (snake->x == 2)
	{
		if (player == 1)
		{
			GotoXY(50, 15);
			printf("  ��ǰ�ٶȣ�����  ");
		}
		else
		{
			if (snake1.x == 2)
			{
				GotoXY(50, 15);
				printf("  ��ǰ�ٶ�:����  ");
			}
			else if (snake2.x == 2)
			{
				GotoXY(70, 15);
				printf("  ��ǰ�ٶ�:����  ");
			}
		}
	}
	Sleep(snake->speed); // �ѽ��̹���һ��ʱ�䣬���ڿ������ƶ����ٶ�
	return 1;
}

/*�ж��Ƿ���ײ��ײǽ,����ֵΪ0��ʾ��ײ��ײǽ������Ϊ1*/

int IsCorrect(Snake *snake)
{
	for (int k = 0; k < barrierCount - 1; k++)
	{
		if (snake->snakeNode[0].x == barriers[k].x && snake->snakeNode[0].y == barriers[k].y || snake->snakeNode[0].x == barriers[k].x + 1 && snake->snakeNode[0].y == barriers[k].y + 1) // �ж���ͷ�Ƿ�ײǽ
			return 0;
	}

	return 1;
}
int ThroughWall(Snake *snake)
{
	if (snake->snakeNode[0].x == 0 || snake->snakeNode[0].y == 0 || snake->snakeNode[0].x == MAP_WIDTH - 1 || snake->snakeNode[0].y == MAP_HEIGHT - 1) // �ж���ͷ�Ƿ�ײǽ
		return 0;
	return 1;
}

/*�ж��Ƿ���������*/

int Overlap(Snake *snake)
{
	for (int i = 1; i < snake->length; i++)
	{ // �ж���ͷ�Ƿ�������ص����ص���ʾ��ײ
		if (snake->snakeNode[0].x == snake->snakeNode[i].x && snake->snakeNode[0].y == snake->snakeNode[i].y)
		{
			return i;
		}
	}
	return 0;
}

/*���ɵ�ͼ����*/
void Map()
{
	// SetColor(rand() % 10 + 2); ������ı�߿���ɫ
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		GotoXY(i, 0);
		printf("-");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("-");
	}
	// ���ɵ�ͼ���ұ߽�
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1, i);
		printf("|");
	}
}
/*���ٵ�������*/

void SpeedControl(Snake *snake)
{
	switch (snake->length)
	{ // �����߳������ߵ��ƶ��ٶ�
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
	{ // �����߳������ߵ��ƶ��ٶ�
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
	printf("�û���");
	GotoXY(58, 12);
	printf("����");
	int i;
	for (i = 0; i < 3; i++)
	{
		GotoXY(48, 12 + (i + 1) * 2);
		printf("%s", data[i].name);
		GotoXY(58, 12 + (i + 1) * 2);
		printf("%d", data[i].score);
	}
	GotoXY(48, 12 + (i + 1) * 2);
	printf("����������ز˵�");
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
		printf("�������û�����");
		GotoXY(48, 14);
		scanf("%s", &data[data[0].count].name);
	}
	else if (x == 2)
	{
		SetConsoleOutputCP(936);
		GotoXY(48, 12);
		printf("�������û���1:");
		GotoXY(48, 14);
		scanf("%s", &data[data[0].count].name);
		data[0].count++;
		system("cls");
		GotoXY(48, 12);
		SetConsoleOutputCP(936);
		printf("�������û���2:");
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

	for (int i = 0; i < data[0].count; i++) // ѡ������
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
	// ��ɫ����
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
/*�����ϰ��ﺯ��*/
void PrintBarrier(Snake *snake)
{
	int flag = 1;
	for (int i = 0; i <= barrierCount - 1; i++)
	{
		while (flag)
		{
			flag = 0;

			// ѭ���ж��ϰ���λ���Ƿ���ߵ�λ���ص�������ص�����Ҫ��������ʳ��λ��
			for (int k = 0; k <= snake->length - 1; k++)
			{
				if (snake->snakeNode[k].x == barriers[i].x && snake->snakeNode[k].y == barriers[i].y)
				{
					barriers[i].x = rand() % (MAP_WIDTH - 2) + 1;
					barriers[i].y = rand() % (MAP_HEIGHT - 2) + 1;
					flag = 1; // λ�����ص�����Ҫ����ѭ��
					break;
				}
			}
			for (int k = 0; k <= foodCount - 1; k++)
			{
				if (foods[k].x == barriers[i].x && foods[k].y == barriers[i].y)
				{
					barriers[i].x = rand() % (MAP_WIDTH - 2) + 1;
					barriers[i].y = rand() % (MAP_HEIGHT - 2) + 1;
					flag = 1; // λ�����ص�����Ҫ����ѭ��
					break;
				}
			}
			if (barriers[i].x == 0 || barriers[i].y == 0 || barriers[i].x == MAP_HEIGHT || barriers[i].y == MAP_WIDTH)
			{
				barriers[i].x = rand() % (MAP_WIDTH - 2) + 1;
				barriers[i].y = rand() % (MAP_HEIGHT - 2) + 1;
				flag = 1; // λ�����ص�����Ҫ����ѭ��
			}
		}
	}
	for (int i = 0; i <= barrierCount - 1; i++)
	{
		GotoXY(barriers[i].x, barriers[i].y);
		printf("��");
	}
}
int Mode()
{
	SetConsoleOutputCP(936);
	GotoXY(40, 12); // ��λ���λ��
	printf("ѡ���Ѷ�ģʽ");
	GotoXY(43, 14);
	printf("1.��ͨģʽ");
	GotoXY(43, 16);
	printf("2.����ģʽ");

	char ch;
	int result = 0;
	ch = _getch(); // �����û�����Ĳ˵�ѡ��
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
	GotoXY(40, 12); // ��λ���λ��
	printf("ѡ�����ģʽ");
	GotoXY(43, 14);
	printf("1.����ģʽ");
	GotoXY(43, 16);
	printf("2.˫��ģʽ");

	char ch;
	int result = 0;
	ch = _getch(); // �����û�����Ĳ˵�ѡ��
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
	GotoXY(40, 12); // ��λ���λ��
	printf("ѡ���Ƿ�����AI");
	GotoXY(43, 14);
	printf("1.����AI");
	GotoXY(43, 16);
	printf("2.������AI");

	char ch;
	int result = 0;
	ch = _getch(); // �����û�����Ĳ˵�ѡ��
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
