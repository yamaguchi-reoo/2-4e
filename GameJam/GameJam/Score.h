#pragma once
#include"Apple.h"

class Score :public Apple
{
private:

	int gScore;
	int gAppleImg[2];
	int gAppleCount[2];

public:
	Score();
	~Score();

	void UpDate();

	void Draw() const;
};