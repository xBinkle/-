#include"Energy.h"

int Energy::findArmors(const cv::Mat& src)  //�˺�������Ѱ�Ҵ�糵װ�װ�ģ��
{
	armors.clear(); // ���ǰһ֡��װ�װ�����
	if (src.empty()) {
		if (show_wrong) cout << "empty!" << endl;
		return 0;
	}
	static Mat dst;
	dst = src.clone();
	if (src.type() == CV_8UC3)
	{
		cvtColor(dst, dst, cv::COLOR_BGR2GRAY);//����ȡ��ͨ����Ƶ�ļ�����ת��Ϊ��ͨ��,������ͼ��dst
	}
	std::vector<vector<Point> > armor_contours;
	std::vector<vector<Point> > armor_contours_external;//����������ȥ��������ֻ��������������ȥ��������Ӱ�졣

	double thresholdValue = 85; // ��ֵ�����Ը�����Ҫ����
	double maxValue = 255; // ��ֵ��������ֵ
	cv::threshold(dst, dst, thresholdValue, maxValue, cv::THRESH_BINARY);
	ArmorDilate(dst);//ͼ�����ͣ���ֹͼ��Ͽ���������Ѱ��
	if (show_process) imshow("Armorstuct", dst);
	findContours(dst, armor_contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	findContours(dst, armor_contours_external, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	for (int i = 0; i < armor_contours_external.size(); i++)//ȥ��������
	{
		int external_contour_size = armor_contours_external[i].size();
		for (int j = 0; j < armor_contours.size(); j++) {
			int all_size = armor_contours[j].size();
			if (external_contour_size == all_size) {
				swap(armor_contours[j], armor_contours[armor_contours.size() - 1]);
				armor_contours.pop_back();//�����������
				break;
			}
		}

	}
	for (auto armor_contour : armor_contours)
	{
		if (!isValidArmorContour(armor_contour)) {
			continue;
		}
		armors.emplace_back(cv::minAreaRect(armor_contour));//�ش�����װ�װ嵽armors������
	}
	return static_cast<int>(armors.size());
}


bool Energy::isValidArmorContour(const vector<cv::Point>& armor_contour)// �˺��������ж��ҵ���װ�װ�ߴ��Ƿ�ϸ�
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

void Energy::showArmors(std::string windows_name, const cv::Mat& src) // �˺���������ʾͼ��������װ�װ�
{
	if (src.empty()) return;
	static Mat image2show;

	if (src.type() == CV_8UC1) { // �ڰ�ͼ��
		cvtColor(src, image2show, cv::COLOR_GRAY2BGR);
	}
	else if (src.type() == CV_8UC3) { // RGB ��ɫ
		image2show = src.clone();
	}
	for (const auto& armor : armors) {
		Point2f vertices[4]; // ������ε�4������
		armor.points(vertices); // ������ε�4������
		for (int i = 0; i < 4; i++) {
			line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2); // ����װ�װ�
		}

		// �������ĵ�
		Point2f center = armor.center;
		circle(image2show, center, 3, Scalar(0, 255, 0), -1); // ���ĵ�����ɫ��ʾ

		// ��ʾ���ĵ�����
		string centerText = "C: (" + to_string(int(center.x)) + ", " + to_string(int(center.y)) + ")";
		putText(image2show, centerText, Point(center.x + 10, center.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);

		// ��ʾ�ĸ�����
		for (int i = 0; i < 4; i++) {
			string vertexText = "(" + to_string(int(vertices[i].x)) + ", " + to_string(int(vertices[i].y)) + ")";
			putText(image2show, vertexText, vertices[i] + Point2f(5.f, 5.f * (i + 1)), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(100, 100, 255), 1);
		}
	}
	imshow(windows_name, image2show);
}