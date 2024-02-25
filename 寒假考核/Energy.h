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

    void run(cv::Mat& src); // ��Ҫ���к���
    void showArmors(std::string windows_name, const cv::Mat& src); // ��ʾװ�װ�


    // ͼ������
    WindmillParamFlow _flow;
    int findArmors(const cv::Mat& src);
    bool isValidArmorContour(const vector<cv::Point>& armor_contour);
    void ArmorDilate(cv::Mat& src);
    void FlowStripFanDilate(cv::Mat& src);

    // ��Ա����
    std::vector<cv::RotatedRect> armors; // �洢ʶ���װ�װ�
    bool show_process = true; // �Ƿ���ʾ�������
    bool show_wrong = true;//�Ƿ���ʾ����
    std::vector<cv::RotatedRect> fans;//ͼ����������Ҷ
};

#endif // ENERGY_H
