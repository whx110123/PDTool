#include "manageriec104master.h"
#include "QtDebug"

ManagerIEC104Master::ManagerIEC104Master()
{

}

ManagerIEC104Master::~ManagerIEC104Master()
{

}

void ManagerIEC104Master::timerRcv()
{
	qDebug() << "111";
}

void ManagerIEC104Master::timerSnd()
{
	qDebug() << "222";
}
