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

#ifndef mainH
#define mainH
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>

#include "Object.h"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBitBtn *bOpenScene;
	TBitBtn *bRender;
	TPanel *Panel2;
	TPanel *pRender;
	TTreeView *tvObjects;
	TPageControl *pcMain;
	TTabSheet *tsMaterial;
	TPageControl *pcMaterial;
	TTabSheet *tsBasic;
	TTabSheet *tsPattern;
	TLabel *Label7;
	TTrackBar *tbTransparency;
	TTrackBar *tbSpecular;
	TLabel *Label6;
	TLabel *Label5;
	TTrackBar *tbShininess;
	TLabel *Label4;
	TLabel *Label3;
	TTrackBar *tbReflectivity;
	TTrackBar *tbDiffuse;
	TLabel *Label2;
	TLabel *Label1;
	TTrackBar *tbAmbient;
	TShape *sMaterialColour;
	TLabel *Label8;
	TLabel *lPatternColour1;
	TShape *sPatternColour1;
	TLabel *lPatternColour2;
	TShape *sPatternColour2;
	TTabSheet *tsTransforms;
	TStatusBar *sbMain;
	TTabSheet *tsMaterialTransforms;
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
	TListBox *lbPatternTransforms;
	TPanel *pPTAngle;
	TLabel *Label16;
	TLabel *Label17;
	TEdit *ePTAngle;
	TPanel *pPTXYZ;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *ePTX;
	TEdit *ePTY;
	TEdit *ePTZ;
	TLabel *Label21;
	TShape *sLightIntensity;
	TComboBox *cbPatternChangeTo;
	TLabel *Label22;
	TSpeedButton *sbAddObject;
	TSpeedButton *sbDeleteObject;
	TSpeedButton *sbAddMaterialTransform;
	TSpeedButton *sbDeleteMaterialTransform;
	TSpeedButton *sbAddTransform;
	TSpeedButton *sbDeleteTransform;
	TBitBtn *bSaveScene;
	TLabel *Label23;
	TLabel *lPatternDesign;
	TSpeedButton *sbPatternChange;
	TLabel *lPScale;
	TEdit *ePScale;
	TLabel *lPPhase;
	TEdit *ePPhase;
	TEdit *ePFrequency;
	TEdit *ePAmplitude;
	TLabel *lPAmplitude;
	TLabel *lPFrequency;
	TEdit *ePLacunarity;
	TEdit *ePPersistence;
	TLabel *lPPersistence;
	TLabel *lPLacunarity;
	TEdit *ePWidth;
	TEdit *ePHeight;
	TLabel *lPHeight;
	TLabel *lPWidth;
	TBitBtn *bNew;
	TLabel *Label32;
	TEdit *eCFoV;
	TLabel *Label33;
	TEdit *eCFromX;
	TEdit *eCFromY;
	TEdit *eCFromZ;
	TLabel *Label34;
	TEdit *eCToX;
	TEdit *eCToY;
	TEdit *eCToZ;
	TLabel *Label35;
	TEdit *eCUpX;
	TEdit *eCUpY;
	TEdit *eCUpZ;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TTabSheet *tsObject;
	TLabel *lOMinimum;
	TEdit *eOMinimum;
	TEdit *eOMaximum;
	TLabel *lOMaximum;
	TCheckBox *cbOClosed;
	TCheckBox *cbPSimple;
	TLabel *lTexture;
	TLabel *lTexturePath;
	TBitBtn *bOpenTexture;
	TLabel *Label9;
	TLabel *lOPrimitive;
	TLabel *lOObjectFileName;
	TLabel *eOObjectFileName;
	TLabel *Label10;
	TEdit *eLPositionX;
	TEdit *eLPositionY;
	TEdit *eLPositionZ;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TEdit *eCWidth;
	TLabel *Label27;
	TEdit *eCHeight;
	TBitBtn *bSelectNewTexture;
	TEdit *eNewTexture;
	TLabel *Label28;
	TEdit *eCSuperSamples;
	TImage *iRender;
	TBitBtn *bSaveImage;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBitBtn *bAddPattern;
	TBitBtn *bAbout;
	TImageList *ImageList1;
	TComboBox *cbIoRList;
	TEdit *eIoR;
	TBevel *Bevel4;
	TCheckBox *cbResizeToDisplay;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall bOpenSceneClick(TObject *Sender);
	void __fastcall bRenderClick(TObject *Sender);
	void __fastcall tvObjectsClick(TObject *Sender);
	void __fastcall sMaterialColourMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sPatternColour1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tbAmbientExit(TObject *Sender);
	void __fastcall lbObjectTransformsClick(TObject *Sender);
	void __fastcall eOTAngleExit(TObject *Sender);
	void __fastcall eOTXExit(TObject *Sender);
	void __fastcall lbPatternTransformsClick(TObject *Sender);
	void __fastcall ePTAngleExit(TObject *Sender);
	void __fastcall sLightIntensityMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ePTXExit(TObject *Sender);
	void __fastcall sbAddMaterialTransformClick(TObject *Sender);
	void __fastcall sbDeleteMaterialTransformClick(TObject *Sender);
	void __fastcall bSaveSceneClick(TObject *Sender);
	void __fastcall sbPatternChangeClick(TObject *Sender);
	void __fastcall sbAddObjectClick(TObject *Sender);
	void __fastcall sbAddTransformClick(TObject *Sender);
	void __fastcall eCFromXExit(TObject *Sender);
	void __fastcall eCToXExit(TObject *Sender);
	void __fastcall eCUpXExit(TObject *Sender);
	void __fastcall eCFoVExit(TObject *Sender);
	void __fastcall ePFrequencyExit(TObject *Sender);
	void __fastcall ePScaleExit(TObject *Sender);
	void __fastcall ePPhaseExit(TObject *Sender);
	void __fastcall ePWidthExit(TObject *Sender);
	void __fastcall cbPSimpleClick(TObject *Sender);
	void __fastcall sbDeleteTransformClick(TObject *Sender);
	void __fastcall sbDeleteObjectClick(TObject *Sender);
	void __fastcall bNewClick(TObject *Sender);
	void __fastcall eLPositionXExit(TObject *Sender);
	void __fastcall eCWidthExit(TObject *Sender);
	void __fastcall cbPatternChangeToChange(TObject *Sender);
	void __fastcall bSaveImageClick(TObject *Sender);
	void __fastcall bSelectNewTextureClick(TObject *Sender);
	void __fastcall bAddPatternClick(TObject *Sender);
	void __fastcall bAboutClick(TObject *Sender);
	void __fastcall cbIoRListChange(TObject *Sender);
	void __fastcall eIoRExit(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall cbResizeToDisplayClick(TObject *Sender);

private:	// User declarations
	TTreeNode* cameras = nullptr;
	TTreeNode* lights = nullptr;
	TTreeNode* objects = nullptr;

	int LastSelectionType = 0;
	int OriginalWidth = 0;
	int OriginalHeight = 0;

	void ConfigureTabLayoutFor(int);
	void PopulateTreeView();

	void AddNewObject(int, int, PatternProperties, std::wstring);

	void BuildCameraPanel(int);

    void BuildLightPanel(int);

    void BuildObjectPanelFromObject(int);
	void BuildMaterialPanelFromObject(int);
	void BuildPatternTab(int);
    void BuildPatternTabControls(PatternDesign);
	void BuildPatternTransformTab(int);

	void BuildTransformTab(int, int);

	void UpdateTransformTab(int, int, int);
	void UpdatePatternTransformTab(int, int, int);
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};

extern PACKAGE TfrmMain *frmMain;

#endif
