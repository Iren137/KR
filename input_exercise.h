#ifndef INPUT_EXERCISE_H
#define INPUT_EXERCISE_H

#include <QString>

#include "exercise.h"

struct InputExercise : public Exercise {
  ExerciseType Type() override {
    return input_answer;
  }

  QString text;
};

#endif //INPUT_EXERCISE_H
