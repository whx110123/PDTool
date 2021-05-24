#include "myhighlighter.h"
#include <QString>

myhighlighter::myhighlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{
	enable = true;
}

void myhighlighter::highlightBlock(const QString& text)
{
	if(!enable)
	{
		return;
	}
	QTextCharFormat myformat1;
	myformat1.setFontWeight(QFont::Bold);
	myformat1.setForeground(Qt::red);
	QTextCharFormat myformat2;
	myformat2.setFontWeight(QFont::Bold);
	myformat2.setForeground(Qt::blue);
	myformat2.setFontPointSize(14);

	QStringList patlis1;
	patlis1  << " 溢出"
			 << " 被闭锁"
			 << " 被取代"
			 << " 非当前值"
			 << " 无效"
			 << "否定确认"
			 << "试验状态"
			 << "未知，无法识别当前的传送原因"
			 << "未完成此ASDU剩余报文的解析"
			 << "出错！"
			 << " 上次读数后计数器被调整"
			 << " 在相应的累加周期内计数器溢出"
			 << " 被测值无效";


	for(int i = 0; i < patlis1.size(); i++)
	{
		QString pattern = patlis1.at(i);
		int length = pattern.length();
		int index = text.indexOf(pattern);
		while(index >= 0)
		{
			setFormat(index, length, myformat1);
			index = text.indexOf(pattern, index + length);
		}
	}

	QString pattern1 = "####第";
	int length1 = pattern1.length();
	QString pattern2 = "帧####";
	int length2 = pattern2.length();
	int index1 = text.indexOf(pattern1);
	int index2 = text.indexOf(pattern2, index1);
	while(index1 >= 0 && index2 >= 0 && (index2 - index1) < (length1 + 8))
	{
		int length = index2 - index1 + length2;
		setFormat(index1, length, myformat2);
		index1 = text.indexOf(pattern1, index1 + length);
		index2 = text.indexOf(pattern2, index1);
	}


	int length = hlstr.length();
	if(length > 0)
	{
		int index = text.indexOf(hlstr);
		while(index >= 0)
		{
			setFormat(index, length, hlformat);
			index = text.indexOf(hlstr, index + length);
		}
	}
}

void myhighlighter::setEnable(bool isOK)
{
	enable = isOK;
}
