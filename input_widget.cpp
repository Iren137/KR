#include "input_widget.h"

InputWidget::InputWidget(QWidget* parent) : QWidget(parent) {
  layout.addWidget(&text_edit);
}
