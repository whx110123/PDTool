#include "iec61850value_utctime.h"

IEC61850Value_UtcTime::IEC61850Value_UtcTime(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_UtcTime::~IEC61850Value_UtcTime()
{

}

bool IEC61850Value_UtcTime::init(const QByteArray& buff)
{
	setDefault(buff);

	QDateTime dt;
	int length = buff.length();
	if(length == 8)
	{
		qint64 s = charTouint(buff.data() + mLen, 4, 1);
		dt.setSecsSinceEpoch(s);
		dt = dt.toTimeSpec(Qt::UTC);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString::number(s) + " 秒  UTC: " + dt.toString("yyyy-MM-dd hh:mm:ss") + "\r\n");
		mLen += 4;
		float ms = charTouint(buff.data() + mLen, 4, 1) / (float)(0x100000000);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString::number(ms) + " 毫秒\r\n");
		mLen += 4;
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
