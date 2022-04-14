#include <QFile>
#include <QTextStream>
#include <iostream>
#include "model.h"

Model::Model() {
  FillPickExercises(":/pick_exercises.txt", pick_input_audio_exercises[0]);
  FillInputExercises(":/input_exercises.txt", pick_input_audio_exercises[1]);
  FillAudioExercises(":/audio_exercises.txt", pick_input_audio_exercises[2]);
  pick_input_audio_randomizers[0].SetRange(0, pick_input_audio_exercises[0].size());
  pick_input_audio_randomizers[1].SetRange(0, pick_input_audio_exercises[1].size());
  pick_input_audio_randomizers[2].SetRange(0, pick_input_audio_exercises[2].size());

  random_mode.SetRange(0, 3);
}

void Model::FillInputExercises(const QString& file_path,
                               std::vector<Exercise*>& vec_ref) {
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  int n = in.readLine().toInt();
  vec_ref.resize(n);
  for (int i = 0; i < n; i++) {
    vec_ref[i] = new InputExercise();
    auto* cur_exercise = dynamic_cast<InputExercise*>(vec_ref[i]);
    cur_exercise->text = in.readLine();
    cur_exercise->correct = in.readLine();
  }
  file.close();
}

void Model::FillPickExercises(const QString& file_path,
                              std::vector<Exercise*>& vec_ref) {
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  int n = in.readLine().toInt();
  vec_ref.resize(n, {});
  for (int i = 0; i < n; i++) {
    vec_ref[i] = new PickExercise();
    auto* cur_exercise = dynamic_cast<PickExercise*>(vec_ref[i]);
    cur_exercise->text = in.readLine();
    cur_exercise->variants[0] = in.readLine();
    cur_exercise->variants[1] = in.readLine();
    cur_exercise->variants[2] = in.readLine();
    cur_exercise->correct = (cur_exercise->variants)[in.readLine().toInt()];
  }
  file.close();
}

void Model::FillAudioExercises(const QString& file_path,
                               std::vector<Exercise*>& vec_ref) {
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  int n = in.readLine().toInt();
  vec_ref.resize(n);
  players = std::vector<QMediaPlayer>(n + 2);
  players[0].setMedia(QMediaContent(QUrl("qrc:/Audio/correct.mp3")));
  players[1].setMedia(QMediaContent(QUrl("qrc:/Audio/incorrect.mp3")));
  for (int i = 0; i < n; i++) {
    vec_ref[i] = new AudioExercise();
    auto* cur_exercise = dynamic_cast<AudioExercise*>(vec_ref[i]);
    players[i + 2].setMedia(QMediaContent(QUrl("qrc:/Audio/" + in.readLine())));
    cur_exercise->audio_id = i + 2;
    cur_exercise->correct = in.readLine();
  }
  file.close();
}

Model::~Model() {
  for (int i = 0; i < 3; i++) {
    int n = pick_input_audio_exercises[i].size();
    for (int j = 0; j < n; j++) {
      delete pick_input_audio_exercises[i][j];
    }
  }
}


