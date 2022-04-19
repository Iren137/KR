#include "exercise_page.h"
#include "controller.h"
#include "main_page.h"
#include <QMovie>
#include <QLabel>

ExercisePage::ExercisePage(QWidget* parent) : QWidget(parent) {
  layout_.addWidget(&progress_bar,0,0,1,1);
  layout_.addWidget(&text,1,0,1,1 ,Qt::AlignCenter);
  layout_.addWidget(&slides,2,0,1,1);
  layout_.setRowStretch(3,1);
  layout_.setRowStretch(4,1);
  layout_.addWidget(&submit,3,0, 1,1, Qt::AlignTop);
  layout_.addWidget(&attempts_remaining,4,0,1,1);
  layout_.addWidget(&to_main_page_button,5,0,1,1);

  SetStyle();

  slides.addWidget(pick_widget);
  slides.addWidget(input_widget);
  slides.addWidget(audio_widget);

  progress_bar.setRange(0, 100);
  progress_bar.setValue(0);

  connect(&submit, SIGNAL(clicked(bool)), this->parent(), SLOT(SubmitPressed()));
  connect(&to_main_page_button, SIGNAL(clicked(bool)), this->parent(), SLOT(SwitchToMainPage()));
}

void ExercisePage::ChangeAttemptsLabel(int new_val) {
  attempts_remaining.setText("Lives remaining: " + QString::number(new_val));
}

void ExercisePage::SetStyle() {
  text.setFont(QFont("Ubuntu", 17));
  attempts_remaining.setFont(QFont("Ubuntu", 14));
  submit.setFont(QFont("Ubuntu", 15));
  to_main_page_button.setFont(QFont("Ubuntu", 15));
  submit.setStyleSheet("QPushButton {background-color: green}");
  to_main_page_button.setStyleSheet("QPushButton {background-color: red}");
}
