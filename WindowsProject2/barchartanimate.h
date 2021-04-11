

#pragma once
#include "wx/wx.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <set>
#include <wx/charts/wxcharts.h>
#include "barchart.h"



using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate : public wxFrame {
private:

	BarChart* barcharts;  // pointer to a C-style array
	int size;
	int capacity;
	string title;
	string xlabel;
	string sources;
	int j;
	map<int , set<Bar>> frames;


public:

	// Functions
	void readFile( wxCommandEvent& evt );
	void ShowFirst( wxVector<wxString>& labels , wxVector<wxDouble>& points1 );
	BarChartAnimate();
	virtual ~BarChartAnimate();

	void nextFrame( wxCommandEvent& evt );
	void previousFrame( wxCommandEvent& evt );
	void autoPlay( wxCommandEvent& evt );
	void OnClose( wxCloseEvent& event );
	void resize();
	void readBlock( ifstream& file , BarChart& b );
	void addFrame( ifstream& file );
	int getSize();
	BarChartAnimate( string title , string xlabel , string source );
	BarChart& operator[]( int i );

	// Timer
	wxTimer* m_timer = nullptr;

	// Buttons
	wxButton* btn_openFile = nullptr;
	wxButton* btn_previousFrame = nullptr;
	wxButton* btn_firstFrame = nullptr;
	wxButton* btn_nextFrame = nullptr;
	wxButton* btn_autoPlay = nullptr;

	//Other boxes
	wxTextCtrl* txt_display = nullptr;
	wxTextCtrl* txt_year = nullptr;
	wxBoxSizer* graphSizer = nullptr;
	wxDECLARE_EVENT_TABLE();

};