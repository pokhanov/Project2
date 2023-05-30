#include "imageProcessing.h"

void imageProcessing::getImage() {

}

Mat imageProcessing::preProcessing(Mat &image) {
	//ת�����Ҷ�ͼ��ȥ�����
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(7, 7), 0, 0);

	//��Ե��ȡ
	Mat edges;
	Canny(gray, edges, 50, 200, 3, false);
	Rect rect1 = boundingRect(edges);

	//͸�ӱ任
	//��ȡ��һ���õ��ľ��ε��ĸ���
	Point2f src_points[4];
	int w = rect1.width;
	int h = rect1.height;
	src_points[0] = rect1.tl();	//��ȡ�������϶�������
	src_points[1] = src_points[0];
	src_points[1].x += w;	//��������϶�������
	src_points[2] = src_points[0];
	src_points[2].y += h;	//��������¶�������
	src_points[3] = rect1.br();	//��ȡ���¶�������

	//����͸�ӱ任���ĸ��ǵ�����꣬����ȡԭͼ���ĸ�����λ��
	Point2f dst_points[4];
	dst_points[0] = Point2f(0.0, 0.0);
	dst_points[1] = Point2f(image.size().width, 0.0);
	dst_points[2] = Point2f(0.0, image.size().height);
	dst_points[3] = Point2f(image.size().width, image.size().height);

	//͸�ӱ任
	Mat rotation, warped;
	//����任����
	rotation = getPerspectiveTransform(src_points, dst_points);
	//Ӧ�ñ任������ʵ��ROI�����͸�ӱ任
	warpPerspective(gray, warped, rotation, image.size());
	return warped;		//�õ���warpedͼ�������������ʶ��
}