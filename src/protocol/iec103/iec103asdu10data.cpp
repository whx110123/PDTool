#include "iec103asdu10data.h"

IEC103Asdu10DataSetGid::IEC103Asdu10DataSetGid()
{
}

IEC103Asdu10DataSetGid::~IEC103Asdu10DataSetGid()
{
	qDeleteAll(gddlist);
	gddlist.clear();
}

bool IEC103Asdu10DataSetGid::initgid(const QByteArray& buff, uchar *gdd)
{
	setDefault(buff);

	qDeleteAll(gddlist);
	gddlist.clear();

	switch(gdd[0])
	{
	case 1:
		{
			QByteArray ba(buff.data() + len, gdd[1]);
			QTextCodec *gbk = QTextCodec::codecForName("GB18030");
			gbkstr = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, gdd[1]) + "\tOS8(ASCII8位码):" + gbkstr + "\r\n");
			len += gdd[1];
		}
		break;
	case 2:
		{
			bit8 = QString("%1").arg(QString::number(*(uchar *)(buff.data() + len), 2), 8, '0');
			mText.append(CharToHexStr(buff.data() + len) + "\t成组8位串:" + bit8 + "\r\n");
			len++;
		}
		break;
	case 3:
		datauint = charTouint(buff.data() + len, gdd[1]);
		mText.append(CharToHexStr(buff.data() + len, gdd[1]) + "\tGID:无符号整数:" + QString::number(datauint) + "\r\n");
		len += gdd[1];
		break;
	case 4:
		dataint = charToint(buff.data() + len, gdd[1]);
		mText.append(CharToHexStr(buff.data() + len, gdd[1]) + "\tGID:整数:" + QString::number(dataint) + "\r\n");
		len += gdd[1];
		break;
	case 7:
		if(gdd[1] != 4)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是4");
			return false;
		}
		datafloat = charTofloat(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len, gdd[1]) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		len += gdd[1];
		break;
	case 9:
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		len++;
		break;
	case 10:
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:" + spiToText(datauchar) + "\r\n");
		len++;
		break;
	case 11:
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:" + dpiteToText(datauchar) + "\r\n");
		len++;
		break;
	case 12:
		if(gdd[1] != 2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datashort = charToshortwithQ(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len, gdd[1]) + "\tGID:带品质描述词的被测值(bit4-16):" + QString::number(datashort) + "   " + ovToText(*(buff.data() + len)) + "   " + erToText(*(buff.data() + len)) + "\r\n");
		len += gdd[1];
		break;
	case 14:
		datet = charToDateTime(buff.data() + len, gdd[1], BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, gdd[1]));
		len += gdd[1];
		break;
	case 15:
		if(gdd[1] != 2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:组号: " + QString::number(datauchar) + "\r\n");
		len++;
		datauchar1 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:条目号: " + QString::number(datauchar1) + "\r\n");
		len++;
		break;
	case 16:
		if(gdd[1] != 2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datauint = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		len += 2;
		break;
	case 17:
		if(gdd[1] != 2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:FUN: " + QString::number(datauchar) + "\r\n");
		len++;
		datauchar1 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:INF: " + QString::number(datauchar1) + "\r\n");
		len++;
		break;
	case 18:
		if(gdd[1] != 6)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是6");
			return false;
		}
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		len++;
		datet = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 4));
		len += 4;
		datauchar1 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:附加信息SIN:" + QString::number(datauchar1) + "\r\n");
		len++;
		break;
	case 19:
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		len++;
		datauint = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		len += 2;

		datauint1 = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:故障序号FAN:" + QString::number(datauint1) + "\r\n");
		len += 2;

		datet = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 4));
		len += 4;

		datauchar1 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:附加信息SIN:" + QString::number(datauchar1) + "\r\n");
		len++;

		break;
	case 20:
		datafloat = charTofloat(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len, 4) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		len += 4;
		datauint = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		len += 2;

		datauint1 = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:故障序号FAN:" + QString::number(datauint1) + "\r\n");
		len += 2;

		datet = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 4));
		len += 4;
		break;
	case 21:
		if(gdd[1] > 4)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2大于4");
			return false;
		}
		datauint = charTouint(buff.data() + len, gdd[1]);
		mText.append(CharToHexStr(buff.data() + len, gdd[1]) + "\tGID:外部文本序号:" + QString::number(datauint) + " \r\n");
		len += gdd[1];
		break;
	case 22:
		if(gdd[1] != 1)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是1");
			return false;
		}
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:" + grcToText(datauchar) + "\r\n");
		len ++;
		break;
	case 23:
		while(len < gdd[1])
		{
			IEC103Asdu10DataSetGdd *mgdd = new IEC103Asdu10DataSetGdd;
			if(!mgdd->init(buff.mid(len)))
			{
				delete mgdd;
				mgdd = NULL;
				return false;
			}
			len += mgdd->len;
			gddlist.append(mgdd);
		}
		if(len != gdd[1])
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GID长度错误");
			return false;
		}
		break;
	case 201:
		datauint = charTouint(buff.data() + len, 4);
		mText.append(CharToHexStr(buff.data() + len, 4) + "\tGID:无符号整数:" + QString::number(datauint) + "\r\n");
		len += 4;
		datauchar = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tGID:预留字节,无定义" + "\r\n");
		len++;
		break;
	case 205:
		datafloat = charTofloat(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len, 4) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		len += 4;
		datauint = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		len += 2;

		datauint1 = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:故障序号FAN:" + QString::number(datauint1) + "\r\n");
		len += 2;

		datet = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
		break;
	default:
		error = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的GDD1").arg(gdd[0]);
		return false;
		break;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu10DataSetGid::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSetGdd *mgdd : gddlist)
	{
		text.append(mgdd->showToText());
	}
	return text;
}



