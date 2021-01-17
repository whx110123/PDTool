#include "iec101asdu16data.h"

IEC101Asdu16Data::IEC101Asdu16Data()
{

}

IEC101Asdu16Data::~IEC101Asdu16Data()
{

}

bool IEC101Asdu16Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	intdata = charToint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t整数:" + QString::number(intdata) + "\r\n");
	len += 4;

	bcr = *(buff.data() + len);
	uchar sq = bcr & 0x1f;
	mText.append(CharToHexStr(buff.data() + len) + "\t顺序号SQ(bit1-5):" + QString::number(sq) + "\r\n\t" + cyToText(bcr) + "\r\n\t" + caToText(bcr) + "\r\n\t" + ivToText(bcr)  + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 3, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 3));
	len += 3;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu16Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
