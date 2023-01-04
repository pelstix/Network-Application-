/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#pragma once

#ifndef CCONTENT_H_INCLUDED
#define CCONTENT_H_INCLUDED

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/dc.h>
#include "CImagePanel.h"
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

// Memory leaks detection
#include "wxmemdbg.h"

class CContent : public wxPanel
{
public:
	// Public constructor and destructor
	CContent(wxWindow* parent = nullptr, wxWindowID id = wxID_ANY, const wxString username = "", const wxString textMessage = "", const wxString filePath = "");
	~CContent();

protected:
	// Message time
	std::chrono::time_point<std::chrono::system_clock> m_contentTime;
	// Message username
	wxString m_username = "";
	// Message string
	wxString m_textMessage = "";
	// File path
	wxString m_filePath = "";
	//Image
	CImagePanel* m_imagePanel = nullptr;
};

#endif CCONTENT_H_INCLUDED