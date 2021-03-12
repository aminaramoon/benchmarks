#include <benchmark/benchmark.h>

#include <algorithm>
#include <bits/stdint-uintn.h>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>

static void CacheJumpBenchmark(benchmark::State &state) {
  auto range = state.range(0);
  std::vector<uint8_t> data(range * 1024);
  std::generate(data.begin(), data.end(), std::default_random_engine{});

  for (auto _ : state) {
    std::size_t sum = 0;
    uint32_t counter = 0;
    int i = 0;
    for (; counter < 1024; i += range, ++counter) {
      data[i] += 1;
      sum += data[i];
    }
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(CacheJumpBenchmark)->RangeMultiplier(2)->Range(1, 16384);


static void AssociativityBenchmark(benchmark::State &state) {
  std::vector<uint32_t> data(32 * 1024 * 1024 / sizeof(uint32_t));
  auto step = state.range(0);

  for (auto _ : state) {
    int i = 0;
    std::size_t sum = 0;
    for (volatile int repeat =0; repeat < 10000; ++repeat) {
      data[i] += 1;
      i = (i + step) % data.size();
      sum += data[i];
    }
    benchmark::DoNotOptimize(data[i]);
  }
}
BENCHMARK(AssociativityBenchmark)->RangeMultiplier(2)->Range(16, 1024);


BENCHMARK_MAIN();
