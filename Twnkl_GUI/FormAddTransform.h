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

#ifndef FormAddTransformH
#define FormAddTransformH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>

class TfrmAddTransform : public TForm
{
__published:	// IDE-managed Components
	TPanel *pAngle;
	TLabel *Label16;
	TLabel *Label17;
	TEdit *eAngle;
	TPanel *pXYZ;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *eX;
	TEdit *eY;
	TEdit *eZ;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TComboBox *cbTransform;
	void __fastcall cbTransformChange(TObject *Sender);
	void __fastcall eAngleExit(TObject *Sender);
	void __fastcall eXExit(TObject *Sender);
	void __fastcall eYExit(TObject *Sender);
	void __fastcall eZExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAddTransform(TComponent* Owner);

    int TransformID = 0;
	double angle = 0;
	double xx = 0;
	double yy = 0;
	double zz = 0;
};

extern PACKAGE TfrmAddTransform *frmAddTransform;

#endif
