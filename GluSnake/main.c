#include "game.h"

void main()
{
	HideCursor(); //隐藏光标
	InitialInterface();
	InitSnake(); //初始化蛇
	srand((unsigned int)time(NULL)); //设置随机数生成起点
	CreateFood(); //随机生成食物
	DrawSnake(1); //打印蛇
	GameLogic(); //开始游戏
}