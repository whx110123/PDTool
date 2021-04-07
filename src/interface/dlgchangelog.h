#ifndef DLGCHANGELOG_H
#define DLGCHANGELOG_H

#include <QDialog>

namespace Ui {
class DlgChangeLog;
}

class DlgChangeLog : public QDialog
{
	Q_OBJECT

public:
	explicit DlgChangeLog(QWidget *parent = nullptr);
	~DlgChangeLog();

private:
	Ui::DlgChangeLog *ui;
};

#endif // DLGCHANGELOG_H
