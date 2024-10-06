/*
Goal: Check whether can we finish all courses or not
CONSTRAINT: for prequisites[i] = [ai, bi] if u want to take bi u need to take ai
Intuition: Check whether theres a cycle in a graph (waiting cycle)
So we will build the graph first and then dfs the graph and check whether did we
visit a node that is already visited Time Complexity : O(V+E) because in worst
case we traverse every single edge and node Space Complexity : O(V+E)
*/
#include <functional>
#include <unordered_set>
#include <vector>

class Solution {
public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    if (prerequisites.size() == 1)
      return true;

    std::vector<std::vector<int>> adjList(numCourses, std::vector<int>());

    for (const auto &pre : prerequisites)
      adjList[pre[0]].emplace_back(pre[1]);

    std::unordered_set<int> visitedNode;

    std::function<bool(const int &)> dfs = [&](const int &curr_node) {
      if (visitedNode.count(curr_node))
        return false;
      // if we reach the end
      if (adjList[curr_node].empty())
        return true;

      visitedNode.insert(curr_node);

      for (const auto &i : adjList[curr_node])
        if (!dfs(i))
          return false;

      visitedNode.erase(curr_node);
      // clean the graph for the completed traversal
      adjList[curr_node].clear();
      return true;
    };

    for (int i = 0; i < numCourses; i++)
      if (!dfs(i))
        return false;

    return true;
  }
};
