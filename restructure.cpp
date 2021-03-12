#include <array>
#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <bits/stdint-uintn.h>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <math.h>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>

struct CPoint {

  CPoint() noexcept {
    xyz.fill(1);
    vel.fill(2);
  }

  std::array<double, 3> xyz;
  double amp;
  char garbage[128];
  std::array<double, 3> vel;
};

struct Point {

  Point() noexcept {
    xyz.fill(1);
    vel.fill(2);
  }

  std::array<double, 3> xyz;
  char garbage[128];
  std::array<double, 3> vel;
  double amp;
};

struct Points {

  Points(std::size_t n) : xyxs(n), garbage(n), vels(n), ampl(n) {}

  std::vector<std::array<double, 3>> xyxs;
  std::vector<char[128]> garbage;
  std::vector<std::array<double, 3>> vels;
  std::vector<double> ampl;
};

void Normalize(std::array<double, 3> &v) {
  auto l = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
  std::for_each(v.begin(), v.end(), [l](auto &item) { item /= l; });
}

double Length(const std::array<double, 3> &v) {
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

double DotProduct(const std::array<double, 3> &n,
                  const std::array<double, 3> &v) {
  return n[0] * v[0] + n[1] * v[1] + n[2] * v[2];
}

static void NormalizeBench(benchmark::State &state) {
  std::vector<Point> points(10000);
  for (auto _ : state) {
    for (auto &point : points) {
      Normalize(point.xyz);
      point.amp = Length(point.xyz) * DotProduct(point.xyz, point.vel);
    }
  }
  benchmark::DoNotOptimize(points);
}
BENCHMARK(NormalizeBench);

static void SeparateBench(benchmark::State &state) {
  Points points(10000);
  for (auto _ : state) {
    for (std::size_t i = 0; i != 10000; ++i) {
      auto& xyz = points.xyxs[i];
      Normalize(xyz);
      points.ampl[i] = Length(xyz) * DotProduct(xyz, points.vels[i]);
    }
  }
  benchmark::DoNotOptimize(points);
}
BENCHMARK(SeparateBench);

/*
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
BENCHMARK(RandomBench); */

/*
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
BENCHMARK(RandomPreSetBench); */

BENCHMARK_MAIN();
