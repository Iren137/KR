#include <QApplication>
#include <QPushButton>
#include <iostream>

#include "controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  Controller window{};
  window.resize(200, 100);
  window.setWindowTitle("Learn With Me!");
  window.setWindowIcon(QIcon(":/icon.png"));
  window.show();
  return QApplication::exec();
}
