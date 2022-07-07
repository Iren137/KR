#include "audio_widget.h"

AudioWidget::AudioWidget(QWidget* parent) : QWidget(parent) {
  layout.addWidget(&listen_button);
  layout.addWidget(&text_edit);

  listen_button.setFont(QFont("Ubuntu", 15));
  text_edit.setFont(QFont("Ubuntu", 15));
  listen_button.setStyleSheet("QPushButton {background-color: blue}");
  connect(&listen_button, SIGNAL(clicked(bool)),
          this->parent()->parent(), SLOT(PlayExerciseAudio()));
}
