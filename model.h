#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "input_exercise.h"
#include "pick_exercise.h"
#include "randomizer.h"

class Model {
 public:
  Model();

 // private:
  void FillInputExercises(const QString& file_path,
                          std::vector<InputExercise>& vec_ref);
  void FillPickExercises(const QString& file_path,
                          std::vector<PickExercise>& vec_ref);

  std::vector<InputExercise> input_exercises_{};
  std::vector<PickExercise> pick_exercises_{};

  Randomizer input_random{};
  Randomizer pick_random{};
};

#endif //MODEL_H
