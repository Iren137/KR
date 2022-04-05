#include "main_page.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

MainPage::MainPage(QWidget* parent) : QWidget(parent) {
  layout_.addWidget(&pick_an_option_button_);
  layout_.addWidget(&input_answer_button_);
  layout_.addWidget(&audio_button_);
  layout_.addWidget(&mixed_button_);

  connect(&pick_an_option_button_, SIGNAL(clicked(bool)),
          this->parent(), SLOT(StartPickExercises()));
}
