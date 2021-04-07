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
	QMutexLocker locker(&mutexSD);
	sndDatas.clear();
}

void ManagerBase::init()
{
	isRun = false;
	handleRcvDataTimer = new QTimer(this);
	connect(handleRcvDataTimer, &QTimer::timeout, this, &ManagerBase::timerRcv);
	connect(this, &ManagerBase::handleData, this, &ManagerBase::timerRcv);
	handleSndDataTimer = new QTimer(this);
	connect(handleSndDataTimer, &QTimer::timeout, this, &ManagerBase::timerSnd);

}

bool ManagerBase::start()
{
	restoreDefaults();
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

void ManagerBase::restoreDefaults()
{

}

void ManagerBase::addRcvData(const QByteArray& data)
{
	if(!isRun || data.isEmpty())
	{
		return;
	}
	mutexRD.lock();
	rcvData.append(data);
	mutexRD.unlock();
	emit handleData();
}

void ManagerBase::addSndData(const QByteArray& data)
{
	if(!isRun || data.isEmpty())
	{
		return;
	}
	QMutexLocker locker(&mutexSD);
	sndDatas.append(data);
}

void ManagerBase::clearData()
{
	if(!isRun)
	{
		return;
	}
	QMutexLocker locker(&mutexRD);
	rcvData.clear();
}

void ManagerBase::timerRcv()
{

}

void ManagerBase::timerSnd()
{

}


