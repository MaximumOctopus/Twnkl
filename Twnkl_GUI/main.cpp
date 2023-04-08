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

#pragma package(smart_init)
#pragma resource "*.dfm"

#include <vcl.h>

#include "main.h"

#include "Constants.h"
#include "Renderer.h"
#include "SceneLoader.h"
#include "TransformConfiguration.h"
#include "Utility.h"
#include "World.h"

#include "Checkerboard.h"
#include "CubeCheckerboard.h"
#include "CubeTexture.h"
#include "CylinderCheckerboard.h"
#include "CylinderTexture.h"
#include "Fractal.h"
#include "Perlin.h"
#include "Perlin2.h"
#include "Perlin3.h"
#include "PlanarTexture.h"
#include "Simplex.h"
#include "SphericalCheckerboard.h"
#include "SphericalTexture.h"

#include "FormAddObject.h"
#include "FormAddTransform.h"
#include "FormColourDialog.h"

TfrmMain *frmMain;

extern World* GWorld;
extern SceneLoader* GSceneLoader;


typedef struct TreeObject
{
	int Type = 0;
	int ID = 0;
} TTreeObject;

typedef TTreeObject* PTreeObject;

TTreeObject *TTreeObjectPtr;

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	std::wstring c = L"Twnkl " + __TwnklVersion + L" :: " + __TwnklDate;

	cameras = tvObjects->Items->Add(NULL, "Cameras");
	lights = tvObjects->Items->Add(NULL, "Lights");
	objects = tvObjects->Items->Add(NULL, "Objects");

	Caption = c.c_str();

	GWorld = new World(0, 0, 1.152);

	GSceneLoader = new SceneLoader();

    bNewClick(NULL);
}


void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete GSceneLoader;
	delete GWorld;

	delete cameras;
	delete lights;
	delete objects;
}


void __fastcall TfrmMain::bNewClick(TObject *Sender)
{
	GWorld->Clear();

	//cameras->DeleteChildren();
	lights->DeleteChildren();
	objects->DeleteChildren();

    GWorld->DefaultScene();

	PopulateTreeView();

	cameras->GetLastChild()->Selected = true;

	tvObjectsClick(NULL);
}


void __fastcall TfrmMain::bOpenSceneClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName();

	if (!file_name.empty())
	{
		sbMain->SimpleText = file_name.c_str();

		GUIProperties gui;
		gui.ResizeToDisplay = cbResizeToDisplay->Checked;
		gui.DisplayWidth = PaintBox1->Width;
		gui.DisplayHeight = PaintBox1->Height;

		if (GSceneLoader->LoadScene(file_name, 0, gui))
		{
			if (!GWorld->Finalise())
			{
				bRender->Enabled = true;

				PopulateTreeView();

				cameras->GetLastChild()->Selected = true;

				tvObjectsClick(NULL);
			}
			else
			{
				bRender->Enabled = false;
			}
		}
	}
}


void __fastcall TfrmMain::bRenderClick(TObject *Sender)
{
	if (!GWorld->Finalise())
	{
		Renderer rx;

	   	rx.Render(0);

		std::wstring c = L"Rendered in " + rx.RenderTime + L" seconds.";

		sbMain->SimpleText = c.c_str();

		for (int x = 0; x < GWorld->Cam->Width; x++)
		{
			for (int y = 0; y < GWorld->Cam->Height; y++)
			{
				PaintBox1->Canvas->Pixels[x][y] = TColor(GWorld->Canvas[y * GWorld->Cam->Width + x].ToIntBGR());
			}
		}
    }
}


void __fastcall TfrmMain::BitBtn1Click(TObject *Sender)
{
//
}


void __fastcall TfrmMain::tvObjectsClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
            ConfigureTabLayoutFor(PTreeObject(tvObjects->Selected->Data)->Type);

            int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			switch (type)
			{
			case 0:         // camera
				BuildCameraPanel(0);
				break;
			case 1:         // light
                BuildLightPanel(id);
				break;
			case 2:         // object
			{
				BuildObjectPanelFromObject(id);
				BuildMaterialPanelFromObject(id);
				BuildTransformTab(type, id);
				break;
			}
			}
		}
	}
}


