#pragma once
#include "wx/wx.h"
#include <iostream>
#include <ctype.h>
#include <stack>
#include <string>

using namespace std;

class Calculator : public wxFrame
{
public:
    Calculator();
    ~Calculator();

  
    

private:
	wxTextCtrl* m_display;
    wxListBox* m_debug;
	vector<wxButton*> m_numButtons;
    stack<string> s;
    vector<string> strings;
	wxButton* m_addButton;
    wxButton* m_deciButton;
    wxButton* m_signButton;
    wxButton* m_subButton;
    wxButton* m_mulButton;
    wxButton* m_divButton;
    wxButton* m_clsButton;
    wxButton* m_equalsButton;

    // internal variables
    std::string m_preDecimal;
    std::string m_postDecimal;
    int leftParen;
    int rightParen;
    double result;
    
    void addToDisplay(wxCommandEvent& evt);
    void getResult();
    void removeSpaces(string &str);
    int prec(string c);
    vector<string> infixToPostfix(vector<string> &s);
    double evaluatePostfix(vector<string> &exp);
  

};

