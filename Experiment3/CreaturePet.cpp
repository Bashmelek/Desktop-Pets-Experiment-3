

#include "stdafx.h"
#include "CreaturePet.h"


CreaturePet::CreaturePet()
{
	currentFrame = 0;
	frameCount = 9;
	frameStartX = currentFrame * 189;
	frameStartY = 0;
	frameWidth = 200;
	frameHeight = 200;
	imageBase = (HBITMAP)LoadImage(
		NULL,
		L"piplup5.bmp",////\\GameResources
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	);
	imageMask = (HBITMAP)LoadImage(
		NULL,
		L"piplup5mask.bmp",////\\GameResources
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	);
}


int CreaturePet::AdvanceFrame()
{
	currentFrame = (currentFrame + 1) % frameCount;
	frameStartX = currentFrame * 189;
	frameStartY = 0;
	frameWidth = 200;
	frameHeight = 200;

	return currentFrame;
}



