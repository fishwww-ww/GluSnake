#include "game.h"

void main()
{
	HideCursor(); //���ع��
	InitialInterface();
	InitSnake(); //��ʼ����
	srand((unsigned int)time(NULL)); //����������������
	CreateFood(); //�������ʳ��
	DrawSnake(1); //��ӡ��
	GameLogic(); //��ʼ��Ϸ
}