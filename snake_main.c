#include "snake.h"
int main()
{

	srand((unsigned int)time(0)); // �������������
	int end = 1, result;
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
			Mode();
			Player_Mode();
			Enable_AI();
			Name();
			InitMap(); // ��ʼ����ͼ���ߺ�ʳ��
			while (MoveSnake())
				; // �������0������ֹͣ�ƶ�������1�������ƶ�
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