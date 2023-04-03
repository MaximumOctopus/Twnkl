

#include <vcl.h>
#pragma hdrstop

#include "FormColourDialog.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmColourDialog *frmColourDialog;


__fastcall TfrmColourDialog::TfrmColourDialog(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TfrmColourDialog::tbRedChange(TObject *Sender)
{
	SelectedColour = (tbBlue->Position << 16) + (tbGreen->Position << 8) + tbRed->Position;

    sShapeColour->Brush->Color = TColor(SelectedColour);
}
