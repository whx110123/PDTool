#include "iec103asdu29data.h"

IEC103Asdu29Data::IEC103Asdu29Data()
{
	fan = 0;
	_not = 0;
	tap = 0;
}

IEC103Asdu29Data::~IEC103Asdu29Data()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool IEC103Asdu29Data::handle(const QByteArray& buff)
{
	qDeleteAll(setlist);
	setlist.clear();
	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	_not = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t带标志的状态变位的数目NOT:" + QString::number(_not) + "\r\n");
	len++;

	tap = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t带标志的状态变位的位置TAP:" + QString::number(tap) + "\r\n");
	len += 2;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");

	for(int index = 0; index < _not; index++)
	{
		IEC103Asdu1Data *mset = new IEC103Asdu1Data;
		bool isOk = mset->init(buff.mid(len, 3));
		if(!isOk)
		{
			delete mset;
			mset = NULL;
			return false;
		}
		len += mset->len;
		setlist.append(mset);
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu29Data::showToText()
{
	QString text = mText;
	for(IEC103Asdu1Data *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103Asdu29Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
