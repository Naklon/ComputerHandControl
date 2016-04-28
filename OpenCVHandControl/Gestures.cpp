#include "stdafx.h"

bool ifLMB = false,if2xLMB=false;
float leftDistance=1, rightDistance=1;

float CalculateDistance(cv::Point a, cv::Point b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Gestures::MouseButtons(std::vector<cv::Point> fingers, cv::Point2f &center, cv::Mat &frame)
{
	mode = MOUSEMOVE;
	int min = 0;
	bool button = false;

	Mouse.MoveMouse();
	cv::Point mouseCurrentPos(center.x, center.y);

	cv::Point leftFinger, rightFinger;

	if (fingers[0].x < fingers[1].x)
	{
		leftFinger = fingers[0];
		rightFinger = fingers[1];
	}
	else
	{
		leftFinger = fingers[1];
		rightFinger = fingers[0];
	}

	if (abs(CalculateDistance(leftFinger, center) - CalculateDistance(rightFinger, center)) < 8)
	{
		leftDistance = CalculateDistance(leftFinger, center);
		rightDistance = CalculateDistance(rightFinger, center);
	}

	if (CalculateDistance(leftFinger, center) / leftDistance < 0.85)
	{
		if (!ifLMB)
		{
			ifLMB = true;
			center = mouseCurrentPos;
			Mouse.LeftMouseButtonDown();
		}
	}
	else
	{
		if (ifLMB)
		{
			ifLMB = false;
			Mouse.LeftMouseButtonUp();
		}
	}

	if (CalculateDistance(rightFinger, center) / rightDistance < 0.85)
	{
		if (!button)
		{
			button = true;
			center = mouseCurrentPos;
			Mouse.RightMouseButton();
		}
	}
}

void Gestures::RecogniseGestures(std::vector<cv::Point> fingers, cv::Point2f &center, cv::Mat &frame)
{
	switch (fingers.size())
	{
	case 0:

		break;
	case 1:

		break;
	case 2:
		Gestures::MouseButtons(fingers, center, frame);
		break;
	default:
		Gestures::Idle();
		break;
	}
}

void Gestures::Idle()
{
	mode = IDLE;
	Mouse.MoveMouse();
}

Gestures::Gestures()
{
}

Gestures::~Gestures()
{
}
