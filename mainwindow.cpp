#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "glwidget.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
	if(event->key() == Qt::Key_A) show_axis = !show_axis;
	if(event->key() == Qt::Key_G) show_grid = !show_grid;
	if(event->key() == Qt::Key_W) show_wave = !show_wave;
	if(event->key() == Qt::Key_U) cam_radius += 0.2;
	if(event->key() == Qt::Key_O) cam_radius -= 0.2;
	if(event->key() == Qt::Key_L) rotate_y += 5;
	if(event->key() == Qt::Key_J) rotate_y -= 5;
	if(event->key() == Qt::Key_K) rotate_x += 5;
	if(event->key() == Qt::Key_I) rotate_x -= 5;
    ui->glwidget->updateGL();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
	ui->glwidget->open_graphic(QFileDialog::getOpenFileName().toStdString());
}
