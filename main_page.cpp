#include "main_page.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QMenu>
#include "controller.h"

MainPage::MainPage(QWidget* parent) : QWidget(parent) {
  layout_.addWidget(&quit_button);
  layout_.addWidget(&score_label);
  layout_.addWidget(&pick_an_option_button_);
  layout_.addWidget(&input_answer_button_);
  layout_.addWidget(&audio_button_);
  layout_.addWidget(&mixed_button_);
  layout_.addWidget(&difficulty_label);
  layout_.addWidget(&difficulty_widget);
  layout_.addWidget(&sound_label);
  layout_.addWidget(&sound_widget);
  layout_.addWidget(&reset_score_button);



  difficulty_widget.addItem("Easy");
  difficulty_widget.addItem("Hard");

  sound_widget.addItem("On");
  sound_widget.addItem("Off");

  score_label.setContextMenuPolicy(Qt::CustomContextMenu);
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
