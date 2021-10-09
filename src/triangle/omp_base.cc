// Copyright 2020 MIT
// Authors: Xuhao Chen <cxh@mit.edu>
#include "tc.h"

void TCSolver(Graph &g, uint64_t &total, int, int) {
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  printf("Launching OpenMP TC solver (%d threads) ...\n", num_threads);
  Timer t;
  t.Start();
  uint64_t counter = 0;
  #pragma omp parallel for reduction(+ : counter) schedule(dynamic, 1)
  for (VertexId u = 0; u < g.V(); u ++) {
    for (auto v : g.N(u)) {
      counter += (uint64_t)intersection_num(g.N(u), g.N(v));
    } 
  }
  total = counter;
  t.Stop();
  std::cout << "runtime [omp_base] = " << t.Seconds() << " sec\n";
  return;
}

