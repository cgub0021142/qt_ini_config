#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#include <QtGui/QWidget>
#include <qsettings.h>
#include <qstring.h>
#include "ui_ini_config.h"
#include <qfiledialog.h>
#include <qdir.h>

#include <iostream>
#include <string>
#include <fstream>

class ini_config : public QWidget
{
	Q_OBJECT

public:
	ini_config(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ini_config();
protected:
	void closeEvent(QCloseEvent *event);
private:
	Ui::ini_configClass ui;
	QSettings *ini_file;
	QString file_path;
	QString file_rfport_path;
	void check_back_slash(std::string path);
	//rf port
	QStringList read_in_array;
	bool found_line_num;
	int setting_line_at;
	int insert_posi;
	QString JLinkArmDllPath;
	QStringList info;

private slots:
	void on_o_JLinkArmDllPath_clicked();
	void on_o_DTM_FW_clicked();
	void on_o_Product_FW_clicked();
	void on_btn_save_settings_clicked();
};

#endif // INI_CONFIG_H
