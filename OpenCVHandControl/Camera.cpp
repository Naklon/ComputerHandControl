#include "stdafx.h"

float x, y;

void Camera::SendImage()
{
	this->cam >> this->frame;
	cv::flip(this->frame,this->frame, 180);
}

void Camera::AdjustFrame()
{
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
	cv::inRange(hsvFrame, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), changeFrame);
	cv::erode(changeFrame, changeFrame, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kerode, kerode)));
	cv::dilate(changeFrame, changeFrame, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kdilate, kdilate)));
}

void Camera::Tracking(bool showChangeFrame)
{
	center.x = x;
	center.y = y;
	cv::Mat temp;
	changeFrame.copyTo(temp);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	int largestArea = 0;
	int contourIntex = 0;
	double refArea = 0;

	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Vec4i> >defects(contours.size());
	std::vector<std::vector<int> >inthull(contours.size());
	std::vector<std::vector<cv::Point> > hull(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		cv::convexHull(cv::Mat(contours[i]), hull[i], false);
		cv::convexHull(cv::Mat(contours[i]), inthull[i], false);
		cv::convexityDefects(contours[i], inthull[i], defects[i]);
	}

	for (int i = 0; i < contours.size(); i++)
	{
		double a = cv::contourArea(contours[i], false);
		if (a > largestArea)
		{
			largestArea = a;
			contourIntex = i;
		}
	}

	cv::Moments moment;

	if (contours.size() > 0)
	{
		moment = cv::moments((cv::Mat)contours[contourIntex]);
		center.x = moment.m10 / largestArea;
		center.y = moment.m01 / largestArea;
		cv::drawContours(frame, contours, contourIntex, CV_RGB(255, 0, 0), 2, 8, hierarchy);
		cv::drawContours(frame, hull, contourIntex, CV_RGB(0, 0, 255), 2, 8, hierarchy);
		this->FindFingerTips(defects[contourIntex], contours[contourIntex],showChangeFrame);
		circle(frame, center, 20, cv::Scalar(255, 0, 0), 2);
	}

	this->ShowMessage(mode);
}

void Camera::FindFingerTips(std::vector<cv::Vec4i> conDefects, std::vector<cv::Point> contour, bool showChangeFrame)
{
	int fingers = 0;
	std::vector<cv::Point> fingerTips;

	for (int i = 0; i < conDefects.size(); i++)
	{
		cv::Point ptStart(contour[(int)conDefects[i].val[0]]);

		double depth = static_cast<double>(conDefects[i].val[3]) / 256;

		if (depth>11 && -ptStart.y + center.y>50)
		{
			fingerTips.push_back(ptStart);
			circle(frame, ptStart, 6, CV_RGB(255, 0, 0), 4);
			fingers++;
		}
	}
	if (!showChangeFrame)
		Gestures::RecogniseGestures(fingerTips, center, frame);
	fingerTips.clear();
}

void Camera::ShowImage(bool showChangeFrame)
{
	if (showChangeFrame)
		imshow("Kamera", this->changeFrame);
	else
		imshow("Kamera", this->frame);
}

void Camera::AdjustFrameValues()
{
	std::string windowName = "HSV Setting";
	cv::namedWindow(windowName, cv::WINDOW_NORMAL);

	cv::createTrackbar("HUE_MIN", windowName, &H_MIN, H_MAX);
	cv::createTrackbar("HUE_MAX", windowName, &H_MAX, H_MAX);

	cv::createTrackbar("SAT_MIN", windowName, &S_MIN, S_MAX);
	cv::createTrackbar("SAT_MAX", windowName, &S_MIN, S_MAX);

	cv::createTrackbar("VAL_MIN", windowName, &V_MIN, V_MAX);
	cv::createTrackbar("VAL_MAX", windowName, &V_MIN, V_MAX);

	cv::createTrackbar("Erode", windowName, &kerode, 31);
	cv::createTrackbar("Dilate", windowName, &kdilate, 31);
}

void Camera::ShowMessage(int mode)
{
	switch (mode)
	{
	case IDLE:
		putText(this->frame, "IDLE", cv::Point(0, 30), 2, 1, cv::Scalar(255, 0, 0), 2);
		break;
	case MOUSEMOVE:
		putText(this->frame, "MouseButtons", cv::Point(0, 30), 2, 1, cv::Scalar(255, 0, 0), 2);
		break;
	}
}

Camera::Camera()
{
}

Camera::Camera(int param)
{
	this->cam = cv::VideoCapture(param);
}


Camera::~Camera()
{
}
