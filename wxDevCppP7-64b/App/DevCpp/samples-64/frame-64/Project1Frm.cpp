///-----------------------------------------------------------------
///
/// @file      Project1Frm.cpp
/// @author    user
/// Created:   6/18/2012 10:18:00 AM
/// @section   DESCRIPTION
///            Project1Frm class implementation
///
///------------------------------------------------------------------

#include "Project1Frm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Project1Frm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Project1Frm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Project1Frm::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,Project1Frm::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

Project1Frm::Project1Frm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Project1Frm::~Project1Frm()
{
}

void Project1Frm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(-1, 0), wxSize(303, 298));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, _("WxButton1"), wxPoint(76, 76), wxSize(133, 59), 0, wxDefaultValidator, _("WxButton1"));

	SetTitle(_("Project1"));
	SetIcon(wxNullIcon);
	SetSize(8,8,320,334);
	Center();
	
	////GUI Items Creation End
}

void Project1Frm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void Project1Frm::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	Destroy();
}
