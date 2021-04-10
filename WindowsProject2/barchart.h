// barchart.h
// Raymundo Ruiz
// NETID: rruiz30
// CS251
// Project 3
// barchart.h creates each individual frame of the animation. Each barchart
// contains a collection of bars in an array and prints out each frame.

#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "bar.h"
// used in autograder, do not remove

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.


//
// BarChart
//
class BarChart {
 private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // Bars.  As a result, you must also keep track of the number of elements
  // stored (size) and the capacity of the array (capacity).  This is not a
  // dynamic array, so it does not expand.
  //
  Bar *bars;  // pointer to a C-style array
  int capacity;
  int size;
  std::string frame;

 public:
  BarChart();
  BarChart(int n);

  BarChart(const BarChart &other);

  BarChart &operator=(const BarChart &other);

  void clear();

   ~BarChart();

  void setFrame(string frame);

  string getFrame();

  bool addBar(string name, int value, string category);

  int getSize();

  Bar &operator[](int i);



  void sortChart();
};