/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** Author: Matthias Schlesinger @ Graz, University of Technology
** Year: 11/2015
** -------------------------------------------------------------------------*/
#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <string>
#include <boost/algorithm/string.hpp>

int main(int argc, char *argv[])
{
	std::string config_file = "eegosport_config.cfg";
	bool link = false;

	for (int k = 1; k<argc; k++) {
		if (std::string(argv[k]) == "-c" || std::string(argv[k]) == "--config")
			config_file = argv[k + 1];
		if (std::string(argv[k]) == "-l" || std::string(argv[k]) == "--link")
			link = std::string(argv[k + 1]) == "0" ? false : true;

	}

	QApplication a(argc, argv);
	MainWindow w(0, config_file, link);

	w.show();


	return a.exec();
}
