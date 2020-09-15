#ifndef PASSWORD_H
#define PASSWORD_H

#include <QWidget>
#include "ui_password.h"
#include <qsettings.h>

class Password : public QWidget
{
	Q_OBJECT

public:
	Password(QWidget *parent = 0);
	~Password();

private:
	Ui::Password ui;
	QSettings *file;
	QString pwd;
	QString pwd_input;
private slots:
	void on_btn_pwd_clicked();
};

#endif // PASSWORD_H
