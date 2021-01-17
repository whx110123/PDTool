#include "iec103asdu37data.h"

IEC103Asdu37Data::IEC103Asdu37Data()
{

}

IEC103Asdu37Data::~IEC103Asdu37Data()
{

}

bool IEC103Asdu37Data::handle(const QByteArray& buff)
{
	intdata = charToint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t计数器读数:" + QString::number(intdata) + "   对应INF:" + QString::number(inf) + "\r\n");
	len += 4;

	bcr = *(buff.data() + len);
	uchar sq = bcr & 0x1f;
	mText.append(CharToHexStr(buff.data() + len) + "\t顺序号SQ(bit1-5):" + QString::number(sq) + "\r\n\t" + cyToText(bcr) + "\r\n\t" + caToText(bcr) + "\r\n\t" + ivToText(bcr)  + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu37Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
