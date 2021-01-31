#include "iec101asdu116data.h"

IEC101Asdu116Data::IEC101Asdu116Data(const MyConfig& Config): IEC101AsduData(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC101Asdu116Data::~IEC101Asdu116Data()
{

}

bool IEC101Asdu116Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	dataType = *(buff.data() + len);
	switch(dataType)
	{
	case 1:
		mText.append(CharToHexStr(buff.data() + len) + "\t附加数据包类型: 程序化操作\r\n");
		len++;
		break;
	case 2:
		mText.append(CharToHexStr(buff.data() + len) + "\t附加数据包类型: 文件传输\r\n");
		len++;
		opFlag = *(buff.data() + len);
		switch(opFlag)
		{
		case 3:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 3 读文件激活\r\n");
			len++;
			fileNameSize = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			len++;
			QByteArray ba(buff.data() + len, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			len += fileNameSize;
			break;
		}
		case 4:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 4 读文件激活确认\r\n");
			len++;
			result = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			len++;
			fileNameSize = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			len++;
			QByteArray ba(buff.data() + len, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			len += fileNameSize;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			fileSize = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
			len += 4;
			break;
		}
		case 5:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 5 读文件数据响应\r\n");
			len++;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			dataIndex = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			len += 4;
			isLast = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t后续标志: " + QString(isLast ? "1 有后续" : "0 无后续") + "\r\n");
			len++;
			fileSize = buff.length() - len - 1;
			QByteArray ba(buff.data() + len, fileSize);
			fileData = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, fileSize) + "\t文件数据:  " + fileData + "\r\n");
			len += fileSize;

			crc = *(buff.data() + len);
			uchar sum = crcsum(buff.data(), len - fileSize, len);
			mText.append(CharToHexStr(buff.data() + len) + "\t校验码: " + QString(crc == sum ? "计算结果正确" : "计算结果错误") + "\r\n");
			len++;
			break;
		}
		case 6:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 6 读文件数据的传输确认\r\n");
			len++;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			dataIndex = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			len += 4;
			result = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			len++;
			break;
		}
		case 7:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 7 写文件激活\r\n");
			len++;
			fileNameSize = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			len++;
			QByteArray ba(buff.data() + len, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			len += fileNameSize;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			fileSize = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
			len += 4;
			break;
		}
		case 8:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 8 写文件激活确认\r\n");
			len++;
			result = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			len++;
			fileNameSize = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			len++;
			QByteArray ba(buff.data() + len, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			len += fileNameSize;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			fileSize = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
			len += 4;
			break;
		}
		case 9:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 9 写文件数据\r\n");
			len++;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			dataIndex = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			len += 4;
			isLast = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t后续标志: " + QString(isLast ? "1 有后续" : "0 无后续") + "\r\n");
			len++;
			fileSize = buff.length() - len - 1;
			QByteArray ba(buff.data() + len, fileSize);
			fileData = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, fileSize) + "\t文件数据:  " + fileData + "\r\n");
			len += fileSize;

			crc = *(buff.data() + len);
			uchar sum = crcsum(buff.data(), len - fileSize, len);
			mText.append(CharToHexStr(buff.data() + len) + "\t校验码: " + QString(crc == sum ? "计算结果正确" : "计算结果错误") + "\r\n");
			len++;
			break;
		}
		case 10:
		{
			mText.append(CharToHexStr(buff.data() + len) + "\t操作标识: 10 写文件数据的传输确认\r\n");
			len++;
			fileID = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			len += 4;
			dataIndex = charTouint(buff.data() + len, 4);
			mText.append(CharToHexStr(buff.data() + len, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			len += 4;
			result = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			len++;
			break;
		}
		default:
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的文件传输标识");
			return false;
			break;
		}
		break;
	case 3:
		mText.append(CharToHexStr(buff.data() + len) + "\t附加数据包类型: IEC103通用分类服务数据\r\n");
		len++;
		break;
	case 4:
		mText.append(CharToHexStr(buff.data() + len) + "\t附加数据包类型: IEC102\r\n");
		len++;
		break;
	case 5:
		mText.append(CharToHexStr(buff.data() + len) + "\t附加数据包类型: 源端维护\r\n");
		len++;
		opFlag = *(buff.data() + len);
		switch(opFlag)
		{
		case 1:
			if(len + 1 == buff.length())
			{
				mText.append(CharToHexStr(buff.data() + len) + "\t命令标识: 1 四遥数据传输激活\r\n");
				len++;
			}
			else
			{
				mText.append(CharToHexStr(buff.data() + len) + "\t状态标识: 1 MAP文件校验\r\n");
				len++;
				result = *(buff.data() + len) & 0x01;
				mText.append(CharToHexStr(buff.data() + len) + "\t状态描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
				len++;
			}
			break;
		case 2:
			mText.append(CharToHexStr(buff.data() + len) + "\t命令标识: 2 四遥数据传输激活确认\r\n");
			len++;
			result = *(buff.data() + len) & 0x01;
			mText.append(CharToHexStr(buff.data() + len) + "\t结果描述字: " + QString(result ? "1 否定" : "0 肯定") + "\r\n");
			len++;
			break;
		default:
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的源端维护标识");
			return false;
			break;
		}
		break;
	default:
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的附加数据包类型");
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

