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
#define MAP_HEIGHT 20 // �����ͼ�߶�
#define MAP_WIDTH 40  // �����ͼ���
#define UP 'w'        // �������Ƽ�
#define DOWN 's'      // �������Ƽ�
#define LEFT 'a'      // �������Ƽ�
#define RIGHT 'd'     // �������Ƽ�
#define Speedup 'q'   // ������ټ�
#define Speeddown 'e' // ������ټ�

/*�ṹ�嶨��*/
typedef struct // ����ʳ����߽ڵ�λ�õĽṹ��
{
    int x; // x����λ��
    int y; // y����λ��
} Food, Snakenode, Barrier;

typedef struct // �����ߵĽṹ��
{
    Snakenode snakeNode[1000]; // �߳�������1000���ڵ�
    int length;                // �߳���
    int speed;                 // ���ƶ��ٶ�
} Snake;

typedef struct
{
    char name[100];
    int score; // ����
    int count; // �û�����
} Data;

/*��������*/
/*��������*/
void GotoXY(int, int); // ��궨λ����
void Hide();           // ���ع�꺯��
int Menu();            // ���˵�����
void Help();           // ������Ϣ
void About();          // ������Ϣ
void InitMap();        // ��ͼ��ʼ��
void PrintFood();      // ����ʳ��
void PrintBarrier();   // �����ϰ���
int MoveSnake();       // ���ƶ�
int IsCorrect();       // ��ײ��ײǽ���
void SpeedControl();   // �����ٶȿ���
void SpeedControl2();  // �����ٶȿ���
void Read();           // ��ȡ��¼
void List();           // ���а�
void Name();           // ��¼�û���
void Rank();           // ��¼�ɼ�
void Write();          // ����¼���浽���±�
void SetColor(int c);  // ̰������ɫ
int Overlap();         // �ж���ײ