void __fastcall TfrmMain::sMaterialColourMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	frmColourDialog->SelectedColour = int(sMaterialColour->Brush->Color);

	if (frmColourDialog->ShowModal() == mrOk)
	{
		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;

				sMaterialColour->Brush->Color = TColor(frmColourDialog->SelectedColour);

				GWorld->Objects[id]->Material->SurfaceColour.FromIntBGR(frmColourDialog->SelectedColour);
			}
		}
	}
}


void TfrmMain::ConfigureTabLayoutFor(int type)
{
	switch (type)
	{
	case 0:         // camera
		tsCamera->TabVisible = true;
		tsLight->TabVisible = false;
		tsObject->TabVisible = false;
		tsTransforms->TabVisible = false;
		tsMaterial->TabVisible = false;
		break;
	case 1:         // light
		tsCamera->TabVisible = false;
		tsLight->TabVisible = true;
		tsObject->TabVisible = false;
		tsTransforms->TabVisible = false;
		tsMaterial->TabVisible = false;
		break;
	case 2:         // object
		tsCamera->TabVisible = false;
		tsLight->TabVisible = false;
        tsObject->TabVisible = true;
		tsTransforms->TabVisible = true;
		tsMaterial->TabVisible = true;
		break;
	}
}


void TfrmMain::PopulateTreeView()
{
	cameras->DeleteChildren();
	lights->DeleteChildren();
	objects->DeleteChildren();

    TTreeObjectPtr = new TTreeObject;
	TTreeObjectPtr->Type = 0;
	TTreeObjectPtr->ID = 0;

	tvObjects->Items->AddChildObject(cameras, "Camera", TTreeObjectPtr);

	for (int t = 0; t < GWorld->Lights.size(); t++)
	{
		TTreeObjectPtr = new TTreeObject;
		TTreeObjectPtr->Type = 1;
		TTreeObjectPtr->ID = t;

		tvObjects->Items->AddChildObject(lights, "L", TTreeObjectPtr);
	}

	for (int t = 0; t < GWorld->Objects.size(); t++)
	{
		TTreeObjectPtr = new TTreeObject;
		TTreeObjectPtr->Type = 2;
		TTreeObjectPtr->ID = t;

		tvObjects->Items->AddChildObject(objects, GWorld->Objects[t]->Name.c_str(), TTreeObjectPtr);
	}
}


void TfrmMain::BuildCameraPanel(int id)
{
	eCFoV->Text = GWorld->Cam->FoV;

	eCWidth->Text = GWorld->Cam->Width;
    eCHeight->Text = GWorld->Cam->Height;

	eCFromX->Text = GWorld->Cam->From.x;
	eCFromY->Text = GWorld->Cam->From.y;
	eCFromZ->Text = GWorld->Cam->From.z;

	eCToX->Text = GWorld->Cam->To.x;
	eCToY->Text = GWorld->Cam->To.y;
	eCToZ->Text = GWorld->Cam->To.z;

	eCUpX->Text = GWorld->Cam->Up.x;
	eCUpY->Text = GWorld->Cam->Up.y;
	eCUpZ->Text = GWorld->Cam->Up.z;
}


void TfrmMain::BuildLightPanel(int id)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 1)
			{
				sLightIntensity->Brush->Color = TColor(GWorld->Lights[id]->Intensity.ToIntBGR());

				eLPositionX->Text = GWorld->Lights[id]->Position.x;
				eLPositionY->Text = GWorld->Lights[id]->Position.y;
				eLPositionZ->Text = GWorld->Lights[id]->Position.z;
			}
		}
	}
}


void TfrmMain::BuildObjectPanelFromObject(int id)
{
	lOPrimitive->Caption = GWorld->Objects[id]->FriendlyName().c_str();

	switch (GWorld->Objects[id]->Primitive)
	{
	case PrimitiveType::Cone:
	case PrimitiveType::Cylinder:
		lOMinimum->Visible = true;
		lOMaximum->Visible = true;
		eOMinimum->Visible = true;
		eOMaximum->Visible = true;
		cbOClosed->Visible = true;

		eOObjectFileName->Visible = false;
		lOObjectFileName->Visible = false;
		break;
	case PrimitiveType::Model:
		lOMinimum->Visible = false;
		lOMaximum->Visible = false;
		eOMinimum->Visible = false;
		eOMaximum->Visible = false;
		cbOClosed->Visible = false;

		eOObjectFileName->Visible = true;
		lOObjectFileName->Visible = true;
		break;
	case PrimitiveType::Cube:
	case PrimitiveType::Plane:
	case PrimitiveType::Sphere:
		lOMinimum->Visible = false;
		lOMaximum->Visible = false;
		eOMinimum->Visible = false;
		eOMaximum->Visible = false;
		cbOClosed->Visible = false;

		eOObjectFileName->Visible = false;
		lOObjectFileName->Visible = false;
		break;
	}
}


