#pragma once
#include "source.h"
#include<opencv2/opencv.hpp>
#include<windows.h>
#include <stdlib.h>
#include <iostream>
using namespace cv;
using namespace std;

class Ui {
private:
	int flag = 1;

public:
	void picture(Mat frame, Point2f center) {
		//显示一张图片，半透明，图片分成四个区域。
		Rect roi(0, 0, 640, 480);
		Mat frame_roi = frame(roi);
		Source s;
		Mat pic = imread(s.uiImage);
		cv::resize(pic, pic, Size(640, 480));
		pic = pic(Range(0, 480), Range(0, 640));
		cv::addWeighted(frame_roi, 0.5, pic, 0.5, 1, frame_roi);  //调整透明度
	}

	int choice(int location_x, int location_y,int newGame) {
		static int nowGame = newGame;
		static int a = 1;
		static int b = 1;
		static long t = 0;
		if (newGame > nowGame) {
			a = 1;
			b = 1;
			t = 0;
			nowGame++;
		}
		if (b > 0) {
			time_t start;
			t = time(&start);
			b--;
		}//刷新时间
		time_t end;
		time(&end);
		if (location_x < 320 && location_y < 240) {
			b = 1;
			if (end - t >= 3 && a > 0) {
				cout << "左上角\n";
				a--;
				flag = 1;
			}
		}
		else if (location_x > 320 && location_y < 240) {
			if (end - t >= 3 && a > 0) {
				printf("右上角\n");
				a--;
				b++;
				flag = 2;
			}
		}
		else if (location_x < 320 && location_y>240) {
			if (end - t >= 3 && a > 0) {
				printf("左下角\n");
				a--;
				b++;
				flag = 4;
			}
		}
		else if (location_x > 320 && location_y > 240) {
			if (end - t >= 3 && a > 0) {
				printf("右下角\n");
				a--;
				b++;
				flag = 3;
			}
		}
		return flag;
	}
	void countdowninst(Mat& frame, Mat& pic, Source& s2,int tag) {
		Rect roi(250, 170, 150, 150);
		Mat frame_roi = frame(roi);
		cv::resize(pic, pic, Size(150, 150));
		pic = pic(Range(0, 150), Range(0, 150));
		Mat grayPng;
		switch (tag) {
			case 1:
				grayPng = imread(s2.num1, 0);
				break;
			case 2:
				grayPng = imread(s2.num2, 0);
				break;
			case 3:
				grayPng = imread(s2.num3, 0);
				break;
		}
		threshold(grayPng, grayPng, 180, 255, CV_THRESH_BINARY);
		Mat mask = 255 - grayPng;
		resize(mask, mask, Size(150, 150));
		mask = mask(Range(0, 150), Range(0, 150));
		resize(pic, pic, Size(150, 150));
		pic = pic(Range(0, 150), Range(0, 150));

		Mat imROI;
		imROI = frame(roi);
		pic.copyTo(imROI, mask);
	}
	void countdown(Mat frame,int newGame) {     //游戏开始倒计时
		static int time_m = 1;
		static long ti1 = 0;  //获取时间
		static int a = newGame;
		if (newGame > a) {
			time_m = 1;
			ti1 = 0;
			a++;
		}
		Source s2;
		if (time_m > 0) {
			time_t start1 = 0;
			ti1 = time(&start1);
			time_m--;
		}
		time_t end1;
		time(&end1);

		Mat pic;
		if (end1 - ti1 >= 1 && end1 - ti1 <= 2) {
			pic = imread(s2.num3);
			countdowninst(frame, pic, s2, 3);
		}
		if (end1 - ti1 > 2 && end1 - ti1 <= 3) {
			pic = imread(s2.num2);
			countdowninst(frame, pic, s2, 2);
		}
		if (end1 - ti1 > 3 && end1 - ti1 <= 4) {
			pic = imread(s2.num1);
			countdowninst(frame, pic, s2, 1);
		}
	}
	void gameui(Mat frame) {
		Rect roi(0, 0, 640, 480);
		Mat frame_roi = frame(roi);
		Source s3;
		Mat pic = imread(s3.background);

		cv::resize(pic, pic, Size(640, 480));
		pic = pic(Range(0, 480), Range(0, 640));
		cv::addWeighted(frame_roi, 0.3, pic, 0.7, 1, frame_roi);  //调整透明度
	}
	void gamecount(Mat frame,int newGame) {     //时间计时器
		int  timing;
		String text;
		static long startlock;
		static int timelock = 1;
		static int a = newGame;
		if (newGame > a) {
			timelock = 1;
			a++;
		}
		if (timelock > 0) {
			time_t start;
			startlock = time(&start);
			timelock--;
		}
		time_t end;
		time(&end);
		timing = end - startlock;
		text = "gametime:" + to_string(timing);
		putText(frame, text, Point(230, 40), CV_FONT_HERSHEY_TRIPLEX, 1.0, Scalar(0, 255, 0), 1, CV_AA);

	}
};