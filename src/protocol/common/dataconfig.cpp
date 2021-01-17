#include "dataconfig.h"

IECDataConfig::IECDataConfig()
{
	masterState = 0;				//状态
	isMaster = false;			//是否为主站
	asdutype = 0;
	cot = 0;
	vsq = 1;
	isfirst = true;
	iec103config = NULL;
}

IECDataConfig::~IECDataConfig()
{
	if(iec103config)
	{
		delete iec103config;
		iec103config = NULL;
	}
}
