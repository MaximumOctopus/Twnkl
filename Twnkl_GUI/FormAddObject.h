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

#ifndef FormAddObjectH
#define FormAddObjectH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "Object.h"

class TfrmAddObject : public TForm
{
__published:	// IDE-managed Components
	TComboBox *cbPrimitive;
	TBitBtn *bOK;
	TBitBtn *bCancel;
	TEdit *eName;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TComboBox *cbPattern;
	TPanel *pPattern;
	TLabel *lPatternColour1;
	TShape *sPatternColour1;
	TShape *sPatternColour2;
	TLabel *lPatternColour2;
	TLabel *lPWidth;
	TLabel *lPHeight;
	TEdit *ePWidth;
	TEdit *ePHeight;
	TEdit *ePScale;
	TLabel *lPScale;
	TLabel *lPPhase;
	TEdit *ePPhase;
	TEdit *ePFrequency;
	TLabel *lPFrequency;
	TEdit *ePAmplitude;
	TEdit *ePLacunarity;
	TLabel *lPLacunarity;
	TLabel *lPPersistence;
	TEdit *ePPersistence;
	TLabel *lPAmplitude;
	TCheckBox *cbPSimple;
	TLabel *lTexture;
	TBitBtn *bOpenTexture;
	TLabel *lTexturePath;
	void __fastcall cbPrimitiveChange(TObject *Sender);
	void __fastcall eNameExit(TObject *Sender);
	void __fastcall cbPatternChange(TObject *Sender);
	void __fastcall bOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sPatternColour1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAddObject(TComponent* Owner);

    PatternProperties Properties;

	std::wstring Name = L"";
	int SelectedPattern = 0;
	int SelectedPrimitive = 0;
};

extern PACKAGE TfrmAddObject *frmAddObject;

#endif
