/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#pragma once

#ifndef CSETTINGS_H_INCLUDED
#define CSETTINGS_H_INCLUDED

#include "CObservable.h"
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <wx/utils.h>
#include <wx/event.h>
#include <string>
#include <cstring>

// Memory leaks detection
#include "wxmemdbg.h"

wxDEFINE_EVENT(myID_RADIOBUTTON, wxCommandEvent);
wxDEFINE_EVENT(myID_OKBUTTON, wxCommandEvent);
wxDEFINE_EVENT(myID_CANCELBUTTON, wxCommandEvent);

class CSettings
	: public wxFrame
	, public CObservable
{
private:
	// Client/Server
	wxRadioButton* m_clientRadioButton;
	wxRadioButton* m_serverRadioButton;
	bool m_isServer = false;

	// IP adress
	wxTextCtrl* m_ipTextBox[4];
	std::string m_IPAdressInput = "";
	
	// Port
	wxTextCtrl* m_portTextBox;
	int m_portInput = -1;
	
	// Username
	wxTextCtrl* m_usernameTextBox;
	std::string m_usernameInput = "";

	// Button pointers
	wxButton* m_buttonOk;
	wxButton* m_buttonCancel;

public:
	// Public constructor and destructor
	CSettings();
	~CSettings();

public:
	bool getStatusIsServer();
	std::string getIPAdress();
	char* getIPAdressChar();
	int getPort();
	std::string getUsername();


private:
	
	// UI events
	void onRadioButton(wxCommandEvent& event);
	void onButtonOk(wxCommandEvent& event);
	void onButtonCancel(wxCommandEvent& event);

	// Checkinf function
	bool isValid();

	wxDECLARE_EVENT_TABLE();
};

#endif // CSETTINGS_H_INCLUDED