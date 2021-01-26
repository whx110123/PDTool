#include "promanager.h"

ProManager::ProManager()
{

}

void ProManager::setProName(const QString& name)
{
	protocolName = name;
}

void ProManager::setMaster(bool Master)
{
	isMaster = Master;
}

void ProManager::setData(const QByteArray& data)
{
	dataAll = data;
}

void ProManager::addData(const QByteArray& data)
{
	dataAll.append(data);
}

void ProManager::clearData()
{
	dataAll.clear();
}
