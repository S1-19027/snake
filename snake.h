/*引入必要的头文件*/
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>

/*MCIERROR mciSendString(
        LPCTSTR lpszCommand, //命令字符串：如 open、play 、close等
        LPTSTR lpszReturnString, //接受返回信息的字符串 ，即字符串
        UINT cchReturn,   //返回字符串的大小，sizeof
        HANDLE hwndCallback //回调窗口句柄，一般设置为NULL
) */

/*宏定义*/
#define MAP_HEIGHT 20    // 定义地图高度
#define MAP_WIDTH 40     // 定义地图宽度
#define UP_P1 'w'        // 定义上移键
#define DOWN_P1 's'      // 定义下移键
#define LEFT_P1 'a'      // 定义左移键
#define RIGHT_P1 'd'     // 定义右移键
#define Speedup_P1 'q'   // 定义加速键
#define Speeddown_P1 'e' // 定义减速键
#define UP_P2 'i'        // 定义上移键
#define DOWN_P2 'k'      // 定义下移键
#define LEFT_P2 'j'      // 定义左移键
#define RIGHT_P2 'l'     // 定义右移键
#define Speedup_P2 'u'   // 定义加速键
#define Speeddown_P2 'o' // 定义减速键
#define MAX_FOOD 10
#define MAX_BARRIER 10

/*结构体定义*/
typedef struct Point // 定义食物、障碍物和蛇位置的结构体
{
    int x; // x坐标位置
    int y; // y坐标位置
}  Barrier, Snakenode;
typedef struct {
    int x;
    int y;
    int score_food;

} Food;
// 方向枚举
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;
typedef struct // 定义蛇的结构体
{
    Snakenode snakeNode[1000]; // 蛇长最多包含1000个节点
    int length;                // 蛇长度
    int speed;                 // 蛇移动速度
    char snake_head;           // 蛇头字符
    char snake_body;           // 蛇身字符
    int x;                     // 加减速
    Direction Dir;

} Snake;
extern char direction1, direction2;
extern clock_t lastUpdateTime;
extern Snake snake1, snake2; // 这里要初始化// 定义蛇结构体变量,设置蛇长初始值为3节,设置蛇初始移动速度为250
// 你需要设计一个函数，将你自定义的蛇来代替默认的蛇；结构体已给出；
typedef struct
{
    char name[100];
    int score; // 分数
    int count; // 用户数量
} Data;
extern Data data[100];
// typedef struct 定义AI蛇
// {
// } AI_snake;

/*函数定义*/
void GotoXY(int, int);                                   // 光标定位函数
void Hide();                                             // 隐藏光标函数
int Menu();                                              // 主菜单函数
void Help();                                             // 帮助信息
void About();                                            // 关于信息
void InitMap(Snake *snake,int player);                              // 地图初始化
void PrintFood(Snake *snake);                            // 生成食物
void PrintBarrier(Snake *snake);                         // 生成障碍物
int MoveSnake(Snake *snake, char direction, int player); // 蛇移动
int IsCorrect();                                         // 自撞或撞墙检测
void SpeedControl(Snake *snake);                         // 高速速度控制
void SpeedControl2(Snake *snake);                        // 低速速度控制
void Read();                                             // 读取记录
void List();                                             // 排行榜
void Name(int);                                          // 记录用户名
void Rank();                                             // 记录成绩
void Write();                                            // 将记录保存到记事本
void SetColor(int c);                                    // 贪吃蛇颜色
int Overlap(Snake *snake);                               // 判断自撞
int ThroughWall(Snake *snake);                           // 判断穿墙
void Map();                                              // 生成地图
int Mode();                                              // 模式选择
int Player_Mode();                                       // 单人or多人
int Enable_AI();                                         // 是否使用ai？如果多人，还得增加是否为第二个玩家作为Ai选项
void Init(int player, int AI);                           // 根据player和ai来初始化地图
void AddBarrier();
void AddFood();
