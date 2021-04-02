#include "iec101asdu100data.h"

IEC101Asdu100Data::IEC101Asdu100Data(const MyConfig& Config): IEC101AsduData(Config)
{
	qoi = 0;
	infaddr = 0;
}

IEC101Asdu100Data::~IEC101Asdu100Data()
{

}

bool IEC101Asdu100Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	qoi = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + qoiToText(qoi) + "\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu100Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(tmp.sqFlag == SQ_INF)
	{
		tmp.data += uintToBa(infaddr, mConfig.infaddrlen);
	}
	tmp.data += qoi;

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}

	return true;
}
