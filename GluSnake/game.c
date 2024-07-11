#include "game.h"

//全局变量
int max = 0;
int grade = 0; //分数
int countStep = 0; //步数
int status[MAPHEIGHT][MAPWIDTH]; //标记游戏区各个位置的状态
Snake snake;
Body body[SNAKESIZE];//开辟足以存储蛇身的结构体数组

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; 
	curInfo.dwSize = 1; //初始化
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}

//光标跳转
void gotoxy(int x, int y)
{
	COORD pos; 
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorPosition(handle, pos); //设置光标位置
}

//游戏初始界面
void InitialInterface() 
{
    system("cls");
	//打印ASCII码字符画
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
	//难度选择
    char selection;
	gotoxy(46, 10);
	printf("请 选 择 难 度");
	gotoxy(45 ,14);
    printf(">  1.简单模式  <");
	gotoxy(45, 16);
    printf(">  2.中等模式  <");
	gotoxy(45, 18);
    printf(">  3.困难模式  <");
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
        goto reselect;//不符合规范的输入将被视为无效输入
    }
}

//简单模式地图
void CreateMap_Easy()
{
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			if (j == 0 || j == MAPWIDTH - 1)
			{
				status[i][j] = BORDER; //标记该位置为边界
				gotoxy(2 * j, i);
				printf("■");
			}
			else if (i == 0 || i == MAPHEIGHT - 1)
			{
				status[i][j] = BORDER; //标记该位置为边界
				gotoxy(2 * j, i);
				printf("■");
			}
			else
			{
				status[i][j] = empty; //标记该位置为空
			}
		}
	}
	//地图下侧打印得分与移动步数
	gotoxy(0, MAPHEIGHT + 2);
	printf("当前得分:%d", grade);
	gotoxy(40, MAPHEIGHT + 2);
	printf("移动步数:%d", countStep);
	//地图右侧打印操作说明
	gotoxy(2 * MAPWIDTH + 9, MAPHEIGHT / 2 - 5);
	printf("操 作 说 明");
	gotoxy(2 * MAPWIDTH + 3, MAPHEIGHT / 2 - 2);
	printf("通过键盘方向键控制蛇的移动");
	gotoxy(2 * MAPWIDTH + 3, MAPHEIGHT / 2 );
	printf("蛇头■碰到蛇身□或边界■，游戏结束");
	gotoxy(2 * MAPWIDTH + 3, MAPHEIGHT / 2 + 2);
	printf("蛇头■吃到食物●，加分");
}

//中等模式地图
void CreateMap_Middle()
{
	//在简单难度基础上添加障碍
	CreateMap_Easy();
	//左上角障碍
	status[4][5] = BORDER;
	gotoxy(10, 4);
	printf("■");
	for(int j = 6; j < 9; j++)
	{
		status[4][j] = BORDER;
		status[j - 1][5] = BORDER;
		gotoxy(2 * j, 4);
		printf("■");
		gotoxy(10, j - 1);
		printf("■");
	}
	//左下角障碍
	status[17][5] = BORDER;
	gotoxy(10, 17);
	printf("■");
	for(int j = 6; j < 9; j++)
	{
		status[17][j] = BORDER;
		status[j + 8][5] = BORDER;
		gotoxy(2 * j, 17);
		printf("■");
		gotoxy(10, j + 8);
		printf("■");
	}
	//右上角障碍
	status[4][33] = BORDER;
	gotoxy(66, 4);
	printf("■");
	for(int j = 6; j < 9; j++)
	{
		status[4][j + 24] = BORDER;
		status[j - 1][33] = BORDER;
		gotoxy(2 * (j + 24), 4);
		printf("■");
		gotoxy(66, j - 1);
		printf("■");
	}
	//右下角障碍
	status[17][33] = BORDER;
	gotoxy(66, 17);
	printf("■");
	for(int j = 6; j < 9; j++)
	{
		status[17][j + 24] = BORDER;
		status[j + 8][33] = BORDER;
		gotoxy(2 * (j + 24), 17);
		printf("■");
		gotoxy(66, j + 8);
		printf("■");
	}
}

//困难模式地图
void CreateMap_Hard()
{
	//在中等难度基础上添加障碍
	CreateMap_Middle();
	//上下障碍
	for(int j = 17;j < 23;j++)
	{
		status[4][j] = BORDER;
		status[17][j] = BORDER;
		gotoxy(2 * j, 4);
		printf("■");
		gotoxy(2 * j, 17);
		printf("■");
	}
	//左右障碍
	for(int j = 7;j < 15;j++)
	{
		status[j][8] = BORDER;
		status[j][16] = BORDER;
		status[j][24] = BORDER;
		status[j][30] = BORDER;
		gotoxy(16, j);
		printf("■");
		gotoxy(32, j);
		printf("■");
		gotoxy(48, j);
		printf("■");
		gotoxy(60, j);
		printf("■");
	}
}

//初始化蛇
void InitSnake()
{
	snake.len = 2; //蛇的身体长度初始化为2
	snake.x = MAPWIDTH / 2; 
	snake.y = MAPHEIGHT / 2;
	//蛇身坐标的初始化
	body[0].x = MAPWIDTH / 2 - 1;
	body[0].y = MAPHEIGHT / 2;
	body[1].x = MAPWIDTH / 2 - 2;
	body[1].y = MAPHEIGHT / 2;
	//将蛇头和蛇身位置进行标记
	status[snake.y][snake.x] = HEAD;
	status[body[0].y][body[0].x] = BODY;
	status[body[1].y][body[1].x] = BODY;
}

