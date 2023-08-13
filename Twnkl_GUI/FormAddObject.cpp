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

#include "FormAddObject.h"
#include "FormColourDialog.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmAddObject *frmAddObject;

__fastcall TfrmAddObject::TfrmAddObject(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TfrmAddObject::cbPrimitiveChange(TObject *Sender)
{
	SelectedPrimitive = cbPrimitive->ItemIndex;

	if (SelectedPrimitive == 3)
	{
		lObjectFileName->Visible = true;
		bSelectNewObject->Visible = true;

		bOK->Enabled = !lObjectFileName->Caption.IsEmpty();
	}
	else
	{
		lObjectFileName->Visible = false;
		bSelectNewObject->Visible = false;

        bOK->Enabled = true;
    }
}


void __fastcall TfrmAddObject::eNameExit(TObject *Sender)
{
	Name = eName->Text.c_str();
}


void __fastcall TfrmAddObject::cbPatternChange(TObject *Sender)
{
	SelectedPattern = cbPattern->ItemIndex;

	if (cbPattern->ItemIndex == 0)
	{
		pPattern->Visible = false;

		return;
	}

	pPattern->Visible = true;

	if (SelectedPattern >= 5 && SelectedPattern <= 7)
	{
		sPatternColour1->Visible = true;
		sPatternColour2->Visible = false;
		lPatternColour1->Visible = true;
		lPatternColour2->Visible = false;
	}
	else if (SelectedPattern == 11)
	{
		sPatternColour1->Visible = false;
		sPatternColour2->Visible = false;
		lPatternColour1->Visible = false;
		lPatternColour2->Visible = false;
	}
	else
	{
		sPatternColour1->Visible = true;
		sPatternColour2->Visible = true;
		lPatternColour1->Visible = true;
		lPatternColour2->Visible = true;
	}

	if (SelectedPattern == 2)
	{
		ePFrequency->Visible = true;
		ePAmplitude->Visible = true;
		ePLacunarity->Visible = true;
		ePPersistence->Visible = true;
		lPFrequency->Visible = true;
		lPAmplitude->Visible = true;
		lPLacunarity->Visible = true;
		lPPersistence->Visible = true;
	}
	else
	{
		ePFrequency->Visible = false;
		ePAmplitude->Visible = false;
		ePLacunarity->Visible = false;
		ePPersistence->Visible = false;
		lPFrequency->Visible = false;
		lPAmplitude->Visible = false;
		lPLacunarity->Visible = false;
		lPPersistence->Visible = false;
	}

	if (SelectedPattern >= 5 && SelectedPattern <= 7)
	{
		ePScale->Visible = true;
		lPScale->Visible = true;

		if (SelectedPattern == 7)
		{
			ePPhase->Visible = true;
			lPPhase->Visible = true;
		}
		else
		{
			ePPhase->Visible = false;
			lPPhase->Visible = false;
		}
	}
	else
	{
		ePPhase->Visible = false;
		ePScale->Visible = false;
		lPPhase->Visible = false;
		lPScale->Visible = false;
	}

	if ((SelectedPattern >= 5 && SelectedPattern <= 7) || SelectedPattern == 1)
	{
		ePWidth->Visible = true;
		ePHeight->Visible = true;
		lPWidth->Visible = true;
		lPHeight->Visible = true;
	}
	else
	{
		ePWidth->Visible = false;
		ePHeight->Visible = false;
		lPWidth->Visible = false;
		lPHeight->Visible = false;
	}

	if (SelectedPattern == 9)
	{
		cbPSimple->Visible = true;
	}
	else
	{
		cbPSimple->Visible = false;
	}

	if (SelectedPattern == 11)
	{
		lTexture->Visible = true;
		lTexturePath->Visible = true;
		bOpenTexture->Visible = true;
	}
	else
	{
		lTexture->Visible = false;
		lTexturePath->Visible = false;
		bOpenTexture->Visible = false;
	}
}


void __fastcall TfrmAddObject::bOKClick(TObject *Sender)
{
	Properties.Colour1.FromIntBGR(sPatternColour1->Brush->Color);
	Properties.Colour2.FromIntBGR(sPatternColour2->Brush->Color);

	Properties.u = ePWidth->Text.ToDouble();
	Properties.v = ePHeight->Text.ToDouble();

	Properties.scale = ePScale->Text.ToDouble();
	Properties.phase = ePPhase->Text.ToDouble();
	Properties.frequency = ePFrequency->Text.ToDouble();
	Properties.amplitude = ePAmplitude->Text.ToDouble();
	Properties.lacunarity = ePLacunarity->Text.ToDouble();
	Properties.persistence = ePPersistence->Text.ToDouble();

	Properties.simple = cbPSimple->Checked;

	Properties.FileName = lTexturePath->Caption.c_str();
}


void __fastcall TfrmAddObject::FormShow(TObject *Sender)
{
	sPatternColour1->Brush->Color = TColor(Properties.Colour1.ToIntBGR());
	sPatternColour2->Brush->Color = TColor(Properties.Colour2.ToIntBGR());

	ePWidth->Text = Properties.u;
	ePHeight->Text = Properties.v;

	ePScale->Text = Properties.scale;
	ePPhase->Text = Properties.phase;
	ePFrequency->Text = Properties.frequency;
	ePAmplitude->Text = Properties.amplitude;
	ePLacunarity->Text = Properties.lacunarity;
	ePPersistence->Text = Properties.persistence;

	cbPSimple->Checked = Properties.simple;

    lTexturePath->Caption = Properties.FileName.c_str();
}


void __fastcall TfrmAddObject::sPatternColour1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	TShape *shape = (TShape*)Sender;

	frmColourDialog->SelectedColour = int(shape->Brush->Color);

	if (frmColourDialog->ShowModal() == mrOk)
	{
		shape->Brush->Color = TColor(frmColourDialog->SelectedColour);
	}
}
//---------------------------------------------------------------------------

