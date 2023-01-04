/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#pragma once

#ifndef CAPP_H_INCLUDED
#define CAPP_H_INCLUDED

#include <ws2tcpip.h>
#include <wx/wx.h>
#include <stdio.h>
#include <thread>

#include "CMain.h"
#include "CDataStructure.h"
#include "CObserver.h"

// Memory leaks detection
#include "wxmemdbg.h"

#pragma comment(lib,"ws2_32.lib")

#define _WINSOCKAPI_ // This is to avoid conflict between winsock2 an wxWidget

/// <summary>
/// Main app class
/// </summary>
class CApp
	: public wxApp
	, public CObserver
{
private:

	bool m_listen = false;
	int m_sinsize = 0;

public:
	
	// Public constructor and destructor
	CApp();
	~CApp();

private:
	
	// Private data to store the main frame
	CMain* m_mainFrame = nullptr;

	// Update server/client state
	// Override the update methode from CObserver
	void update(Notification notif) override;

public:
	
	// Launcher methode
	virtual bool OnInit();
	// Listening loop
	void Listen();

private:
	
	// Network stuff
	WSADATA wsa;

	// Main socket
	SOCKET sock;

	// Socket informations
	SOCKADDR_IN sin;
};

#endif // CAPP_H_INCLUDED