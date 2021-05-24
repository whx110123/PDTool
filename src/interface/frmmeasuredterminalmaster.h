#ifndef FRMMEASUREDTERMINALMASTER_H
#define FRMMEASUREDTERMINALMASTER_H

#include <QWidget>
#include <managermtmaster.h>
#include <mybase.h>

namespace Ui
{
class frmMeasuredTerminalMaster;
}

class frmMeasuredTerminalMaster : public QWidget
{
	Q_OBJECT

public:
	explicit frmMeasuredTerminalMaster(QWidget *parent = nullptr);
	~frmMeasuredTerminalMaster();
private:
	void initfrm();
	void init();
	void initConfig();

signals:
	void ToTcpClient(const QString& data);
	void ToTcpServer(const QString& data);
	void ToUdpClient(const QString& data);
	void ToUdpServer(const QString& data);
	void ToCom(const QString& data);
	void toLog(const MyLog& log);

public slots:
	void dealRcvData(const QString& data, const QString& title);
private slots:
	void sendData(const QByteArray& data);
	void startdebug();
	void stopdebug();
	void handleLog(MyLog& log);
	void emitsignals(const QString& data);

	void on_pushButton_startdebug_clicked();

	void on_pushButton_MTstart_clicked();

	void on_pushButton_MTread1_clicked();

	void on_pushButton_MTread2_clicked();

	void on_pushButton_MTreaddata_clicked();

	void on_pushButton_MTreadhisdata_clicked();

private:
	Ui::frmMeasuredTerminalMaster *ui;
	ManagerMTMaster *manager;
	ConfigMTMaster managerConfig;		//参数配置
	MyConfig myConfig;						//报文格式
};

#endif // FRMMEASUREDTERMINALMASTER_H
