#ifndef DIALOGDEBUG_H
#define DIALOGDEBUG_H

#include <QDialog>

namespace Ui
{
	class DialogDebug;
}

class DialogDebug : public QDialog
{
	Q_OBJECT

public:
	explicit DialogDebug(QWidget *parent = nullptr);
	~DialogDebug();

private slots:
	void on_Bt1_clicked();
	QString msgTodata(QString msg);

	void on_Bt2_clicked();

	void on_Bt_clear_clicked();


	void on_lineEdit_textChanged(const QString& arg1);

private:
	Ui::DialogDebug *ui;
};

#endif // DIALOGDEBUG_H
