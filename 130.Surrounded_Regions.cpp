/*
Goal: Replace all 'o' with 'x' in the input matrix board if the 'o' is
surrounded by x in all 4 directions Intuition: All the Os' in the side will not
be surrounded So basically what we need to do is to find out the Os' at the side
and that is connected to any other Os that are not in the side. So all these Os
are not surrounded by x in all 4 directions and will not flip to X Time
Complexity: O(m*n) Space Complexity: O(m*n)
*/
#include <functional>
#include <utility>
#include <vector>

class Solution {
public:
  const std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  void solve(std::vector<std::vector<char>> &board) {
    int n_row = board.size();
    int n_col = board[0].size();

    std::function<void(const int &, const int &)> dfs = [&](const int &row,
                                                            const int &col) {
      board[row][col] = 'T';

      for (const auto &[_row, _col] : DIRECTIONS) {
        auto new_row = row + _row;
        auto new_col = col + _col;

        if (new_row >= 0 && new_row < n_row && new_col >= 0 &&
            new_col < n_col && board[new_row][new_col] == 'O')
          dfs(new_row, new_col);
      }
    };

    for (int i = 0; i < n_row; i++)
      for (int j = 0; j < n_col; j++)
        if (board[i][j] == 'O' &&
            (i == 0 || j == 0 || i == n_row - 1 || j == n_col - 1))
          dfs(i, j);

    for (int i = 0; i < n_row; i++)
      for (int j = 0; j < n_col; j++)
        if (board[i][j] == 'O')
          board[i][j] = 'X';

    for (int i = 0; i < n_row; i++)
      for (int j = 0; j < n_col; j++)
        if (board[i][j] == 'T')
          board[i][j] = 'O';
  }
};
