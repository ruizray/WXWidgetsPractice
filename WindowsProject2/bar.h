#pragma once
#include <iostream>
#include <string>
using namespace std;

class Bar  {
 private:
  int year;
  std::string name;
  int value;
  std::string category;

 public:
  Bar();
   ~Bar();

  Bar(std::string name, int value, std::string category);
  std::string getName();
  int getValue();
  string getCategory();
  bool operator<(const Bar &other) const;
  bool operator<=(const Bar &other) const;
  bool operator>(const Bar &other) const;
  bool operator>=(const Bar &other) const;
};