void TfrmMain::BuildMaterialPanelFromObject(int id)
{
	sMaterialColour->Brush->Color = TColor(GWorld->Objects[id]->Material->SurfaceColour.ToIntBGR());

	tbAmbient->Position = GWorld->Objects[id]->Material->Ambient * 100.0;
	tbDiffuse->Position = GWorld->Objects[id]->Material->Diffuse * 100.0;
	tbReflectivity->Position = GWorld->Objects[id]->Material->Reflectivity * 100.0;
	//tbIoR->Position = GWorld->Objects[id]->Material->Ambient * 100.0;
	tbShininess->Position = GWorld->Objects[id]->Material->Shininess * 100.0;
	tbSpecular->Position = GWorld->Objects[id]->Material->Specular * 100.0;
	tbTransparency->Position = GWorld->Objects[id]->Material->Transparency * 100.0;

	bool HasPattern = GWorld->Objects[id]->Material->HasPattern;

	lSurfaceColourWarning->Visible = HasPattern;
	tsPattern->TabVisible = HasPattern;
    tsMaterialTransforms->TabVisible = HasPattern;

	if (GWorld->Objects[id]->Material->HasPattern)
	{
		BuildPatternTab(id);
	}
	else
	{

	}
}


void TfrmMain::BuildTransformTab(int type, int id)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
	{
		lbObjectTransforms->Clear();

		if (GWorld->Objects[id]->TransformsCount != 0)
		{
			for (int t = 0; t < GWorld->Objects[id]->TransformsCount(); t++)
			{
				TransformConfiguration tc = GWorld->Objects[id]->TransformAt(t);

				lbObjectTransforms->Items->Add(tc.TypeAsString().c_str());
            }
        }

		break;
	}
	}
}


void TfrmMain::BuildPatternTab(int id)
{
    lPatternDesign->Caption = GWorld->Objects[id]->Material->SurfacePattern->FriendlyName().c_str();

	sPatternColour1->Brush->Color = TColor(GWorld->Objects[id]->Material->SurfacePattern->Colours[0].ToIntBGR());
	sPatternColour2->Brush->Color = TColor(GWorld->Objects[id]->Material->SurfacePattern->Colours[1].ToIntBGR());

	BuildPatternTabControls(GWorld->Objects[id]->Material->SurfacePattern->Design);

	switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
	{
	case PatternDesign::Checkerboard:
	case PatternDesign::Gradient:
	case PatternDesign::Gradient2:
	case PatternDesign::Ring:
	case PatternDesign::Stripey:
		break;
	case PatternDesign::Fractal:
	{
		Fractal* p = dynamic_cast<Fractal*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePFrequency->Text = p->noize->Frequency;
		ePAmplitude->Text = p->noize->Amplitude;
		ePLacunarity->Text = p->noize->Lacunarity;
		ePPersistence->Text = p->noize->Persistence;
		break;
	}
	case PatternDesign::Simplex:
	{
		Simplex* p = dynamic_cast<Simplex*>(GWorld->Objects[id]->Material->SurfacePattern);
		cbPSimple->Checked = p->Simple;
		break;
	}
	case PatternDesign::Perlin1:
	{
		Perlin* p = dynamic_cast<Perlin*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->Width;
		ePHeight->Text = p->Height;
		ePScale->Text = p->Scale;
		break;
	}
	case PatternDesign::Perlin2:
	{
		Perlin2* p = dynamic_cast<Perlin2*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->Width;
		ePHeight->Text = p->Height;
		ePScale->Text = p->Scale;
		break;
	}
	case PatternDesign::Perlin3:
	{
		Perlin3* p = dynamic_cast<Perlin3*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->Width;
		ePHeight->Text = p->Height;
		ePScale->Text = p->Scale;
		ePPhase->Text = p->Phase;
		break;
	}
	case PatternDesign::CubeCheckerboard:
	{
		CubeChecker* p = dynamic_cast<CubeChecker*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->Width;
		ePHeight->Text = p->Height;
		break;
	}
	case PatternDesign::CubeTexture:
	{
		CubeTexture* p = dynamic_cast<CubeTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		break;
	}
	case PatternDesign::CylinderCheckerboard:
	{
		CylinderCheckerboard* p = dynamic_cast<CylinderCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->Width;
		ePHeight->Text = p->Height;
		break;
	}
	case PatternDesign::CylinderTexture:
	{
		CylinderTexture* p = dynamic_cast<CylinderTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		break;
	}
	case PatternDesign::PlanarTexture:
	{
		PlanarTexture* p = dynamic_cast<PlanarTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		break;
	}
	case PatternDesign::SphericalCheckerboard:
	{
		SphericalCheckerboard* p = dynamic_cast<SphericalCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->Width;
		ePHeight->Text = p->Height;
		break;
	}
	case PatternDesign::SphericalTexture:
	{
		SphericalTexture* p = dynamic_cast<SphericalTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		break;
	}
    }
}


