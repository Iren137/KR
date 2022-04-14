#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>

enum ExerciseType {
  pick_an_option = 0,
  input_answer = 1,
  audio = 2,

  mixed
};

struct Exercise {
  virtual ExerciseType Type() = 0;
  virtual ~Exercise() = default;

  QString correct;
};

#endif //EXERCISE_H
