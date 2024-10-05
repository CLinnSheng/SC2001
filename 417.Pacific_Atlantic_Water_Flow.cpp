/*
Goal: Return the list of cell that the water can flow to pacific and atlantic
ocean

Intuition: This is a graph problem so can be solve either by using dfs or bfd
The first row and first column will be flow into the pacific ocean and last col
and last row for atlantic ocean So we need to find the cell that will to the
pacific ocean and the same for atlantic ocean The way of doing it is we dfs from
the cell of first row and first col check whether the cell of it neighboring
will into it or not by simply checking are the neighboring cell is higher than
it or not This also the same for atlantic ocean So the cells are able to flow
into both ocean just simply take the intersection of both set

Time Complexity: O(m*n)
Space Complexity: O(m*n)
*/
#include <functional>
#include <utility>
#include <vector>
class Solution {
public:
  std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  std::vector<std::vector<int>>
  pacificAtlantic(std::vector<std::vector<int>> &heights) {

    int n_row = heights.size();
    int n_col = heights[0].size();

    std::vector<std::vector<bool>> visited_pacific(
        n_row, std::vector<bool>(n_col, false));
    std::vector<std::vector<bool>> visited_atlantic(
        n_row, std::vector<bool>(n_col, false));

    // Initialize the row and col that is adjacent to the ocean
    for (int i = 0; i < n_row; i++) {
      visited_pacific[i][0] = true;
      visited_atlantic[i][n_col - 1] = true;
    }

    for (int i = 0; i < n_col; i++) {
      visited_pacific[0][i] = true;
      visited_atlantic[n_row - 1][i] = true;
    }

    std::function<void(const int &, const int &,
                       std::vector<std::vector<bool>> &)>
        dfs = [&](const int &row, const int &col,
                  std::vector<std::vector<bool>> &visited) {
          visited[row][col] = true;

          for (const auto &[_row, _col] : DIRECTIONS) {
            auto new_row = row + _row;
            auto new_col = col + _col;

            if (new_row >= 0 && new_row < n_row && new_col >= 0 &&
                new_col < n_col && !visited[new_row][new_col] &&
                heights[row][col] <= heights[new_row][new_col])
              dfs(new_row, new_col, visited);
          }
        };
    // dfs from all the cells that are adjacent to the ocean
    for (int i = 0; i < n_row; i++) {
      dfs(i, 0, visited_pacific);
      dfs(i, n_col - 1, visited_atlantic);
    }

    for (int i = 0; i < n_col; i++) {
      dfs(0, i, visited_pacific);
      dfs(n_row - 1, i, visited_atlantic);
    }

    std::vector<std::vector<int>> ans;
    for (int i = 0; i < n_row; i++)
      for (int j = 0; j < n_col; j++)
        if (visited_atlantic[i][j] && visited_pacific[i][j])
          ans.push_back({i, j});

    return std::move(ans);
  }
};
