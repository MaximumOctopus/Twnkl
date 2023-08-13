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
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

class TfrmAddObject : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *bOK;
	TBitBtn *bCancel;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TLabel *lObjectFileName;
	TComboBox *cbPrimitive;
	TEdit *eName;
	TBitBtn *bSelectNewObject;
	TGroupBox *GroupBox2;
	TBevel *Bevel2;
	TComboBox *cbPattern;
	TPanel *pPattern;
	TLabel *lPatternColour1;
	TShape *sPatternColour1;
	TShape *sPatternColour2;
	TLabel *lPatternColour2;
	TLabel *lPWidth;
	TLabel *lPHeight;
	TLabel *lPScale;
	TLabel *lPPhase;
	TLabel *lPFrequency;
	TLabel *lPLacunarity;
	TLabel *lPPersistence;
	TLabel *lPAmplitude;
	TLabel *lTexture;
	TLabel *lTexturePath;
	TEdit *ePWidth;
	TEdit *ePHeight;
	TEdit *ePScale;
	TEdit *ePPhase;
	TEdit *ePFrequency;
	TEdit *ePAmplitude;
	TEdit *ePLacunarity;
	TEdit *ePPersistence;
	TCheckBox *cbPSimple;
	TBitBtn *bOpenTexture;
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
