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

#include "FormAddTransform.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAddTransform *frmAddTransform;

__fastcall TfrmAddTransform::TfrmAddTransform(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TfrmAddTransform::cbTransformChange(TObject *Sender)
{
	switch (cbTransform->ItemIndex)
	{
	case 0:
	case 1:
		pAngle->Visible = false;
		pXYZ->Visible = true;
		break;
	case 2:
	case 3:
	case 4:
		pAngle->Visible = true;
		pXYZ->Visible = false;
		break;
	}

    TransformID = cbTransform->ItemIndex;
}


void __fastcall TfrmAddTransform::eAngleExit(TObject *Sender)
{
	angle = eAngle->Text.ToDouble();
}


void __fastcall TfrmAddTransform::eXExit(TObject *Sender)
{
	xx = eX->Text.ToDouble();
}


void __fastcall TfrmAddTransform::eYExit(TObject *Sender)
{
	yy = eY->Text.ToDouble();
}


void __fastcall TfrmAddTransform::eZExit(TObject *Sender)
{
     zz = eZ->Text.ToDouble();
}
