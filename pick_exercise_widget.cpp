#include "pick_exercise_widget.h"
#include "controller.h"
#include "main_page.h"
#include <QMovie>
#include <QLabel>
#include <iostream>

PickExerciseWidget::PickExerciseWidget(QWidget* parent) : QWidget(parent) {
  layout_.addWidget(&variant1_);
  layout_.addWidget(&variant2_);
  layout_.addWidget(&variant3_);
  layout_.addWidget(&text);
  layout_.addWidget(&submit);

  button_group_.addButton(&variant1_, 1);
  button_group_.addButton(&variant2_, 2);
  button_group_.addButton(&variant3_, 3);

  connect(&submit, SIGNAL(clicked(bool)), this, SLOT(ShowReplyMessage()));
  connect(&reply_message, SIGNAL(finished(int)), this, SLOT(NextExercise()));
}

void PickExerciseWidget::Start() {
  amount_of_correct = 0;
  NextExercise();
}

void PickExerciseWidget::ShowReplyMessage() {
  if (button_group_.checkedId() == -1) {
    return;
  }
  PickExercise* cur_exercise = exercises.back();
  if (cur_exercise->correct_answer == button_group_.checkedId()) {
    amount_of_correct++;
    reply_message.setText("Correct!");
  } else {
    attempts_left--;
    reply_message.setText("Incorrect!\nThe number of correct answer is " +
        QString::number(cur_exercise->correct_answer) + ".");
  }
  exercises.pop_back();
  reply_message.open();
}

void PickExerciseWidget::NextExercise() {
  if (attempts_left == 0) {
    dynamic_cast<Controller*>(this->parent())->no_attempts_message.open();
    return;
  }
  if (!exercises.empty()) {
    PickExercise* cur_exercise = exercises.back();
    text.setText(cur_exercise->text);
    variant1_.setText(cur_exercise->answer1);
    variant2_.setText(cur_exercise->answer2);
    variant3_.setText(cur_exercise->answer3);
    return;
  }
  auto controller = dynamic_cast<Controller*>(this->parent());
  int score_diff = (controller->difficulty == easy ?
                    amount_of_correct : 2 * amount_of_correct);
  controller->IncreaseScoreBy(score_diff);
  controller->win_label.setText("You've passed this set of exercises!\nYou get " +
      QString::number(score_diff) + (score_diff == 1 ? " point." : " points."));
  controller->movie_dialog.open();
}
