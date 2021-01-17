#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QSyntaxHighlighter>
class myhighlighter : public QSyntaxHighlighter
{
	Q_OBJECT
public:
	explicit myhighlighter(QTextDocument *parent = 0);
public:
	QString hlstr;
	QTextCharFormat hlformat;
	void highlightBlock(const QString& text);
};

#endif // MYHIGHLIGHTER_H
