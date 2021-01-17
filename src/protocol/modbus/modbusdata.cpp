#include "modbusdata.h"

ModbusData::ModbusData()
{

}

ModbusData::~ModbusData()
{

}

bool ModbusData::initData(const QByteArray& buff, ModbusDataGroup *group)
{
	setDefault(buff);
	if(index <  group->analysis.length())
	{
		mcode = group->analysis.at(index);
	}
	else
	{
		mcode = group->analysis.back();
	}
	mtype = group->type;
	int mod = 0;
	if(mtype == YC)
	{
		switch(mcode.unicode())
		{
		case '0':
			if(group->sort == SORT1 || group->sort == SORT2)
			{
				mod = 1;
			}
			datashort = charToint(buff.data() + len, 2, mod);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + QString("第%1个数据  ").arg(index + 1) + "有符号整数:" + QString::number(datashort) + "\r\n");
			len += 2;
			break;
		case '1':
			if(group->sort == SORT1 || group->sort == SORT2)
			{
				mod = 1;
			}
			dataushort = charTouint(buff.data() + len, 2, mod);
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + QString("第%1个数据  ").arg(index + 1) + "无符号整数:" + QString::number(dataushort) + "\r\n");
			len += 2;
			break;
		case '2':
			if(group->sort == SORT1 || group->sort == SORT2)
			{
				mod = 1;
			}
			dataushort = charTouint(buff.data() + len, 2, mod);
			if(dataushort & 0x8000)
			{
				datashort = (dataushort & 0x7fff) * (-1);
			}
			else
			{
				datashort = dataushort;
			}
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + QString("第%1个数据  ").arg(index + 1) + "原码表示的有符号整数:" + QString::number(datashort) + "\r\n");
			len += 2;
			break;
		case '3':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			dataint = charToint(buff.data() + len, 4, mod);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + QString("第%1个数据  ").arg(index + 1) + "有符号整数:" + QString::number(dataint) + "\r\n");
			len += 4;
			break;
		case '4':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datauint = charTouint(buff.data() + len, 4, mod);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + QString("第%1个数据  ").arg(index + 1) + "无符号整数:" + QString::number(datauint) + "\r\n");
			len += 4;
			break;
		case '5':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datafloat = charTofloat(buff.data() + len, mod);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + QString("第%1个数据  ").arg(index + 1) + "浮点数:" + QString::number(datafloat, 'g', 10) + "\r\n");
			len += 4;
			break;
		case '6':
			datachar = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t" + QString("第%1个数据  ").arg(index + 1) + "有符号整数:" + QString::number(datachar) + "\r\n");
			len++;
			break;
		case '7':
			datauchar = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t" + QString("第%1个数据  ").arg(index + 1) + "无符号整数:" + QString::number(datauchar) + "\r\n");
			len++;
			break;
		case 'A':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datadouble = charTodouble(buff.data() + len, mod);
			mText.append(CharToHexStr(buff.data() + len, 8) + "\t" + QString("第%1个数据  ").arg(index + 1) + "双精度浮点数:" + QString::number(datadouble, 'g', 20) + "\r\n");
			len += 8;
			break;
		case 'F':
			mText.append(CharToHexStr(buff.data() + len, 2) + "\t忽略两个字节\r\n");
			len += 2;
			break;
		default:
			error = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的解析码").arg(mcode);
			return false;
			break;
		}
	}
	else if(mtype == YX)
	{
		switch(mcode.unicode())
		{
		case '0':
			datauchar = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len));
			for(int i = 0; i < 8; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(index + 1).arg(i + 1));
				mText.append((datauchar >> i) & 0x01 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			len++;
			break;
		case '1':
			dataushort = charTouint(buff.data() + len, 2, 1);
			mText.append(CharToHexStr(buff.data() + len, 2));
			for(int i = 0; i < 16; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(index + 1).arg(i + 1));
				mText.append((dataushort >> i) & 0x01 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			len += 2;
			break;
		case '2':
			datauint = charTouint(buff.data() + len, 4, 1);
			mText.append(CharToHexStr(buff.data() + len, 4));
			for(int i = 0; i < 32; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(index + 1).arg(i + 1));
				mText.append((datauint >> i) & 0x01 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			len += 4;
			break;
		case '3':
			datauchar = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len));
			for(int i = 0; i < 8; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(index + 1).arg(i + 1));
				mText.append((datauchar << i) & 0x80 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			len++;
			break;
		case 'F':
			mText.append(CharToHexStr(buff.data() + len) + "\t忽略一个字节\r\n");
			len++;
			break;
		default:
			error = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的解析码").arg(mcode);
			return false;
			break;
		}
	}
	else if(mtype == YM)
	{
		switch(mcode.unicode())
		{
		case '0':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datauint = charTouint(buff.data() + len, 4, mod);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + QString("第%1个数据  ").arg(index + 1) + "无符号整数:" + QString::number(datauint) + "\r\n");
			len += 4;
			break;
		case '1':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datafloat = charTofloat(buff.data() + len, mod);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + QString("第%1个数据  ").arg(index + 1) + "浮点数:" + QString::number(datafloat, 'g', 10) + "\r\n");
			len += 4;
			break;
		case 'F':
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t忽略四个字节\r\n");
			len += 4;
			break;
		default:
			error = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的解析码").arg(mcode);
			return false;
			break;
		}
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未知类型");
		return false;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

