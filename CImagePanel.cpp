/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

// Constructor macro
#define PANELCTOR   m_image.LoadFile(filePath, format);\
                    w = m_image.GetSize().GetWidth();\
                    h = m_image.GetSize().GetHeight();

 // >>> CREDIT : wxWidgets Wiki > https://wiki.wxwidgets.org/An_image_panel
#include "CImagePanel.h"

 // Event table
wxBEGIN_EVENT_TABLE(CImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(CImagePanel::paintEvent)
//Size event
EVT_SIZE(CImagePanel::OnSize)
wxEND_EVENT_TABLE()

// some useful events
/*
 void wxImagePanel::mouseMoved(wxMouseEvent& event) {}
 void wxImagePanel::mouseDown(wxMouseEvent& event) {}
 void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
 void wxImagePanel::mouseReleased(wxMouseEvent& event) {}
 void wxImagePanel::rightClick(wxMouseEvent& event) {}
 void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
 void wxImagePanel::keyPressed(wxKeyEvent& event) {}
 void wxImagePanel::keyReleased(wxKeyEvent& event) {}
 */

CImagePanel::CImagePanel(wxPanel* parent, wxString filePath, wxBitmapType format) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 200))
{
    // load the file... ideally add a check to see if loading was successful
    PANELCTOR
}

CImagePanel::CImagePanel(wxFrame* parent, wxString filePath, wxBitmapType format) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
    PANELCTOR
}


CImagePanel::~CImagePanel()
{
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
void CImagePanel::paintEvent(wxPaintEvent& evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void CImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void CImagePanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

/*
 * Here we do the actual rendering.I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g.wxPaintDC or wxClientDC) is used.
 */
void CImagePanel::render(wxDC& dc)
{
    // Fix a static value for h
    int newh = 200;
    // Compute a new value for w
    int neww = w * (200.0f / h);

    if (neww != w || newh != h)
    {
        m_resized = wxBitmap(m_image.Scale(neww, newh, wxIMAGE_QUALITY_HIGH));
        w = neww;
        h = newh;
        dc.DrawBitmap(m_resized, 0, 0, false);
    }
    else {
        dc.DrawBitmap(m_resized, 0, 0, false);
    }
}
