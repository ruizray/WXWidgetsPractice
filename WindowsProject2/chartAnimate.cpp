#include "chartAnimate.h"
#include "barchartanimate.h"
#include "cMain.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <wx/textfile.h>



chartAnimate::chartAnimate() : wxFrame( nullptr , wxID_ANY , "BarChartAnimator" , wxPoint( 30 , 30 ) , wxSize( 800 , 600 ) ) {  // create Window
	wxBoxSizer* topSizer = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* displaySizer = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* buttonSizer = new wxBoxSizer( wxVERTICAL );
	wxSize buttonSize( 64 , 64 );
	btn_openFile = new wxButton( this , 10 , "Add File" , wxPoint( 10 , 10 ) , wxSize( 150 , 50 ) );
	btn_openFile->Bind( wxEVT_COMMAND_BUTTON_CLICKED , &chartAnimate::readFile , this );
	
	txt_display = new wxTextCtrl( this , wxID_ANY , "" , wxDefaultPosition , wxSize( wxALL , 50 ) , wxTE_MULTILINE ); 
	
	

	displaySizer->Add( txt_display , 1 , wxEXPAND , 0 );
	buttonSizer->Add( btn_openFile , 0 , 0 , 0 );
	topSizer->Add( buttonSizer , 0 , wxEXPAND , 0 );
	topSizer->Add( displaySizer , 1 , wxEXPAND , 0 );
	SetSizer( topSizer );
}







chartAnimate::~chartAnimate() {
}

