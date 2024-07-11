#include "game.h"

//ȫ�ֱ���
int max = 0;
int grade = 0; //����
int countStep = 0; //����
int status[MAPHEIGHT][MAPWIDTH]; //�����Ϸ������λ�õ�״̬
Snake snake;
Body body[SNAKESIZE];//�������Դ洢����Ľṹ������

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; 
	curInfo.dwSize = 1; //��ʼ��
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}

//�����ת
void gotoxy(int x, int y)
{
	COORD pos; 
	pos.X = x; //������
	pos.Y = y; //������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}

//��Ϸ��ʼ����
void InitialInterface() 
{
    system("cls");
	//��ӡASCII���ַ���
    gotoxy(25, 2);
    printf("  ____   _           ____                    _           ");
	gotoxy(25, 3);
    printf(" / ___| | |  _   _  / ___|   _ __     __ _  | | __   ___ ");
	gotoxy(25, 4);
    printf("| |  _  | | | | | | \\___ \\  | '_ \\   / _` | | |/ /  / _ ");
	gotoxy(25, 5);
    printf("| |_| | | | | |_| |  ___) | | | | | | (_| | |   <  |  __/");
	gotoxy(25, 6);
    printf(" \\____| |_|  \\__,_| |____/  |_| |_|  \\__,_| |_|\\_\\  \\___|");
	//�Ѷ�ѡ��
    char selection;
	gotoxy(46, 10);
	printf("�� ѡ �� �� ��");
	gotoxy(45 ,14);
    printf(">  1.��ģʽ  <");
	gotoxy(45, 16);
    printf(">  2.�е�ģʽ  <");
	gotoxy(45, 18);
    printf(">  3.����ģʽ  <");
	reselect :
	selection = getch();
    switch (selection)
    {
    case '1':
		system("cls");
        CreateMap_Easy();
        break;
    case '2':
        system("cls");
		CreateMap_Middle();
        break;
    case '3':
        system("cls");
		CreateMap_Hard();
        break;
    default:
        goto reselect;//�����Ϲ淶�����뽫����Ϊ��Ч����
    }
}

//��ģʽ��ͼ
void CreateMap_Easy()
{
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			if (j == 0 || j == MAPWIDTH - 1)
			{
				status[i][j] = BORDER; //��Ǹ�λ��Ϊ�߽�
				gotoxy(2 * j, i);
				printf("��");
			}
			else if (i == 0 || i == MAPHEIGHT - 1)
			{
				status[i][j] = BORDER; //��Ǹ�λ��Ϊ�߽�
				gotoxy(2 * j, i);
				printf("��");
			}
			else
			{
				status[i][j] = empty; //��Ǹ�λ��Ϊ��
			}
		}
	}
	//��ͼ�²��ӡ�÷����ƶ�����
	gotoxy(0, MAPHEIGHT + 2);
	printf("��ǰ�÷�:%d", grade);
	gotoxy(40, MAPHEIGHT + 2);
	printf("�ƶ�����:%d", countStep);
	//��ͼ�Ҳ��ӡ����˵��
	gotoxy(2 * MAPWIDTH + 9, MAPHEIGHT / 2 - 5);
	printf("�� �� ˵ ��");
	gotoxy(2 * MAPWIDTH + 3, MAPHEIGHT / 2 - 2);
	printf("ͨ�����̷���������ߵ��ƶ�");
	gotoxy(2 * MAPWIDTH + 3, MAPHEIGHT / 2 );
	printf("��ͷ�������������߽������Ϸ����");
	gotoxy(2 * MAPWIDTH + 3, MAPHEIGHT / 2 + 2);
	printf("��ͷ���Ե�ʳ��񣬼ӷ�");
}

