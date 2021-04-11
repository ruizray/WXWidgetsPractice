#include "wx/wx.h"
#include "barchartanimate.h"


wxBEGIN_EVENT_TABLE( BarChartAnimate , wxFrame )
EVT_MENU( wxID_OPEN , BarChartAnimate::readFile )
EVT_CLOSE( BarChartAnimate::OnClose )

wxEND_EVENT_TABLE()
using namespace std;

BarChartAnimate::BarChartAnimate() : wxFrame( nullptr , wxID_ANY , "BarChartAnimator" , wxPoint( 30 , 30 ) , wxSize( 800 , 600 ) ) {  // create Window
	wxMenu* file_menu = new wxMenu;
	wxMenuBar* menu_bar = new wxMenuBar;
	menu_bar->Append( file_menu , "&File" );

	file_menu->Append( wxID_OPEN , "&Open File...\tCtrl+O" , "Loads a file" );
	SetMenuBar( menu_bar );
	int min = 0;
	int max = 0;
	m_timer = new wxTimer( this , wxID_EXECUTE );
	barcharts = new BarChart[4];
	size = 0;
	capacity = 4;
	j = 0;
	string title;
	string xlabel;
	string sources;

	graphSizer = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* topSizer = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	wxVector<wxString> labels;
	wxVector<wxDouble> points1;
	wxSize buttonSize( 64 , 64 );

	btn_previousFrame = new wxButton( this , 10 , "Show Previous Frame" , wxPoint( 10 , 10 ) , wxSize( 150 , 50 ) );
	btn_previousFrame->Bind( wxEVT_COMMAND_BUTTON_CLICKED , &BarChartAnimate::previousFrame , this );
	btn_previousFrame->Disable();
	btn_nextFrame = new wxButton( this , 10 , "Show Next Frame" , wxPoint( 10 , 10 ) , wxSize( 150 , 50 ) );
	btn_nextFrame->Bind( wxEVT_COMMAND_BUTTON_CLICKED , &BarChartAnimate::nextFrame , this );
	btn_nextFrame->Disable();
	btn_autoPlay = new wxButton( this , 10 , "AutoPlay" , wxPoint( 10 , 10 ) , wxSize( 150 , 50 ) );
	btn_autoPlay->Bind( wxEVT_COMMAND_BUTTON_CLICKED , &BarChartAnimate::autoPlay , this );
	btn_autoPlay->Disable();

	wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared( labels );
	wxChartsDoubleDataset::ptr dataset1( new wxChartsDoubleDataset( "Dataset 1" , points1 ) );
	chartData->AddDataset( dataset1 );
	wxBarChartCtrl* barChartCtrl = new wxBarChartCtrl( this , wxID_ANY , chartData , wxDefaultPosition , wxSize( wxEXPAND , wxEXPAND ) );

	buttonSizer->Add( btn_previousFrame , 1 , wxALL | wxEXPAND , 5 );
	buttonSizer->Add( btn_autoPlay , 1 , wxALL | wxEXPAND , 5 );
	buttonSizer->Add( btn_nextFrame , 1 , wxALL | wxEXPAND , 5 );

	graphSizer->Add( barChartCtrl , 0 , wxALL | wxEXPAND , 5 );
	topSizer->Add( graphSizer , 1 , wxEXPAND , 0 );
	topSizer->Add( buttonSizer , 0 , wxALIGN_CENTER | wxALL , 5 );
	SetSizer( topSizer , true );
	Layout();
	Centre( wxBOTH );



}

void BarChartAnimate::readFile( wxCommandEvent& WXUNUSED( event ) ) {
	wxFileDialog dialog( this , "Please choose an animation" ,
		wxEmptyString , wxEmptyString , "*.txt;" , wxFD_OPEN );
	string filename = "cities.txt";
	ifstream inFile( filename );
	if(inFile.is_open() != true) {
		return;
	}
	getline( inFile , this->title );
	getline( inFile , this->xlabel );
	getline( inFile , this->sources );
	while(!inFile.eof()) {
		addFrame( inFile );
	}
	wxVector<wxString> label;
	wxVector<wxDouble> nums;
	barcharts[0].sortChart();

	for(int i = 0; i < barcharts[0].getSize(); i++) {
		label.push_back( barcharts[0][i].getName() );
		nums.push_back( barcharts[0][i].getValue() );
	}
	ShowFirst( label , nums );
	btn_autoPlay->Enable();
	btn_previousFrame->Enable();
	btn_nextFrame->Enable();
	return;
}



