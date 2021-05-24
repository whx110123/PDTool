#include "iec61850value_utf8string.h"

IEC61850Value_UTF8String::IEC61850Value_UTF8String(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_UTF8String::~IEC61850Value_UTF8String()
{

}

bool IEC61850Value_UTF8String::init(const QByteArray& buff)
{
	setDefault(buff);

	int length = buff.length();
	str = buff;
	if(length > 4)
	{
		mText.append(CharToHexStr(buff.data() + mLen, length) + "\r\n\t" + str + "\r\n");
	}
	else
	{
		mText.append(CharToHexStr(buff.data() + mLen, length) + "\t" + str + "\r\n");
	}
	mLen += length;
	mText.append("----------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}
