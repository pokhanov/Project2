#include "imageProcessing.h"

void imageProcessing::getImage() {

}

Mat imageProcessing::preProcessing(Mat &image) {
	//转换出灰度图像并去除噪点
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(7, 7), 0, 0);

	//边缘提取
	Mat edges;
	Canny(gray, edges, 50, 200, 3, false);
	Rect rect1 = boundingRect(edges);

	//透视变换
	//获取上一步得到的矩形的四个点
	Point2f src_points[4];
	int w = rect1.width;
	int h = rect1.height;
	src_points[0] = rect1.tl();	//获取矩形左上顶点坐标
	src_points[1] = src_points[0];
	src_points[1].x += w;	//计算出右上顶点坐标
	src_points[2] = src_points[0];
	src_points[2].y += h;	//计算出左下顶点坐标
	src_points[3] = rect1.br();	//获取右下顶点坐标

	//期望透视变换后四个角点的坐标，这里取原图的四个顶点位置
	Point2f dst_points[4];
	dst_points[0] = Point2f(0.0, 0.0);
	dst_points[1] = Point2f(image.size().width, 0.0);
	dst_points[2] = Point2f(0.0, image.size().height);
	dst_points[3] = Point2f(image.size().width, image.size().height);

	//透视变换
	Mat rotation, warped;
	//计算变换矩阵
	rotation = getPerspectiveTransform(src_points, dst_points);
	//应用变换矩阵来实现ROI区域的透视变换
	warpPerspective(gray, warped, rotation, image.size());
	return warped;		//得到的warped图像可以用于文字识别
}