#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class MainPage : public QWidget {
 public:
  MainPage(QWidget* parent);

 private:
  QGridLayout layout_{this};

  QPushButton pick_an_option_button_{"Pick an Option"};
  QPushButton input_answer_button_{"Input Answer"};
  QPushButton audio_button_{"Audio"};
  QPushButton mixed_button_{"Mixed"};
};

#endif //MAIN_PAGE_H
