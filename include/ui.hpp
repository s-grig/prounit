#ifndef menu_hpp
#define menu_hpp
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QObject>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <iostream>
#include <drawer.hpp>
#include <QMessageBox>
#include <QApplication>

class Win : public QWidget {
	Q_OBJECT
public:
	Win(QWidget* parent = 0);
	QString get_path();
	void set_path(const QString& path_);
	void photo_processing();
	void error_occured();
	bool is_error();
	std::pair<std::vector<double>, std::vector<double>> get_data();
public slots:
	void clicked_choose();
private:
	QLabel* label;
	QPushButton* exitButton;
	QPushButton* chooseButton;
	QString path;
	bool error = false;
	std::pair<std::vector<double>, std::vector<double>> data;
};

class AnotherWin : public QDialog {
	Q_OBJECT
public:
	AnotherWin(QWidget* parent = 0);
public slots:
	void clicked_linear();
	void clicked_log();
	void set_data(const std::pair<std::vector<double>, std::vector<double>>& data1);
private:
	QLabel* label1;
	QPushButton* linearButton;
	QPushButton* logButton;
	std::pair<std::vector<double>, std::vector<double>> data_;
};

#endif
