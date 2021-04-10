#include "barchart.h"

#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "bar.h"


using namespace std;

//
// BarChart
//
BarChart::BarChart() {
	capacity = 0;
	size = 0;
	frame = "";
	bars = new Bar[0];
}

// parameterized constructor:
// Parameter passed in determines memory allocated for bars.
BarChart::BarChart( int n ) {
	capacity = n;
	size = 0;
	frame = "";
	bars = new Bar[n];
}

BarChart::BarChart( const BarChart& other ) {
	this->bars = new Bar[other.capacity];
	this->capacity = other.capacity;
	this->size = other.size;
	this->frame = other.frame;

	for(int i = 0; i < other.size; i++) {
		this->bars[i] = other.bars[i];
	}
}

BarChart& BarChart::operator=( const BarChart& other ) {
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

void BarChart::clear() {
	delete[] bars;
	bars = nullptr;
	size = 0;
	capacity = 0;
	frame = "";
}

BarChart::~BarChart() {
	if(bars != nullptr) {
		this->clear();
	}
}

// setFrame
void BarChart::setFrame( string frame ) { this->frame = frame; }

// getFrame()
// Returns the frame of the BarChart oboject.
string BarChart::getFrame() { return frame; }

// addBar
// adds a Bar to the BarChart.
// returns true if successful
// returns false if there is not room
bool BarChart::addBar( string name , int value , string category ) {
	if(size == capacity) {
		return false;
	}
	Bar newBar( name , value , category );
	bars[size] = newBar;
	size++;

	return true;
}

int BarChart::getSize() { return size; }

Bar& BarChart::operator[]( int i ) {
	if(i < 0 || i >= size) {
		throw out_of_range( "BarChart: i out of bounds" );
	}
	return bars[i];
}


void BarChart::sortChart() {
	sort( &bars[0] , &bars[size] , greater<Bar>() );
}


