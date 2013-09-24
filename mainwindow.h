#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
	void keyPressEvent(QKeyEvent* event);

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};

extern double rotate_y;
extern double rotate_x;
extern bool show_axis;
extern bool show_grid;
extern bool show_wave;
extern double cam_radius;

#endif // MAINWINDOW_H
