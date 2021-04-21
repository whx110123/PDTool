#ifndef FRMLOG_H
#define FRMLOG_H

#include <QWidget>

namespace Ui {
class frmLog;
}

class frmLog : public QWidget
{
	Q_OBJECT

public:
	explicit frmLog(QWidget *parent = nullptr);
	~frmLog();

private:
	Ui::frmLog *ui;
};

#endif // FRMLOG_H
