#ifndef DIALOGSENDDATA_H
#define DIALOGSENDDATA_H

#include <QDialog>
#include <QtNetwork>
#include <QLineEdit>
#include <QCheckBox>
#include "iec104.h"

namespace Ui
{
	class DialogSendData;
}
#define CYCLEONCE       0   //循环一次，发完停止
#define CYCLEONCEREC    1   //循环一次，先有接受，再发送
#define CYCLE           2   //循环发送
#define CYCLEREC        3   //周期循环，先有接受，再发送
class DialogSendData : public QDialog
{
	Q_OBJECT

public:
	explicit DialogSendData(QWidget *parent = nullptr);
	~DialogSendData();

private:
	QStringList dataList;
	QMap<int, QLineEdit *> mapline;
	QMap<int, QCheckBox *> mapchk;
	QMap<int, QString > mapstr;
	int lstindex;
	int cycleflag;
	QTimer *timercycle;
	int recflag;
//	IEC104 *piec104;
//	IECDataConfig config;
//	QTimer *handleDataTimer;
//	QByteArray recvData;
//	bool haveData;
	void initfrom();
	void initdataList();
	void closeEvent(QCloseEvent *event);

public slots:
	void dealData(const QString& data, const QString& title);
signals:

	void dlgTotcpclient(const QString& data);
	void dlgTotcpserver(const QString& data);
	void dlgToudpclient(const QString& data);
	void dlgToudpserver(const QString& data);
	void dlgTocom(const QString& data);

private slots:
	void sendDatacycle();
//	void handleData();
//	void startdebug();
//	void stopdebug();
	void emitsignals(const QString& data);
	void stopTimer();
	void on_btnSendAll_clicked();

	void on_btnSendcycle_clicked();

	void on_comboBox_currentIndexChanged(int index);

	void on_Cb_recv_stateChanged(int arg1);

	void on_timeinterval_textChanged(const QString& arg1);

	void on_checkBox_stateChanged(int arg1);

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_btnopenfile_clicked();

	void on_btnsendfile_clicked();

//	void on_pushButton_start_clicked();

//	void on_pushButton_sendasdu_clicked();

	void on_pushButton_send1_clicked();

	void on_pushButton_send2_clicked();

	void on_pushButton_send3_clicked();

	void on_pushButton_send4_clicked();


	void on_pushButton_send5_clicked();

	void on_pushButton_send6_clicked();

	void on_pushButton_send7_clicked();

	void on_pushButton_send8_clicked();

	void on_pushButton_send9_clicked();

	void on_pushButton_send10_clicked();

private:
	Ui::DialogSendData *ui;
};

#endif // DIALOGSENDDATA_H
