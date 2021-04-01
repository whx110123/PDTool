#include "mybase.h"

MyBase::MyBase(const MyConfig& Config): mConfig(Config)
{

}

MyBase::~MyBase()
{

}

bool MyBase::init(const QByteArray& buff)
{
	mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未进行解析");
	return false;
}

QString MyBase::showToText()
{
	return mText;
}

bool MyBase::createData(MyData& proData)
{
	mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未进行组包");
	return false;
}

void MyBase::setDefault(const QByteArray& buff)
{
	mRecvData = buff;
	mText.clear();
	mError.clear();
	len = 0;
}

QString MyBase::mError = QString();
QString MyBase::mTextS = QString();
