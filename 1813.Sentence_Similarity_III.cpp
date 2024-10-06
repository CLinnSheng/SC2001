/*
Goal: Check whether the 2 strings are similar or not
there are 3 ways to append into the shorter string
front, end or in the middle
Intuition: Have a prefix and suffix which is one traverse from the front and one
from the back so just insert the words between the prefix and suffix in the
longest string into the shorter string which is between the prefix and suffix so
the way we check whether the prefix + suffix is equal to the length of the
shorter string Time Complexity: O(m + n) Space Complexity : O(m + n)
*/
#include <string>
#include <vector>

class Solution {
public:
  bool areSentencesSimilar(std::string sentence1, std::string sentence2) {
    // first split the words
    auto splitWords = [](const std::string &sentence) {
      std::vector<std::string> words;
      std::string word = "";
      for (const auto &c : sentence) {
        if (c == ' ') {
          words.emplace_back(word);
          word = "";
        } else
          word += c;
      }
      if (word.length())
        words.emplace_back(word);
      return std::move(words);
    };

    std::vector<std::string> word1(splitWords(sentence1));
    std::vector<std::string> word2(splitWords(sentence2));

    if (word1.size() > word2.size())
      std::swap(word1, word2);

    int l = 0, r = 0;
    int len1 = word1.size(), len2 = word2.size();

    while (l < len1 && word1[l] == word2[l])
      l++;
    while (r < len1 && word1[len1 - r - 1] == word2[len2 - r - 1])
      r++;

    return l + r >= word1.size();
  }
};
