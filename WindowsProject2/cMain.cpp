#include "cMain.h"

wxBEGIN_EVENT_TABLE( cMain , wxFrame ) 
EVT_BUTTON( 10002 , btnRemoveFromList ) EVT_BUTTON( 10004 , openCalculator )
EVT_BUTTON( 10005 , openChartAnimate )

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame( nullptr , wxID_ANY , "Testing the framework" , wxPoint( 30 , 30 ) , wxSize( 800 , 600 ) ) {  // create Window
	wxFlexGridSizer* menuSizer = new wxFlexGridSizer( 2 , 0 , 0 );
	wxBoxSizer* generalSizer = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* appSizer = new wxBoxSizer( wxVERTICAL );
	wxSize buttonSize( 64 , 64 );

	btn_openCalc = new wxButton( this , 10004 , "Open Calculator" , wxPoint( 350 , 10 ) , wxSize( 150 , 50 ) );  // Create button
	btn_openChartAnimate = new wxButton( this , 10005 , "Open BarChart Animator" , wxPoint( 350 , 10 ) , wxSize( 150 , 50 ) );  // Create button
	m_list1 = new wxListBox( this , wxID_ANY , wxPoint( 10 , 110 ) , wxSize( 300 , 300 ) , 0 , NULL , 0 , wxDefaultValidator , "Items" );  // Create listbox
	


	appSizer->Add( btn_openCalc , 0 , 0 , 0 );
	appSizer->Add( btn_openChartAnimate , 0 , 0 , 0 );

	menuSizer->Add( appSizer );
	menuSizer->Add( generalSizer );
	SetSizerAndFit( menuSizer );
}

cMain::~cMain() {}



void cMain::openCalculator( wxCommandEvent& evt ) {
	m_frame2 = new Calculator();
	m_frame2->Show();
	evt.Skip();
}

void cMain::openChartAnimate( wxCommandEvent& evt ) {
	m_frame3 = new BarChartAnimate();
	m_frame3->Show();
	evt.Skip();
}

void cMain::btnRemoveFromList( wxCommandEvent& evt ) { evt.Skip(); }