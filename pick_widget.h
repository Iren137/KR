#ifndef PICK_WIDGET_H
#define PICK_WIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>

class PickWidget : public QWidget {
 public:
  PickWidget(QWidget* parent);
  void SetAllUnchecked();
  QRadioButton variant0_{this};
  QRadioButton variant1_{this};
  QRadioButton variant2_{this};
  QButtonGroup button_group_{this};
  QGridLayout layout_{this};
};

#endif //PICK_WIDGET_H
