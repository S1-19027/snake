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
#define MAP_HEIGHT 20 // 定义地图高度
#define MAP_WIDTH 40  // 定义地图宽度
#define UP 'w'        // 定义上移键
#define DOWN 's'      // 定义下移键
#define LEFT 'a'      // 定义左移键
#define RIGHT 'd'     // 定义右移键
#define Speedup 'q'   // 定义加速键
#define Speeddown 'e' // 定义减速键

/*结构体定义*/
typedef struct // 定义食物和蛇节点位置的结构体
{
    int x; // x坐标位置
    int y; // y坐标位置
} Food, Snakenode, Barrier;

typedef struct // 定义蛇的结构体
{
    Snakenode snakeNode[1000]; // 蛇长最多包含1000个节点
    int length;                // 蛇长度
    int speed;                 // 蛇移动速度
} Snake;

typedef struct
{
    char name[100];
    int score; // 分数
    int count; // 用户数量
} Data;

/*函数定义*/
/*函数定义*/
void GotoXY(int, int); // 光标定位函数
void Hide();           // 隐藏光标函数
int Menu();            // 主菜单函数
void Help();           // 帮助信息
void About();          // 关于信息
void InitMap();        // 地图初始化
void PrintFood();      // 生成食物
void PrintBarrier();   // 生成障碍物
int MoveSnake();       // 蛇移动
int IsCorrect();       // 自撞或撞墙检测
void SpeedControl();   // 高速速度控制
void SpeedControl2();  // 低速速度控制
void Read();           // 读取记录
void List();           // 排行榜
void Name();           // 记录用户名
void Rank();           // 记录成绩
void Write();          // 将记录保存到记事本
void SetColor(int c);  // 贪吃蛇颜色
int Overlap();         // 判断自撞
