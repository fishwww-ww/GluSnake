#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//��Ϸ�����С
#define MAPHEIGHT 22 //��Ϸ������
#define MAPWIDTH 42 //��Ϸ������
#define SNAKESIZE 50 //������󳤶�

//�����ڸ�����λ��״̬
#define empty 0 //��ǿ�
#define BORDER 1 //��Ǳ߽�
#define FOOD 2 //���ʳ��
#define HEAD 3 //�����ͷ
#define BODY 4 //�������

//���ݼ�
#define UP 72 //���������
#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������

//��ͷ
typedef struct Snake
{
	int len; //��¼������
	int x; //��ͷ������
	int y; //��ͷ������
}Snake;

//����
typedef struct Body
{
	int x; //���������
	int y; //����������
}Body;

//���ܺ���
void HideCursor();//���ع��
void gotoxy(int x, int y);//�����ת
void InitialInterface();//��Ϸ��ʼ����
void CreateMap_Easy();//��ģʽ��ͼ
void CreateMap_Middle();//�е�ģʽ��ͼ
void CreateMap_Hard();//����ģʽ��ͼ
void InitSnake();//��ʼ����
void CreateFood();//�������ʳ��
void Judge(int x, int y);//�жϵ÷������
void DrawSnake(int flag);//��ӡ���븲����
void MoveSnake(int x, int y);//�ƶ���
void RunKey(int x, int y);//ִ�а���
void GameLogic();//��Ϸ�����߼�����