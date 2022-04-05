#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QGridLayout>
#include <QStackedWidget>
#include <QPushButton>
#include "input_exercise.h"
#include "pick_exercise.h"
#include "model.h"
#include "randomizer.h"
#include <QLabel>
#include <QDialog>
#include <QMovie>
#include <QMessageBox>

class MainPage;
class PickExerciseWidget;

enum Difficulty {
  easy,
  hard
};

class Controller : public QStackedWidget {
  Q_OBJECT
 public:
  Controller();
  void IncreaseScoreBy(int diff);

 public slots:
  void StartPickExercises();
  void SwitchToMainPage();
  void FinishMovieDialog();

 private:
  MainPage* main_page_;
  Model model_{};

  PickExerciseWidget* pick_exercise_widget{};

  const int pack_of_exercises_size_ = 1;

  Difficulty difficulty = easy;

  int score = 0;

  QDialog movie_dialog{this};
  QMovie movie{":/minions.gif"};
  QLabel movie_label{&movie_dialog};
  QLabel win_label{&movie_dialog};

  QPushButton leave_movie_dialog_button{"Ok", &movie_dialog};

  QMessageBox no_attempts_message{this};

  friend class PickExerciseWidget;
};

#endif //CONTROLLER_H
