#ifndef ASN1BER_H
#define ASN1BER_H

#include <mybase.h>

struct BERGroup
{
	uchar type;				//数据类型
	QString typeDes;		//数据类型描述
	QString des;			//描述
	uint index;				//下标
};


class ASN1BERValue;
class ASN1BER : public MyBase
{
public:
	ASN1BER(const MyConfig& Config);
	~ASN1BER();
	virtual bool init(const QByteArray& buff) override;
	virtual void initMap();
	ASN1BER *CreateBER(uint tagNo, uchar tag, uint index);	//创建ber
	ASN1BER *CreateUniversalBER(uint tagNo, uint index);	//创建通用的ber
	ASN1BER *CreateBERByType(uint type, uint index = 0);		//按通用标签类型创建
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index);		//创建根据规范内容定义的ber
//	virtual ASN1BER *CreateBERByTagNo(uint tagNo);			//按指定标签号创建
//	virtual ASN1BER *CreateBERByIndex(uint& index);			//按下标创建，针对没有标签号的情况
	virtual ASN1BER *CreateSequenceBER(uint index);
//	virtual ASN1BER *CreateBERByMyType(uint type);		//

	void setBERGroup(ASN1BER *ber, const BERGroup group);		//

private:
	QString tagNoToText(uint tagNo);
	QString tagToText(uchar tag);
	bool getTagNo(const QByteArray& buff, uchar& tag, uchar& tagNoLen, uint& tagNo);
	bool getLength(const QByteArray& buff, uchar& lengthType, uchar& lengthLen, uint& length);

public:
	enum
	{
		EndOfContents,					//	0	不定长度编码的内容结尾标记的保留标识符。
		Boolean	,						//	1	Boolean 的通用类标记值。
		Integer,						//	2	Integer 的通用类标记值。
		BitString,						//	3	Bit String 的通用类标记值。
		OctetString,					//	4	Octet String 的通用类标记值。
		Null,							//	5	Null 的通用类标记值。
		ObjectIdentifier,				//	6	Object Identifier 的通用类标记值。
		ObjectDescriptor,				//	7	Object Descriptor 的通用类标记值。
		External,						//	8	External 的通用类标记值。
		InstanceOf = External,			//	8	Instance-Of 的通用类标记值。
		Real,							//	9	Real 的通用类标记值。
		Enumerated,						//	10	Enumerated 的通用类标记值。
		Embedded,						//	11	Embedded-PDV 的通用类标记值。
		UTF8String,						//	12	UTF8String 的通用类标记值。
		RelativeObjectIdentifier,		//	13	Relative Object Identifier 的通用类标记值。
		Time,							//	14	Time 的通用类标记值。
		Sequence = 16,					//	16	Sequence 的通用类标记值。
		SequenceOf = Sequence,			//	16	Sequence-Of 的通用类标记值。
		Set,							//	17	Set 的通用类标记值。
		SetOf = Set,					//	17	Set-Of 的通用类标记值。
		NumericString,					//	18	NumericString 的通用类标记值。
		PrintableString,				//	19	PrintableString 的通用类标记值。
		T61String,						//	20	T61String (TeletexString) 的通用类标记值。
		TeletexString = T61String,		//	20	TeletexString (T61String) 的通用类标记值。
		VideotexString,					//	21	VideotexString 的通用类标记值。
		IA5String,						//	22	IA5String 的通用类标记值。
		UtcTime,						//	23	UTCTime 的通用类标记值。
		GeneralizedTime,				//	24	GeneralizedTime 的通用类标记值。
		GraphicString,					//	25	GraphicString 的通用类标记值。
		VisibleString,					//	26	VisibleString (ISO646String) 的通用类标记值。
		ISO646String = VisibleString,	//	26	ISO646String (VisibleString) 的通用类标记值。
		GeneralString,					//	27	GeneralString 的通用类标记值。
		UniversalString,				//	28	UniversalString 的通用类标记值。
		UnrestrictedCharacterString,	//	29	不受限制的字符串的通用类标记值。
		BMPString,						//	30	BMPString 的通用类标记值。
		Date,							//	31	Date 的通用类标记值。
		TimeOfDay,						//	32	Time-Of-Day 的通用类标记值。
		DateTime,						//	33	Date-Time 的通用类标记值。
		Duration,						//	34	Duration 的通用类标记值。
		ObjectIdentifierIRI,			//	35	Object Identifier Internationalized Resource Identifier (IRI) 的通用类标记值。
		RelativeObjectIdentifierIRI,	//	36	Relative Object Identifier Internationalized Resource Identifier (IRI) 的通用类标记值。
		Choice,
		ChoiceWithTag,
	};
	BERGroup myGroup;		//信息

	uchar myTag;			//标签
	uchar myTagNoLen;		//标签编号字节数
	uint myTagNo;			//标签编号
	uchar myLengthType;		//长度类型
	uchar myLengthLen;		//长度字节数
	uint myLength;			//长度
	QMap<uint, BERGroup> myTagNoMap;		//记录标签编号及对应的数据类型与描述
	QMap<uint, BERGroup> myIndexMap;			//记录下标及对应的数据类型与描述
	//1
	ASN1BERValue *myValue;
	//2
	QList<ASN1BER *> myList;
};

#endif // ASN1BER_H
