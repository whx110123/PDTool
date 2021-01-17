#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QString>
#include <QDateTime>
#include <QTextCodec>
#include <QVector>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int  uint;

#define YC "遥测"
#define YX "遥信"
#define YM "遥脉"

#define SORT1 "高字  高字节"
#define SORT2 "低字  高字节"
#define SORT3 "高字  低字节"
#define SORT4 "低字  低字节"

#define PW_AVAILABLE 0x01
#define TP_AVAILABLE 0x02
#define ISMASTER 0x80
enum
{
	TYPE_UINT32,
};

enum
{
	ITYPE = 1,
	UTYPE,
	STYPE
};

enum
{
	STATE_NODATA,				//无数据
	STATE_INIT,					//初始化
	STATE_CALLALL,				//发送总召
	STATE_SETTIME,				//对时
	STATE_NORMAL,				//正常,状态,回复S帧
	STATE_TESTACT,				//激活测试
	STATE_TESTCONFIRM,			//确认测试
	STATE_USER,					//自定义ASDU
	STATE_HOTKEY,				//通过点击快捷键
	STATE_NUM					//所有状态的数目
};

enum
{
	IEC103END_NO,
	IEC103END_SIN,
	IEC103END_SCN,
	IEC103END_RII
};
enum
{
	BCDTIME1 = 0,		//BCD时间1
	BINARYTIME1,		//二进制时间1
	BINARYTIME2A,		//二进制时间2a
	BINARYTIME2B,		//二进制时间2b
	BINARYTIME2C,		//二进制时间2c
	MYTIME1,			//自定义时间方式，4字节对应日时分秒
	MYTIME2,			//自定义时间方式，6字节对应年月日时分的BCD码
};


QString CharToHexStr(uchar data);           //将一个uchar字符转换成2个字符的16进制QString
QString CharToHexStr(const char *data, int len = 1);
QString CharToHexStr(uchar *data, int len = 1);
uint charTouint(const char *data, int len, int model = 0);
uint charTouint(uchar *data, int len, int model = 0);    //将len个uchar合成一个uint,model 0:低字节在前 1:高字节在前 2:低字在前 高字节在前 3:高字在前 低字节在前
int charToint(uchar *data, int len, int model = 0);    //将4个uchar合成一个int,model 0:低字节在前 1:高字节在前 2:低字在前 高字节在前 3:高字在前 低字节在前
int charToint(const char *data, int len, int model = 0);      //将4个char合成一个int,model 0:低字节在前 1:高字节在前 2:低字在前 高字节在前 3:高字在前 低字节在前
short charToshortwithQ(uchar *data, uchar& ov, uchar& er, int model = 0);
short charToshortwithQ(uchar *data, int model = 0);
short charToshortwithQ(const char *data, int model = 0);
float charTofloat(const char *data, int model = 0);
float charTofloat(uchar *data, int model = 0);
double charTodouble(const char *data, int model = 0);
double charTodouble(uchar *data, int model = 0);
QDateTime charToDateTime(uchar *data, int len, int model = BINARYTIME2A); //将len个uchar合成一个日期,model时间类型
QDateTime charToDateTime(const char *data, int len, int model = BINARYTIME2A);//将len个char合成一个日期,model时间类型

QByteArray uintToBa(uint data, int len);
QByteArray floatToBa(float data);
QByteArray dateTimeToBa(QDateTime datatime, int len, int model = BINARYTIME2A);

void BaReverse(QByteArray& ba);

uchar crcsum(const char *data, int start, int end);
ushort crc16(uchar *data, ushort start, ushort end);
ushort crc16(uchar *data, ushort len);
uint bcdTouint(const char *bcd, int len);
uint bcdTouint(uchar *bcd, int len);
int stringToInt(QString data);

#define IEC_104 "104"
#define IEC_101 "101"
#define IEC_103WISCOMNET "金智网络103"
#define IEC_103COM "串口103"
#define IEC_103ASDU "103ASDU"
#define IEC_103BAOXINNET "保信网络103"
#define IEC_103XUJINET "许继网络103"
#define IEC_103NANZINET "南自网络103"
#define IEC_103HUABEI "华北103"
#define MODBUS_RTU "modbus RTU"
#define MODBUS_TCP "modbus TCP"
#define MEASUREDTERMINAL_NW_NET "南网计量终端网络"

#define IEC_SINGLE "单字节"
#define IEC_DOUBLESAME "双字节 重复"
#define IEC_DOUBLEDIFF "双字节 组合"
#endif // GLOBALDEFINE_H
