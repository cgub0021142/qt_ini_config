#include "password.h"
#include "ini_config.h"

Password::Password(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	file = new QSettings(".\\ADMFG_Configure\\ADMFG_Configure.ini", QSettings::IniFormat);
	pwd = file->value("Password/pwd", "admin").toString();

}

Password::~Password()
{

}
void Password::on_btn_pwd_clicked(){
	pwd_input = ui.e_pwd->text();
	if(pwd == pwd_input){
		ini_config *w;
		w = new ini_config();
		w->show();
		this->close();
	}
	else{
		ui.l_log->setText("<font color = red> Not correct. </font>");
	}
}
