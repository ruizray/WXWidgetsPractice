#pragma once
#include "wx/wx.h"
#include <iostream>

#include "Calculator.h"
#include "BarChartAnimate.h"


using namespace std;
class cMain : public wxFrame {
 public:
  cMain();
  ~cMain();

 public:
	 //List of buttons
  wxButton* m_btn1 = nullptr;
  wxButton* m_btn2 = nullptr;
  wxButton* btn_openCalc = nullptr;
  wxButton* btn_openChartAnimate = nullptr;
  //List of other boxes
  wxTextCtrl* m_txt1 = nullptr;
  wxTextCtrl* m_txt2 = nullptr;
  wxListBox* m_list1 = nullptr;

  //Frames 
  Calculator* m_frame2 = nullptr;
  BarChartAnimate* m_frame3 = nullptr;
 
  //Functions
  void btnAddToList(wxCommandEvent& evt);
  void btnRemoveFromList(wxCommandEvent& evt);
  void openCalculator(wxCommandEvent& evt);
  void openChartAnimate(wxCommandEvent& evt);


  wxDECLARE_EVENT_TABLE();
};
