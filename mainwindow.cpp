#include <QDebug>
#include <QColor>
#include <QBitmap>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);


	connect(ui->bgButtonBottom, SIGNAL (released()), this, SLOT (handleBgButtonBottom()));
	connect(ui->bgButtonTop, SIGNAL (released()), this, SLOT (handleBgButtonTop()));
	connect(ui->iconButtonBattery, SIGNAL (released()), this, SLOT (handleIconButtonBattery()));
	connect(ui->saveButton, SIGNAL (released()), this, SLOT (handleSaveButton()));
}

MainWindow::~MainWindow() {
	delete ui;
	delete &bottomBgPixmap;
	delete &topBgPixmap;
	delete imageObject;
	delete scene;
}

void MainWindow::handleBgButtonBottom(void) { loadBg(ui->bgViewBottom, bottomBgPixmap); }
void MainWindow::handleBgButtonTop(void) { loadBg(ui->bgViewTop, topBgPixmap); }
void MainWindow::handleIconButtonBattery(void) { loadBg(ui->iconViewBattery, iconBatteryPixmap); }
void MainWindow::handleSaveButton(void) { save(); }

void MainWindow::loadBg(QGraphicsView *graphicsView, QPixmap &image) {
	QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), tr("All Images (*.png *.jpg *jpeg *.bmp);;PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)"));

	if(imagePath != "") {
		imageObject = new QImage();
		imageObject->load(imagePath);

		image = QPixmap::fromImage(*imageObject);

//		image = image.scaled(256, 192);

		image.setMask(image.createMaskFromColor(QColor(255, 0, 255)));

		scene = new QGraphicsScene(this);
		scene->addPixmap(image);
		scene->setSceneRect(image.rect());
		graphicsView->setScene(scene);
	}
}

void MainWindow::save(void) {
	QString path = QFileDialog::getExistingDirectory(this, tr("Select output folder"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));

	if(path != "") {
		if(!QDir(path+"/theme").exists())	QDir().mkdir(path+"/theme");
		if(!QDir(path+"/theme/background_girt").exists())	QDir().mkdir(path+"/theme/background_girt");
		bottomBgPixmap.toImage().save(path+"/theme/background_girt/bottom.png");
		topBgPixmap.toImage().save(path+"/theme/background_girt/top.png");
	}
}
