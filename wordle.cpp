#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void backtrack(const std::string& currString, const std::string& in, const std::string& floating, std::vector<std::string>& out);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::vector<std::string> possiblePermutations;
    std::set<std::string> out;
    backtrack("", in, floating, possiblePermutations);
    for (const std::string& permutation : possiblePermutations) {
      if (dict.find(permutation) != dict.end())
        out.emplace(permutation);
    }
    return out;
}

// Define any helper functions here
void backtrack(const std::string& currString, const std::string& in, const std::string& floating, std::vector<std::string>& out) {
  if (currString.size() == in.size()) {
    bool hasAllFloating = true;
    for (const char letter : floating) {
      hasAllFloating = hasAllFloating && currString.find(letter) != std::string::npos;
    }
    if (hasAllFloating)
      out.emplace_back(currString);
  }
  else {
    if (in[currString.size()] != '-') {
      backtrack(currString + in[currString.size()], in, floating, out);
    }
    else {
      for (char nextLetter = 'a'; nextLetter < 'z' + 1; ++nextLetter) {
        backtrack(currString + nextLetter, in, floating, out);
      }
    }
  }
}