/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#include "CSettings.h"

// Event table
wxBEGIN_EVENT_TABLE(CSettings, wxFrame)
	EVT_RADIOBUTTON(myID_RADIOBUTTON, CSettings::onRadioButton)
	EVT_BUTTON(myID_OKBUTTON, CSettings::onButtonOk)
	EVT_BUTTON(myID_CANCELBUTTON, CSettings::onButtonCancel)
wxEND_EVENT_TABLE()

CSettings::CSettings()
	: wxFrame(nullptr, wxID_ANY, "Settings", wxDefaultPosition, wxSize(290, 210), wxDEFAULT_FRAME_STYLE &~(wxRESIZE_BORDER))
	, CObservable()
{
	// ========== GUI GENERATION ========== //
	
	// Panel
	wxPanel* panelGlobal = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500), wxTE_MULTILINE);

	// Sizer
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* flexSizer = new wxFlexGridSizer(3, 2, 5, 30);
	wxBoxSizer* statusSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ipSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	
	// Static text labels
	wxStaticText* statusLabel = new wxStaticText(panelGlobal, -1, wxT("Status"));
	wxStaticText* ipLabel = new wxStaticText(panelGlobal, -1, wxT("Destination IP"));
	wxStaticText* portLabel = new wxStaticText(panelGlobal, -1, wxT("Port"));
	wxStaticText* usernameLable = new wxStaticText(panelGlobal, -1, wxT("Username"));
	
	// Client/Server inputs
	m_clientRadioButton = new wxRadioButton(panelGlobal, myID_RADIOBUTTON, wxT("Client"));
	m_serverRadioButton = new wxRadioButton(panelGlobal, myID_RADIOBUTTON, wxT("Server"));

	// Add everything to the sizer
	statusSizer->Add(m_clientRadioButton, 1, wxEXPAND);
	statusSizer->Add(m_serverRadioButton, 1, wxEXPAND);

	// IP inputs
	for (size_t i = 0; i < 4; i++)
	{
		m_ipTextBox[i] = new wxTextCtrl(panelGlobal, wxID_ANY, "", wxDefaultPosition, wxSize(30, -1));
	}
	
	// Add everything to the sizer
	ipSizer->Add(m_ipTextBox[0], 1, wxEXPAND);
	ipSizer->Add(new wxStaticText(panelGlobal, -1, wxT(" : ")));
	ipSizer->Add(m_ipTextBox[1], 1, wxEXPAND);
	ipSizer->Add(new wxStaticText(panelGlobal, -1, wxT(" : ")));
	ipSizer->Add(m_ipTextBox[2], 1, wxEXPAND);
	ipSizer->Add(new wxStaticText(panelGlobal, -1, wxT(" : ")));
	ipSizer->Add(m_ipTextBox[3], 1, wxEXPAND);
	
	// Port input
	m_portTextBox = new wxTextCtrl(panelGlobal, -1);
	
	// Username input
	m_usernameTextBox = new wxTextCtrl(panelGlobal, -1, wxT(""), wxPoint(-1, -1), wxSize(200, -1));
	
	// Buttons
	m_buttonOk = new wxButton(panelGlobal, myID_OKBUTTON, "OK", wxDefaultPosition, wxSize(110, 30));
	m_buttonCancel = new wxButton(panelGlobal, myID_CANCELBUTTON, "Cancel", wxDefaultPosition, wxSize(110, 30));
	m_buttonCancel->Disable();
	buttonSizer->Add(m_buttonCancel, 1, wxALL, 5);
	buttonSizer->Add(m_buttonOk, 1, wxALL, 5);

	// Add everything to the sizer
	flexSizer->Add(statusLabel, 1, wxEXPAND);
	flexSizer->Add(statusSizer, 1, wxEXPAND);
	flexSizer->Add(ipLabel);
	flexSizer->Add(ipSizer, 1, wxEXPAND);
	flexSizer->Add(portLabel);
	flexSizer->Add(m_portTextBox, 1, wxEXPAND);
	flexSizer->Add(usernameLable);
	flexSizer->Add(m_usernameTextBox, 1, wxEXPAND);
	mainSizer->Add(flexSizer, 1, wxEXPAND | wxALL, 10);
	mainSizer->Add(buttonSizer, 1, wxEXPAND);
	
	mainSizer->Layout();
	panelGlobal->SetSizer(mainSizer);

	// ======== END GUI GENERATION ======== //

	wxTopLevelWindow();
	EnableCloseButton(false);
}

