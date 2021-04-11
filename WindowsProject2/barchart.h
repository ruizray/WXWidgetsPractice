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

#include "bar.h"


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
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string frame;

public:
    // default constructor:
    BarChart() {
        capacity = 0;
        size = 0;
        frame = "";
        bars = new Bar[0];
    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart( int n ) {
        capacity = n;
        size = 0;
        frame = "";
        bars = new Bar[n];
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart( const BarChart& other ) {
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;

        for(int i = 0; i < other.size; i++) {
            this->bars[i] = other.bars[i];
        }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    // If this object is copied to itself, then this object is returned.
    // Each object in the other list is copied to the current object.
    BarChart& operator=( const BarChart& other ) {
        if(this == &other) {
            return *this;
        }

        delete[] this->bars;

        this->bars = new Bar[other.capacity];
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        for(int i = 0; i < other.capacity; i++) {
            this->bars[i] = other.bars[i];
        }
        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;
        bars = nullptr;
        size = 0;
        capacity = 0;
        frame = "";
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
        if(bars != nullptr) {
            this->clear();
        }
    }

    // setFrame
    void setFrame( string frame ) { this->frame = frame; }

    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() { return frame; }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar( string name , int value , string category ) {
        if(size == capacity) {
            return false;
        }
        Bar newBar( name , value , category );
        bars[size] = newBar;
        size++;

        return true;  // TO DO:  update this, it is only here so code compiles.
    }

    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() { return size; }

    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    Bar& operator[]( int i ) {
        if(i < 0 || i >= size) {
            throw out_of_range( "BarChart: i out of bounds" );
        }
        return bars[i];
    }
    void sortChart() {
        sort( &bars[0] , &bars[size] , greater<Bar>() );
    }
};