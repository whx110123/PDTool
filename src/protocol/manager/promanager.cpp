#include "promanager.h"

ProManager::ProManager()
{
	init();
}

ProManager::~ProManager()
{
	sndDatas.clear();
}

void ProManager::init()
{
	isRun = false;
	handleRcvDataTimer = new QTimer(this);
	connect(handleRcvDataTimer, &QTimer::timeout, this, &ProManager::timerRcv);
	handleSndDataTimer = new QTimer(this);
	connect(handleSndDataTimer, &QTimer::timeout, this, &ProManager::timerSnd);

}

bool ProManager::start()
{
	return false;
}

bool ProManager::stop()
{
	handleRcvDataTimer->stop();
	handleSndDataTimer->stop();
	isRun = false;
	return true;
}

void ProManager::setProName(const QString& name)
{
	protocolName = name;
}

void ProManager::setMaster(bool Master)
{
	isMaster = Master;
}

void ProManager::setRcvData(const QByteArray& data)
{
	if(!isRun)
	{
		return;
	}
	rcvData = data;
}

void ProManager::addRcvData(const QByteArray& data)
{
	if(!isRun)
	{
		return;
	}
	rcvData.append(data);
}

void ProManager::addSndData(const QByteArray& data)
{
	if(!isRun)
	{
		return;
	}
	sndDatas.append(data);
}

void ProManager::clearData()
{
	if(!isRun)
	{
		return;
	}
	rcvData.clear();
}

void ProManager::timerRcv()
{

}

void ProManager::timerSnd()
{

}
