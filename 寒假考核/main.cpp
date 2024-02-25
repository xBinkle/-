#include "Energy.h"
#include <opencv2/opencv.hpp>

int main() {
    Energy energy;
    cv::Mat frame; // 用于存储每一帧图像或单张图片
    cv::Mat frameForDisplay; // 用于绘制和显示的帧或图片
    cv::VideoCapture cap; // 用于视频处理的VideoCapture对象

    // 尝试以视频方式打开输入
    bool isVideo = cap.open("wind.mp4"); // 视频

    // 检查是否成功打开了视频
    if (isVideo) {
        // 创建窗口显示结果
        cv::namedWindow("最终识别结果", cv::WINDOW_AUTOSIZE);

        while (true) {
            // 从VideoCapture对象中读取下一帧
            if (!cap.read(frame)) {
                std::cerr << "无法读取视频帧"<<endl;
                break; // 如果读取失败，退出循环
            }

            frameForDisplay = frame.clone(); // 在绘制前复制原始帧

            // 清除之前的装甲板数据，并在当前帧上进行识别
            energy.findArmors(frame); // 在原始帧上进行识别

            // 在复制的帧上进行绘制和显示，只显示当前帧的识别结果
            energy.showArmors("最终识别结果", frameForDisplay);

            // 等待1ms，检查是否有按键事件，如果按下'q'，则退出循环
            if (cv::waitKey(1) == 'q') {
                break;
            }
        }

        // 释放VideoCapture资源
        cap.release();
    }
    else {
        // 作为图片处理
        frame = cv::imread("wind5.jpg"); // 图片
        if (frame.empty()) {
            std::cerr << "错误：无法打开或找到图片" << std::endl;
            return -1;
        }

        frameForDisplay = frame.clone(); // 在绘制前复制原始图片

        // 清除之前的装甲板数据，并在图片上进行识别
        energy.findArmors(frame); // 在原始图片上进行识别

        // 在复制的图片上进行绘制和显示，显示图片的识别结果
        energy.showArmors("最终识别结果", frameForDisplay);

        // 等待按键事件，以便查看结果
        cv::waitKey(0);
    }

    // 销毁所有创建的窗口
    cv::destroyAllWindows();
    return 0;
}