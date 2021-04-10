// bar.h
// Raymundo Ruiz
// NETID: rruiz30
// CS251
// Project 3
// Each bar of a the barchart is created here. Each bar contains information
// about the data being read from the file such as the year, name, country,

#include "bar.h"



//
// Bar
//
Bar::Bar() {
	year = 0;
	name = "";
	value = 0;
	category = "";
}
//
// a second constructor:
//
// Parameter passed in constructor Bar object.
//
Bar::Bar( std::string name , int value , std::string category ) : name( name ) , value( value ) , category( category ) {
}




// destructor:
Bar:: ~Bar() {}

// getName:
// returns name of the bar
string Bar::getName() { return name; }

// getValue:
// returns value of the bar
int Bar::getValue() { return value; }

// getCategory:
string Bar::getCategory() { return category; }

// less than operator:
// Returns true if this bar is less than another bar by comparing value
bool Bar:: operator<( const Bar& other ) const {
	if(this->value < other.value) {
		return true;
	}
	return false;
}
// less than equal to operator:
// Returns true if this bar is less than or equal to another bar by comparing
// value
bool Bar:: operator<=( const Bar& other ) const {
	if(this->value <= other.value) {
		return true;
	}
	return false;
}
// greater than operator:
// Returns true if this bar is greater than another bar by comparing value
bool Bar:: operator>( const Bar& other ) const {
	if(this->value > other.value) {
		return true;
	}
	return false;
}
// greater than equal to operator:
// Returns true if this bar is greater than or equal to another bar by
// comparing value
bool Bar::operator>=( const Bar& other ) const {
	if(this->value >= other.value) {
		return true;
	}
	return false;
};