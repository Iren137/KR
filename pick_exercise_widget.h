#ifndef PICK_EXERCISE_WIDGET_H
#define PICK_EXERCISE_WIDGET_H

#include <QRadioButton>
#include <QButtonGroup>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QMovie>
#include "pick_exercise.h"

class PickExerciseWidget : public QWidget {
  Q_OBJECT
 public:
  PickExerciseWidget(QWidget* parent);
  void Start();

 public slots:
  void ShowReplyMessage();
  void NextExercise();

 public:
  QGridLayout layout_{this};

  QLabel text{this};
  QPushButton submit{"Submit", this};

  QRadioButton variant1_{this};
  QRadioButton variant2_{this};
  QRadioButton variant3_{this};
  QButtonGroup button_group_{this};

  std::vector<PickExercise*> exercises{};

  QMessageBox reply_message{this};

  int amount_of_correct{};

  int attempts_left{};
};

#endif //PICK_EXERCISE_WIDGET_H
