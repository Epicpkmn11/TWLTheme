#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QGraphicsScene>
#include <QLabel>
#include <QMainWindow>
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void handleBgButtonBottom(void);
	void handleBgButtonTop(void);
	void handleIconButtonBattery(void);
	void handleSaveButton(void);
	void loadBg(QGraphicsView *graphicsView, QPixmap &image);
	void save(void);

private:
	Ui::MainWindow *ui;
	QPixmap bottomBgPixmap;
	QPixmap topBgPixmap;
	QPixmap iconBatteryPixmap;
	QImage *imageObject;
	QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
