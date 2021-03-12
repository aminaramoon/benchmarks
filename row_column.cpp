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

const std::size_t Size = 64;

static void RowMajorBench(benchmark::State &state) {
  unsigned **data;
  data = new unsigned *[Size];
  for (int i = 0; i != Size; ++i) {
    data[i] = new unsigned[Size];
  }

  for (auto _ : state) {
    for (int i = 0; i != Size; ++i) {
      for (int j = 0; j != Size; ++j) {
        data[i][j]++;
      }
    }
  }
  benchmark::DoNotOptimize(data);
  for (int i = 0; i != Size; ++i) {
    delete data[i];
  }
  delete data;
}
BENCHMARK(RowMajorBench);

static void ColumnMajorBench(benchmark::State &state) {
  unsigned **data;
  data = new unsigned *[Size];
  for (int i = 0; i != Size; ++i) {
    data[i] = new unsigned[Size];
  }

  for (auto _ : state) {
    for (int j = 0; j != Size; ++j) {
      for (int i = 0; i != Size; ++i) {
        data[i][j]++;
      }
    }
  }

  for (int i = 0; i != Size; ++i) {
    delete data[i];
  }
  delete data;
  benchmark::DoNotOptimize(data);
}
BENCHMARK(ColumnMajorBench);

static void RandomBench(benchmark::State &state) {
  unsigned **data;
  data = new unsigned *[Size];
  for (int i = 0; i != Size; ++i) {
    data[i] = new unsigned[Size];
  }

  for (auto _ : state) {
    for (int j = 0; j != Size; ++j) {
      for (int i = 0; i != Size; ++i) {
        data[rand() % Size][rand() % Size]++;
      }
    }
  }
  benchmark::DoNotOptimize(data);
  for (int i = 0; i != Size; ++i) {
    delete data[i];
  }
  delete data;
}
BENCHMARK(RandomBench);


// SMART PRE-FETCHER
static void RandomPreSetBench(benchmark::State &state) {
  unsigned **data;
  data = new unsigned *[Size];
  for (int i = 0; i != Size; ++i) {
    data[i] = new unsigned[Size];
  }

  std::vector<uint8_t> index(Size);
  std::generate(index.begin(), index.end(), []() { return rand() % Size; });

  for (auto _ : state) {
    for (auto i : index) {
      for (auto j : index) {
        data[i][j]++;
      }
    }
  }
  benchmark::DoNotOptimize(data);
  for (int i = 0; i != Size; ++i) {
    delete data[i];
  }
  delete data;
}
BENCHMARK(RandomPreSetBench);

BENCHMARK_MAIN();
