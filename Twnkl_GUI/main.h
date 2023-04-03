//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBitBtn *bOpenSource;
	TBitBtn *bRender;
	TPanel *Panel2;
	TPanel *Panel3;
	TPaintBox *PaintBox1;
	TBitBtn *BitBtn1;
	TCheckBox *cbResizeToDisplay;
	TTreeView *tvObjects;
	TPageControl *PageControl1;
	TTabSheet *tsMaterial;
	TPageControl *PageControl2;
	TTabSheet *tsBasic;
	TTabSheet *tsPattern;
	TLabel *Label7;
	TTrackBar *tbTransparency;
	TTrackBar *tbSpecular;
	TLabel *Label6;
	TLabel *Label5;
	TTrackBar *tbShininess;
	TTrackBar *tbIoR;
	TLabel *Label4;
	TLabel *Label3;
	TTrackBar *tbReflectivity;
	TTrackBar *tbDiffuse;
	TLabel *Label2;
	TLabel *Label1;
	TTrackBar *tbAmbient;
	TShape *sMaterialColour;
	TLabel *Label8;
	TLabel *Label9;
	TShape *sPatternColour1;
	TLabel *Label10;
	TShape *sPatternColour2;
	TTabSheet *TabSheet3;
	TStatusBar *sbMain;
	TTabSheet *Transforms;
	TLabel *lSurfaceColourWarning;
	TTabSheet *tsCamera;
	TTabSheet *tsLight;
	TListBox *lbObjectTransforms;
	TPanel *pOTAngle;
	TLabel *Label11;
	TEdit *eOTAngle;
	TLabel *Label15;
	TPanel *pOTXYZ;
	TLabel *Label12;
	TEdit *eOTX;
	TEdit *eOTY;
	TEdit *eOTZ;
	TLabel *Label14;
	TLabel *Label13;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall bOpenSceneClick(TObject *Sender);
	void __fastcall bRenderClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall tvObjectsClick(TObject *Sender);
	void __fastcall sMaterialColourMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sPatternColour1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tbAmbientExit(TObject *Sender);
	void __fastcall lbObjectTransformsClick(TObject *Sender);
	void __fastcall eOTAngleExit(TObject *Sender);
	void __fastcall eOTXExit(TObject *Sender);
private:	// User declarations
	void ConfigureTabLayoutFor(int);
	void PopulateTreeView();
	void BuildMaterialPanelFromObject(int);
	void BuildTransformTab(int, int);
    void UpdateTransformTab(int, int, int);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
