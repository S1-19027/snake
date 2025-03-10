/*�����Ҫ��ͷ�ļ�*/
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>

/*MCIERROR mciSendString(
        LPCTSTR lpszCommand, //�����ַ������� open��play ��close��
        LPTSTR lpszReturnString, //���ܷ�����Ϣ���ַ��� �����ַ���
        UINT cchReturn,   //�����ַ����Ĵ�С��sizeof
        HANDLE hwndCallback //�ص����ھ����һ������ΪNULL
) */

/*�궨��*/
#define MAP_HEIGHT 20    // �����ͼ�߶�
#define MAP_WIDTH 40     // �����ͼ���
#define UP_P1 'w'        // �������Ƽ�
#define DOWN_P1 's'      // �������Ƽ�
#define LEFT_P1 'a'      // �������Ƽ�
#define RIGHT_P1 'd'     // �������Ƽ�
#define Speedup_P1 'q'   // ������ټ�
#define Speeddown_P1 'e' // ������ټ�
#define UP_P2 'i'        // �������Ƽ�
#define DOWN_P2 'k'      // �������Ƽ�
#define LEFT_P2 'j'      // �������Ƽ�
#define RIGHT_P2 'l'     // �������Ƽ�
#define Speedup_P2 'u'   // ������ټ�
#define Speeddown_P2 'o' // ������ټ�
#define MAX_FOOD 10
#define MAX_BARRIER 10

/*�ṹ�嶨��*/
typedef struct Point // ����ʳ��ϰ������λ�õĽṹ��
{
    int x; // x����λ��
    int y; // y����λ��
}  Barrier, Snakenode;
typedef struct {
    int x;
    int y;
    int score_food;

} Food;
// ����ö��
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;
typedef struct // �����ߵĽṹ��
{
    Snakenode snakeNode[1000]; // �߳�������1000���ڵ�
    int length;                // �߳���
    int speed;                 // ���ƶ��ٶ�
    char snake_head;           // ��ͷ�ַ�
    char snake_body;           // �����ַ�
    int x;                     // �Ӽ���
    Direction Dir;

} Snake;
extern char direction1, direction2;
extern clock_t lastUpdateTime;
extern Snake snake1, snake2; // ����Ҫ��ʼ��// �����߽ṹ�����,�����߳���ʼֵΪ3��,�����߳�ʼ�ƶ��ٶ�Ϊ250
// ����Ҫ���һ�������������Զ������������Ĭ�ϵ��ߣ��ṹ���Ѹ�����
typedef struct
{
    char name[100];
    int score; // ����
    int count; // �û�����
} Data;
extern Data data[100];
// typedef struct ����AI��
// {
// } AI_snake;

/*��������*/
void GotoXY(int, int);                                   // ��궨λ����
void Hide();                                             // ���ع�꺯��
int Menu();                                              // ���˵�����
void Help();                                             // ������Ϣ
void About();                                            // ������Ϣ
void InitMap(Snake *snake,int player);                              // ��ͼ��ʼ��
void PrintFood(Snake *snake);                            // ����ʳ��
void PrintBarrier(Snake *snake);                         // �����ϰ���
int MoveSnake(Snake *snake, char direction, int player); // ���ƶ�
int IsCorrect();                                         // ��ײ��ײǽ���
void SpeedControl(Snake *snake);                         // �����ٶȿ���
void SpeedControl2(Snake *snake);                        // �����ٶȿ���
void Read();                                             // ��ȡ��¼
void List();                                             // ���а�
void Name(int);                                          // ��¼�û���
void Rank();                                             // ��¼�ɼ�
void Write();                                            // ����¼���浽���±�
void SetColor(int c);                                    // ̰������ɫ
int Overlap(Snake *snake);                               // �ж���ײ
int ThroughWall(Snake *snake);                           // �жϴ�ǽ
void Map();                                              // ���ɵ�ͼ
int Mode();                                              // ģʽѡ��
int Player_Mode();                                       // ����or����
int Enable_AI();                                         // �Ƿ�ʹ��ai��������ˣ����������Ƿ�Ϊ�ڶ��������ΪAiѡ��
void Init(int player, int AI);                           // ����player��ai����ʼ����ͼ
void AddBarrier();
void AddFood();
