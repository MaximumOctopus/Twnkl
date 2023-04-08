//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmMain);
USEFORM("FormColourDialog.cpp", frmColourDialog);
USEFORM("FormAddObject.cpp", frmAddObject);
USEFORM("FormAddTransform.cpp", frmAddTransform);
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