void TfrmMain::BuildPatternTabControls(PatternDesign design)
{
	if (design == PatternDesign::Perlin1 || design == PatternDesign::Perlin2 || design == PatternDesign::Perlin3)
	{
		sPatternColour1->Visible = true;
		sPatternColour2->Visible = false;
		lPatternColour1->Visible = true;
		lPatternColour2->Visible = false;
	}
	else if (design == PatternDesign::CubeTexture || design == PatternDesign::CylinderTexture || design == PatternDesign::PlanarTexture ||
		design == PatternDesign::SphericalTexture)
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

	if (design == PatternDesign::Fractal)
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

	if (design == PatternDesign::Perlin1 || design == PatternDesign::Perlin2 || design == PatternDesign::Perlin3)
	{
		ePScale->Visible = true;
		lPScale->Visible = true;

		if (design == PatternDesign::Perlin3)
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

	if (design == PatternDesign::Perlin1 || design == PatternDesign::Perlin2 || design == PatternDesign::Perlin3 ||
		design == PatternDesign::CubeCheckerboard || design == PatternDesign::CylinderCheckerboard ||
		design == PatternDesign::SphericalCheckerboard)
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

	if (design == PatternDesign::Simplex)
	{
		cbPSimple->Visible = true;
	}
	else
	{
		cbPSimple->Visible = false;
	}

	if (design == PatternDesign::CubeTexture || design == PatternDesign::CylinderTexture || design == PatternDesign::PlanarTexture ||
		design == PatternDesign::SphericalTexture)
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


void TfrmMain::BuildPatternTransformTab(int id)
{
	lbPatternTransforms->Clear();

	if (GWorld->Objects[id]->Material->SurfacePattern->TransformsCount != 0)
	{
		for (int t = 0; t < GWorld->Objects[id]->Material->SurfacePattern->TransformsCount(); t++)
		{
			TransformConfiguration tc = GWorld->Objects[id]->Material->SurfacePattern->TransformAt(t);

			lbPatternTransforms->Items->Add(tc.TypeAsString().c_str());
		}
	}
}


void __fastcall TfrmMain::sPatternColour1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	TShape *shape = (TShape*)Sender;

	frmColourDialog->SelectedColour = int(shape->Brush->Color);

	if (frmColourDialog->ShowModal() == mrOk)
	{
		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;

				shape->Brush->Color = TColor(frmColourDialog->SelectedColour);

				GWorld->Objects[id]->Material->SurfacePattern->Colours[shape->Tag].FromIntBGR(frmColourDialog->SelectedColour);
			}
		}
	}
}


void __fastcall TfrmMain::tbAmbientExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;

			TTrackBar *trackbar = (TTrackBar*)Sender;

			switch (trackbar->Tag)
			{
			case 0:
				GWorld->Objects[id]->Material->Ambient = (double)trackbar->Position / 100.0;
				break;
			case 1:
				GWorld->Objects[id]->Material->Diffuse = (double)trackbar->Position / 100.0;
				break;
			case 2:
				GWorld->Objects[id]->Material->Reflectivity = (double)trackbar->Position / 100.0;
				break;
			case 3:
//				GWorld->Objects[id]->Material->Ambient = trackbar->Position / 100;
				break;
			case 4:
				GWorld->Objects[id]->Material->Shininess = (double)trackbar->Position / 100.0;
				break;
			case 5:
				GWorld->Objects[id]->Material->Specular = (double)trackbar->Position / 100.0;
				break;
			case 6:
				GWorld->Objects[id]->Material->Transparency = (double)trackbar->Position / 100.0;
				break;
            }
		}
	}
}


