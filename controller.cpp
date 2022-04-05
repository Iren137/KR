#include "main_page.h"
#include "controller.h"
#include "pick_exercise_widget.h"
#include <iostream>

Controller::Controller()
    : main_page_(new MainPage(this)),
      pick_exercise_widget(new PickExerciseWidget(this)) {
  addWidget(main_page_);
  addWidget(pick_exercise_widget);

  movie_label.setMovie(&movie);
  movie.start();
  QGridLayout* movie_msg_layout{new QGridLayout(&movie_dialog)};
  movie_msg_layout->addWidget(&win_label, 0, 0, Qt::AlignCenter);
  movie_msg_layout->addWidget(&movie_label, 1, 0, Qt::AlignCenter);
  movie_msg_layout->addWidget(&leave_movie_dialog_button, 2, 0, Qt::AlignCenter);

  no_attempts_message.setText("You have used all your attempts :(");

  connect(&leave_movie_dialog_button, SIGNAL(clicked(bool)),
          this, SLOT(FinishMovieDialog()));
  connect(&movie_dialog, SIGNAL(finished(int)), this, SLOT(SwitchToMainPage()));
  connect(&no_attempts_message, SIGNAL(finished(int)), this, SLOT(SwitchToMainPage()));

  setCurrentWidget(main_page_);
  main_page_->setMinimumSize(300, 300);
}

void Controller::StartPickExercises() {
  std::vector<int> indexes{};
  indexes.reserve(pack_of_exercises_size_);
  for (int i = 0; i < pack_of_exercises_size_; i++) {
    indexes.push_back(model_.pick_random.Generate());
    model_.pick_random.Delete(indexes.back());
  }
  for (int i = 0; i < pack_of_exercises_size_; i++) {
    model_.pick_random.Add(indexes[i]);
  }
  pick_exercise_widget->exercises.resize(pack_of_exercises_size_);
  for (int i = 0; i < pack_of_exercises_size_; i++) {
    pick_exercise_widget->exercises[i] = &model_.pick_exercises_[indexes[i]];
  }
  setCurrentWidget(pick_exercise_widget);
  pick_exercise_widget->attempts_left = difficulty == easy ? 3 : 1;
  pick_exercise_widget->Start();
}

void Controller::IncreaseScoreBy(int diff) {

}

void Controller::SwitchToMainPage() {
  setCurrentWidget(main_page_);
}

void Controller::FinishMovieDialog() {
  movie_dialog.close();
}