#include "iec103asdu18data.h"

HisInfo::HisInfo(const MyConfig& Config): MyBase(Config)
{
	devaddr = 0;
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

	if(mConfig.protocolName == IEC_103HUABEI)
	{
		devaddr = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t装置地址:" + QString::number(devaddr) + "\r\n");
		mLen++;
	}

	eventType = *(buff.data() + mLen);
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + eventTypeToText_nw(eventType) + "\r\n");
	}
	else
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + eventTypeToText(eventType) + "\r\n");
	}
	mLen++;

	fun = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t功能类型FUN:" + QString::number(fun) + "\r\n");
	mLen++;
	inf = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t信息序号INF:" + QString::number(inf) + "\r\n");
	mLen++;

	dpi = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dpiToText(dpi) + "\r\n");
	mLen++;
	ret = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t相对时间RET:" + QString::number(ret));
	mText.append("   秒:" + QString::number(ret / 1000) + "   毫秒:" + QString::number(ret % 1000) + " \r\n");
	mLen += 2;
	fan = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t故障序号FAN :" + QString::number(fan) + "\r\n");
	mLen += 2;

	if(mConfig.protocolName == IEC_103HUABEI)
	{
		scl = charTofloat(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t短路位置SCL: " + QString::number(scl) + "\r\n");
		mLen += 4;

		fpt = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + fptToText(fpt) + "\r\n");
		mLen++;
	}

	dt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	if(mConfig.protocolName == IEC_103HUABEI)
	{
		//规约无此内容
	}
	else
	{
		rcvdt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;

		eventNum = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t故障量个数:" + QString::number(eventNum) + "\r\n");
		mLen++;

		mText.append("-----------------------------------------------------------------------------------------------\r\n");
		for(int index = 0; index < eventNum; index++)
		{
			IEC103Asdu10DataSet *mset = new IEC103Asdu10DataSet(mConfig);
			bool isOk = mset->init(buff.mid(mLen));
			if(!isOk)
			{
				delete mset;
				mset = NULL;
				return false;
			}
			mset->mIndex = index;
			mLen += mset->mLen;
			setlist.append(mset);
		}
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
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


IEC103Asdu18Data::IEC103Asdu18Data(const MyConfig& Config): IEC103Asdu15Data(Config)
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
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		rii = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		mLen++;
	}

	if(mConfig.protocolName == IEC_103HUABEI)
	{
		//规约无此内容
	}
	else
	{
		isLast = *(buff.data() + mLen) & 0x01;
		mText.append(CharToHexStr(buff.data() + mLen) + "\t后续位标志: " + QString(isLast ? "1 有后续帧" : "0 最后的帧") + "\r\n");
		mLen++;
	}

	dtBegin = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	dtEnd = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	hisNum = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t历史信息条数: " + QString::number(hisNum) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < hisNum; index++)
	{
		HisInfo *minfo = new HisInfo(mConfig);
		bool isOk = minfo->init(buff.mid(mLen));
		if(!isOk)
		{
			delete minfo;
			minfo = NULL;
			return false;
		}
		minfo->mIndex = index;
		mLen += minfo->mLen;
		hisInfos.append(minfo);
	}

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
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


