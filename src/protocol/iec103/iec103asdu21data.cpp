#include "iec103asdu21data.h"

IEC103Asdu21Data::IEC103Asdu21Data(const MyConfig& Config): IEC103AsduData(Config)
{
	rii = 0;
	nog = 0;
}

IEC103Asdu21Data::~IEC103Asdu21Data()
{
	qDeleteAll(setlist);
	setlist.clear();
}


bool IEC103Asdu21Data::handle(const QByteArray& buff)
{
	qDeleteAll(setlist);
	setlist.clear();

	rii = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	mLen++;
	if(mLen == buff.size())
	{
		return true;
	}

	nog = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + nogToText(nog) + "\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen == buff.size())
	{
		return true;
	}


	for(int index = 0; index < nog; index++)
	{
		IEC103Asdu10DataSet *mset = new IEC103Asdu10DataSet(mConfig);
		bool isOk = mset->init(buff.mid(mLen, 3));
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

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


QString IEC103Asdu21Data::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103Asdu21Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(tmp.sqFlag == SQ_FUNINF)
	{
		tmp.data += fun;
		tmp.data += inf;
	}
	else if(tmp.sqFlag == SQ_INF)
	{
		tmp.data += inf;
	}
	tmp.data += rii;
	tmp.data += nog;

	int index = 0;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		if(!mset->createData(tmp))
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
			return false;
		}
		index++;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}

	return true;
//	config.data += config.inf;
//	config.data += config.rii;
//	config.data += config.nog;
//	if(config.isMaster)
//	{
//		for(int i = 0; i < config.nog; i++)
//		{
//			config.data += config.gin[i][0];
//			config.data += config.gin[i][1];
//			config.data += config.kod[i];
//		}
//		return true;
//	}
//	mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
//	return false;
}
