#ifndef AUDIO_EXERCISE_H
#define AUDIO_EXERCISE_H

#include <QString>

#include "exercise.h"

struct AudioExercise : public Exercise {
  ExerciseType Type() override {
    return audio;
  }

  int audio_id;
};

#endif //AUDIO_EXERCISE_H
