#include <QApplication>
#include <QPushButton>

#include "controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  Controller window{};
  window.resize(200, 100);
  window.setWindowTitle("Learn With Me!");
  window.show();
  return QApplication::exec();
}
