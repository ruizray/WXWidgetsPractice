#include "Calculator.h"

#include "cMain.h"

Calculator::Calculator() : wxFrame( nullptr , wxID_ANY , "Calculator" , wxPoint( 30 , 30 ) , wxSize( 800 , 600 ) ) {  // create Window
	m_numButtons;
	leftParen = 0;
	rightParen = 0;
	stack<string> s;
	vector<string> strings;
	wxBoxSizer* topSizer = new wxBoxSizer( wxVERTICAL );
	wxGridSizer* menuSizer = new wxGridSizer( 2 , 0 , 0 );
	wxBoxSizer* debugSizer = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* displaySizer = new wxBoxSizer( wxHORIZONTAL );
	wxGridSizer* buttonSizer = new wxGridSizer( 4 , 0 , 0 );
	wxSize buttonSize( 64 , 64 );

	m_display = new wxTextCtrl( this , wxID_ANY , "" , wxDefaultPosition , wxSize( wxALL , 50 ) , wxTE_RIGHT );
	m_display->SetEditable( true );
	wxFont font = m_display->GetFont();
	font.SetPointSize( font.GetPointSize() + 18 );
	m_display->SetFont( font );

	m_debug = new wxListBox( this , wxID_ANY , wxPoint( 10 , 110 ) , wxSize( 300 , 300 ) , 0 , NULL , 0 , wxDefaultValidator , "Items" );  // Create listbox

	debugSizer->Add( m_debug , 1 , wxEXPAND | wxALL , 0 );
	displaySizer->Add( m_display , 1 , wxEXPAND | wxALL , 0 );
	topSizer->Add( displaySizer , 0 , wxEXPAND , 0 );
	topSizer->AddSpacer( 10 );

	vector<string> characters = { "C", "( )", "%", "/", "7", "8", "9",
								 "*", "4",   "5", "6", "-", "1", "2",
								 "3", "+",   "~", "0", ".", "=", "^" };
	for(int i = 0; i < characters.size(); i++) {
		m_numButtons.push_back( new wxButton( this , i , characters[i] , wxDefaultPosition , buttonSize ) );
		m_numButtons[i]->Bind( wxEVT_COMMAND_BUTTON_CLICKED , &Calculator::addToDisplay , this );
	}

	for(int num = 0; num < m_numButtons.size(); ++num) {
		buttonSizer->Add( m_numButtons[num] , 1 , wxEXPAND , 0 );
	}

	topSizer->Add( buttonSizer , 1 , wxEXPAND , 0 );
	menuSizer->Add( topSizer , 1 , wxEXPAND , 0 );
	menuSizer->Add( debugSizer , 1 , wxEXPAND , 0 );
	SetSizerAndFit( menuSizer );
}

void Calculator::addToDisplay( wxCommandEvent& evt ) {
	wxString disValue = m_display->GetValue();
	wxButton* myButton = dynamic_cast<wxButton*>(evt.GetEventObject());
	wxString symbol = myButton->GetLabelText();
	std::string stlstring = string( symbol.mb_str() );

	if(symbol.compare( "( )" ) == 0) {
		if(leftParen == rightParen) {
			disValue << " (";
			m_display->SetValue( disValue );
			leftParen++;
			return;
		}
		else if(leftParen > rightParen) {
			disValue << ") ";
			m_display->SetValue( disValue );
			rightParen++;
			return;
		}
	}
	else if(symbol.compare( "=" ) == 0) {
		getResult();
		strings.clear();
	}
	else if(symbol.compare( "C" ) == 0) {
		disValue = "";
		m_display->SetValue( disValue );
	}
	else if(disValue.IsEmpty() == true || isdigit( stlstring[0] )) {
		disValue << symbol;
	}
	else {
		disValue << " " << symbol << " ";
	}
	m_display->SetValue( disValue );
}

void Calculator::getResult() {
	wxString disValue = m_display->GetValue();
	if(rightParen != leftParen) {
		m_debug->AppendString( "Missing closing parentheses" );
		m_debug->AppendString( "0" );
		return;
	}

	string stlstring = string( disValue.mb_str() );
	int i = 0;
	removeSpaces( stlstring );
	while(i != stlstring.length()) {
		string letter = "";
		letter.push_back( stlstring[i] );

		if(isdigit( stlstring[i] ) != 0) {
			string temp = "";
			while(isdigit( stlstring[i] ) != 0) {
				temp += stlstring[i];
				i++;
			}
			strings.push_back( temp );
		}
		else {
			strings.push_back( letter );
			i++;
		}
	}

	infixToPostfix( strings );
	m_debug->AppendString( stlstring );

	double result = evaluatePostfix( strings );
	wxString mystring = wxString::Format( wxT( "%f" ) , result );
	m_debug->AppendString( mystring );
}

int Calculator::prec( string c ) {
	if(c == "^")
		return 3;
	else if(c == "*" || c == "/" || c == "%")
		return 2;
	else if(c == "+" || c == "-")
		return 1;
	else
		return -1;
}

vector<string> Calculator::infixToPostfix( vector<string>& s ) {
	stack<string> st;
	st.push( "N" );
	int l = s.size();
	vector<string> newVector;
	string ns;
	for(int i = 0; i < l; i++) {
		if(all_of( s[i].begin() , s[i].end() , ::isdigit ) != 0 && s[i] != '(' &&
			s[i] != ')') {
			newVector.push_back( s[i] );

		}
		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if(s[i] == "(") {
			st.push( "(" );
		}

		else if(s[i] == ')') {
			while(st.top() != "N" && st.top() != "(") {
				string c = st.top();
				st.pop();
				newVector.push_back( c );
			}
			if(st.top() == "(") {
				string c = st.top();
				st.pop();
			}
		}

		else {
			while(st.top() != "N" && prec( s[i] ) <= prec( st.top() )) {
				string c = st.top();
				st.pop();
				newVector.push_back( c );
			}
			st.push( s[i] );
		}
	}

	// Pop all the remaining elements from the stack
	while(st.top() != "N") {
		string c = st.top();
		st.pop();
		newVector.push_back( c );
	}

	s = newVector;
	return newVector;
}

double Calculator::evaluatePostfix( vector<string>& exp ) {
	// Create a stack of capacity equal to expression size
	stack<double> s;
	int i;
	double result = 0;

	// Scan all characters one by one
	for(i = 0; i < exp.size(); ++i) {
		// If the scanned character is an operand (number here),
		// push it to the stack.
		if(all_of( exp[i].begin() , exp[i].end() , ::isdigit ) != 0) {
			s.push( stoi( exp[i] ) );
		}
		// If the scanned character is an operator, pop two
		// elements from stack apply the operator
		else {
			double val1 = s.top();
			s.pop();
			double val2 = s.top();
			s.pop();

			if(exp[i] == "+") {
				result = val2 + val1;
				s.push( result );
			}
			else if(exp[i] == "-") {
				result = val2 - val1;
				s.push( result );
			}
			else if(exp[i] == "*") {
				result = val2 * val1;
				s.push( result );
			}
			else if(exp[i] == "/") {
				result = val2 / val1;
				s.push( result );
			}
			else if(exp[i] == "%") {
				result = fmod( val2 , val1 );
				s.push( result );
			}
		}
	}
	return s.top();
}

void Calculator::removeSpaces( string& str ) {
	int count = 0;
	string newString;
	// Traverse the given string. If current character
	// is not space, then place it at index 'count++'
	for(int i = 0; i < str.size(); i++)
		if(str[i] != ' ') newString += str[i];

	m_debug->AppendString( newString );
	str = newString;
}

Calculator::~Calculator() {}
