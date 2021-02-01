#ifndef FRMIEC104MASTER_H
#define FRMIEC104MASTER_H

#include <manageriec104master.h>
#include <mybase.h>

namespace Ui
{
class frmIEC104Master;
}

class frmIEC104Master : public QWidget
{
	Q_OBJECT

public:
	explicit frmIEC104Master(QWidget *parent = nullptr);
	~frmIEC104Master();

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


public slots:
	void dealRcvData(const QString& data, const QString& title);
//	bool createAndSendData(IECDataConfig& config);
private slots:
	void sendData(const QByteArray& data);
	void startdebug();
	void stopdebug();
	void showToText(const QString& data, int type);		//type 0接收 1发送
	void showLog(const QString& data);
	void emitsignals(const QString& data);
	QByteArray getYKYTData(uchar type);

	void on_pushButton_start_clicked();

private:
	Ui::frmIEC104Master *ui;
	ManagerIEC104Master *manager;
	ConfigIEC104Master managerConfig;		//参数配置
	MyConfig myConfig;						//报文格式

};

#endif // FRMIEC104MASTER_H
