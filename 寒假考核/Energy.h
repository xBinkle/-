#pragma once
#ifndef ENERGY_H
#define ENERGY_H

#include<iostream>
#include<opencv2/opencv.hpp>
#include"struct_define.h"

using namespace std;
using namespace cv;

class Energy {
public:
    Energy();
    ~Energy();

    void run(cv::Mat& src); // 主要运行函数
    void showArmors(std::string windows_name, const cv::Mat& src); // 显示装甲板


    // 图像处理函数
    WindmillParamFlow _flow;
    int findArmors(const cv::Mat& src);
    bool isValidArmorContour(const vector<cv::Point>& armor_contour);
    void ArmorDilate(cv::Mat& src);
    void FlowStripFanDilate(cv::Mat& src);

    // 成员变量
    std::vector<cv::RotatedRect> armors; // 存储识别的装甲板
    bool show_process = true; // 是否显示处理过程
    bool show_wrong = true;//是否显示报错
    std::vector<cv::RotatedRect> fans;//图像中所有扇叶
};

#endif // ENERGY_H
