#include "managerbase.h"

ManagerConfig::ManagerConfig()
{

}

ManagerConfig::~ManagerConfig()
{

}

ManagerBase::ManagerBase()
{
	init();
}

ManagerBase::~ManagerBase()
{
	sndDatas.clear();
}

void ManagerBase::init()
{
	isRun = false;
	handleRcvDataTimer = new QTimer(this);
	connect(handleRcvDataTimer, &QTimer::timeout, this, &ManagerBase::timerRcv);
	handleSndDataTimer = new QTimer(this);
	connect(handleSndDataTimer, &QTimer::timeout, this, &ManagerBase::timerSnd);

}

bool ManagerBase::start()
{
	handleRcvDataTimer->start(1000);
	handleSndDataTimer->start(200);
	isRun = true;
	return true;
}

bool ManagerBase::stop()
{
	handleRcvDataTimer->stop();
	handleSndDataTimer->stop();
	isRun = false;
	return true;
}

void ManagerBase::initConfig(ManagerConfig *config)
{
	protocolName = config->protocolName;
	isMaster = config->isMaster;
	initMyConfig(config);
}

void ManagerBase::initMyConfig(ManagerConfig *config)
{
	return;
}

void ManagerBase::setRcvData(const QByteArray& data)
{
	if(!isRun)
	{
		return;
	}
	rcvData = data;
}

void ManagerBase::addRcvData(const QByteArray& data)
{
	if(!isRun)
	{
		return;
	}
	rcvData.append(data);
}

void ManagerBase::addSndData(const QByteArray& data)
{
	if(!isRun)
	{
		return;
	}
	sndDatas.append(data);
}

void ManagerBase::clearData()
{
	if(!isRun)
	{
		return;
	}
	rcvData.clear();
}

void ManagerBase::timerRcv()
{

}

void ManagerBase::timerSnd()
{

}


