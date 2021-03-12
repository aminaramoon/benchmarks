#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>

struct IFace {
  ~IFace() = default;
  virtual float Show() const = 0;
};

struct B : IFace {
  float Show() const override {
    return 6;
  }
};

struct A : IFace {
  float Show() const override {
    return 4;
  }
};

static void RandomBench(benchmark::State &state) {
  std::vector<IFace *> data;

  for (int i = 0; i != 1000; ++i) {
    data.push_back(new A());
    data.push_back(new B());
  }

  for (auto _ : state) {
    auto count = std::count_if(data.begin(), data.end(),
                               [](auto &x) { return x->Show() > 5; });
    benchmark::DoNotOptimize(count);
  }
  std::for_each(data.begin(), data.end(), [](auto p) { delete p; });
}
BENCHMARK(RandomBench);

static void SortedBenchmark(benchmark::State &state) {
  std::vector<IFace *> data;
  for (int i = 0; i != 1000; ++i) {
    data.push_back(new A());
  }
  for (int i = 0; i != 1000; ++i) {
    data.push_back(new B());
  }

  for (auto _ : state) {
    auto count = std::count_if(data.begin(), data.end(),
                               [](auto &x) { return x->Show() > 5; });
    benchmark::DoNotOptimize(count);
  }

  std::for_each(data.begin(), data.end(), [](auto p) { delete p; });
}
BENCHMARK(SortedBenchmark);

BENCHMARK_MAIN();