void __fastcall TfrmMain::lbObjectTransformsClick(TObject *Sender)
{
	if (lbObjectTransforms->SelCount != 0)
	{
		int id = PTreeObject(tvObjects->Selected->Data)->ID;
		int type = PTreeObject(tvObjects->Selected->Data)->Type;

		UpdateTransformTab(type, id, lbObjectTransforms->ItemIndex);
	}
}


void TfrmMain::UpdateTransformTab(int type, int id, int selected)
{
	TransformConfiguration tc = GWorld->Objects[id]->TransformAt(selected);

	if (tc.Type == TransformType::Scale || tc.Type == TransformType::Translate)
	{
		eOTX->Text = tc.XYZ.x;
		eOTY->Text = tc.XYZ.y;
		eOTZ->Text = tc.XYZ.z;

		pOTAngle->Visible = false;
		pOTXYZ->Visible = true;
	}
	else
	{
		eOTAngle->Text = tc.Angle;

		pOTAngle->Visible = true;
		pOTXYZ->Visible = false;
	}
}


void __fastcall TfrmMain::eOTAngleExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
            if (lbObjectTransforms->ItemIndex != -1)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbObjectTransforms->ItemIndex);

				std::wstring a = eOTAngle->Text.c_str();

				tc.Angle = stod(a);

				GWorld->Objects[id]->TransformReplaceAt(lbObjectTransforms->ItemIndex, tc);
            }
		}
    }
}


void __fastcall TfrmMain::eOTXExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			if (lbObjectTransforms->ItemIndex != -1)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbObjectTransforms->ItemIndex);

				tc.XYZ.x = eOTX->Text.ToDouble();
				tc.XYZ.y = eOTY->Text.ToDouble();
				tc.XYZ.z = eOTZ->Text.ToDouble();

				GWorld->Objects[id]->TransformReplaceAt(lbObjectTransforms->ItemIndex, tc);
			}
		}
	}
}


void __fastcall TfrmMain::lbPatternTransformsClick(TObject *Sender)
{
	if (lbPatternTransforms->SelCount != 0)
	{
		int id = PTreeObject(tvObjects->Selected->Data)->ID;
		int type = PTreeObject(tvObjects->Selected->Data)->Type;

		UpdatePatternTransformTab(type, id, lbPatternTransforms->ItemIndex);
	}
}


void TfrmMain::UpdatePatternTransformTab(int type, int id, int selected)
{
	TransformConfiguration tc = GWorld->Objects[id]->Material->SurfacePattern->TransformAt(selected);

	if (tc.Type == TransformType::Scale || tc.Type == TransformType::Translate)
	{
		ePTX->Text = tc.XYZ.x;
		ePTY->Text = tc.XYZ.y;
		ePTZ->Text = tc.XYZ.z;

		pPTAngle->Visible = false;
		pPTXYZ->Visible = true;
	}
	else
	{
		ePTAngle->Text = tc.Angle;

		pPTAngle->Visible = true;
		pPTXYZ->Visible = false;
	}
}


void __fastcall TfrmMain::ePTAngleExit(TObject *Sender)
{
	int id = PTreeObject(tvObjects->Selected->Data)->ID;
	int type = PTreeObject(tvObjects->Selected->Data)->Type;

	TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbPatternTransforms->ItemIndex);

	std::wstring a = ePTAngle->Text.c_str();

	tc.Angle = stod(a);

	GWorld->Objects[id]->Material->SurfacePattern->TransformReplaceAt(lbPatternTransforms->ItemIndex, tc);
}


void __fastcall TfrmMain::sLightIntensityMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	frmColourDialog->SelectedColour = int(sLightIntensity->Brush->Color);

	if (frmColourDialog->ShowModal() == mrOk)
	{
		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				if (type == 1)
				{
					sLightIntensity->Brush->Color = TColor(frmColourDialog->SelectedColour);

					GWorld->Lights[id]->Intensity.FromIntBGR(frmColourDialog->SelectedColour);
				}
			}
		}
	}
}


