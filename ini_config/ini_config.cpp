#include "ini_config.h"
#include <qdebug.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <QCloseEvent>
ini_config::ini_config(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags),
	file_path("./ADMFG_Configure/ADMFG_Configure.ini"),
	file_rfport_path("./BT_Profile.ini")
{
	ui.setupUi(this);
	check_back_slash(file_path.toStdString());
	ini_file = new QSettings( file_path, QSettings::IniFormat);
	//ini_file->setIniCodec( "ISO 8859-1");
	qDebug()<<ini_file->iniCodec();
	ini_file->beginGroup("GeneralSetting");
	ui.e_TesterID->setText(ini_file->value("TesterID", "no data").toString());
	ini_file->endGroup();


	ini_file->beginGroup("MESSetting");
	int i = ini_file->value("Enable", "no data").toInt();
	ui.cbo_Enable->setCurrentIndex(ini_file->value("Enable", "no data").toInt());
	ui.e_MES_IP->setText(ini_file->value("MES_IP", "no data").toString());
	ui.e_MES_Uname->setText(ini_file->value("MES_Uname", "no data").toString());
	ui.e_MES_Upass->setText(ini_file->value("MES_Upass", "no data").toString());
	ui.e_MES_Station_Num->setText(ini_file->value("MES_Station_Num", "no data").toString());
	ui.e_MES_Machine_Num->setText(ini_file->value("MES_Machine_Num", "no data").toString());
	ui.e_MES_Mo_Num->setText(ini_file->value("MES_Mo_Num", "no data").toString());
	ui.e_MES_PrjID->setText(ini_file->value("MES_PrjID", "no data").toString());
	ui.e_MES_MAC_Begin->setText(ini_file->value("MES_MAC_Begin", "no data").toString());
	ui.e_MES_MAC_End->setText(ini_file->value("MES_MAC_End", "no data").toString());
	ini_file->endGroup();

	ini_file->beginGroup("DUT_BT_nRF52840");
	QString power_type =ini_file->value("PowerType", "no data").toString();
	if(power_type == "UART")
		ui.cbo_PowerType->setCurrentIndex(1);
	else if(power_type == "LAN")
		ui.cbo_PowerType->setCurrentIndex(0);
	else
		ui.cbo_PowerType->setCurrentIndex(-1);



	ui.cbo_PowerLanChannel->setCurrentIndex(ini_file->value("PowerLanChannel", "no data").toInt() - 1);
	ui.e_PowerLanIP_CH1->setText(ini_file->value("PowerLanIP_CH1", "no data").toString());
	ui.e_PowerLanIP_CH2->setText(ini_file->value("PowerLanIP_CH2", "no data").toString());
	ui.e_PowerLanPort_CH1->setText(ini_file->value("PowerLanPort_CH1", "no data").toString());
	ui.e_PowerLanPort_CH2->setText(ini_file->value("PowerLanPort_CH2", "no data").toString());
	ui.e_PowerCurrentMin->setText(ini_file->value("PowerCurrentMin", "no data").toString());
	ui.e_PowerCurrentMax->setText(ini_file->value("PowerCurrentMax", "no data").toString());
	ui.e_PowerVoltage->setText(ini_file->value("PowerVoltage", "no data").toString());
	ui.e_PowerCurrent->setText(ini_file->value("PowerCurrent", "no data").toString());
	ui.e_JLinkArmDllPath->setText(ini_file->value("JLinkArmDllPath", "no data").toString());
	ui.e_DTM_FW->setText(ini_file->value("DTM_FW", "no data").toString());
	ui.e_Product_FW->setText(ini_file->value("Product_FW", "no data").toString());

	ini_file->endGroup();
	delete ini_file;

	//get rf port
	QFile file_rf_port(file_rfport_path);
	if( !file_rf_port.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qFatal("******File can not open.******");
	}
	else{
		QTextStream in(&file_rf_port);
		//find out the line number where record rf port

		found_line_num = false;
		for(int idx = 0; !in.atEnd(); idx++){
			read_in_array<< in.readLine();
			if(!found_line_num && 
				!read_in_array[idx].compare("###General") ){
					while(!in.atEnd()){
						read_in_array<< in.readLine();
						++idx;
						qDebug()<<read_in_array[idx][0];
						if(read_in_array[idx][0] =='#' || read_in_array[idx].count(",") != 5)
							continue;
						setting_line_at = idx;
						found_line_num = true;
						break;
					}
			}
		}		
		if( !found_line_num ){
			qFatal("Can't find the data which format should be five comma and six number.");
		}
		//QFile::remove(backup_file_name);
		//file.copy(backup_file_name);

		//get the original setting
		//get the position
		insert_posi = read_in_array[setting_line_at].lastIndexOf(',') + 1;
		QString before = read_in_array[setting_line_at].mid(insert_posi);
		ui.cbo_rfport->setCurrentIndex(before.toInt() - 1);
		

	}
	file_rf_port.close();

}

