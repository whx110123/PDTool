#ifndef DIALOGMODBUS_H
#define DIALOGMODBUS_H

#include <QDialog>

namespace Ui
{
	class DialogModbus;
}

class DialogModbus : public QDialog
{
	Q_OBJECT

public:
	explicit DialogModbus(QWidget *parent = nullptr);
	~DialogModbus();
private:
	enum FieldColNum {colType = 0, colAnaly, colLen, colDes};
	void initShow();
	void addItems();
	void addItem(QStringList list);
	void setItem(int rowNo, QStringList list);
private:
	Ui::DialogModbus *ui;
};

#endif // DIALOGMODBUS_H
