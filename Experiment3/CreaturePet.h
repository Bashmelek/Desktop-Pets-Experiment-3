#pragma once




#ifndef CREATUREPETDEF
#define CREATUREPETDEF

class CreaturePet
{
	public:
		HBITMAP imageBase;
		HBITMAP imageMask;
		int currentFrame;
		int frameCount;
		int frameStartX;
		int frameStartY;
		int frameWidth;
		int frameHeight;

		CreaturePet();
		int AdvanceFrame();
};



#endif CREATUREPETDEF
