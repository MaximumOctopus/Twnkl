//---------------------------------------------------------------------------

#ifndef FormColourDialogH
#define FormColourDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmColourDialog : public TForm
{
__published:	// IDE-managed Components
	TShape *sShapeColour;
	TTrackBar *tbRed;
	TTrackBar *tbGreen;
	TTrackBar *tbBlue;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBevel *Bevel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	void __fastcall tbRedChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmColourDialog(TComponent* Owner);

    int SelectedColour = 0;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmColourDialog *frmColourDialog;
//---------------------------------------------------------------------------
#endif