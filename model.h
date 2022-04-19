#ifndef MODEL_H
#define MODEL_H

#include <QMediaPlayer>
#include <vector>

#include "input_exercise.h"
#include "pick_exercise.h"
#include "audio_exercise.h"
#include "randomizer.h"

class Model {
 public:
  Model();
  ~Model();

 private:
  void FillInputExercises(const QString& file_path,
                          std::vector<Exercise*>& vec_ref);
  void FillPickExercises(const QString& file_path,
                          std::vector<Exercise*>& vec_ref);
  void FillAudioExercises(const QString& file_path,
                         std::vector<Exercise*>& vec_ref);

  std::vector<Exercise*> pick_input_audio_exercises[3] = {};
  Randomizer pick_input_audio_randomizers[3] = {};
  Randomizer random_mode{};
  std::vector<QMediaPlayer> players{};

  friend class Controller;
};

#endif //MODEL_H
