#pragma once
#include "wx/wx.h"
#include <iostream>
#include "Calculator.h"
using namespace std;
class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	
public:
	wxButton* m_btn1 = nullptr;
	wxButton* m_btn2 = nullptr;
	wxButton* btn_openCalc = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxTextCtrl* m_txt2 = nullptr;
	wxListBox* m_list1 = nullptr;
	Calculator* m_frame2 = nullptr;
	
	void btnAddToList(wxCommandEvent& evt );
	void btnRemoveFromList(wxCommandEvent& evt);
	void openCalculator(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

