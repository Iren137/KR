#include <QMediaContent>
#include <QApplication>
#include <QShortcut>

#include "main_page.h"
#include "controller.h"
#include "exercise_page.h"

Controller::Controller()
    : main_page_(new MainPage(this)),
      exercise_page(new ExercisePage(this)) {
  resize(700, 500);
  setMinimumSize(650,400);

  setObjectName("Whole");
  setStyleSheet(
      "#Whole { background-color : rgba(190, 230, 200, 250) } ");

  setting.setValue("difficulty", setting.value("difficulty", "easy"));
  setting.setValue("sound", setting.value("sound", "on"));
  setting.setValue("score", setting.value("score", 0));

  main_page_->SetScoreLabel(setting.value("score").toInt());
  main_page_->difficulty_widget.setCurrentIndex(
      setting.value("difficulty") == "easy" ? 0 : 1);
  main_page_->sound_widget.setCurrentIndex(
      setting.value("sound") == "on" ? 0 : 1);

  addWidget(main_page_);
  addWidget(exercise_page);

  movie_label.setMovie(&movie);
  movie.start();
  QGridLayout* movie_msg_layout{new QGridLayout(&movie_dialog)};
  movie_msg_layout->addWidget(&win_label, 0, 0, Qt::AlignCenter);
  movie_msg_layout->addWidget(&movie_label, 1, 0, Qt::AlignCenter);
  movie_msg_layout->addWidget(&leave_movie_dialog_button, 2, 0, Qt::AlignCenter);

  no_attempts_message.setText("You have used all your lives :(");

  close_dialog.setWindowTitle("Are you sure?");
  close_dialog.setText("Are you sure to close the app?");
  close_dialog.addButton("Yes", QMessageBox::YesRole);
  close_dialog.addButton("No", QMessageBox::NoRole);

  new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q),
                this, SLOT(AnswerIfSureToLeave()));

  connect(&close_dialog, SIGNAL(buttonClicked(QAbstractButton *)),
          this, SLOT(ProcessCloseDialogButtonClick(QAbstractButton *)));
  connect(&reply_message, SIGNAL(finished(int)), this, SLOT(NextExercise()));
  connect(&leave_movie_dialog_button, SIGNAL(clicked(bool)),
          this, SLOT(FinishMovieDialog()));
  connect(&movie_dialog, SIGNAL(finished(int)), this, SLOT(SwitchToMainPage()));
  connect(&no_attempts_message, SIGNAL(finished(int)), this, SLOT(SwitchToMainPage()));

  setCurrentWidget(main_page_);
  main_page_->setMinimumSize(300, 300);
}

void Controller::StartPickExercises() {
  StartExercises(pick_an_option);
}

void Controller::IncreaseScoreBy(int diff) {
  int new_score = setting.value("score").toInt() + diff;
  setting.setValue("score", new_score);
  main_page_->SetScoreLabel(new_score);
}

void Controller::SwitchToMainPage() {
  setCurrentWidget(main_page_);
}

void Controller::FinishMovieDialog() {
  movie_dialog.close();
}

void Controller::StartExercises(ExerciseType type_arg) {
  std::vector<std::pair<int, ExerciseType>> index_type{};
  index_type.reserve(pack_of_exercises_size_);
  for (int i = 0; i < pack_of_exercises_size_; i++) {
    ExerciseType type =
        (type_arg == mixed ? (ExerciseType)model_.random_mode.Generate() : type_arg);
    index_type.emplace_back(
        model_.pick_input_audio_randomizers[type].Generate(), type);
    model_.pick_input_audio_randomizers[type].Delete(index_type.back().first);
  }
  exercises.resize(pack_of_exercises_size_);
  for (int i = 0; i < pack_of_exercises_size_; i++) {
    model_.pick_input_audio_randomizers[index_type[i].second].Add(
        index_type[i].first);
    exercises[i] =
        model_.pick_input_audio_exercises[index_type[i].second][index_type[i].first];
  }
  attempts_left = setting.value("difficulty") == "easy" ? 3 : 1;
  exercise_page->ChangeAttemptsLabel(attempts_left);
  exercise_page->progress_bar.setValue(0);
  amount_of_correct = 0;
  NextExercise();
}

