//
// TwnklX 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/Twnkl
//
//

#include <vcl.h>
#pragma hdrstop

#include "FormAbout.h"

#include "Constants.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAbout *frmAbout;

__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
	std::wstring c = __TwnklVersion + L" // " + __TwnklDate;

	lVersion->Caption = c.c_str();
}

