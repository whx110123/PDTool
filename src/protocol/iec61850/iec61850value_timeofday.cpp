#include "iec61850value_timeofday.h"

#include <QDateTime>

IEC61850Value_TimeOfDay::IEC61850Value_TimeOfDay(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_TimeOfDay::~IEC61850Value_TimeOfDay()
{

}

bool IEC61850Value_TimeOfDay::init(const QByteArray& buff)
{
	setDefault(buff);

	QTime time(0, 0);
	QDate date(1984, 1, 1);

	int length = buff.length();
	if(length == 4 || length == 6)
	{
		int ms = charToint(buff.data() + mLen, 4, 1);
		time = time.addMSecs(ms);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString::number(ms) + " 毫秒  UTC: " + time.toString("hh:mm:ss.zzz") + "\r\n");
		mLen += 4;
		if(length == 6)
		{
			qint64 day = charToint(buff.data() + mLen, 2, 1);
			date = date.addDays(day);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + QString::number(day) + " 天数  UTC: " + date.toString("yyyy-MM-dd") + "\r\n");
			mLen += 2;
		}
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！报文长度(%1)有问题").arg(length));
		return false;
	}
	mText.append("----------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}
