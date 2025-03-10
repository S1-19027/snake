#include "snake.h"

clock_t lastUpdateTime;
int main()
{

	srand((unsigned int)time(0)); // 生成随机数种子
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
		result = Menu(); // 显示主菜单，并根据用户选择菜单选项决定游戏的执行
		switch (result)
		{
		case 1: // 选择1表示，开始贪吃蛇游戏
			SetConsoleOutputCP(936);
			result_mode = Mode();
			result_player = Player_Mode();
			result_AI = Enable_AI();
			Name(result_player);
			if (result_player == 1)
			{
				Init(result_player, result_AI); // 初始化地图、蛇和食物
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
				Init(result_player, result_AI); // 初始化地图、蛇和食物

				while (1)
				{
					int alive1 = MoveSnake(&snake1, direction1, 2);
					int alive2 = MoveSnake(&snake2, direction2, 2);

					if (!alive1 || !alive2)
					{
						// 记录两条蛇的最终得分
						data[data[0].count - 2].score = snake1.length - 3;
						data[data[0].count - 1].score = snake2.length - 3;

						break; // 结束游戏
					}
				};

			} // 如果返回0，则蛇停止移动；返回1，继续移动
			Rank();
			break;
		case 2: // 选择2表示，显示帮助信息
			SetConsoleOutputCP(936);
			Help();
			break;
		case 3:
			SetConsoleOutputCP(936);
			About();
			break;
		case 4:
			SetConsoleOutputCP(936);
			List(); // 选择4表示，显示排行榜
			break;
		case 0: // 选择0表示，表示结束程序
			end = 0;
			Write();
			break;
		}
	}
	return 0;
}