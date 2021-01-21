#ifndef FRMIEC104MASTER_H
#define FRMIEC104MASTER_H

#include <QWidget>
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

public slots:
	void dealData(const QString& data, const QString& title);
	bool createAndSendData(IECDataConfig& config);

signals:
	void ToTcpClient(const QString& data);
	void ToTcpServer(const QString& data);
	void ToUdpClient(const QString& data);
	void ToUdpServer(const QString& data);
	void ToCom(const QString& data);

private slots:
	void handleData();
	void startdebug();
	void stopdebug();
	void showToText(QByteArray ba);
	void emitsignals(const QString& data);
	QByteArray getYKYTData(uchar type);

private:
	Ui::frmIEC104Master *ui;
	MyBase *mProtocol;
	MyBase *mProtocolShow;
	IECDataConfig config;
	QTimer *handleDataTimer;
	QByteArray recvData;
	bool haveData;
};

#endif // FRMIEC104MASTER_H
