#include "stdafx.h"

#pragma region Locals

void GetScreenResolution(int&, int&);
float CalculateDistance(cv::Point, cv::Point);

int mode = IDLE;
int H_MIN = 0;
int H_MAX = 255;
int S_MIN = 0;
int S_MAX = 255;
int V_MIN = 0;
int V_MAX = 255;
int kerode = 1;
int kdilate = 1;
int screenWidth = 0;
int ScreenHeight = 0;

bool showChangeFrame = true;
bool objectFound = false;

float tempX, tempY;

double refArea = 0;

cv::Point2f center;

std::vector<cv::Point> fingerTips;

INPUT ip;
Computer Mouse(ip, INPUT_MOUSE);

#pragma endregion

void GetScreenResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

int main()
{
	int key;

	//FreeConsole();
	Camera Cam1(0);
	Cam1.AdjustFrameValues();

	while ((key = cv::waitKey(30)) != 27)
	{
		Cam1.SendImage();
		if (kerode < 1)
			kerode = 1;
		if (kdilate < 1)
			kdilate = 1;
		Cam1.AdjustFrame();
		Cam1.Tracking(showChangeFrame);
		
		if (key == ' ')
			showChangeFrame = !showChangeFrame;

		Cam1.ShowImage(showChangeFrame);
		Cam1.ShowMessage(mode);
	}

	return 0;
}