#pragma once
#include"BaseObj.h"
class BaseMapchip:public BaseObj{

public:
	BaseMapchip();
	~BaseMapchip();
	void Init()override;
	virtual void RenderingPipeline()override;
};

