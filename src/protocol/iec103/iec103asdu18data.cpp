#include "iec103asdu18data.h"

HisInfo::HisInfo()
{

}

HisInfo::~HisInfo()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool HisInfo::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(setlist);
	setlist.clear();

	eventType = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + eventTypeToText(eventType) + "\r\n");
	len++;

	fun = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t功能类型FUN:" + QString::number(fun) + "\r\n");
	len++;
	inf = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t信息序号INF:" + QString::number(inf) + "\r\n");
	len++;

	dpi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(dpi) + "\r\n");
	len++;
	ret = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t相对时间RET:" + QString::number(ret));
	mText.append("   秒:" + QString::number(ret / 1000) + "   毫秒:" + QString::number(ret % 1000) + " \r\n");
	len += 2;
	fan = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN :" + QString::number(fan) + "\r\n");
	len += 2;

	dt = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	rcvdt = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	eventNum = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t故障量个数:" + QString::number(eventNum) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < eventNum; index++)
	{
		IEC103Asdu10DataSet *mset = new IEC103Asdu10DataSet;
		bool isOk = mset->init(buff.mid(len));
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

QString HisInfo::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}


IEC103Asdu18Data::IEC103Asdu18Data()
{

}

IEC103Asdu18Data::~IEC103Asdu18Data()
{
	qDeleteAll(hisInfos);
	hisInfos.clear();
}

bool IEC103Asdu18Data::handle(const QByteArray& buff)
{
	qDeleteAll(hisInfos);
	hisInfos.clear();

	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	isLast = *(buff.data() + len) & 0x01;
	mText.append(CharToHexStr(buff.data() + len) + "\t后续位标志: " + QString(isLast ? "1 有后续帧" : "0 最后的帧") + "\r\n");
	len++;

	dtBegin = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	dtEnd = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	hisNum = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t历史信息条数: " + QString::number(hisNum) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < hisNum; index++)
	{
		HisInfo *minfo = new HisInfo;
		bool isOk = minfo->init(buff.mid(len));
		if(!isOk)
		{
			delete minfo;
			minfo = NULL;
			return false;
		}
		len += minfo->len;
		hisInfos.append(minfo);
	}

	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu18Data::showToText()
{
	QString text = mText;
	for(HisInfo *info : hisInfos)
	{
		text.append(info->showToText());
	}
	return text;
}


