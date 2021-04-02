#include "dataconfig.h"

MyData::MyData()
{
	sqFlag = SQ_INF;
	reverse = false;
}

MyData::~MyData()
{

}

void MyData::getAttribute(const MyData& md)
{
	sqFlag = md.sqFlag;
}

MyData MyData::operator+(const MyData& md) const
{
	MyData sum;
	sum.data = data + md.data;
	return sum;
}
