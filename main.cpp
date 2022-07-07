#include <QApplication>
#include <QPushButton>

#include "controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  Controller window{};
  window.setWindowTitle("Learn With Me!");
  window.setWindowIcon(QIcon(":/icon.png"));
  window.show();
  return QApplication::exec();
}
