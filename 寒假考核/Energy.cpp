#include "Energy.h"
#include"struct_define.h"
#include<opencv2/opencv.hpp>

Energy::Energy() {
	_flow.BLUE_GRAY_THRESH = 100;//敌方红色时的阈值
	_flow.RED_GRAY_THRESH = 180;//敌方蓝色时的阈值

	_flow.armor_contour_area_max = 10000; //装甲板的相关筛选参数
	_flow.armor_contour_area_min = 300;
	_flow.armor_contour_length_max = 100;
	_flow.armor_contour_length_min = 10;
	_flow.armor_contour_width_max = 100;
	_flow.armor_contour_width_min = 0;
	_flow.armor_contour_hw_ratio_max = 2;
	_flow.armor_contour_hw_ratio_min = 1.3;

}

Energy::~Energy() {
    // 析构函数，用于清理资源
}

#include"Energy.h"

void Energy::ArmorDilate(cv::Mat& src)  // 此函数对图像进行腐蚀与膨胀操作
{
	Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));

	dilate(src, src, element_dilate_1);
	erode(src, src, element_erode_1);
}

