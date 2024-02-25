#include"Energy.h"

int Energy::findArmors(const cv::Mat& src)  //此函数用于寻找大风车装甲板模块
{
	armors.clear(); // 清空前一帧的装甲板数据
	if (src.empty()) {
		if (show_wrong) cout << "empty!" << endl;
		return 0;
	}
	static Mat dst;
	dst = src.clone();
	if (src.type() == CV_8UC3)
	{
		cvtColor(dst, dst, cv::COLOR_BGR2GRAY);//若读取三通道视频文件，需转换为单通道,覆盖了图像dst
	}
	std::vector<vector<Point> > armor_contours;
	std::vector<vector<Point> > armor_contours_external;//用总轮廓减去外轮廓，只保留内轮廓，除去流动条的影响。

	double thresholdValue = 85; // 阈值，可以根据需要调整
	double maxValue = 255; // 二值化后的最大值
	cv::threshold(dst, dst, thresholdValue, maxValue, cv::THRESH_BINARY);
	ArmorDilate(dst);//图像膨胀，防止图像断开并更方便寻找
	if (show_process) imshow("Armorstuct", dst);
	findContours(dst, armor_contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	findContours(dst, armor_contours_external, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	for (int i = 0; i < armor_contours_external.size(); i++)//去除外轮廓
	{
		int external_contour_size = armor_contours_external[i].size();
		for (int j = 0; j < armor_contours.size(); j++) {
			int all_size = armor_contours[j].size();
			if (external_contour_size == all_size) {
				swap(armor_contours[j], armor_contours[armor_contours.size() - 1]);
				armor_contours.pop_back();//清除掉流动条
				break;
			}
		}

	}
	for (auto armor_contour : armor_contours)
	{
		if (!isValidArmorContour(armor_contour)) {
			continue;
		}
		armors.emplace_back(cv::minAreaRect(armor_contour));//回传所有装甲板到armors容器中
	}
	return static_cast<int>(armors.size());
}


bool Energy::isValidArmorContour(const vector<cv::Point>& armor_contour)// 此函数用于判断找到的装甲板尺寸是否合格
{
	double cur_contour_area = contourArea(armor_contour);
	if (cur_contour_area > _flow.armor_contour_area_max ||
		cur_contour_area < _flow.armor_contour_area_min) {
		return false;
	}
	RotatedRect cur_rect = minAreaRect(armor_contour);
	Size2f cur_size = cur_rect.size;
	float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
	float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
	if (length < _flow.armor_contour_length_min || width < _flow.armor_contour_width_min ||
		length >  _flow.armor_contour_length_max || width > _flow.armor_contour_width_max) {
		return false;
	}
	float length_width_ratio = length / width;
	if (length_width_ratio > _flow.armor_contour_hw_ratio_max ||
		length_width_ratio < _flow.armor_contour_hw_ratio_min) {
		return false;
	}
	return true;
}

void Energy::showArmors(std::string windows_name, const cv::Mat& src) // 此函数用于显示图像中所有装甲板
{
	if (src.empty()) return;
	static Mat image2show;

	if (src.type() == CV_8UC1) { // 黑白图像
		cvtColor(src, image2show, cv::COLOR_GRAY2BGR);
	}
	else if (src.type() == CV_8UC3) { // RGB 彩色
		image2show = src.clone();
	}
	for (const auto& armor : armors) {
		Point2f vertices[4]; // 定义矩形的4个顶点
		armor.points(vertices); // 计算矩形的4个顶点
		for (int i = 0; i < 4; i++) {
			line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2); // 绘制装甲板
		}

		// 绘制中心点
		Point2f center = armor.center;
		circle(image2show, center, 3, Scalar(0, 255, 0), -1); // 中心点用绿色表示

		// 显示中心点坐标
		string centerText = "C: (" + to_string(int(center.x)) + ", " + to_string(int(center.y)) + ")";
		putText(image2show, centerText, Point(center.x + 10, center.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);

		// 显示四个顶点
		for (int i = 0; i < 4; i++) {
			string vertexText = "(" + to_string(int(vertices[i].x)) + ", " + to_string(int(vertices[i].y)) + ")";
			putText(image2show, vertexText, vertices[i] + Point2f(5.f, 5.f * (i + 1)), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(100, 100, 255), 1);
		}
	}
	imshow(windows_name, image2show);
}