void __fastcall TfrmMain::eLPositionXExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 1)
			{
				GWorld->Lights[id]->Position.x = eLPositionX->Text.ToDouble();
				GWorld->Lights[id]->Position.y = eLPositionY->Text.ToDouble();
				GWorld->Lights[id]->Position.z = eLPositionZ->Text.ToDouble();
			}
		}
	}
}


void __fastcall TfrmMain::ePTXExit(TObject *Sender)
{
	int id = PTreeObject(tvObjects->Selected->Data)->ID;
	int type = PTreeObject(tvObjects->Selected->Data)->Type;

	TransformConfiguration tc = GWorld->Objects[id]->Material->SurfacePattern->TransformAt(lbPatternTransforms->ItemIndex);

	tc.XYZ.x = ePTX->Text.ToDouble();
	tc.XYZ.y = ePTY->Text.ToDouble();
	tc.XYZ.z = ePTZ->Text.ToDouble();

    tc.Rebuild();

	GWorld->Objects[id]->Material->SurfacePattern->TransformReplaceAt(lbPatternTransforms->ItemIndex, tc);
}


void __fastcall TfrmMain::sbAddMaterialTransformClick(TObject *Sender)
{
	if (frmAddTransform->ShowModal() == mrOk)
	{
		TransformConfiguration tc;

		switch (frmAddTransform->TransformID)
		{
		case 0:
			tc.Type = TransformType::Scale;
			tc.XYZ.x = frmAddTransform->xx;
			tc.XYZ.y = frmAddTransform->yy;
			tc.XYZ.z = frmAddTransform->zz;

			tc.Transform = Matrix4(0, tc.XYZ.x, tc.XYZ.y, tc.XYZ.z);

			break;
		case 1:
			tc.Type = TransformType::Translate;
			tc.XYZ.x = frmAddTransform->xx;
			tc.XYZ.y = frmAddTransform->yy;
			tc.XYZ.z = frmAddTransform->zz;

			tc.Transform = Matrix4(1, tc.XYZ.x, tc.XYZ.y, tc.XYZ.z);

			break;
		case 2:
			tc.Type = TransformType::RotateX;
			tc.Angle = frmAddTransform->angle;

			tc.Transform = Matrix4(0, tc.Angle);

			break;
		case 3:
			tc.Type = TransformType::RotateY;
			tc.Angle = frmAddTransform->angle;

			tc.Transform = Matrix4(1, tc.Angle);

			break;
		case 4:
			tc.Type = TransformType::RotateZ;
			tc.Angle = frmAddTransform->angle;

			tc.Transform = Matrix4(2, tc.Angle);

			break;
		}

		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				if (type == 2)
				{
					if (GWorld->Objects[id]->Material->HasPattern)
					{
						GWorld->Objects[id]->Material->SurfacePattern->AddTransform(tc);

						BuildPatternTransformTab(id);
					}
				}
			}
		}
	}
}


void __fastcall TfrmMain::sbDeleteMaterialTransformClick(TObject *Sender)
{
	if (lbPatternTransforms->ItemIndex != -1)
	{
        int id = PTreeObject(tvObjects->Selected->Data)->ID;
		int type = PTreeObject(tvObjects->Selected->Data)->Type;

		if (type == 2)
		{
			if (GWorld->Objects[id]->Material->HasPattern)
			{
				GWorld->Objects[id]->Material->SurfacePattern->RemoveTransformAt(lbPatternTransforms->ItemIndex);

				BuildPatternTransformTab(id);
			}
		}
    }
}


void __fastcall TfrmMain::bSaveSceneClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName();

	if (!file_name.empty())
	{
		GWorld->SaveScene(file_name);
	}
}


void __fastcall TfrmMain::sbPatternChangeClick(TObject *Sender)
{
 //
}


void __fastcall TfrmMain::sbAddObjectClick(TObject *Sender)
{
	if (frmAddObject->ShowModal() == mrOk)
	{
		AddNewObject(frmAddObject->SelectedPrimitive, frmAddObject->SelectedPattern, frmAddObject->Properties, frmAddObject->Name);

        PopulateTreeView();
    }
}


