#include<opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include "hinder.h"
#include "source.h"
#include "ui.h"
#include "user.h"
#include "grade.h"
#include "isHit.h"
#include "play.h"
using namespace cv;

int main()
{
	int c = waitKey(100);
	int newGame = 0; //用来标记是否为新一轮游戏，若为新一轮游戏，各函数中静态变量重新赋初值
	while (c != 35) {
		play(newGame);
		newGame++;
	}
}