//�е�ģʽ��ͼ
void CreateMap_Middle()
{
	//�ڼ��ѶȻ���������ϰ�
	CreateMap_Easy();
	//���Ͻ��ϰ�
	status[4][5] = BORDER;
	gotoxy(10, 4);
	printf("��");
	for(int j = 6; j < 9; j++)
	{
		status[4][j] = BORDER;
		status[j - 1][5] = BORDER;
		gotoxy(2 * j, 4);
		printf("��");
		gotoxy(10, j - 1);
		printf("��");
	}
	//���½��ϰ�
	status[17][5] = BORDER;
	gotoxy(10, 17);
	printf("��");
	for(int j = 6; j < 9; j++)
	{
		status[17][j] = BORDER;
		status[j + 8][5] = BORDER;
		gotoxy(2 * j, 17);
		printf("��");
		gotoxy(10, j + 8);
		printf("��");
	}
	//���Ͻ��ϰ�
	status[4][33] = BORDER;
	gotoxy(66, 4);
	printf("��");
	for(int j = 6; j < 9; j++)
	{
		status[4][j + 24] = BORDER;
		status[j - 1][33] = BORDER;
		gotoxy(2 * (j + 24), 4);
		printf("��");
		gotoxy(66, j - 1);
		printf("��");
	}
	//���½��ϰ�
	status[17][33] = BORDER;
	gotoxy(66, 17);
	printf("��");
	for(int j = 6; j < 9; j++)
	{
		status[17][j + 24] = BORDER;
		status[j + 8][33] = BORDER;
		gotoxy(2 * (j + 24), 17);
		printf("��");
		gotoxy(66, j + 8);
		printf("��");
	}
}

//����ģʽ��ͼ
void CreateMap_Hard()
{
	//���е��ѶȻ���������ϰ�
	CreateMap_Middle();
	//�����ϰ�
	for(int j = 17;j < 23;j++)
	{
		status[4][j] = BORDER;
		status[17][j] = BORDER;
		gotoxy(2 * j, 4);
		printf("��");
		gotoxy(2 * j, 17);
		printf("��");
	}
	//�����ϰ�
	for(int j = 7;j < 15;j++)
	{
		status[j][8] = BORDER;
		status[j][16] = BORDER;
		status[j][24] = BORDER;
		status[j][30] = BORDER;
		gotoxy(16, j);
		printf("��");
		gotoxy(32, j);
		printf("��");
		gotoxy(48, j);
		printf("��");
		gotoxy(60, j);
		printf("��");
	}
}

//��ʼ����
void InitSnake()
{
	snake.len = 2; //�ߵ����峤�ȳ�ʼ��Ϊ2
	snake.x = MAPWIDTH / 2; 
	snake.y = MAPHEIGHT / 2;
	//��������ĳ�ʼ��
	body[0].x = MAPWIDTH / 2 - 1;
	body[0].y = MAPHEIGHT / 2;
	body[1].x = MAPWIDTH / 2 - 2;
	body[1].y = MAPHEIGHT / 2;
	//����ͷ������λ�ý��б��
	status[snake.y][snake.x] = HEAD;
	status[body[0].y][body[0].x] = BODY;
	status[body[1].y][body[1].x] = BODY;
}

//�������ʳ��
void CreateFood()
{
	int i, j;
	while (1)
	{
		i = rand() % MAPHEIGHT;
		j = rand() % MAPWIDTH;
		if(status[i][j] == empty)//ȷ������λ�ò��Ǳ߽���ߵ�λ��
			break;
	}
	status[i][j] = FOOD; //��ʳ��λ�ý��б��
	gotoxy(2 * j, i); 
	printf("��"); 
}

//��ӡ���븲����
void DrawSnake(int flag)
{
	if (flag == 1) //��ӡ��
	{
		gotoxy(2 * snake.x, snake.y);
		printf("��"); //��ӡ��ͷ
		for (int i = 0; i < snake.len; i++)
		{
			gotoxy(2 * body[i].x, body[i].y);
			printf("��"); //��ӡ����
		}
	}
	else //������
	{
		if (body[snake.len - 1].x != 0) //��ֹlen++��(0, 0)λ�õ�ǽ����
		{
			//����β����Ϊ�ո񼴿�
			gotoxy(2 * body[snake.len - 1].x, body[snake.len - 1].y);
			printf("  ");
		}
	}
}

//�ƶ���
void MoveSnake(int x, int y)
{
	DrawSnake(0); //�ȸ��ǵ�ǰ����ʾ����
	status[body[snake.len - 1].y][body[snake.len - 1].x] = empty; //���ƶ�����β���±��Ϊ��
	status[snake.y][snake.x] = BODY; //�ƶ�����ͷ��λ�ñ�Ϊ����
	//�����������
	for (int i = snake.len - 1; i > 0; i--)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	//��0����������ҲҪ����
	body[0].x = snake.x;
	body[0].y = snake.y;
	//��ͷ�������
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	DrawSnake(1); //��ӡ�ƶ������
}

