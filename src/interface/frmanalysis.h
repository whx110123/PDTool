#ifndef FRMANALYSIS_H
#define FRMANALYSIS_H

#include <QWidget>
#include <mybase.h>
#include "globaldefine.h"
#include "dialogmodbus.h"

namespace Ui
{
class frmAnalysis;
}
class myhighlighter;
class frmAnalysis : public QWidget
{
	Q_OBJECT

public:
	explicit frmAnalysis(QWidget *parent = nullptr);
	~frmAnalysis();


signals:
	void emitstr(QString str);

private slots:
	void initForm();
	void initConfig();
//    void saveConfig();

private slots:

	void on_clearBtn_clicked();

	void on_protocolcbox_currentIndexChanged(const QString& arg1);

	void on_highlightEdit_textChanged(const QString& arg1);

	void on_fontcolor_clicked();

	void on_backgroundcolor_clicked();

	void on_fontchange_clicked();

	void on_pushButton_Analysis_clicked();


	void on_pushButton_change_clicked();

	void on_pushButton_clean_clicked();

	void on_pushButton_clicked();


private:
	Ui::frmAnalysis *ui;
	myhighlighter *highlighter1;
	myhighlighter *highlighter2;
	DialogModbus *modbusdlg;
public:
	void initProtocolConfig();
	MyBase *createByName(QString name);
};

#endif // FRMANALYSIS_H
