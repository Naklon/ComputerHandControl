#pragma once
class Computer
{
public:
	void MoveMouse();
	void LeftMouseButtonDown();
	void LeftMouseButtonUp();
	void RightMouseButton();
	void DoubleLeftMouseButton();

	Computer();
	Computer(INPUT,const int);
	~Computer();

private:
	INPUT ip;
};

