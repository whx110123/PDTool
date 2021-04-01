#include "dataconfig.h"

MyData::MyData()
{
	flag = 0;
	reverse = false;
}

MyData::~MyData()
{

}

void MyData::getAttribute(const MyData& md)
{
	flag = md.flag;
}

MyData MyData::operator+(const MyData& md) const
{
	MyData sum;
	sum.data = data + md.data;
	return sum;
}
