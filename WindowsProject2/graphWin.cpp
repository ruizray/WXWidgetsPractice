#include "wx/wx.h"
#include "graphWin.h"
#include "barchartanimate.h"

graphWin::graphWin( wxVector<wxString>& labels , wxVector<wxDouble>& points1 ) : wxFrame( nullptr , wxID_ANY , "Bar Chart Graph" , wxPoint( 30 , 30 ) , wxSize( 800 , 600 ) ) {
	wxBoxSizer* panel = new wxBoxSizer( wxHORIZONTAL );

	wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared( labels );
	wxChartsDoubleDataset::ptr dataset1( new wxChartsDoubleDataset( "Dataset 1" , points1 ) );
	chartData->AddDataset( dataset1 );
	wxBarChartCtrl* barChartCtrl = new wxBarChartCtrl( this , wxID_ANY , chartData );

	// Set up the sizer for the panel
	wxBoxSizer* panelSizer = new wxBoxSizer( wxHORIZONTAL );
	panel->Add( barChartCtrl , 1 , wxEXPAND );


	// Set up the sizer for the frame
	wxBoxSizer* topSizer = new wxBoxSizer( wxHORIZONTAL );
	topSizer->Add( panel , 1 , wxEXPAND );
	SetSizer( topSizer );
}

graphWin::~graphWin() {

}

void graphWin::clearGraph() {

	DestroyChildren();
	wxBoxSizer* displaySizer = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* topSizer = new wxBoxSizer( wxVERTICAL );
	wxVector<wxString> labels;
	wxVector<wxDouble> points1;


	wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared( labels );
	wxChartsDoubleDataset::ptr dataset1( new wxChartsDoubleDataset( "Dataset 1" , points1 ) );
	chartData->AddDataset( dataset1 );
	wxBarChartCtrl* barChartCtrl = new wxBarChartCtrl( this , wxID_ANY , chartData , wxDefaultPosition , wxSize( wxEXPAND , wxEXPAND ) );
	displaySizer->Add( barChartCtrl , 1 , wxEXPAND | wxALL , 0 );


	topSizer->Add( displaySizer , 1 , wxEXPAND , 0 );
	SetSizer( topSizer , true );


	Layout();

}

void graphWin::setGraph( wxVector<wxString>& labels , wxVector<wxDouble>& points1 ) {


	Freeze();
	DestroyChildren();
	wxBoxSizer* displaySizer = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* topSizer = new wxBoxSizer( wxVERTICAL );



	wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared( labels );
	wxChartsDoubleDataset::ptr dataset1( new wxChartsDoubleDataset( "Dataset 1" , points1 ) );
	chartData->AddDataset( dataset1 );
	wxBarChartCtrl* barChartCtrl = new wxBarChartCtrl( this , wxID_ANY , chartData , wxDefaultPosition , wxSize( wxEXPAND , wxEXPAND ) );
	displaySizer->Add( barChartCtrl , 1 , wxEXPAND | wxALL , 0 );


	topSizer->Add( displaySizer , 1 , wxEXPAND , 0 );
	SetSizer( topSizer , true );


	Layout();
	Thaw();
}



