#include "iec61850value_boolean.h"

IEC61850Value_Boolean::IEC61850Value_Boolean(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_Boolean::~IEC61850Value_Boolean()
{

}

bool IEC61850Value_Boolean::init(const QByteArray& buff)
{
	setDefault(buff);

	data = *(buff.data() + mLen);
	QString ret = data ? "True " : "False";
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + ret + "\r\n");
	mLen++;

	mText.append("----------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}
