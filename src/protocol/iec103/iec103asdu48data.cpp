#include "iec103asdu48data.h"

IEC103Asdu48Data::IEC103Asdu48Data(const MyConfig& Config): IEC103AsduData(Config)
{
	dataFloat = 0;
	qds = 0;
}

IEC103Asdu48Data::~IEC103Asdu48Data()
{

}

bool IEC103Asdu48Data::handle(const QByteArray& buff)
{

	dataFloat = bcdTouint(buff.data() + len, 3) / 100.0;
	mText.append(CharToHexStr(buff.data() + len, 3) + "\tBCD码:水位(bit1-24): " + QString::number(dataFloat) + "\r\n");
	len += 3;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


