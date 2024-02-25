#pragma once
#ifndef STRUCT_DEFINE_H
#define STRUCT_DEFINE_H
#include<opencv2/opencv.hpp>
#include<iostream>

struct WindmillParamFlow 
{
	int RED_GRAY_THRESH;//�з���ɫʱ����ֵ
	int BLUE_GRAY_THRESH;//�з���ɫʱ����ֵ
	float armor_contour_area_max;//װ�װ�����ɸѡ����
	float armor_contour_area_min;
	float armor_contour_length_max;
	float armor_contour_length_min;
	float armor_contour_width_max;
	float armor_contour_width_min;
	float armor_contour_hw_ratio_max;
	float armor_contour_hw_ratio_min;

};













#endif
