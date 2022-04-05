#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <vector>
#include <unordered_map>

class Randomizer {
 public:
  Randomizer();
  int Generate();
  void Delete(int x);
  void Add(int x);
  void SetRange(int a, int b);

 private:
  std::vector<int> vec_{};
  std::unordered_map<int, int> index_of_{};
};

#endif //RANDOMIZER_H
