#include "iec101asdu15data.h"

IEC101Asdu15Data::IEC101Asdu15Data(const MyConfig& Config): IEC101AsduData(Config)
{
	intdata = 0;
	bcr = 0;
}

IEC101Asdu15Data::~IEC101Asdu15Data()
{

}

bool IEC101Asdu15Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	intdata = charToint(buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t整数:" + QString::number(intdata) + "\r\n");
	mLen += 4;

	bcr = *(buff.data() + mLen);
	uchar sq = bcr & 0x1f;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t顺序号SQ(bit1-5):" + QString::number(sq) + "\r\n\t" + cyToText(bcr) + "\r\n\t" + caToText(bcr) + "\r\n\t" + ivToText(bcr)  + "\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


