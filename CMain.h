/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#pragma once

#ifndef CMAIN_H_INCLUDED
#define CMAIN_H_INCLUDED

#include "CSettings.h"
#include "CContent.h"
#include "CObservable.h"
#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/wfstream.h>
#include <wx/utils.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <string>
#include <list>

// Memory leaks detection
#include "wxmemdbg.h"

wxDEFINE_EVENT(myID_SETTINGS, wxCommandEvent);
wxDEFINE_EVENT(myID_SENDBUTTON, wxCommandEvent);
wxDEFINE_EVENT(myID_FILEBUTTON, wxCommandEvent);

/// <summary>
/// Main frame class
/// </summary>
class CMain
	: public wxFrame
	, public CObservable
{
public:
	// Public constructor and destructor
	CMain();
	~CMain();

protected:
	// Menus
	wxMenuBar* m_mainMenuBar;
	wxMenu* m_fileMenu;
	wxMenu* m_helpMenu;
	// Child frame
	CSettings* m_settings;

private:
	// Panels
	wxScrolledWindow* m_panelOutput;
	wxPanel* m_panelInput;
	// Output sizer
	wxBoxSizer* m_secondaryOutputSizer;
	wxBoxSizer* m_secondaryInputSizer;
	// Text ctrl
	wxTextCtrl* m_textCtrlBox;
	// Data from input
	wxString m_inputText = "";
	wxString m_inputFilePath = "";
	std::list<CContent*> m_contentList = {};

public:
	// Getter for inputs data
	CSettings* getSettings();
	std::string getInputText();
	std::string getInputContentPath();
	// Add a content object
	void addContent(wxString username, wxString textMessage);
	// Main update methode
	void updateContent();

private:
	// Menu events
	void OnQuit(wxCommandEvent& event);
	void OnSettings(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	// UI events
	void OnButtonSend(wxCommandEvent& event);
	void OnButtonAddfile(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif // CMAIN_H_INCLUDED