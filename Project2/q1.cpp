#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> generate_graph(const int &n_vertex,
                                             const int &n_edges) {
  srand(time(0));

  std::vector<std::vector<int>> adjMatrix(n_vertex,
                                          std::vector<int>(n_vertex, 0));
  int cnt{n_edges};

  while (cnt > 0) {
    int a{rand() % n_vertex};
    int b{rand() % n_vertex};

    if (a != b && adjMatrix[a][b] == 0) {
      adjMatrix[a][b] = 1;
      cnt--;
    }
  }
  return std::move(adjMatrix);
}

int main() {

  int n_vertex{10};
  int n_edges{n_vertex * (n_vertex - 1)};

  std::vector<std::vector<int>> adjMatrix_ = generate_graph(n_vertex, n_edges);

  for (int i = 0; i < n_vertex; i++) {
    for (int j = 0; j < n_vertex; j++)
      std::cout << adjMatrix_[i][j] << '\t';

    std::cout << '\n';
  }

  return 0;
}
