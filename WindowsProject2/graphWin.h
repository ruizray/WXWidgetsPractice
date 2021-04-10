#pragma once
#include "wx/wx.h"


using namespace std;

class graphWin : public wxFrame
{
public:
	
	
	graphWin( wxVector<wxString>&labels , wxVector<wxDouble>& points1 );
	~graphWin();
	void clearGraph();
	void setGraph( wxVector<wxString>& labels , wxVector<wxDouble>& points1 );
	
	


public:
	


};

