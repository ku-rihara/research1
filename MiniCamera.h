#pragma once
#include"BaseMiniCamera.h"
class MiniCamera:public BaseMiniCamera{
public:

public:

	MiniCamera();
	~MiniCamera();
	void Init()override;
	void MakeCamelaMatrix()override;



};

