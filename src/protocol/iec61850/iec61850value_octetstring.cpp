#include "iec61850value_octetstring.h"

IEC61850Value_OctetString::IEC61850Value_OctetString(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_OctetString::~IEC61850Value_OctetString()
{

}

bool IEC61850Value_OctetString::init(const QByteArray& buff)
{
	setDefault(buff);

	int length = buff.length();
	mText.append(CharToHexStr(buff.data() + mLen, length) + "\t八位组串，字节流\r\n");
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
