﻿#include "iec103asdu39data.h"

IEC103Asdu39Data::IEC103Asdu39Data()
{

}

IEC103Asdu39Data::~IEC103Asdu39Data()
{

}

bool IEC103Asdu39Data::handle(const QByteArray& buff)
{
	vti = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + vtiToText_iec103(vti)  + "\r\n");
	len++;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
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


