#include "mybase.h"

MyBase::MyBase()
{
	setDefault(NULL);
	masterState = STATE_NORMAL;
	slaveState = STATE_NORMAL;
	index = 0;
}

MyBase::~MyBase()
{

}

bool MyBase::init(const QByteArray& buff)
{
	return false;
}

QString MyBase::showToText()
{
	return mText;
}

bool MyBase::createData(IECDataConfig& config)
{
	return false;
}

void MyBase::setDefault(const QByteArray& buff)
{
	mRecvData = buff;
	mText.clear();
	error.clear();
	len = 0;
}
QString MyBase::error = QString();
MyConfig MyBase::mConfig = MyConfig();
