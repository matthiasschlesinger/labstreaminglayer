/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** Author: Matthias Schlesinger @ Graz, University of Technology
** Year: 11/2015
** -------------------------------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <vector>

// LSL API
#include <lsl_cpp.h>

// eegoSports
#define WIN32_LEAN_AND_MEAN
#define EEGO_SDK_BIND_STATIC
#include <windows.h>
#include <../eemagine/sdk/factory.h>


namespace Ui {
	class MainWindow;
}

class Reader : public QObject {
	Q_OBJECT

public:
	Reader();
	~Reader();

	public slots:
	void read();
	void setStop(bool stop) {
		this->stop = stop;
	}
	void setParams(int samplingRate);

signals:
	void finished();
	void errorMsg(QString err);
	void timeout();

private:
	eemagine::sdk::amplifier* amp;
	eemagine::sdk::stream* eegStream;
	int samplingRate;
	bool stop = false;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent, const std::string &config_file, const bool linkOnStart);
	~MainWindow();

	private slots:
	void threadFinished();
	void threadTimeout();
	void threadError(QString message);
	void load_config_dialog();
	void save_config_dialog();

	void link();

	// close event (potentially disabled)
	void closeEvent(QCloseEvent *ev);
private:
	// raw config file IO
	void load_config(const std::string &filename);
	void save_config(const std::string &filename);

	eemagine::sdk::amplifier* amp; 
	eemagine::sdk::stream* eegStream;
	Reader *reader = NULL;
	QThread *thread;

	Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