ini_config::~ini_config()
{
}

void ini_config::closeEvent(QCloseEvent *event)
 {


        event->accept();

 }

void ini_config::on_o_JLinkArmDllPath_clicked(){
	//ui.e_JLinkArmDllPath->setText(
	//	QFileDialog::getOpenFileName(this, "", "C:\\Program Files (x86)", "dll (*.dll)"));
	//ini_file->setValue("DUT_BT_nRF52840/JLinkArmDllPath", ui.e_DTM_FW->text());
	QString absolute_path = QFileDialog::getOpenFileName(this, "", "C:\\Program Files (x86)", "dll (*.dll)");
	if (!absolute_path.isEmpty())
		ui.e_JLinkArmDllPath->setText(absolute_path);
}

void ini_config::on_o_DTM_FW_clicked(){
	QDir path( ".\\");
	QString relative_path = path.relativeFilePath(QFileDialog::getOpenFileName(this, "", ".\\", "firmware file (*.hex *.bin)"));
	if (!relative_path.isEmpty())
		ui.e_DTM_FW->setText(relative_path);
}

void ini_config::on_o_Product_FW_clicked(){
	QDir path( ".\\");
	QString relative_path = path.relativeFilePath(QFileDialog::getOpenFileName(this, "", ".\\",  "firmware file (*.hex *.bin)"));
	if (!relative_path.isEmpty())
		ui.e_DTM_FW->setText(relative_path);
}

