#ifndef DLGMODBUS_H
#define DLGMODBUS_H

#include <QDialog>

namespace Ui
{
class DlgModbus;
}

class DlgModbus : public QDialog
{
	Q_OBJECT

public:
	explicit DlgModbus(QWidget *parent = nullptr);
	~DlgModbus();
private:
	enum FieldColNum {colType = 0, colAnaly, colLen, colDes};
	void initShow();
	void addItems();
	void addItem(QStringList list);
	void setItem(int rowNo, QStringList list);
private:
	Ui::DlgModbus *ui;
};

#endif // DIALOGMODBUS_H
