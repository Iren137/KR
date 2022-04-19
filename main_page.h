#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class MainPage : public QWidget {
  Q_OBJECT
 public slots:
  void ShowContextMenu(const QPoint& pos);

 public:
  MainPage(QWidget* parent);
  void SetScoreLabel(int score);
  void SetStyle();
  void DoConnections();

 private:
  QGridLayout layout_{this};

  QLabel difficulty_label{"Difficulty", this};
  QComboBox difficulty_widget{this};

  QLabel sound_label{"Sound", this};
  QComboBox sound_widget{this};

  QPushButton quit_button{"Quit", this};
  QPushButton reset_score_button{"Reset Score", this};

  QLabel score_label{this};
  QPushButton pick_an_option_button_{"Pick an Option"};
  QPushButton input_answer_button_{"Input Answer"};
  QPushButton audio_button_{"Audio"};
  QPushButton mixed_button_{"Mixed"};

  friend class Controller;
};

#endif //MAIN_PAGE_H
