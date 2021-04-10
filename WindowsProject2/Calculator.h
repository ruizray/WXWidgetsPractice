#pragma once
#include "wx/wx.h"
#include <iostream>
#include <ctype.h>
#include <stack>
#include <string>

using namespace std;

class Calculator : public wxFrame {
 public:
  Calculator();
  ~Calculator();

 private:
  wxTextCtrl* m_display;
  wxListBox* m_debug;
  vector<wxButton*> m_numButtons;
  stack<string> s;
  vector<string> strings;

  // internal variables
  std::string m_preDecimal;
  std::string m_postDecimal;
  int leftParen;
  int rightParen;
  double result;

  void addToDisplay(wxCommandEvent& evt);
  void getResult();
  void removeSpaces(string& str);
  int prec(string c);
  vector<string> infixToPostfix(vector<string>& s);
  double evaluatePostfix(vector<string>& exp);
};
