//---------------------------------------------------------------------------

#ifndef FormDebugH
#define FormDebugH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmDebug : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMemo *mLoader;
	TMemo *mWorld;
	TPanel *Panel1;
	TBitBtn *OK;
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmDebug(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDebug *frmDebug;
//---------------------------------------------------------------------------
#endif
