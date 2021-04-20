#include "iec104asdu58data.h"

IEC104Asdu58Data::IEC104Asdu58Data(const MyConfig& Config): IEC101Asdu45Data(Config)
{

}

IEC104Asdu58Data::~IEC104Asdu58Data()
{

}

bool IEC104Asdu58Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	sco = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText_iec101(sco) + "\r\n");
	mLen++;

	datetime = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC104Asdu58Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(tmp.sqFlag == SQ_INF)
	{
		tmp.data += uintToBa(infaddr, mConfig.infaddrlen);
	}
	tmp.data += sco;
	tmp.data += dateTimeToBa(datetime, 7);
	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}
