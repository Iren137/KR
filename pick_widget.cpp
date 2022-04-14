#include "pick_widget.h"

PickWidget::PickWidget(QWidget* parent) : QWidget(parent) {
  button_group_.addButton(&variant0_, 0);
  button_group_.addButton(&variant1_, 1);
  button_group_.addButton(&variant2_, 2);
  layout_.addWidget(&variant0_);
  layout_.addWidget(&variant1_);
  layout_.addWidget(&variant2_);
}

void PickWidget::SetAllUnchecked() {
  button_group_.setExclusive(false);
  variant0_.setChecked(false);
  variant1_.setChecked(false);
  variant2_.setChecked(false);
  button_group_.setExclusive(true);
}
