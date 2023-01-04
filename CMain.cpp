/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#include "CMain.h"

// Event table
wxBEGIN_EVENT_TABLE(CMain, wxFrame)
	EVT_MENU(wxID_EXIT, CMain::OnQuit)
	EVT_MENU(myID_SETTINGS, CMain::OnSettings)
	EVT_MENU(wxID_ABOUT, CMain::OnAbout)
	EVT_BUTTON(myID_SENDBUTTON, CMain::OnButtonSend)
	EVT_BUTTON(myID_FILEBUTTON, CMain::OnButtonAddfile)
wxEND_EVENT_TABLE()

/// <summary>
/// Constructor with PARENT, ID, TITLE
/// </summary>
CMain::CMain()
	: wxFrame(nullptr, wxID_ANY, "Better MSN", wxDefaultPosition, wxSize(615, 865))
	, CObservable()
{
	// ======== MENU BAR CREATION ========//
	
	// Main menu bar
	m_mainMenuBar = new wxMenuBar();
	
	// Menus creation
	m_fileMenu = new wxMenu();
	m_helpMenu = new wxMenu();
	
	SetMenuBar(m_mainMenuBar);

	m_mainMenuBar->Append(m_fileMenu, _T("&File"));
	m_mainMenuBar->Append(m_helpMenu, _T("&Help"));
	
	// File menu
	m_fileMenu->Append(myID_SETTINGS, _T("Connection Settigs\tCtrl+T"));
	m_fileMenu->AppendSeparator();
	m_fileMenu->Append(wxID_EXIT, _T("&Quit"));
	
	// Help menu
	m_helpMenu->Append(wxID_ABOUT, _T("&About\tF1"));

	// ========== GUI GENERATION ========== //
	
	// Sizers
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	m_secondaryOutputSizer = new wxBoxSizer(wxVERTICAL);
	m_secondaryInputSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* secondaryInputButtonSizer = new wxBoxSizer(wxVERTICAL);
	
	// Panels
	m_panelOutput = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxTE_MULTILINE);
	m_panelOutput->SetWindowStyle(wxVSCROLL);
	m_panelOutput->SetScrollbar(wxVERTICAL, 0, 10, 100, true);
	m_panelOutput->FitInside();
	m_panelOutput->SetScrollRate(5, 5);
	m_panelInput = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxTE_MULTILINE);
	mainSizer->Add(m_panelOutput, 1, wxEXPAND | wxALL, 5);
	mainSizer->Add(m_panelInput, 0, wxEXPAND | wxRIGHT | wxBOTTOM | wxLEFT, 5);
	
	// Text input
	m_textCtrlBox = new wxTextCtrl(m_panelInput, wxID_ANY, "", wxDefaultPosition, wxSize(110, 100), wxTE_AUTO_URL | wxTE_MULTILINE);
	m_secondaryInputSizer->Add(m_textCtrlBox, 1, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 5);
	
	// Buttons
	wxButton* buttonSend = new wxButton(m_panelInput, myID_SENDBUTTON, "Send", wxDefaultPosition, wxSize(110, 30), wxTE_MULTILINE);
	wxButton* buttonAddfile = new wxButton(m_panelInput, myID_FILEBUTTON, "Add a file", wxDefaultPosition, wxSize(110, 30), wxTE_MULTILINE);
	secondaryInputButtonSizer->Add(buttonSend, 0, wxEXPAND | wxALL, 5);
	secondaryInputButtonSizer->Add(buttonAddfile, 0, wxEXPAND | wxRIGHT | wxBOTTOM | wxLEFT, 5);
	m_secondaryInputSizer->Add(secondaryInputButtonSizer);

	// Sizer structuration
	m_panelOutput->SetSizer(m_secondaryOutputSizer);
	this->SetSizer(mainSizer);
	m_panelInput->SetSizer(m_secondaryInputSizer);
	mainSizer->Layout();

	// ========= END GUI GENERATION ======== //

	// Settings instance creation
	m_settings = new CSettings();
	// Show this at start
	this->Show();
	// Show the setting dialog box on top
	m_settings->Show();
}

/// <summary>
/// Destructor
/// </summary>
CMain::~CMain()
{
	m_settings->Destroy();
}

CSettings* CMain::getSettings()
{
	return m_settings;
}

std::string CMain::getInputText()
{
	m_inputText = m_textCtrlBox->GetValue();
	return std::string(m_inputText);
}

std::string CMain::getInputContentPath()
{
	return std::string(m_inputFilePath);
}

void CMain::addContent(wxString username, wxString textMessage)
{
	m_contentList.push_back(new CContent(m_panelOutput, wxID_ANY, username, textMessage, m_inputFilePath));
	updateContent();
}

void CMain::updateContent()
{
	m_secondaryOutputSizer->Clear();
	for (CContent* iContent : m_contentList)
	{
		m_secondaryOutputSizer->Add(iContent, 0, wxEXPAND | wxALL, 5);
	}
	Layout();
}

void CMain::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void CMain::OnSettings(wxCommandEvent& WXUNUSED(event))
{
	m_settings->Show();
}

void CMain::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxLaunchDefaultBrowser("https://github.com/Paracetamol56/Cpp-Network-App");
}

void CMain::OnButtonSend(wxCommandEvent& event)
{
	// Network part
	notify(Notification::Notification_Send);

	// UI part
	if (m_inputText.empty())
	{
		wxMessageDialog WarnEmptyDialog(nullptr, "You should enter a message", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		WarnEmptyDialog.ShowModal();
	}
	else
	{
		m_contentList.push_back(new CContent(m_panelOutput, wxID_ANY, m_settings->getUsername(), m_inputText, m_inputFilePath));
		updateContent();
		m_inputText.clear();
		m_textCtrlBox->Clear();
	}
}

void CMain::OnButtonAddfile(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(nullptr, _("Open a file"), "", "",
			"", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		wxMessageDialog WarnEmptyDialog(nullptr, "Cannot open file '%s'.", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		return;
	}
	else
	{
		m_inputFilePath = openFileDialog.GetPath();
	}
}