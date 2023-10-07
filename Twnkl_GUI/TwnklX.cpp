//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmMain);
USEFORM("FormAddTransform.cpp", frmAddTransform);
USEFORM("FormAddObject.cpp", frmAddObject);
USEFORM("FormAbout.cpp", frmAbout);
USEFORM("FormColourDialog.cpp", frmColourDialog);
USEFORM("FormDebug.cpp", frmDebug);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmColourDialog), &frmColourDialog);
		Application->CreateForm(__classid(TfrmAddObject), &frmAddObject);
		Application->CreateForm(__classid(TfrmAddTransform), &frmAddTransform);
		Application->CreateForm(__classid(TfrmAbout), &frmAbout);
		Application->CreateForm(__classid(TfrmDebug), &frmDebug);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
