#include "Energy.h"
#include <opencv2/opencv.hpp>

int main() {
    Energy energy;
    cv::Mat frame; // ���ڴ洢ÿһ֡ͼ�����ͼƬ
    cv::Mat frameForDisplay; // ���ڻ��ƺ���ʾ��֡��ͼƬ
    cv::VideoCapture cap; // ������Ƶ�����VideoCapture����

    // ��������Ƶ��ʽ������
    bool isVideo = cap.open("wind.mp4"); // ��Ƶ

    // ����Ƿ�ɹ�������Ƶ
    if (isVideo) {
        // ����������ʾ���
        cv::namedWindow("����ʶ����", cv::WINDOW_AUTOSIZE);

        while (true) {
            // ��VideoCapture�����ж�ȡ��һ֡
            if (!cap.read(frame)) {
                std::cerr << "�޷���ȡ��Ƶ֡"<<endl;
                break; // �����ȡʧ�ܣ��˳�ѭ��
            }

            frameForDisplay = frame.clone(); // �ڻ���ǰ����ԭʼ֡

            // ���֮ǰ��װ�װ����ݣ����ڵ�ǰ֡�Ͻ���ʶ��
            energy.findArmors(frame); // ��ԭʼ֡�Ͻ���ʶ��

            // �ڸ��Ƶ�֡�Ͻ��л��ƺ���ʾ��ֻ��ʾ��ǰ֡��ʶ����
            energy.showArmors("����ʶ����", frameForDisplay);

            // �ȴ�1ms������Ƿ��а����¼����������'q'�����˳�ѭ��
            if (cv::waitKey(1) == 'q') {
                break;
            }
        }

        // �ͷ�VideoCapture��Դ
        cap.release();
    }
    else {
        // ��ΪͼƬ����
        frame = cv::imread("wind5.jpg"); // ͼƬ
        if (frame.empty()) {
            std::cerr << "�����޷��򿪻��ҵ�ͼƬ" << std::endl;
            return -1;
        }

        frameForDisplay = frame.clone(); // �ڻ���ǰ����ԭʼͼƬ

        // ���֮ǰ��װ�װ����ݣ�����ͼƬ�Ͻ���ʶ��
        energy.findArmors(frame); // ��ԭʼͼƬ�Ͻ���ʶ��

        // �ڸ��Ƶ�ͼƬ�Ͻ��л��ƺ���ʾ����ʾͼƬ��ʶ����
        energy.showArmors("����ʶ����", frameForDisplay);

        // �ȴ������¼����Ա�鿴���
        cv::waitKey(0);
    }

    // �������д����Ĵ���
    cv::destroyAllWindows();
    return 0;
}