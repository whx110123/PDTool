#include "modbus.h"

Modbus::Modbus(const MyConfig& Config): MyBase(Config)
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
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}

	addr = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t装置地址: " + QString::number(addr) + "\r\n");
	mLen++;

	code = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + codeToText() + "\r\n");
	mLen++;

	if(isMaster == true)
	{
		switch(code)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			dataAddr = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t起始地址: " + QString::number(dataAddr) + "\r\n");
			mLen += 2;
			data_num = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t寄存器/bit数量: " + QString::number(data_num) + "\r\n");
			mLen += 2;
			break;
		case 5:
		case 6:
			dataAddr = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t遥控地址: " + QString::number(dataAddr) + "\r\n");
			mLen += 2;
			data_num = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t遥控命令字: " + QString::number(data_num) + "\r\n");
			mLen += 2;
			break;
		case 15:
		case 16:
			dataAddr = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t起始地址: " + QString::number(dataAddr) + "\r\n");
			mLen += 2;
			data_num = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t寄存器/bit数量: " + QString::number(data_num) + "\r\n");
			mLen += 2;
			bytenum = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t字节数: " + QString::number(bytenum) + "\r\n");
			mLen++;
			mText.append(CharToHexStr(buff.data() + mLen, bytenum) + "\t多点控制数据\r\n");
			mLen += bytenum;
			break;
		default:
			mError = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的功能码").arg(code);
			return false;
			break;
		}

	}
	else if(isMaster == false)
	{
		mgroup.dataLen = *(buff.data() + mLen);
		mgroup.type.clear();
		mgroup.analysis.clear();
		mText.append(CharToHexStr(buff.data() + mLen) + "\t长度: " + QString::number(mgroup.dataLen) + "\r\n");
		mLen++;

		for(ModbusDataGroup g : mConfig.groups)
		{
			if(g.dataLen == mgroup.dataLen)
			{
				mgroup = g;
				break;
			}
		}
		if(mgroup.analysis.isEmpty())
		{
			mText.append(CharToHexStr(buff.data() + mLen, mgroup.dataLen) + "\t数据，未解析\r\n");
			mLen += mgroup.dataLen;
		}
		else
		{
			int m_index = 0;
			while(mLen < mgroup.dataLen + 3)
			{
				ModbusData *mdata = new ModbusData(mConfig);
				if(!mdata)
				{
					mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！申请内存失败");
					return false;
				}
				mdata->mIndex = m_index;
				if(!mdata->initData(buff.mid(mLen), &mgroup))
				{
					return false;
				}
				datalist.append(mdata);
				mLen += mdata->mLen;
				m_index++;
			}
		}
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！无法确定此报文为召唤或应答报文");
		return false;
	}



	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
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
