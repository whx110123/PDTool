#include "iec103asdu21data.h"

IEC103Asdu21Data::IEC103Asdu21Data()
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

	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;
	if(len == buff.size())
	{
		return true;
	}

	nog = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + nogToText(nog) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len == buff.size())
	{
		return true;
	}


	for(int index = 0; index < nog; index++)
	{
		IEC103Asdu10DataSet *mset = new IEC103Asdu10DataSet;
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


QString IEC103Asdu21Data::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103Asdu21Data::createData(IECDataConfig& config)
{
	config.data += config.inf;
	config.data += config.rii;
	config.data += config.nog;
	if(config.isMaster)
	{
		for(int i = 0; i < config.nog; i++)
		{
			config.data += config.gin[i][0];
			config.data += config.gin[i][1];
			config.data += config.kod[i];
		}
		return true;
	}
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
