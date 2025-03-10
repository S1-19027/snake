#include "snake.h"

clock_t lastUpdateTime;
int main()
{

	srand((unsigned int)time(0)); // �������������
	int end = 1, result;
	int result_mode;
	int result_player;
	int result_AI;
	int alive1, alive2;
	SetConsoleOutputCP(936);
	SetConsoleCP(936);
	lastUpdateTime = clock();
	Read();
	while (end)
	{
		SetConsoleOutputCP(936);
		result = Menu(); // ��ʾ���˵����������û�ѡ��˵�ѡ�������Ϸ��ִ��
		switch (result)
		{
		case 1: // ѡ��1��ʾ����ʼ̰������Ϸ
			SetConsoleOutputCP(936);
			result_mode = Mode();
			result_player = Player_Mode();
			result_AI = Enable_AI();
			Name(result_player);
			if (result_player == 1)
			{
				Init(result_player, result_AI); // ��ʼ����ͼ���ߺ�ʳ��
				while (1)
				{
					alive1 = MoveSnake(&snake1, direction1, 1);
					if (alive1 != 1)
					{
						data[data[0].count - 1].score = snake1.length - 3;
						break;
					}
				}
			}
			else if (result_player == 2)
			{
				Init(result_player, result_AI); // ��ʼ����ͼ���ߺ�ʳ��

				while (1)
				{
					int alive1 = MoveSnake(&snake1, direction1, 2);
					int alive2 = MoveSnake(&snake2, direction2, 2);

					if (!alive1 || !alive2)
					{
						// ��¼�����ߵ����յ÷�
						data[data[0].count - 2].score = snake1.length - 3;
						data[data[0].count - 1].score = snake2.length - 3;

						break; // ������Ϸ
					}
				};

			} // �������0������ֹͣ�ƶ�������1�������ƶ�
			Rank();
			break;
		case 2: // ѡ��2��ʾ����ʾ������Ϣ
			SetConsoleOutputCP(936);
			Help();
			break;
		case 3:
			SetConsoleOutputCP(936);
			About();
			break;
		case 4:
			SetConsoleOutputCP(936);
			List(); // ѡ��4��ʾ����ʾ���а�
			break;
		case 0: // ѡ��0��ʾ����ʾ��������
			end = 0;
			Write();
			break;
		}
	}
	return 0;
}