#include "mainwindow.h"

#include <QApplication>

//добавить , фотография из слов

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
