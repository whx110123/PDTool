﻿#include "iec103asdu29data.h"

IEC103Asdu29Data::IEC103Asdu29Data(const MyConfig& Config): IEC103AsduData(Config)
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
	fan = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	mLen += 2;

	_not = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t带标志的状态变位的数目NOT:" + QString::number(_not) + "\r\n");
	mLen++;

	tap = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t带标志的状态变位的位置TAP:" + QString::number(tap) + "\r\n");
	mLen += 2;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");

	for(int index = 0; index < _not; index++)
	{
		IEC103Asdu1Data *mset = new IEC103Asdu1Data(mConfig);
		setlist.append(mset);
		mset->mIndex = index;
		bool isOk = mset->init(buff.mid(mLen, 3));
		mText.append(mset->showToText());
		if(!isOk)
		{
			return false;
		}
		mLen += mset->mLen;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


