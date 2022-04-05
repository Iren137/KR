#include <QFile>
#include <QTextStream>

#include "model.h"


Model::Model() {
  FillInputExercises(":/input_exercises.txt", input_exercises_);
  FillPickExercises(":/pick_exercises.txt", pick_exercises_);
  input_random.SetRange(0, input_exercises_.size());
  pick_random.SetRange(0, pick_exercises_.size());
}

void Model::FillInputExercises(const QString& file_path,
                               std::vector<InputExercise>& vec_ref) {
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  int n = in.readLine().toInt();
  vec_ref.resize(n, {});
  for (int i = 0; i < n; i++) {
    vec_ref[i].text = in.readLine();
    vec_ref[i].answer = in.readLine();
  }
  file.close();
}

void Model::FillPickExercises(const QString& file_path,
                              std::vector<PickExercise>& vec_ref) {
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  int n = in.readLine().toInt();
  vec_ref.resize(n, {});
  for (int i = 0; i < n; i++) {
    vec_ref[i].text = in.readLine();
    vec_ref[i].answer1 = in.readLine();
    vec_ref[i].answer2 = in.readLine();
    vec_ref[i].answer3 = in.readLine();
    vec_ref[i].correct_answer = in.readLine().toInt();
  }
  file.close();
}
