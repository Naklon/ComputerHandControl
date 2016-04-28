#include "stdafx.h"

void Computer::MoveMouse()
{
	SetCursorPos(3000 / 400 * (center.x - 100), 1900 / 200 * (center.y - 200));
}

void Computer::LeftMouseButtonDown()
{
	ZeroMemory(&this->ip, sizeof(INPUT));
	this->ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &this->ip, sizeof(INPUT));
}

void Computer::LeftMouseButtonUp()
{
	ZeroMemory(&this->ip, sizeof(INPUT));
	this->ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &this->ip, sizeof(INPUT));
	ZeroMemory(&this->ip, sizeof(INPUT));
}

void Computer::RightMouseButton()
{
	ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &ip, sizeof(INPUT));
	ZeroMemory(&ip, sizeof(INPUT));
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &ip, sizeof(INPUT));
	ZeroMemory(&ip, sizeof(INPUT));
}

void Computer::DoubleLeftMouseButton()
{
	ZeroMemory(&this->ip, sizeof(INPUT));
	this->ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &this->ip, sizeof(INPUT));
	ZeroMemory(&this->ip, sizeof(INPUT));
	this->ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &this->ip, sizeof(INPUT));
	ZeroMemory(&this->ip, sizeof(INPUT));

	this->ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &this->ip, sizeof(INPUT));
	ZeroMemory(&this->ip, sizeof(INPUT));
	this->ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &this->ip, sizeof(INPUT));
	ZeroMemory(&this->ip, sizeof(INPUT));
}

Computer::Computer()
{
}

Computer::Computer(INPUT ip, const int type)
{
	this->ip = ip;
	this->ip.type = type;
}

Computer::~Computer()
{
}