void ini_config::on_btn_save_settings_clicked(){

	ini_file = new QSettings( file_path, QSettings::IniFormat);

	ini_file->beginGroup("GeneralSetting");
	ini_file->setValue("TesterID", ui.e_TesterID->text());
	ini_file->endGroup();

	ini_file->beginGroup("MESSetting");
	int enable_index = ui.cbo_Enable->currentIndex();
	if( enable_index == 0 || enable_index == 1)
		ini_file->setValue("Enable", enable_index);
	ini_file->setValue("MES_IP", ui.e_MES_IP->text());
	ini_file->setValue("MES_Uname", ui.e_MES_Uname->text());
	ini_file->setValue("MES_Upass", ui.e_MES_Upass->text());
	ini_file->setValue("MES_Station_Num", ui.e_MES_Station_Num->text());
	ini_file->setValue("MES_Machine_Num", ui.e_MES_Machine_Num->text());
	ini_file->setValue("MES_Mo_Num", ui.e_MES_Mo_Num->text());
	ini_file->setValue("MES_PrjID", ui.e_MES_PrjID->text());
	ini_file->setValue("MES_MAC_Begin", ui.e_MES_MAC_Begin->text());
	ini_file->setValue("MES_MAC_End", ui.e_MES_MAC_End->text());
	ini_file->endGroup();

	int powerType_idx = ui.cbo_PowerType->currentIndex();
	switch( powerType_idx){
	case 0:
		ini_file->setValue("DUT_BT_nRF52840/PowerType", "LAN");
		break;
	case 1:
		ini_file->setValue("DUT_BT_nRF52840/PowerType", "UART");
		break;
	}

	ini_file->setValue("DUT_BT_nRF52840/PowerLanChannel", ui.cbo_PowerLanChannel->currentIndex() + 1);
	ini_file->setValue("DUT_BT_nRF52840/PowerLanIP_CH1", ui.e_PowerLanIP_CH1->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerLanIP_CH2", ui.e_PowerLanIP_CH2->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerLanPort_CH1", ui.e_PowerLanPort_CH1->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerLanPort_CH2", ui.e_PowerLanPort_CH2->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerCurrentMin", ui.e_PowerCurrentMin->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerCurrentMax", ui.e_PowerCurrentMax->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerVoltage", ui.e_PowerVoltage->text());
	ini_file->setValue("DUT_BT_nRF52840/PowerCurrent", ui.e_PowerCurrent->text());
	ini_file->setValue("DUT_BT_nRF52840/JLinkArmDllPath", ui.e_JLinkArmDllPath->text());
	ini_file->setValue("DUT_BT_nRF52840/DTM_FW", ui.e_DTM_FW->text());
	ini_file->setValue("DUT_BT_nRF52840/Product_FW", ui.e_Product_FW->text());

	delete ini_file;

	//change %23 to # cause by ini destructor
	QString read_in_data;
    QFile file(file_path);
    if( !file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug()<<"file can not open.";
    }
    else{
        QTextStream in(&file);
        read_in_data = in.readAll();
		//while(!in.atEnd()){
		//	read_in_data += in.readLine() + "\n";
		//}
		read_in_data.replace("%23","#");
		int last_new_line_posi = read_in_data.lastIndexOf('\n');
		read_in_data.remove(last_new_line_posi, 1);
        file.close();
		qDebug()<<"Change %23 back to # now save in tmp buffer";
	}
	QFile rewrite(file_path);
	rewrite.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
	QTextStream out(&rewrite);
	out<<read_in_data;
	rewrite.close();

	//save rf port
	QString port = ui.cbo_rfport->currentText();
	read_in_array[setting_line_at] = read_in_array[setting_line_at].mid(0,insert_posi) + port;
	QFile file_rf_port(file_rfport_path);
	if( !file_rf_port.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
		qFatal("******File can not open.******");
	}
	else{
		QTextStream out(&file_rf_port);
		QList<QString>::const_iterator i;
		for(i = read_in_array.constBegin(); i < read_in_array.constEnd() -1; ++i){
			out<< *i + "\n";
		}
		out<< *i;//last line can't have new line.
	}
	file.close();


	//log
	QMessageBox msg_box;
	msg_box.setWindowTitle(" ");
	msg_box.setText("<font size = 20 >Save completed. </font>");
	msg_box.setIcon(QMessageBox::Information);
	msg_box.setStandardButtons(QMessageBox::Ok);
	QTimer::singleShot(1500, &msg_box,SLOT(close()));
	msg_box.exec();

}

void ini_config::check_back_slash(std::string path){
	//using namespace std;
	//ifstream in( path, ios::in);
	//string tmp;
 //   string text ;
	//getline(in,tmp);
	////remove all before[  due to utf-8 codec cause error "ef bb bf"
	////int start_at = tmp.find("[");
	////text.append(tmp.substr(start_at));
 //   while(!in.eof()){
	//	getline(in,tmp);
	//	for (int i = 0 ; i < tmp.size();i++) 
	//	{
	//		if(tmp[i] == '\\')
	//		{
	//			tmp[i] = '/' ;
	//		}
	//	}
	//	text.append(tmp);
	//	text.append("\n");
	//}
	//text.erase(text.length()-1);
	//
	//ofstream out( path, ios::out);
	//out<< text;
	//remove the bom of utf8 and transform the \ to /
	QFile file(file_path);
	file.open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream in(&file);
    QString read_in_data = in.readAll();
	read_in_data.replace(QString("\\"), QString("/"));
	file.close();
	QFile file_out(file_path);
	file_out.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file_out);
	out<< read_in_data;
	file_out.close();
}