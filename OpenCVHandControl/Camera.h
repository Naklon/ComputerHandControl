#pragma once
class Camera
{
public:
	void SendImage();
	void AdjustFrame();
	void Tracking(bool);
	void FindFingerTips(std::vector<cv::Vec4i>, std::vector<cv::Point>,bool);
	void ShowImage(bool);
	void AdjustFrameValues();
	void ShowMessage(int);

	Camera();
	Camera(int);
	~Camera();

private:
	cv::VideoCapture cam;
	cv::Mat frame, hsvFrame, changeFrame;
};

