#include <memory>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
class MyApp : public wxApp
{
public:
  auto OnInit() -> bool override;
};
class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
  void OnHello(wxCommandEvent const &event);
  void OnExit(wxCommandEvent const &event);
  void OnAbout(wxCommandEvent const &event);
};
enum
{
    ID_Hello = 1
};
wxIMPLEMENT_APP(MyApp);
bool
MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
    // wxMenu *menuFile = new wxMenu;
    auto menuFile = std::make_unique<wxMenu>();
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    // wxMenu *menuHelp = new wxMenu;
    auto menuHelp = std::make_unique<wxMenu>();
    menuHelp->Append(wxID_ABOUT);
    // wxMenuBar *menuBar = new wxMenuBar;
    auto menuBar = std::make_unique<wxMenuBar>();
    menuBar->Append(menuFile.release(), "&File");
    menuBar->Append(menuHelp.release(), "&Help");
    SetMenuBar(menuBar.release());
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
void
MyFrame::OnExit(wxCommandEvent const &event)
{
    Close(true);
}
void
MyFrame::OnAbout(wxCommandEvent const &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
void
MyFrame::OnHello(wxCommandEvent const &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
