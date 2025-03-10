#include "snake.h"
int main()
{

	srand((unsigned int)time(0)); // �������������
	int end = 1, result;
	int result_mode;
	int result_player;
	int result_AI;
	SetConsoleOutputCP(936);
	SetConsoleCP(936);
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
				while (MoveSnake(&snake1,direction1))
					;
			}
			else if (result_player == 2)
			{
				Init(result_player, result_AI); // ��ʼ����ͼ���ߺ�ʳ��
				while (MoveSnake(&snake1,direction1) && MoveSnake(&snake2,direction2))
					;
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