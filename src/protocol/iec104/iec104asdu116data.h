#ifndef IEC104ASDU116DATA_H
#define IEC104ASDU116DATA_H

#include "iec101asdu.h"


//源端维护
class IEC104Asdu116Data : public IEC101AsduData
{
public:
	IEC104Asdu116Data(const MyConfig& Config);
	~IEC104Asdu116Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar dataType;
	uchar objType;		//操作标识
	uchar objlen;		//操作票号长度
	QString obj;		//操作票号
	ushort step;		//步骤号
	uchar opCode;		//命令限定词
	uchar infCode;		//信息限定词
	QString infStr;		//信息字符
	QDateTime dt;		//配置更新时间
	uchar idLen;		//变电站ID长度
	QString id;			//变电站ID
	uchar opFlag;
	uchar result;
	uchar charTmp;
	uchar fileNameSize;
	QString fileName;
	uint fileID;
	uint fileSize;
	uint dataIndex;
	uchar isLast;
	QString fileData;
	uchar crc;
	QTextCodec *gbk;
private:
	QString opCodeToText();
	QString infCodeToText();
};

#endif // IEC104ASDU116DATA_H
