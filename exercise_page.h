#ifndef EXERCISE_PAGE_H
#define EXERCISE_PAGE_H

#include <QRadioButton>
#include <QButtonGroup>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QMovie>
#include <QProgressBar>
#include <QStackedWidget>

#include "pick_exercise.h"
#include "pick_widget.h"
#include "audio_widget.h"
#include "input_widget.h"

class ExercisePage : public QWidget {
 public:
  ExercisePage(QWidget* parent);
  void ChangeAttemptsLabel(int new_val);
  void SetStyle();

 public:
  QGridLayout layout_{this};

  QLabel text{this};
  QPushButton submit{"Submit", this};
  QProgressBar progress_bar{this};
  QLabel attempts_remaining{this};
  QPushButton to_main_page_button{"Stop", this};

  PickWidget* pick_widget = new PickWidget(this);
  InputWidget* input_widget = new InputWidget(this);
  AudioWidget* audio_widget = new AudioWidget(this);

  std::vector<QWidget*> exercise_widgets{pick_widget, input_widget, audio_widget};
  QStackedWidget slides{this};

};

#endif //EXERCISE_PAGE_H
