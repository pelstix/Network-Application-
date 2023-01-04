/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#include "CApp.h"

#pragma comment(lib, "Ws2_32.lib")

// Entry point definition
wxIMPLEMENT_APP(CApp);
wxDECLARE_APP(CApp);

/// <summary>
/// Constructor
/// </summary>
CApp::CApp()
{
    // Socket initializing
    WSAStartup(MAKEWORD(2, 0), &wsa);
}

/// <summary>
/// Destructor
/// </summary>
CApp::~CApp()
{
    closesocket(sock);
    WSACleanup();
}

/// <summary>
/// Main launcher methode
/// </summary>
/// <returns>
/// Always true
/// </returns>
bool CApp::OnInit()
{
    m_mainFrame = new CMain;
    m_mainFrame->Show();

    m_mainFrame->getSettings()->atach(this);
    m_mainFrame->atach(this);

    return true;
}

/// <summary>
/// Update the state (server/client) when the Ok button is pressed in settings
/// </summary>
void CApp::update(Notification notif)
{
    switch (notif)
    {
        // CASE : update the state (Client/Server)
    case Notification::Notification_State:
    {
        // IF SERVER SIDE
        if (m_mainFrame->getSettings()->getStatusIsServer())
        {
            // Change the main window title
            m_mainFrame->SetTitle("Better MSN - Serveur");

            // Socket creation
            sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            // Create the structure describing various Server parameters
            sin.sin_family = AF_INET;
            sin.sin_addr.s_addr = INADDR_ANY;
            sin.sin_port = htons(m_mainFrame->getSettings()->getPort());

            // Socket configuration to listen the port
            if (bind(sock, (SOCKADDR*)&sin, sizeof(sin)) < 0)
            {
                // If an error occure when binding the socket : display a ERROR message dialog
                wxMessageDialog ErrorEmptyDialog(nullptr, "Socket bind failed", "ERROR", wxICON_STOP | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
                ErrorEmptyDialog.ShowModal();
            }

            // No queue
            listen(sock, 0);

            // Initialize the listening mode to WRITE
            m_listen = false;
        }
        // IF CLIENT SIDE
        else
        {
            // Change the main window title
            m_mainFrame->SetTitle("Better MSN - Client");

            // Socket creation
            sock = socket(AF_INET, SOCK_STREAM, 0);

            // Create the structure describing various Server parameters
            sin.sin_family = AF_INET;
            inet_pton(AF_INET, m_mainFrame->getSettings()->getIPAdressChar(), &sin.sin_addr.s_addr);
            sin.sin_port = htons(m_mainFrame->getSettings()->getPort());

            // Socket connection
            if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0 )
            {
                wxMessageDialog ErrorEmptyDialog(nullptr, "Socket connection failed", "ERROR", wxICON_STOP | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
                ErrorEmptyDialog.ShowModal();
            }

            // Initialize the listening mode to READ
            m_listen = true;

            // Launch the listening methode
            std::thread m_listeningThread(&CApp::Listen, this);
            m_listeningThread.detach();
        }
    }
        break;
        // CASE : send a message
    case Notification::Notification_Send:
        // Writing mode verification
        if(m_listen == false)
        {
            // Valid socket verification
            if (sock != INVALID_SOCKET)
            {
                // IF SERVER SIDE
                if (m_mainFrame->getSettings()->getStatusIsServer())
                {
                    // Temporary socket creation (to accepte the connection)
                    SOCKET server;
                    SOCKADDR_IN sinserv;

                    // Initialize m_sinsize
                    m_sinsize = sizeof(sinserv);

                    // Accepting the connection
                    if ((server = accept(sock, (SOCKADDR*)&sinserv, &m_sinsize)) != INVALID_SOCKET)
                    {
                        // Data structure creation
                        // Parameters : username, input text
                        CDataStructure transfertData(m_mainFrame->getSettings()->getUsername(), m_mainFrame->getInputText());

                        // Try sending
                        if (send(server, (char*)&transfertData, sizeof(transfertData), 0) < 0)
                        {
                            // If an error occure when sending : display a ERROR message dialog
                            wxMessageDialog ErrorEmptyDialog(nullptr, "Send failed", "ERROR", wxICON_WARNING | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
                            ErrorEmptyDialog.ShowModal();
                        }
                    }
                    else
                    {
                        // If an error occure when accepting the socket : display a ERROR message dialog
                        wxMessageDialog ErrorEmptyDialog(nullptr, "Socket connection not accepted", "ERROR", wxICON_WARNING | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
                        ErrorEmptyDialog.ShowModal();
                    }

                    // Close the temporary socket
                    closesocket(server);
                }
                // IF CLIENT SIDE
                else
                {
                    // Data structure creation
                    // Parameters : username, input text
                    CDataStructure transfertData(m_mainFrame->getSettings()->getUsername(), m_mainFrame->getInputText());

                    // Try sending
                    if (send(sock, (char*)&transfertData, sizeof(transfertData), 0) < 0)
                    {
                        // If an error occure when sending : display a ERROR message dialog
                        wxMessageDialog ErrorEmptyDialog(nullptr, "Send failed", "ERROR", wxICON_WARNING | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
                        ErrorEmptyDialog.ShowModal();
                    }
                }

                // Set the application in listening mode
                m_listen = true;

                // Launch the listening methode
                std::thread m_listeningThread(&CApp::Listen, this);

                m_listeningThread.detach();
            }
            else
            {
                // If the socket is invalid : display a ERROR message dialog
                wxMessageDialog ErrorEmptyDialog(nullptr, "Invalid socket", "ERROR", wxICON_STOP | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
                ErrorEmptyDialog.ShowModal();
            }
        }
        else
        {
            // If the application is not in writing mode : display a ERROR message dialog
            wxMessageDialog ErrorEmptyDialog(nullptr, "This is not your turn", "ERROR", wxICON_WARNING | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
            ErrorEmptyDialog.ShowModal();
        }
        break;
    default:
        break;
    }
}

/// <summary>
/// Listening for connections and receive messages
/// </summary>
void CApp::Listen()
{
    // Reading mode verification
    if (m_listen)
    {
        // IF SERVER SIDE
        if (m_mainFrame->getSettings()->getStatusIsServer())
        {
            // Temporary socket creation (to accepte the connection)
            SOCKET server;
            SOCKADDR_IN sinserv;

            // Initialize m_sinsize
            m_sinsize = sizeof(sinserv);

            // Accepting the connection
            if ((server = accept(sock, (SOCKADDR*)&sinserv, &m_sinsize)) != INVALID_SOCKET)
            {
                // Empty data structure creation to recieve new message
                CDataStructure ClientData;

                // Wait for receiving a message
                recv(server, (char*)&ClientData, sizeof(ClientData), 0);

                // Add the message to the main frame
                m_mainFrame->addContent(ClientData.m_name, ClientData.m_message);
            }

            // Close the temporary socket
            closesocket(server);
        }
        // IF CLIENT SIDE
        else
        {
            // Initialize m_sinsize
            m_sinsize = sizeof(sin);

            // Empty data structure creation to recieve new message
            CDataStructure ServerData;

            // Wait for receiving a message
            recv(sock, (char*)&ServerData, sizeof(ServerData), 0);

            // Add the message to the main frame
            m_mainFrame->addContent(ServerData.m_name, ServerData.m_message);
        }


        // Set the application in listening mode
        m_listen = false;
    }
}
