//---------------------------------------------------------------------------
//
// Name:        Project1App.cpp
// Author:      user
// Created:     6/18/2012 10:18:00 AM
// Description: 
//
//---------------------------------------------------------------------------

#include "Project1App.h"
#include "Project1Frm.h"

IMPLEMENT_APP(Project1FrmApp)

bool Project1FrmApp::OnInit()
{
    Project1Frm* frame = new Project1Frm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int Project1FrmApp::OnExit()
{
	return 0;
}
