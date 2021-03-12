#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <set>
#include <unordered_map>
#include <vector>

const std::size_t len = 200;
const std::size_t range = 500;

static void VectorPairBench(benchmark::State &state) {
  std::vector<int> keys;
  std::vector<std::pair<int, std::function<int()>>> s;
  std::srand(std::time(nullptr));
  for (int i = 0; i != len; ++i) {
    int value = rand() % range;
    keys.push_back(value);
    s.emplace_back(std::make_pair(value, []() { return 1; }));
  }
  std::size_t sum = 0;
  for (auto _ : state) {
    int value = rand() % len;
    int key = keys[value];
    auto iter = std::find_if(s.begin(), s.end(),
                             [key](auto &arg) { return arg.first == key; });
    if (iter != s.end()) {
      sum += iter->second();
    }
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(VectorPairBench);

static void VectorBench(benchmark::State &state) {
  std::vector<int> s;
  std::vector<std::function<int()>> values;
  std::srand(std::time(nullptr));
  for (int i = 0; i != len; ++i) {
    s.emplace_back(rand() % range);
    values.emplace_back([]() { return 1; });
  }
  std::size_t sum = 0;
  for (auto _ : state) {
    int value = rand() % len;
    int key = s[value];
    auto iter = std::find(s.begin(), s.end(), key);
    if (iter != s.end()) {
      sum += values[std::distance(s.begin(), iter)]();
    }
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(VectorBench);

static void HashTableBench(benchmark::State &state) {
  std::vector<int> keys;
  std::unordered_map<int, std::function<int()>> s;
  std::srand(std::time(nullptr));
  while (s.size() != len) {
    int key = rand() % range;
    s[key] = []() { return 1; };
    keys.push_back(key);
  }
  std::size_t sum = 0;
  for (auto _ : state) {
    int value = rand() % len;
    int key = keys[value];
    auto iter = s.find(key);
    if (iter != s.end()) {
      sum += iter->second();
    }
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(HashTableBench);

BENCHMARK_MAIN();
