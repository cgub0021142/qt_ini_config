#include "ini_config.h"
#include <QtGui/QApplication>
#include "password.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//ini_config w;
	//w.hide();

	Password gui_pwd;
	gui_pwd.show();


	return a.exec();
}
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/ini_parser.hpp>
//
//void save(const std::string &filename)
//{
//   using boost::property_tree::ptree;
//
//	//   pt.put("a.path.to.float.value", 3.14f);
//	//   pt.put("a.path.to.float.value", 2.72f);
//	//   pt.add("a.path.to.float.value", 3.14f);
//
//	//ptree pt;
//	//pt.put("a.value", 3.14f);
//	//// Overwrites the value
//	//pt.put("a.value", 2.72f);
//	//// Adds a second node with the new value.
//	//pt.add("a.bvalue", 3.14159f);
//
//	//write_ini( filename, pt );
//
//
//	ptree pt2;
//	boost::property_tree::ini_parser::read_ini(filename, pt2);
//	float f1 = pt2.get<float>("a.value") ;
//	//std::cout << pt.get<std::string>("Section1.Value2") << std::endl;
//
//	pt2.put("a.value", 2.72f);
//	pt2.add("a.bvalue", 3.14159f);
//	write_ini( "test2.ini", pt2 );
//
//	//write_ini( filename, pt );
//}
//
//int main()
//{
//    std::string f( "test.ini" );
//    save( f );
//}


//#include <iostream>
//#include <string>
//#include <fstream>
//
//
//using namespace std;
//int main() 
//{
//
//    ifstream lire("ADMFG_Configure\\ADMFG_Configure.ini",ios::in);
//	string tmp;
//    string text ;
//
//    while(!lire.eof()){
//		getline(lire,tmp);
//		for (int i = 0 ; i < tmp.size();i++) 
//		{
//			if(tmp[i] == '\\')
//			{
//				tmp.insert(i,"\\") ;
//				i++;
//			}
//		}
//		text.append(tmp);
//		text.append("\n");
//	}
//
//return  0;
//}
//