//�жϵ÷������
void Judge(int x, int y)
{
	//����ͷ���������λ����ʳ���÷�
	if (status[snake.y + y][snake.x + x] == FOOD)
	{
		snake.len++; 
		grade += 10; //���µ�ǰ�÷�
		gotoxy(0, MAPHEIGHT + 2);
		printf("��ǰ�÷�:%d", grade); //���´�ӡ��ǰ�÷�
		CreateFood(); //�����������ʳ��
	}
	//����ͷ���������λ����ǽ������������Ϸ����
	else if (status[snake.y + y][snake.x + x] == BORDER || status[snake.y + y][snake.x + x] == BODY)
	{
		Sleep(1000); //������ͣ1s,������ҷ�Ӧʱ��
		system("cls");
		gotoxy(41, 10);
		printf("GAME OVER");
		//�Ƿ�����һ��
		while (1)
		{
			char ch;
			gotoxy(40, 12);
			printf("����y����һ��");
			gotoxy(40, 14);
			printf("����n��ֹ��Ϸ");
			reselect :
			ch = getch();
			if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();
			}
			else if (ch == 'n' || ch == 'N')
			{
				gotoxy(2 * (MAPWIDTH / 3), MAPHEIGHT / 2 + 5);
				exit(0);
			}
			else
			{
				goto reselect;//����������Ч����ת����������
			}
		}
	}
}

//ִ�а���
void RunKey(int x, int y)
{
	int speed = 0;
	while (1)
	{
		if (speed == 0)
			speed = 3000; //����speedԽС�����ƶ��ٶ�Խ�죨���Ը��ݴ�������Ϸ�Ѷȣ�
		while (--speed)
		{
			if (kbhit() != 0) //�����̱��û������˳�ѭ��
				break;
		}
		if (speed == 0) //����δ���û�,�߽������ƶ�
		{
			Judge(x, y); //�жϵ����λ�ú��Ƿ�÷�����Ϸ����
			MoveSnake(x, y); //�ƶ���
		}
		else //���̱��û�
		{
			break; //����GameLogic������ȡ��ֵ
		}
	}
}

//��Ϸ�����߼�����
void GameLogic()
{
	int direction = RIGHT; //��ʼ��Ϸʱ��Ĭ�������ƶ�
	int tmp = RIGHT; //�ݴ��ߵ���һ���ƶ�����
	int isFirst = 1;
	while (1)
	{
		//��һ�β�ִ��
		if(!isFirst)
		{
			direction = getch(); 
			//�������������ܳ�����ͷ�����ƶ������
			switch (direction)
			{
			case UP:
			case DOWN: //����û����ǡ��ϡ����¡�
				if (tmp != LEFT && tmp != RIGHT) //������һ���ߵ��ƶ������ǡ��󡱻��ҡ�
				{
					direction = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
				}
				break;
			case LEFT:
			case RIGHT: //����û����ǡ��󡱻��ҡ�
				if (tmp != UP && tmp != DOWN) //������һ���ߵ��ƶ������ǡ��ϡ����¡�
				{
					direction = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
				}
				break;
			default:
				direction = tmp; //��������Ч��Ĭ��Ϊ��һ�����ƶ��ķ���
				break;
			}
		}
		//�������ȷ�ķ����������ƶ�����
		if(direction != tmp)
		{
			countStep++;
			gotoxy(40, MAPHEIGHT + 2);
			printf("�ƶ�����:%d", countStep);
		}
		//��������ķ����ƶ���
		switch (direction)
		{
		case UP: 
			RunKey(0, -1); //�����ƶ�
			tmp = UP; 
			break;
		case DOWN:
			RunKey(0, 1); //�����ƶ�
			tmp = DOWN; 
			break;
		case LEFT: 
			RunKey(-1, 0); //�����ƶ�
			tmp = LEFT; 
			break;
		case RIGHT: 
			RunKey(1, 0); //�����ƶ�
			tmp = RIGHT;
			break;
		}
		isFirst = 0;//֮���ѭ���������ǡ���һ�Ρ�ѭ��
	}
}