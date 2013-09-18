#include <QApplication>
#include <QPushButton>
int main(int argc, char **argv){
	QApplication app(argc,argv);
	QPushButton buttom("Hello world!");
	buttom.show();
	return app.exec();
}
