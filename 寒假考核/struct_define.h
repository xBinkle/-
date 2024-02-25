#pragma once
#ifndef STRUCT_DEFINE_H
#define STRUCT_DEFINE_H
#include<opencv2/opencv.hpp>
#include<iostream>

struct WindmillParamFlow 
{
	int RED_GRAY_THRESH;//敌方红色时的阈值
	int BLUE_GRAY_THRESH;//敌方蓝色时的阈值
	float armor_contour_area_max;//装甲板的相关筛选参数
	float armor_contour_area_min;
	float armor_contour_length_max;
	float armor_contour_length_min;
	float armor_contour_width_max;
	float armor_contour_width_min;
	float armor_contour_hw_ratio_max;
	float armor_contour_hw_ratio_min;

};













#endif