void __fastcall TfrmMain::sbDeleteObjectClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 2)
			{
				delete GWorld->Objects[id];

				GWorld->Objects.erase(GWorld->Objects.begin() + id);

                PopulateTreeView();
			}
		}
	}
}


void TfrmMain::AddNewObject(int primitive, int pattern, PatternProperties properties, std::wstring name)
{
	AvailablePatterns ap = AvailablePatterns::None;

	switch (pattern)
	{
	case 1:
		switch (primitive)
		{
		case 0:
		case 2:
			ap = AvailablePatterns::CylinderChecker;
			break;
		case 1:
			ap = AvailablePatterns::CubeChecker;
			break;
		case 4:
			ap = AvailablePatterns::Checker;
			break;
		case 5:
			ap = AvailablePatterns::SphericalChecker;
			break;
		}
		break;
	case 2:
		ap = AvailablePatterns::Fractal;
		break;
	case 3:
		ap = AvailablePatterns::Gradient;
		break;
	case 4:
		ap = AvailablePatterns::Gradient2;
		break;
	case 5:
		ap = AvailablePatterns::Perlin;
		break;
	case 6:
		ap = AvailablePatterns::Perlin2;
		break;
	case 7:
		ap = AvailablePatterns::Perlin3;
		break;
	case 8:
		ap = AvailablePatterns::Ring;
		break;
	case 9:
		ap = AvailablePatterns::Simplex;
		break;
	case 10:
		ap = AvailablePatterns::Stripey;
		break;
	case 11:
		switch (primitive)
		{
		case 0:
		case 2:
			ap = AvailablePatterns::CylinderTexture;
			break;
		case 1:
			ap = AvailablePatterns::CubicTexture;
			break;
		case 4:
			ap = AvailablePatterns::PlanarTexture;
			break;
		case 5:
			ap = AvailablePatterns::SphericalTexture;
            break;
		}
		break;
	}

	GWorld->AddNewObject(primitive, ap, properties, name);
}


void __fastcall TfrmMain::sbAddTransformClick(TObject *Sender)
{
	if (frmAddTransform->ShowModal() == mrOk)
	{
		TransformConfiguration tc;

		switch (frmAddTransform->TransformID)
		{
		case 0:
			tc.Type = TransformType::Scale;
			tc.XYZ.x = frmAddTransform->xx;
			tc.XYZ.y = frmAddTransform->yy;
			tc.XYZ.z = frmAddTransform->zz;

			tc.Transform = Matrix4(0, tc.XYZ.x, tc.XYZ.y, tc.XYZ.z);

			break;
		case 1:
			tc.Type = TransformType::Translate;
			tc.XYZ.x = frmAddTransform->xx;
			tc.XYZ.y = frmAddTransform->yy;
			tc.XYZ.z = frmAddTransform->zz;

			tc.Transform = Matrix4(1, tc.XYZ.x, tc.XYZ.y, tc.XYZ.z);

			break;
		case 2:
			tc.Type = TransformType::RotateX;
			tc.Angle = frmAddTransform->angle;

			tc.Transform = Matrix4(0, tc.Angle);

			break;
		case 3:
			tc.Type = TransformType::RotateY;
			tc.Angle = frmAddTransform->angle;

			tc.Transform = Matrix4(1, tc.Angle);

			break;
		case 4:
			tc.Type = TransformType::RotateZ;
			tc.Angle = frmAddTransform->angle;

			tc.Transform = Matrix4(2, tc.Angle);

			break;
		}

		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				if (type == 2)
				{
					GWorld->Objects[id]->AddTransform(tc);

					BuildTransformTab(type, id);
				}
			}
		}
	}
}


void __fastcall TfrmMain::sbDeleteTransformClick(TObject *Sender)
{
	if (lbObjectTransforms->ItemIndex != -1)
	{
		int id = PTreeObject(tvObjects->Selected->Data)->ID;
		int type = PTreeObject(tvObjects->Selected->Data)->Type;

		GWorld->Objects[id]->RemoveTransformAt(lbObjectTransforms->ItemIndex);

		BuildTransformTab(type, id);
	}
}


void __fastcall TfrmMain::eCFromXExit(TObject *Sender)
{
	GWorld->Cam->From.x = eCFromX->Text.ToDouble();
	GWorld->Cam->From.y = eCFromY->Text.ToDouble();
	GWorld->Cam->From.z = eCFromZ->Text.ToDouble();
}


