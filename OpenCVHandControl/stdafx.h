// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define IDLE 0
#define MOUSEMOVE 1

#include "targetver.h"

#include <wtypes.h>
#include <stdio.h>
#include <tchar.h>
#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "Computer.h"
#include "Gestures.h"
#include "Camera.h"

#include <iostream>
#include <ctype.h>

#pragma region Globals

extern float CalculateDistance(cv::Point a, cv::Point b);

extern cv::Point2f center;

extern bool ifLMB;
extern bool if2xLMB;
extern int mode;
extern int H_MIN;
extern int H_MAX;
extern int S_MIN;
extern int S_MAX;
extern int V_MIN;
extern int V_MAX;
extern int kerode;
extern int kdilate;

extern Computer Mouse;

#pragma endregion
