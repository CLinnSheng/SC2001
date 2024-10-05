#include <ios>
#include <iostream>
#include <string>
#include <unordered_map>

/*
 * Goal: Find out that if s2 contains a permutation of s1
 * Intuition: length of s2 must be greater than s1
 * Since length of s1 is much more shorter than s2, we need to check every
 * substring of length s1 in s2 We can done it by using naive approach this will
 * cost n^2
 *
 * We can think of reduce the time complexity to linear time by using sliding
 * window since we need to check length of s1 at every section of s2 Time
 * complexity: O(n) Space complexity: O(26) -> O(1)
 * */
class Solution {
public:
  bool checkInclusion(std::string s1, std::string s2) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int len1 = s1.length(), len2 = s2.length();
    if (len1 == 0)
      return true;
    if (len1 > len2)
      return false;

    std::unordered_map<int, int> map1, map2;
    int matches = 0;

    for (int i = 0; i < len1; i++) {
      map1[s1[i] - 'a']++;
      map2[s2[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++)
      if (map1[i] == map2[i])
        matches++;

    int l = 0, r = len1;
    while (r < len2) {

      if (matches == 26)
        return true;

      // Moving the right pointer of the window
      int right_index = s2[r] - 'a';
      map2[right_index]++;
      // if the new character insert is inside s1
      if (map2[right_index] == map1[right_index])
        matches++;
      // if the new character insert is not inside s2
      else if (map2[right_index] == map1[right_index] + 1)
        matches--;

      // Moving the left pointer of the window
      int left_index = s2[l] - 'a';
      map2[left_index]--;
      // if the character remove is not inside s1
      if (map2[left_index] == map1[left_index])
        matches++;
      // if the character remove is inside s1
      if (map2[left_index] == map1[left_index] - 1)
        matches--;

      l++, r++;
    }
    return matches == 26;
  }
};
