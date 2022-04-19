#include <QFile>
#include <QMenu>

#include "controller.h"
#include "main_page.h"

MainPage::MainPage(QWidget* parent) : QWidget(parent) {
  layout_.addWidget(&sound_label, 0, 0, 1,2, Qt::AlignBottom);
  layout_.addWidget(&sound_widget, 1,0,1,2);
  layout_.addWidget(&difficulty_label,2,0,1,2, Qt::AlignBottom);
  layout_.addWidget(&difficulty_widget,3,0,1,2);
  layout_.addWidget(&score_label,4,0,1,2, Qt::AlignBottom);
  layout_.addWidget(&reset_score_button,5,0,1,2);
  layout_.addWidget(&pick_an_option_button_,6,0,2,1);
  layout_.addWidget(&input_answer_button_,6,1,2,1);
  layout_.addWidget(&audio_button_, 8,0,2,1);
  layout_.addWidget(&mixed_button_,8,1,2,1);
  layout_.addWidget(&quit_button,10,0,1,2);

  SetStyle();

  difficulty_widget.addItem("Easy");
  difficulty_widget.addItem("Hard");

  sound_widget.addItem("On");
  sound_widget.addItem("Off");

  score_label.setContextMenuPolicy(Qt::CustomContextMenu);

  DoConnections();
}

void MainPage::SetScoreLabel(int score) {
  score_label.setText("Score: " + QString::number(score));
}

void MainPage::ShowContextMenu(const QPoint& pos) {
  QMenu menu;
  menu.addAction("Reset");
  if (menu.exec(score_label.mapToGlobal(pos))) {
    dynamic_cast<Controller*>(this->parent())->ResetScore();
  }
}

void MainPage::SetStyle() {
  pick_an_option_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  input_answer_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  audio_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mixed_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  sound_label.setFont(QFont("Ubuntu", 15));
  difficulty_label.setFont(QFont("Ubuntu", 15));
  score_label.setFont(QFont("Ubuntu", 15));
  reset_score_button.setFont(QFont("Ubuntu", 15));
  pick_an_option_button_.setFont(QFont("Ubuntu", 15));
  input_answer_button_.setFont(QFont("Ubuntu", 15));
  audio_button_.setFont(QFont("Ubuntu", 15));
  mixed_button_.setFont(QFont("Ubuntu", 15));
  quit_button.setFont(QFont("Ubuntu", 15));
  pick_an_option_button_.setStyleSheet("QPushButton {background-color: green}");
  input_answer_button_.setStyleSheet("QPushButton {background-color: blue}");
  audio_button_.setStyleSheet("QPushButton {background-color: yellow}");
  mixed_button_.setStyleSheet("QPushButton {background-color: purple}");
  reset_score_button.setStyleSheet("QPushButton {background-color: rgba(220,170,170,240)}");
  quit_button.setStyleSheet("QPushButton {background-color: red}");
  sound_widget.setStyleSheet("QComboBox {background-color: rgba(100, 150, 200, 255)}");
  difficulty_widget.setStyleSheet("QComboBox {background-color: rgba(100, 150, 200, 255)}");
}

void MainPage::DoConnections() {
  connect(&score_label, SIGNAL(customContextMenuRequested(const QPoint &)),
          this, SLOT(ShowContextMenu(const QPoint&)));
  connect(&reset_score_button, SIGNAL(clicked(bool)),
          this->parent(), SLOT(ResetScore()));
  connect(&quit_button, SIGNAL(clicked(bool)),
          this->parent(), SLOT(AnswerIfSureToLeave()));
  connect(&difficulty_widget, SIGNAL(activated(int)),
          this->parent(), SLOT(DifficultyChanged()));
  connect(&sound_widget, SIGNAL(activated(int)),
          this->parent(), SLOT(SoundChanged()));
  connect(&pick_an_option_button_, SIGNAL(clicked(bool)),
          this->parent(), SLOT(StartPickExercises()));
  connect(&input_answer_button_, SIGNAL(clicked(bool)),
          this->parent(), SLOT(StartInputExercises()));
  connect(&audio_button_, SIGNAL(clicked(bool)),
          this->parent(), SLOT(StartAudioExercises()));
  connect(&mixed_button_, SIGNAL(clicked(bool)),
          this->parent(), SLOT(StartMixedExercises()));
}