CSettings::~CSettings()
{
}

bool CSettings::getStatusIsServer()
{
	return m_serverRadioButton->GetValue();
}

std::string CSettings::getIPAdress()
{
	return m_IPAdressInput;
}

char* CSettings::getIPAdressChar()
{
	char IPAdressChar[15];
	memcpy(IPAdressChar, m_IPAdressInput.c_str(), 15);

	return(IPAdressChar);
}

int CSettings::getPort()
{
	return m_portInput;
}

std::string CSettings::getUsername()
{
	return m_usernameInput;
}

void CSettings::onRadioButton(wxCommandEvent& WXUNUSED(event))
{
	if (m_serverRadioButton->GetValue())
	{
		for (wxTextCtrl* iIpTextBox : m_ipTextBox)
		{
			iIpTextBox->Enable(false);
		}
	}
	else
	{
		for (wxTextCtrl* iIpTextBox : m_ipTextBox)
		{
			iIpTextBox->Enable(true);
		}
	}
}

void CSettings::onButtonOk(wxCommandEvent& WXUNUSED(event))
{
	if (isValid())
	{
		// Add the IP adress to the private attribute
		if (m_clientRadioButton->GetValue())
		{
			m_IPAdressInput = "";
			for (size_t i = 0; i < 3; i++)
			{
				m_IPAdressInput += m_ipTextBox[i]->GetValue();
				m_IPAdressInput += '.';
			}
			m_IPAdressInput += m_ipTextBox[3]->GetValue();
		}
		else
		{
			m_IPAdressInput = "127.0.0.1";
		}

		// Add the port adress to the private attribute
		m_portInput = std::stoi(std::string(m_portTextBox->GetValue()));     

		// Add the port adress to the private attribute
		m_usernameInput = std::string(m_usernameTextBox->GetValue());

		m_buttonCancel->Enable();
		this->Hide();

		// Notify the App
		notify(Notification::Notification_State);
	}
	// Else : nothing
}

void CSettings::onButtonCancel(wxCommandEvent& WXUNUSED(event))
{
	this->Hide();
}

bool CSettings::isValid()
{
	// Checking for errors in IP adress
	if (m_clientRadioButton->GetValue())
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (m_ipTextBox[i]->GetValue().empty() == true)
			{
				wxMessageDialog WarnEmptyDialog(nullptr, "The IP Adress is not complete", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
				WarnEmptyDialog.ShowModal();
				return false;
			}

			if (m_ipTextBox[i]->GetValue().IsNumber() == false)
			{
				wxMessageDialog WarnEmptyDialog(nullptr, "The IP Adress is not a integer", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
				WarnEmptyDialog.ShowModal();
				return false;
			}
		}

		for (size_t i = 0; i < 4; i++)
		{
			int ipNum = std::stoi(std::string(m_ipTextBox[i]->GetValue()));
			if (ipNum > 254 || ipNum < 0)
			{
				wxMessageDialog WarnEmptyDialog(nullptr, "The IP Adress should be between 0.0.0.0 and 254.254.254.254", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
				WarnEmptyDialog.ShowModal();
				return false;
			}
		}
	}

	// Checking for errors in port
	if (m_portTextBox->GetValue().empty() == true)
	{
		wxMessageDialog WarnEmptyDialog(nullptr, "The port is empty", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		WarnEmptyDialog.ShowModal();
		return false;
	}

	if (m_portTextBox->GetValue().IsNumber() == false)
	{
		wxMessageDialog WarnEmptyDialog(nullptr, "The port is not a integer", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		WarnEmptyDialog.ShowModal();
		return false;
	}

	int portNum = std::stoi(std::string(m_portTextBox->GetValue()));
	if (portNum > 49151 || portNum < 1023)
	{
		wxMessageDialog WarnEmptyDialog(nullptr, "The port should be between 1024 and 49150", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		WarnEmptyDialog.ShowModal();
		return false;
	}

	// Checking for errors in username
	if (m_usernameTextBox->GetValue().empty() == true)
	{
		wxMessageDialog WarnEmptyDialog(nullptr, "The username is empty", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		WarnEmptyDialog.ShowModal();
		return false;
	}
	
	return true;
}