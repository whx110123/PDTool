#ifndef FRMDEBUG_H
#define FRMDEBUG_H

#include <QCheckBox>
#include <QLineEdit>
#include <QWidget>

namespace Ui
{
class frmDebug;
}

#define CYCLEONCE       0   //循环一次，发完停止
#define CYCLEONCEREC    1   //循环一次，先有接受，再发送
#define CYCLE           2   //循环发送
#define CYCLEREC        3   //周期循环，先有接受，再发送

class frmDebug : public QWidget
{
	Q_OBJECT

public:
	explicit frmDebug(QWidget *parent = nullptr);
	~frmDebug();

private:
	QStringList dataList;
	QMap<int, QLineEdit *> mapline;
	QMap<int, QCheckBox *> mapchk;
	QMap<int, QString > mapstr;
	int lstindex;
	int cycleflag;
	QTimer *timercycle;
	int recflag;

	void initfrom();
	void initdataList();
public slots:
	void dealData(const QString& data, const QString& title);
signals:

	void ToTcpClient(const QString& data);
	void ToTcpServer(const QString& data);
	void ToUdpClient(const QString& data);
	void ToUdpServer(const QString& data);
	void ToCom(const QString& data);

private slots:
	void sendDatacycle();
	void emitsignals(const QString& data);
	void stopTimer();

	void on_btnSendAll_clicked();

	void on_btnSendcycle_clicked();

	void on_comboBox_currentIndexChanged(const QString& arg1);

	void on_timeinterval_textChanged(const QString& arg1);

	void on_Cb_recv_stateChanged(int arg1);

	void on_checkBox_stateChanged(int arg1);

	void on_pushButton_load_clicked();

	void on_pushButton_clearAll_clicked();

	void on_btnopenfile_clicked();

	void on_btnsendfile_clicked();

	void on_pushButton_send1_clicked();

	void on_pushButton_send2_clicked();

	void on_pushButton_send3_clicked();

	void on_pushButton_send4_clicked();

	void on_pushButton_send5_clicked();

	void on_pushButton_send6_clicked();


private:
	Ui::frmDebug *ui;
};

#endif // FRMDEBUG_H
