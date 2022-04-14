#ifndef PICK_EXERCISE_H
#define PICK_EXERCISE_H

#include <QString>

#include "exercise.h"

struct PickExercise : public Exercise {
  ExerciseType Type() override {
    return pick_an_option;
  }
  QString text;
  QString variants[3] = {};
};

#endif //PICK_EXERCISE_H
