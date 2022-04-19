#include "input_widget.h"

InputWidget::InputWidget(QWidget* parent) : QWidget(parent) {
  layout.addWidget(&text_edit);
  text_edit.setFont(QFont("Ubuntu", 15));
}
