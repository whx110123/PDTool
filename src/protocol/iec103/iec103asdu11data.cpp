#include "iec103asdu11data.h"


IEC103Asdu11DataSet::IEC103Asdu11DataSet(const MyConfig& Config): IEC103Asdu10DataSet(Config)
{

}

IEC103Asdu11DataSet::~IEC103Asdu11DataSet()
{

}

bool IEC103Asdu11DataSet::init(const QByteArray& buff)
{
	setDefault(buff);

	kod = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + kodToText(kod) + "\r\n");
	mLen++;

	if(buff.size() == mLen)
	{
		return true;
	}
	if(!mygdd.init(buff.mid(mLen)))
	{
		mText.append(mygdd.showToText());
		return false;
	}
	mText.append(mygdd.showToText());
	mLen += mygdd.mLen;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}


IEC103Asdu11Data::IEC103Asdu11Data(const MyConfig& Config): IEC103AsduData(Config)
{
	rii = 0;
	memset(gin, 0, sizeof(gin));
	nde = 0;
}

IEC103Asdu11Data::~IEC103Asdu11Data()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool IEC103Asdu11Data::handle(const QByteArray& buff)
{
	qDeleteAll(setlist);
	setlist.clear();

	rii = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	mLen++;

	memcpy(gin, buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGIN:组号" + QString::number(gin[0]) + "   条目号" + QString::number(gin[1]) + "\r\n");
	mLen += 2;

	nde = *(buff.data() + mLen);
	setnum = nde & 0x3f;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + ndeToText(nde) + "\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < setnum; index++)
	{
		IEC103Asdu11DataSet *mset = new IEC103Asdu11DataSet(mConfig);
		setlist.append(mset);
		mset->mIndex = index;
		bool isOk = mset->init(buff.mid(mLen));
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



