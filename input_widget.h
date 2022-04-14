#ifndef INPUT_WIDGET_H
#define INPUT_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>

class InputWidget : public QWidget {
 public:
  InputWidget(QWidget* parent);

  QTextEdit text_edit{this};
  QGridLayout layout{this};


};

#endif //INPUT_WIDGET_H
