#ifndef IEC101ASDU55DATA_H
#define IEC101ASDU55DATA_H

#include "iec101asdu.h"

class IEC101Asdu55Data : public IEC101AsduData
{
public:
	IEC101Asdu55Data();
	~IEC101Asdu55Data();
	virtual bool init(const QByteArray& buff);

public:
	uchar code;		//序列控制命令限定词
	uchar mindex;	//控制对象顺序号
	uchar objlen;	//控制对象长度
	QString obj;	//控制对象
	uchar step;		//步骤号
	uchar rii;		//返回信息功能码
	uchar userlen;	//操作用户名长度
	QString user;	//操作用户名
private:
	QString codeToText();
	QString riiToText();
};

#endif // IEC101ASDU55DATA_H
