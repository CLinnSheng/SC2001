#include <deque>
#include <ios>
#include <iostream>
#include <string>

/*
 * Goal: Return the minimum possible length of resulting string that can
 * obtained after removing any occurence of one of the substring eg: "ABCD" -->
 * Result String: ""
 *
 * Intuition: We can kinda achieve it by using brute force which is double loop
 * this will cost O(n^2) and it might cost more than that because we need to
 * keep checking even after removing the substring, because the new string
 * created might also have.
 *
 * A more optimized way is using stack. The idea behind this is due to we need
 * to keep checking s[i] and s[i - 1] after or before removing substring. This
 * will greatly reduced the time complexity to O(n) Space complexity: O(n)
 * */

class Solution {
public:
  int minLength(std::string s) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::deque<char> stack;
    int len = s.length();

    if (len == 1)
      return len;

    int index = 0;

    while (index < len) {
      if (stack.empty()) {
        stack.emplace_back(s[index++]);
        continue;
      }
      if (stack.back() == s[index] - 1 &&
          (stack.back() == 'A' || stack.back() == 'C'))
        stack.pop_back();
      else
        stack.emplace_back(s[index]);

      index++;
    }
    return stack.size();
  }
};
