#include "cMain.h"
 

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, btnAddToList)
EVT_BUTTON(10002, btnRemoveFromList)
EVT_BUTTON(10004, openCalculator)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY , "Testing the framework" , wxPoint(30,30), wxSize(800,600)) { // create Window
	m_btn1 = new wxButton(this, 10001, "Add to list" , wxPoint(10, 10), wxSize(150,50)); // Create button
	m_btn2 = new wxButton(this, 10002, "Remove from list", wxPoint(200, 10), wxSize(150, 50)); // Create button
	btn_openCalc = new wxButton(this, 10004, "Open Calculator", wxPoint(350, 10), wxSize(150, 50)); // Create button
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "CLICK ME", wxPoint(10, 70), wxSize(300, 30)); // Create Textbox
	m_txt2 = new wxTextCtrl(this, 10003, "0", wxPoint(310, 70), wxSize(300, 30)); // Create Textbox
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300),0,NULL, 0 , wxDefaultValidator, "Items"); // Create listbox
}

cMain::~cMain() {

}



void cMain::btnAddToList(wxCommandEvent& evt) {
	m_list1->AppendString(m_txt1->GetValue()); // Gets item in m_txt1 and appends it to listbox
	int num = m_list1->GetCount();
	m_txt2->SetValue(wxString::Format(wxT("%i"), num)); // set m_txt2 value to iterated number
	evt.Skip();
}

void cMain::openCalculator(wxCommandEvent& evt) {
	m_frame2 = new Calculator();
	m_frame2->Show();
	evt.Skip();
}



void cMain::btnRemoveFromList(wxCommandEvent& evt) {
	
	evt.Skip();
}