#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QGridLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QMovie>
#include <QMessageBox>
#include <QSettings>

#include "input_exercise.h"
#include "pick_exercise.h"
#include "model.h"
#include "randomizer.h"

class MainPage;
class ExercisePage;

class Controller : public QStackedWidget {
  Q_OBJECT
 public:
  Controller();
  void IncreaseScoreBy(int diff);
  QString Trimmed(QString str);

 public slots:
  void StartPickExercises();
  void StartInputExercises();
  void StartAudioExercises();
  void StartMixedExercises();
  void PlayExerciseAudio();
  void DifficultyChanged();
  void SoundChanged();
  void AnswerIfSureToLeave();
  void ProcessCloseDialogButtonClick(QAbstractButton *);
  void ResetScore();

  void SwitchToMainPage();
  void FinishMovieDialog();
  void StartExercises(ExerciseType type);
  void NextExercise();
  void SubmitPressed();
  void PlaySound(int id);
  void CheckAnswerCorrectness(const QString& input, const QString& correct);

 private:

  std::vector<Exercise*> exercises{};
  QMessageBox reply_message{this};
  int amount_of_correct{};
  int attempts_left{};

  MainPage* main_page_;
  Model model_{};

  ExercisePage* exercise_page{};

  const int pack_of_exercises_size_ = 5;

  QDialog movie_dialog{this};
  QMovie movie{":/minions.gif"};
  QLabel movie_label{&movie_dialog};
  QLabel win_label{&movie_dialog};

  QPushButton leave_movie_dialog_button{"Ok", &movie_dialog};

  QMessageBox no_attempts_message{this};
  QSettings setting{};

  QMessageBox close_dialog{this};
};

#endif //CONTROLLER_H
