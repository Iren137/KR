#include "audio_widget.h"

AudioWidget::AudioWidget(QWidget* parent) : QWidget(parent) {
  layout.addWidget(&listen_button);
  layout.addWidget(&text_edit);

  connect(&listen_button, SIGNAL(clicked(bool)),
          this->parent()->parent(), SLOT(PlayExerciseAudio()));
}