void Controller::NextExercise() {
  if (attempts_left == 0) {
    no_attempts_message.open();
    return;
  }
  if (!exercises.empty()) {
    if (exercises.back()->Type() == pick_an_option) {
      auto* cur_exercise = dynamic_cast<PickExercise*>(exercises.back());
      exercise_page->text.setText(cur_exercise->text);
      exercise_page->pick_widget->variant0_.setText(cur_exercise->variants[0]);
      exercise_page->pick_widget->variant1_.setText(cur_exercise->variants[1]);
      exercise_page->pick_widget->variant2_.setText(cur_exercise->variants[2]);

      exercise_page->pick_widget->SetAllUnchecked();

    } else if (exercises.back()->Type() == input_answer) {
      auto* cur_exercise = dynamic_cast<InputExercise*>(exercises.back());
      exercise_page->text.setText(cur_exercise->text);
      exercise_page->input_widget->text_edit.clear();
    } else {
      exercise_page->text.setText("Press the button and type, what you here.");
      exercise_page->audio_widget->text_edit.clear();
    }
    setCurrentWidget(exercise_page);
    exercise_page->slides.setCurrentWidget(exercise_page->exercise_widgets[exercises.back()->Type()]);
    return;
  }
  int score_diff =
      (setting.value("difficulty") == "easy" ? amount_of_correct : 2 * amount_of_correct);
  IncreaseScoreBy(score_diff);
  win_label.setText("You've passed this set of exercises!\nYou get " +
      QString::number(score_diff) + (score_diff == 1 ? " point." : " points."));
  movie_dialog.open();
}

void Controller::SubmitPressed() {
  QString input{};
  if (exercises.back()->Type() == pick_an_option) {
    if (exercise_page->pick_widget->button_group_.checkedId() == -1) {
      return;
    }
    int checked_id = exercise_page->pick_widget->button_group_.checkedId();
    input = dynamic_cast<PickExercise*>(exercises.back())->variants[checked_id];
  } else if (exercises.back()->Type() == input_answer) {
      input = exercise_page->input_widget->text_edit.toPlainText();
  } else {
    input = exercise_page->audio_widget->text_edit.toPlainText();
  }
  CheckAnswerCorrectness(input, exercises.back()->correct);
  exercise_page->ChangeAttemptsLabel(attempts_left);
  exercises.pop_back();
  exercise_page->progress_bar.setValue(100 * (pack_of_exercises_size_ - exercises.size() ) / pack_of_exercises_size_);
  reply_message.open();
}

void Controller::StartInputExercises() {
  StartExercises(input_answer);
}

void Controller::StartAudioExercises() {
  StartExercises(audio);
}

void Controller::StartMixedExercises() {
  StartExercises(mixed);
}

QString Controller::Trimmed(QString str) {
  str = str.toLower();
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ',' || str[i] == '.' || str[i] == '!' || str[i] == '?' ||
        str[i] == ':' || str[i] == '-' || str[i] == '\'' || str[i] == '\"') {
      str[i] = ' ';
    }
  }
  int write = 0;
  for (int read = 0; read < str.size(); read++) {
    if ((str[read] == ' ' || str[read] == '\n') &&
        (read == 0 || str[read - 1] == ' ' || str[read - 1] == '\n')) {
      continue;
    }
    str[write++] = str[read];
  }
  str.resize(write);
  if (!str.isEmpty() && (str.back() == ' ' || str.back() == '\n')) {
    str.resize(write - 1);
  }
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '\n') {
      str[i] = ' ';
    }
  }
  return str;
}

void Controller::PlaySound(int id) {
  static int prev_id = -1;
  if (setting.value("sound") == "off") {
    return;
  }
  if (prev_id != -1) {
    model_.players[prev_id].stop();
  }
  model_.players[id].play();
  prev_id = id;
}

void Controller::PlayExerciseAudio() {
  PlaySound(dynamic_cast<AudioExercise*>(exercises.back())->audio_id);
}

void Controller::CheckAnswerCorrectness(const QString& input, const QString& correct) {
  if (Trimmed(input) == Trimmed(correct)) {
    PlaySound(0);
    amount_of_correct++;
    reply_message.setText("Correct!");
  } else {
    PlaySound(1);
    attempts_left--;
    reply_message.setText("Incorrect!\nThe correct answer is:\n" + correct);
  }
}

void Controller::DifficultyChanged() {
  setting.setValue("difficulty",
                   main_page_->difficulty_widget.currentText().toLower());
}

void Controller::SoundChanged() {
  setting.setValue("sound", main_page_->sound_widget.currentText().toLower());
}

void Controller::AnswerIfSureToLeave() {
  close_dialog.open();
}

void Controller::ProcessCloseDialogButtonClick(QAbstractButton* button) {
  if (button->text() == "Yes") {
    QApplication::quit();
  }
}

void Controller::ResetScore() {
  setting.setValue("score", 0);
  main_page_->SetScoreLabel(0);
}
