#include "iec103asdu11data.h"


IEC103Asdu11DataSet::IEC103Asdu11DataSet()
{

}

IEC103Asdu11DataSet::~IEC103Asdu11DataSet()
{

}

bool IEC103Asdu11DataSet::init(const QByteArray& buff)
{
	setDefault(buff);

	kod = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + kodToText(kod) + "\r\n");
	len++;

	if(buff.size() == len)
	{
		return true;
	}
	if(!mygdd.init(buff.mid(len)))
	{
		return false;
	}
	len += mygdd.len;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu11DataSet::showToText()
{
	QString text = mText;
	text.append(mygdd.showToText());
	return text;
}

bool IEC103Asdu11DataSet::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

IEC103Asdu11Data::IEC103Asdu11Data()
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

	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	memcpy(gin, buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\tGIN:组号" + QString::number(gin[0]) + "   条目号" + QString::number(gin[1]) + "\r\n");
	len += 2;

	nde = *(buff.data() + len);
	setnum = nde & 0x3f;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + ndeToText(nde) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < setnum; index++)
	{
		IEC103Asdu11DataSet *mset = new IEC103Asdu11DataSet;
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

QString IEC103Asdu11Data::showToText()
{
	QString text = mText;
	for(IEC103Asdu11DataSet *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103Asdu11Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

