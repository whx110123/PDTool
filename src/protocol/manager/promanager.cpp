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
	handleRcvDataTimer = new QTimer(this);
	connect(handleRcvDataTimer, &QTimer::timeout, this, &ProManager::timerRcv);
	handleRcvDataTimer->start(1000);

	handleSndDataTimer = new QTimer(this);
	connect(handleSndDataTimer, &QTimer::timeout, this, &ProManager::timerSnd);
	handleSndDataTimer->start(200);
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
	rcvData = data;
}

void ProManager::addRcvData(const QByteArray& data)
{
	rcvData.append(data);
}

void ProManager::addSndData(const QByteArray& data)
{
	sndDatas.append(data);
}

void ProManager::clearData()
{
	rcvData.clear();
}

void ProManager::timerRcv()
{

}

void ProManager::timerSnd()
{

}
