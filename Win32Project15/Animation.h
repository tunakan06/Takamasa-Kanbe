#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "TextParam.h"
#include "BinaryFile.h"
#include "Sound.h"

class Animation {

	TextParam*	mTextParam;
	BinaryFile* mBinFile;
	Sound*		mSound;

public:



	Animation();

	~Animation();

	};

#endif
