#include <random>

#include "randomizer.h"

Randomizer::Randomizer() {}

int Randomizer::Generate() {
  static std::mt19937 gen((std::random_device()()));
  if (vec_.empty()) {
    throw std::runtime_error("No variants to generate");
  }
  std::uniform_int_distribution<int> dist(0, static_cast<int>(vec_.size()) - 1);
  int i = dist(gen);
  return vec_[i];
}

void Randomizer::Delete(int x) {
  if (index_of_.find(x) == index_of_.end()) {
    return;
  }
  vec_[index_of_[x]] = vec_.back();
  index_of_[vec_.back()] = index_of_[x];
  vec_.pop_back();
  index_of_.erase(x);
}

void Randomizer::Add(int x) {
  if (index_of_.find(x) != index_of_.end()) {
    return;
  }
  vec_.push_back(x);
  index_of_[x] = static_cast<int>(vec_.size()) - 1;
}

void Randomizer::SetRange(int a, int b) {
  vec_.resize(b-a);
  index_of_.clear();
  for (int i = a; i < b; i++) {
    vec_[i - a] = i;
    index_of_[i] = i - a;
  }
}
