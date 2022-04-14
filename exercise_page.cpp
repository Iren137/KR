#include "exercise_page.h"
#include "controller.h"
#include "main_page.h"
#include <QMovie>
#include <QLabel>
#include <iostream>

ExercisePage::ExercisePage(QWidget* parent) : QWidget(parent) {
  layout_.addWidget(&text);
  layout_.addWidget(&slides);
  layout_.addWidget(&submit);
  layout_.addWidget(&progress_bar);
  layout_.addWidget(&attempts_remaining);
  layout_.addWidget(&to_main_page_button);

  slides.addWidget(pick_widget);
  slides.addWidget(input_widget);
  slides.addWidget(audio_widget);

  progress_bar.setRange(0, 100);
  progress_bar.setValue(0);

  connect(&submit, SIGNAL(clicked(bool)), this->parent(), SLOT(SubmitPressed()));
  connect(&to_main_page_button, SIGNAL(clicked(bool)), this->parent(), SLOT(SwitchToMainPage()));
}

void ExercisePage::ChangeAttemptsLabel(int new_val) {
  attempts_remaining.setText("Attempts remaining: " + QString::number(new_val));
}