//随机生成食物
void CreateFood()
{
	int i, j;
	while (1)
	{
		i = rand() % MAPHEIGHT;
		j = rand() % MAPWIDTH;
		if(status[i][j] == empty)//确保生成位置不是边界或蛇的位置
			break;
	}
	status[i][j] = FOOD; //将食物位置进行标记
	gotoxy(2 * j, i); 
	printf("●"); 
}

//打印蛇与覆盖蛇
void DrawSnake(int flag)
{
	if (flag == 1) //打印蛇
	{
		gotoxy(2 * snake.x, snake.y);
		printf("■"); //打印蛇头
		for (int i = 0; i < snake.len; i++)
		{
			gotoxy(2 * body[i].x, body[i].y);
			printf("□"); //打印蛇身
		}
	}
	else //覆盖蛇
	{
		if (body[snake.len - 1].x != 0) //防止len++后将(0, 0)位置的墙覆盖
		{
			//将蛇尾覆盖为空格即可
			gotoxy(2 * body[snake.len - 1].x, body[snake.len - 1].y);
			printf("  ");
		}
	}
}

//移动蛇
void MoveSnake(int x, int y)
{
	DrawSnake(0); //先覆盖当前所显示的蛇
	status[body[snake.len - 1].y][body[snake.len - 1].x] = empty; //蛇移动后蛇尾重新标记为空
	status[snake.y][snake.x] = BODY; //移动后蛇头的位置变为蛇身
	//蛇身坐标更新
	for (int i = snake.len - 1; i > 0; i--)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	//第0个蛇身坐标也要更新
	body[0].x = snake.x;
	body[0].y = snake.y;
	//蛇头坐标更新
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	DrawSnake(1); //打印移动后的蛇
}

//判断得分与结束
void Judge(int x, int y)
{
	//若蛇头即将到达的位置是食物，则得分
	if (status[snake.y + y][snake.x + x] == FOOD)
	{
		snake.len++; 
		grade += 10; //更新当前得分
		gotoxy(0, MAPHEIGHT + 2);
		printf("当前得分:%d", grade); //重新打印当前得分
		CreateFood(); //重新随机生成食物
	}
	//若蛇头即将到达的位置是墙或者蛇身，则游戏结束
	else if (status[snake.y + y][snake.x + x] == BORDER || status[snake.y + y][snake.x + x] == BODY)
	{
		Sleep(1000); //程序暂停1s,留给玩家反应时间
		system("cls");
		gotoxy(41, 10);
		printf("GAME OVER");
		//是否再来一局
		while (1)
		{
			char ch;
			gotoxy(40, 12);
			printf("输入y再来一局");
			gotoxy(40, 14);
			printf("输入n终止游戏");
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
				goto reselect;//其它输入无效，跳转至重新输入
			}
		}
	}
}

//执行按键
void RunKey(int x, int y)
{
	int speed = 0;
	while (1)
	{
		if (speed == 0)
			speed = 3000; //这里speed越小，蛇移动速度越快（可以根据次设置游戏难度）
		while (--speed)
		{
			if (kbhit() != 0) //若键盘被敲击，则退出循环
				break;
		}
		if (speed == 0) //键盘未被敲击,蛇将持续移动
		{
			Judge(x, y); //判断到达该位置后，是否得分与游戏结束
			MoveSnake(x, y); //移动蛇
		}
		else //键盘被敲击
		{
			break; //返回GameLogic函数读取键值
		}
	}
}

//游戏主体逻辑函数
void GameLogic()
{
	int direction = RIGHT; //开始游戏时，默认向右移动
	int tmp = RIGHT; //暂存蛇的上一次移动方向
	int isFirst = 1;
	while (1)
	{
		//第一次不执行
		if(!isFirst)
		{
			direction = getch(); 
			//调整按键，不能出现蛇头反向移动的情况
			switch (direction)
			{
			case UP:
			case DOWN: //如果敲击的是“上”或“下”
				if (tmp != LEFT && tmp != RIGHT) //并且上一次蛇的移动方向不是“左”或“右”
				{
					direction = tmp; //那么下一次蛇的移动方向设置为上一次蛇的移动方向
				}
				break;
			case LEFT:
			case RIGHT: //如果敲击的是“左”或“右”
				if (tmp != UP && tmp != DOWN) //并且上一次蛇的移动方向不是“上”或“下”
				{
					direction = tmp; //那么下一次蛇的移动方向设置为上一次蛇的移动方向
				}
				break;
			default:
				direction = tmp; //其他键无效，默认为上一次蛇移动的方向
				break;
			}
		}
		//如果是正确的方向，则增加移动步数
		if(direction != tmp)
		{
			countStep++;
			gotoxy(40, MAPHEIGHT + 2);
			printf("移动步数:%d", countStep);
		}
		//根据输入的方向移动蛇
		switch (direction)
		{
		case UP: 
			RunKey(0, -1); //向上移动
			tmp = UP; 
			break;
		case DOWN:
			RunKey(0, 1); //向下移动
			tmp = DOWN; 
			break;
		case LEFT: 
			RunKey(-1, 0); //向左移动
			tmp = LEFT; 
			break;
		case RIGHT: 
			RunKey(1, 0); //向右移动
			tmp = RIGHT;
			break;
		}
		isFirst = 0;//之后的循环都不再是“第一次”循环
	}
}