bool IEC103Asdu10DataSetGid::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}


IEC103Asdu10DataSetGdd::IEC103Asdu10DataSetGdd()
{
	gidnum = 0;
	memset(gdd, 0, sizeof(gdd));
}

IEC103Asdu10DataSetGdd::~IEC103Asdu10DataSetGdd()
{
	qDeleteAll(gidlist);
	gidlist.clear();
}

bool IEC103Asdu10DataSetGdd::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(gidlist);
	gidlist.clear();

	memcpy(gdd, buff.data() + len, 3);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + gdd1ToText(gdd[0]) + "\r\n");
	len++;
	mText.append(CharToHexStr(buff.data() + len) + "\tGDD2:" + QString::number(gdd[1]) + " 数据宽度\r\n");
	len++;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + gdd3ToText(gdd[2]) + "\r\n");
	len++;
	if(gdd[0] == 2)
	{
		gidnum = ((ushort)gdd[1] * (gdd[2] & 0x7f) - 1) / 8 + 1;
	}
	else
	{
		gidnum = gdd[2] & 0x7f;
	}

	for(int i = 0; i < gidnum; i++)
	{
		IEC103Asdu10DataSetGid *mgid = new IEC103Asdu10DataSetGid;
		bool isOk = mgid->initgid(buff.mid(len), gdd);
		if(!isOk)
		{
			delete mgid;
			mgid = NULL;
			return false;
		}
		len += mgid->len;
		gidlist.append(mgid);
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu10DataSetGdd::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSetGid *mgid : gidlist)
	{
		text.append(mgid->showToText());
	}
	return text;
}

bool IEC103Asdu10DataSetGdd::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

IEC103Asdu10DataSet::IEC103Asdu10DataSet()
{
	memset(gin, 0, sizeof(gin));
	kod = 0;
}

IEC103Asdu10DataSet::~IEC103Asdu10DataSet()
{

}

bool IEC103Asdu10DataSet::init(const QByteArray& buff)
{
	setDefault(buff);

	memcpy(gin, buff.data() + len, sizeof(gin));
	mText.append(CharToHexStr(buff.data() + len, 2) + "\tGIN:组号" + QString::number(gin[0]) + "   条目号" + QString::number(gin[1]) + "\r\n");
	len += 2;

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

QString IEC103Asdu10DataSet::showToText()
{
	QString text = mText;
	text.append(mygdd.showToText());
	return text;
}

bool IEC103Asdu10DataSet::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}


IEC103Asdu10Data::IEC103Asdu10Data()
{
	rii = 0;
	ngd = 0;
}

IEC103Asdu10Data::~IEC103Asdu10Data()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool IEC103Asdu10Data::handle(const QByteArray& buff)
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

	ngd = *(buff.data() + len);
	setnum = ngd & 0x3f;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + ngdToText(ngd) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < setnum; index++)
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


QString IEC103Asdu10Data::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103Asdu10Data::createData(IECDataConfig& config)
{
	config.data += config.inf;
	config.data += config.rii;
	config.data += config.ngd;
	if(config.isMaster)
	{
		for(int i = 0; i < (config.ngd & 0x3f); i++)
		{
			config.data += config.gin[i][0];
			config.data += config.gin[i][1];
			config.data += config.kod[i];
			config.data += config.gdd[i][0];
			config.data += config.gdd[i][1];
			config.data += config.gdd[i][2];
			for(int j = 0; j < config.gdd[i][1] * config.gdd[i][2] ; j++)
			{
				config.data += config.gid[i * config.gdd[i][1] * config.gdd[i][2] + j];
			}
		}
		return true;
	}
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}



