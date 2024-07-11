#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//游戏区域大小
#define MAPHEIGHT 22 //游戏区行数
#define MAPWIDTH 42 //游戏区列数
#define SNAKESIZE 50 //蛇身最大长度

//区域内各个点位的状态
#define empty 0 //标记空
#define BORDER 1 //标记边界
#define FOOD 2 //标记食物
#define HEAD 3 //标记蛇头
#define BODY 4 //标记蛇身

//操纵键
#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右

//蛇头
typedef struct Snake
{
	int len; //记录蛇身长度
	int x; //蛇头横坐标
	int y; //蛇头纵坐标
}Snake;

//蛇身
typedef struct Body
{
	int x; //蛇身横坐标
	int y; //蛇身纵坐标
}Body;

//功能函数
void HideCursor();//隐藏光标
void gotoxy(int x, int y);//光标跳转
void InitialInterface();//游戏初始界面
void CreateMap_Easy();//简单模式地图
void CreateMap_Middle();//中等模式地图
void CreateMap_Hard();//困难模式地图
void InitSnake();//初始化蛇
void CreateFood();//随机生成食物
void Judge(int x, int y);//判断得分与结束
void DrawSnake(int flag);//打印蛇与覆盖蛇
void MoveSnake(int x, int y);//移动蛇
void RunKey(int x, int y);//执行按键
void GameLogic();//游戏主体逻辑函数