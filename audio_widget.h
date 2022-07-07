#ifndef AUDIO_WIDGET_H
#define AUDIO_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>

class AudioWidget : public QWidget {
 public:
  AudioWidget(QWidget* parent);

  QTextEdit text_edit{this};
  QPushButton listen_button{"Listen", this};

  QGridLayout layout{this};
};

#endif //AUDIO_WIDGET_H