void BarChartAnimate::ShowFirst( wxVector<wxString>& labels , wxVector<wxDouble>& points1 ) {
	graphSizer->Clear( true );
	SetLabel( title + " Current frame: " + barcharts[j].getFrame() );
	wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared( labels );
	wxChartsDoubleDataset::ptr dataset1( new wxChartsDoubleDataset( "Dataset 1" , points1 ) );
	chartData->AddDataset( dataset1 );
	wxBarChartCtrl* barChartCtrl = new wxBarChartCtrl( this , wxID_ANY , chartData , wxDefaultPosition , wxSize( wxEXPAND , wxEXPAND ) );
	graphSizer->Add( barChartCtrl , 0 , wxALL | wxEXPAND , 5 );
	Layout();
	Centre( wxBOTH );

}

void BarChartAnimate::nextFrame( wxCommandEvent& evt ) {
	wxVector<wxString> label;
	wxVector<wxDouble> nums;
	j++;
	SetLabel( title + " Current frame: " + barcharts[j].getFrame() );
	barcharts[j].sortChart();

	for(int i = 0; i < barcharts[0].getSize(); i++) {
		label.push_back( barcharts[j][i].getName() );
		nums.push_back( barcharts[j][i].getValue() );
	}
	ShowFirst( label , nums );
}

void BarChartAnimate::previousFrame( wxCommandEvent& evt ) {
	wxVector<wxString> label;
	wxVector<wxDouble> nums;
	j--;
	SetLabel( title + " Current frame: " + barcharts[j].getFrame() );
	barcharts[j].sortChart();

	for(int i = 0; i < barcharts[0].getSize(); i++) {
		label.push_back( barcharts[j][i].getName() );
		nums.push_back( barcharts[j][i].getValue() );
	}
	ShowFirst( label , nums );
}

void BarChartAnimate::autoPlay( wxCommandEvent& evt ) {
	if(m_timer->IsRunning() == false) {
		m_timer = new wxTimer( this , wxID_EXECUTE );
		m_timer->Start( 500 );
		this->Bind( wxEVT_TIMER , [&]( wxTimerEvent& )
			{
				wxVector<wxString> label;
				wxVector<wxDouble> nums;
				j++;
				this->SetLabel( title + " Current frame: " + barcharts[j].getFrame() );
				barcharts[j].sortChart();

				for(int i = 0; i < barcharts[0].getSize(); i++) {
					label.push_back( barcharts[j][i].getName() );
					nums.push_back( barcharts[j][i].getValue() );
				}
				ShowFirst( label , nums );
			} , wxID_EXECUTE );
	}
	else {

		m_timer->Stop();
		
	}

}

void BarChartAnimate::OnClose( wxCloseEvent& event ) {
	if(m_timer->IsRunning() == true) {
		m_timer->Stop();
	}

	event.Skip();
}


BarChartAnimate::BarChartAnimate( string title , string xlabel , string source ) {
	barcharts = new BarChart[4];
	size = 0;
	capacity = 4;
	j = 0;
	this->title = title;
	this->xlabel = xlabel;
	this->sources = source;
}

BarChartAnimate::~BarChartAnimate() {
	delete[] barcharts;
	barcharts = nullptr;
	size = 0;
	capacity = 0;
}


void BarChartAnimate::resize() {
	this->capacity = this->capacity * 2;
	BarChart* temp = new BarChart[capacity];
	for(int i = 0; i < size; i++) {
		temp[i] = barcharts[i];
	}
	delete[] barcharts;
	barcharts = new BarChart[this->capacity];
	for(int i = 0; i < capacity; i++) {
		barcharts[i] = temp[i];
	}
	delete[] temp;
}

void BarChartAnimate::readBlock( ifstream& file , BarChart& b ) {
	string test , year , value , place , country , category , valueConvert , blank;
	int value2 = 0;
	getline( file , test );
	istringstream iss( test );
	getline( iss , year , ',' );
	b.setFrame( year );
	getline( iss , place , ',' );
	getline( iss , country , ',' );
	getline( iss , value , ',' );
	getline( iss , category , ',' );

	value2 = stoi( value );
	b.addBar( place , value2 , category );

}

void BarChartAnimate::addFrame( ifstream& file ) {
	int numOfRecords = 0;
	if(!file.good()) {
		return;
	}
	if(size == capacity) {
		resize();
	}
	file >> numOfRecords;
	if(numOfRecords == 0) {
		return;
	}
	file.ignore();

	BarChart b( numOfRecords + 1 );
	for(int i = 0; i < numOfRecords; i++) {
		readBlock( file , b );
	}

	this->barcharts[size] = b;
	size++;
	return;
}

int BarChartAnimate::getSize() { return size; }

BarChart& BarChartAnimate::operator[]( int i ) {
	if(i < 0 || i >= size) {
		throw out_of_range( "BarChart: i out of bounds" );
	}
	return barcharts[i];
}