void __fastcall TfrmMain::eCToXExit(TObject *Sender)
{
	GWorld->Cam->To.x = eCToX->Text.ToDouble();
	GWorld->Cam->To.y = eCToY->Text.ToDouble();
	GWorld->Cam->To.z = eCToZ->Text.ToDouble();
}


void __fastcall TfrmMain::eCUpXExit(TObject *Sender)
{
	GWorld->Cam->Up.x = eCUpX->Text.ToDouble();
	GWorld->Cam->Up.y = eCUpY->Text.ToDouble();
	GWorld->Cam->Up.z = eCUpZ->Text.ToDouble();
}


void __fastcall TfrmMain::eCFoVExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 0)
			{
				GWorld->Cam->FoV = eCFoV->Text.ToDouble();

				GWorld->Cam->CalculatePixelSize();
			}
		}
    }
}


void __fastcall TfrmMain::eCWidthExit(TObject *Sender)
{
	GWorld->Cam->Width = eCWidth->Text.ToDouble();
	GWorld->Cam->Height = eCHeight->Text.ToDouble();
}

void __fastcall TfrmMain::ePFrequencyExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 2)
			{
				Fractal* p = dynamic_cast<Fractal*>(GWorld->Objects[id]->Material->SurfacePattern);

				p->SetFALP(ePFrequency->Text.ToDouble(),
					 ePAmplitude->Text.ToDouble(),
					 ePLacunarity->Text.ToDouble(),
					 ePPersistence->Text.ToDouble());
			}
		}
	}
}


void __fastcall TfrmMain::ePScaleExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 2)
			{
				switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
				{
				case PatternDesign::Perlin1:
				{
					Perlin* p = dynamic_cast<Perlin*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Scale = ePScale->Text.ToDouble();
					break;
				}
				case PatternDesign::Perlin2:
				{
					Perlin2* p = dynamic_cast<Perlin2*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Scale = ePScale->Text.ToDouble();
					break;
				}
				case PatternDesign::Perlin3:
				{
					Perlin3* p = dynamic_cast<Perlin3*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Scale = ePScale->Text.ToDouble();
					break;
				}
				}
			}
		}
	}
}


void __fastcall TfrmMain::ePPhaseExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 2)
			{
				switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
				{
				case PatternDesign::Perlin3:
				{
					Perlin3* p = dynamic_cast<Perlin3*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Scale = ePScale->Text.ToDouble();
					break;
				}
				}
			}
		}
	}
}


void __fastcall TfrmMain::ePWidthExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 2)
			{
				switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
				{
				case PatternDesign::CubeCheckerboard:
				{
					CubeChecker* p = dynamic_cast<CubeChecker*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Width = ePWidth->Text.ToDouble();
					p->Height = ePHeight->Text.ToDouble();
					break;
				}
				case PatternDesign::CylinderCheckerboard:
				{
					CylinderCheckerboard* p = dynamic_cast<CylinderCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Width = ePWidth->Text.ToDouble();
					p->Height = ePHeight->Text.ToDouble();
					break;
				}
				case PatternDesign::Perlin1:
				{
					Perlin* p = dynamic_cast<Perlin*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Width = ePWidth->Text.ToDouble();
					p->Height = ePHeight->Text.ToDouble();
					break;
				}
				case PatternDesign::Perlin2:
				{
					Perlin2* p = dynamic_cast<Perlin2*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Width = ePWidth->Text.ToDouble();
					p->Height = ePHeight->Text.ToDouble();
					break;
				}
				case PatternDesign::Perlin3:
				{
					Perlin3* p = dynamic_cast<Perlin3*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Width = ePWidth->Text.ToDouble();
					p->Height = ePHeight->Text.ToDouble();
					break;
				}
				case PatternDesign::SphericalCheckerboard:
				{
					SphericalCheckerboard* p = dynamic_cast<SphericalCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Width = ePWidth->Text.ToDouble();
					p->Height = ePHeight->Text.ToDouble();
					break;
				}
				}
			}
		}
	}
}


void __fastcall TfrmMain::cbPSimpleClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == 2)
			{
				switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
				{
				case PatternDesign::Simplex:
				{
					Simplex* p = dynamic_cast<Simplex*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Simple = cbPSimple->Checked;
					break;
				}
				}
			}
		}
	}
}
