#include "modbus.h"

Modbus::Modbus()
{
	isMaster = false;
}

Modbus::~Modbus()
{
	qDeleteAll(datalist);
	datalist.clear();


}

bool Modbus::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();

	if(buff.count() < 3)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}

	addr = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t装置地址: " + QString::number(addr) + "\r\n");
	len++;

	code = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + codeToText() + "\r\n");
	len++;

	if(isMaster == true)
	{
		switch(code)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			dataAddr = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t起始地址: " + QString::number(dataAddr) + "\r\n");
			len += 2;
			data_num = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t寄存器/bit数量: " + QString::number(data_num) + "\r\n");
			len += 2;
			break;
		case 5:
		case 6:
			dataAddr = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t遥控地址: " + QString::number(dataAddr) + "\r\n");
			len += 2;
			data_num = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t遥控命令字: " + QString::number(data_num) + "\r\n");
			len += 2;
			break;
		case 15:
		case 16:
			dataAddr = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t起始地址: " + QString::number(dataAddr) + "\r\n");
			len += 2;
			data_num = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t寄存器/bit数量: " + QString::number(data_num) + "\r\n");
			len += 2;
			bytenum = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t字节数: " + QString::number(bytenum) + "\r\n");
			len++;
			mText.append(CharToHexStr(buff.data() + len, bytenum) + "\t多点控制数据\r\n");
			len += bytenum;
			break;
		default:
			error = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的功能码").arg(code);
			return false;
			break;
		}

	}
	else if(isMaster == false)
	{
		mgroup.dataLen = *(buff.data() + len);
		mgroup.type.clear();
		mgroup.analysis.clear();
		mText.append(CharToHexStr(buff.data() + len) + "\t长度: " + QString::number(mgroup.dataLen) + "\r\n");
		len++;

		for(ModbusDataGroup *g : mConfig.groups)
		{
			if(g->dataLen == mgroup.dataLen)
			{
				mgroup.type = g->type;
				mgroup.analysis = g->analysis;
				mgroup.sort = g->sort;
				break;
			}
		}
		if(mgroup.analysis.isEmpty())
		{
			mText.append(CharToHexStr(buff.data() + len, mgroup.dataLen) + "\t数据，未解析\r\n");
			len += mgroup.dataLen;
		}
		else
		{
			int mindex = 0;
			while(len < mgroup.dataLen + 3)
			{
				ModbusData *mdata = new ModbusData;
				mdata->index = mindex;
				if(!mdata->initData(buff.mid(len), &mgroup))
				{
					return false;
				}
				datalist.append(mdata);
				len += mdata->len;
				mindex++;
			}
		}


	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！无法确定此报文为召唤或应答报文");
		return false;
	}



	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString Modbus::showToText()
{
	for(ModbusData *d : datalist)
	{
		mText.append(d->showToText());
	}
	return mText;
}

QString Modbus::codeToText()
{
	QString text = "功能码: " + QString::number(code) + "   ";
	switch(code)
	{
	case 1:
		text.append("读DO状态");
		break;
	case 2:
		text.append("读DI状态");
		break;
	case 3:
		text.append("读保持寄存器");
		break;
	case 4:
		text.append("读输入寄存器");
		break;
	case 5:
		text.append("写单线圈");
		break;
	case 6:
		text.append("写单寄存器");
		break;
	case 15:
		text.append("写多线圈");
		break;
	case 16:
		text.append("写多寄存器");
		break;
	default:
		text.append("未解析");
		break;
	}
	return text;
}
