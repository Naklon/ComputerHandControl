#pragma once
class Gestures
{
public:
	static void MouseButtons(std::vector < cv::Point>,cv::Point2f&,cv::Mat&);
	static void RecogniseGestures(std::vector < cv::Point>, cv::Point2f&, cv::Mat&);
	static void Idle();

	Gestures();
	~Gestures();
};