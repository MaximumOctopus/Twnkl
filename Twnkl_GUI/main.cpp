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
#include <Vcl.Imaging.pngimage.hpp>

#include "main.h"

#include "Constants.h"
#include "Model.h"
#include "Renderer.h"
#include "SceneLoader.h"
#include "TransformConfiguration.h"
#include "Utility.h"
#include "World.h"

#include "AreaLight.h"
#include "Checkerboard.h"
#include "CubeCheckerboard.h"
#include "CubeTexture.h"
#include "CubeMultiTexture.h"
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

#include "FormAbout.h"
#include "FormAddObject.h"
#include "FormAddTransform.h"
#include "FormColourDialog.h"
#include "FormDebug.h"

TfrmMain *frmMain;

extern World* GWorld;
extern SceneLoader* GSceneLoader;


typedef struct TreeObject
{
	int Type = -1;
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

	project = tvObjects->Items->Add(NULL, "Twnkl");
	cameras = tvObjects->Items->Add(NULL, "Cameras");
	lights = tvObjects->Items->Add(NULL, "Lights");
	objects = tvObjects->Items->Add(NULL, "Objects");

	TTreeObjectPtr = new TTreeObject;
	TTreeObjectPtr->Type = __TypeProject;
	TTreeObjectPtr->ID = 0;

	tvObjects->Items->AddChildObject(project, "Project", TTreeObjectPtr);

	Caption = c.c_str();

	GWorld = new World(0, 0, 1.152);

	GSceneLoader = new SceneLoader();

	for (int t = 0; t < IndexOfRefractionCount; t++)
	{
		cbIoRList->Items->Add(IndexOfRefractionName[t].c_str());
	}

	cbIoRList->ItemIndex = 0;

    ResetScene();
}


void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete GSceneLoader;
	delete GWorld;

	delete cameras;
	delete lights;
	delete objects;
}


void __fastcall TfrmMain::FormResize(TObject *Sender)
{
	if (cbResizeToDisplay->Checked)
	{
		GWorld->Cam->ResizeToFit(pRender->Width, pRender->Height);

		eCWidth->Text = GWorld->Cam->Width;
        eCHeight->Text = GWorld->Cam->Height;
	}
}


void __fastcall TfrmMain::File2Click(TObject *Sender)
{
	Application->Free();
}


void __fastcall TfrmMain::bDebugClick(TObject *Sender)
{
    frmDebug->ShowModal();
}


void __fastcall TfrmMain::bAboutClick(TObject *Sender)
{
	frmAbout->ShowModal();
}


void __fastcall TfrmMain::bNewClick(TObject *Sender)
{
	if (MessageDlg("Are you sure?", mtWarning, mbOKCancel, 0) == mrOk)
	{
		ResetScene();
	}
}


void __fastcall TfrmMain::bOpenSceneClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName(0);

	if (!file_name.empty())
	{
		if (!cbResizeToDisplay->Checked)
		{
			GWorld->Cam->Width = 0;
            GWorld->Cam->Height = 0;
		}

		GWorld->Clear();

		cameras->DeleteChildren();
		lights->DeleteChildren();
		objects->DeleteChildren();

		sbMain->SimpleText = file_name.c_str();

		if (GSceneLoader->LoadScene(file_name, 0))
		{
			if (!GWorld->Finalise())
			{
				bRender->Enabled = true;

				OriginalWidth = GWorld->Cam->Width;
				OriginalHeight = GWorld->Cam->Height;

				iRender->Width = OriginalWidth;
				iRender->Height = OriginalHeight;

				BuildProjectPanel();

				PopulateTreeView();

				project->GetLastChild()->Selected = true;

				tvObjectsClick(NULL);

              	FormResize(NULL);
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

        int ss = eCSuperSamples->Text.ToInt();

	   	rx.Render(ss);

		std::wstring c = L"Rendered in " + rx.RenderTime + L" seconds.";

		sbMain->SimpleText = c.c_str();

		TBitmap* bit = new TBitmap();
		bit->PixelFormat = pf24bit;
		bit->Width = GWorld->Cam->Width;
		bit->Height = GWorld->Cam->Height;

		TRGBTriple *ptr;

		for (int y = 0; y < bit->Height; y++)
		{
			ptr = reinterpret_cast<TRGBTriple *>(bit->ScanLine[y]);

			for (int x = 0; x < bit->Width; x++)
			{
				ptr[x] = GWorld->Canvas[y * GWorld->Cam->Width + x].ToRGBTriple();
			}
		}

		iRender->Picture->Assign(bit);

        delete bit;
    }
}


void __fastcall TfrmMain::bSaveImageClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetSaveFileName(1);

	if (!file_name.empty())
	{
		if (file_name.find(L".png") == std::wstring::npos)
		{
			file_name += L".png";
		}

		TPngImage* png  = new TPngImage();
		png->Assign(iRender->Picture->Bitmap);

		png->SaveToFile(file_name.c_str());

		delete png;
	}
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
			case __TypeCamera:
				BuildCameraPanel(0);
				break;
			case __TypeLight:
				BuildLightPanel(id);
				break;
			case __TypeObject:
			{
				BuildObjectPanelFromObject(id);
				BuildMaterialPanelFromObject(id);
				BuildTransformTab(type, id);

				if (GWorld->Objects[id]->Material->HasPattern)
				{
					BuildPatternTransformTab(id);
				}
				else
				{
					lbPatternTransforms->Clear();
				}
				break;
			}
			case __TypeProject:
			{
				BuildProjectPanel();
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


void TfrmMain::ResetScene()
{
	GWorld->Clear();

	//cameras->DeleteChildren();

	lights->DeleteChildren();
	objects->DeleteChildren();

	GWorld->DefaultScene();

	OriginalWidth = GWorld->Cam->Width;
	OriginalHeight = GWorld->Cam->Height;

	PopulateTreeView();

	project->GetLastChild()->Selected = true;

	tvObjectsClick(NULL);

	FormResize(NULL);
}



void TfrmMain::ConfigureTabLayoutFor(int type)
{
	switch (type)
	{
	case __TypeCamera:
		tsProject->TabVisible = false;
		tsCamera->TabVisible = true;
		tsLight->TabVisible = false;
		tsObject->TabVisible = false;
		tsTransforms->TabVisible = false;
		tsMaterial->TabVisible = false;
		break;
	case __TypeLight:
		tsProject->TabVisible = false;
		tsCamera->TabVisible = false;
		tsLight->TabVisible = true;
		tsObject->TabVisible = false;
		tsTransforms->TabVisible = false;
		tsMaterial->TabVisible = false;
		break;
	case __TypeObject:
		tsProject->TabVisible = false;
		tsCamera->TabVisible = false;
		tsLight->TabVisible = false;
		tsObject->TabVisible = true;
		tsTransforms->TabVisible = true;
		tsMaterial->TabVisible = true;
		break;
	case __TypeProject:
		tsProject->TabVisible = true;
		tsCamera->TabVisible = false;
		tsLight->TabVisible = false;
		tsObject->TabVisible = false;
		tsTransforms->TabVisible = false;
		tsMaterial->TabVisible = false;
		break;
	}

	if (type != LastSelectionType)
	{
		pcMain->TabIndex = 0;
		pcMaterial->TabIndex = 0;
	}

	LastSelectionType = type;
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
		TTreeObjectPtr->Type = __TypeLight;
		TTreeObjectPtr->ID = t;

		tvObjects->Items->AddChildObject(lights, GWorld->Lights[t]->Name.c_str(), TTreeObjectPtr);
	}

	for (int t = 0; t < GWorld->Objects.size(); t++)
	{
		TTreeObjectPtr = new TTreeObject;
		TTreeObjectPtr->Type = __TypeObject;
		TTreeObjectPtr->ID = t;

		tvObjects->Items->AddChildObject(objects, GWorld->Objects[t]->Name.c_str(), TTreeObjectPtr);
	}
}


void TfrmMain::BuildProjectPanel()
{
	mDescription->Text = GWorld->Project.Description.c_str();
	eAuthor->Text = GWorld->Project.Author.c_str();
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

			if (type == __TypeLight)
			{
				sLightIntensity->Brush->Color = TColor(GWorld->Lights[id]->Intensity.ToIntBGR());

				eLPositionX->Text = GWorld->Lights[id]->Position.x;
				eLPositionY->Text = GWorld->Lights[id]->Position.y;
				eLPositionZ->Text = GWorld->Lights[id]->Position.z;

				if (GWorld->Lights[id]->HasSamples)
				{
					lLSamples->Visible = true;
					eLSamples->Visible = true;

                    eLSamples->Text = GWorld->Lights[id]->Samples;
				}
				else
				{
					lLSamples->Visible = false;
					eLSamples->Visible = false;
                }
			}
		}
	}
}


void TfrmMain::BuildObjectPanelFromObject(int id)
{
	eOName->Text = GWorld->Objects[id]->Name.c_str();

	lOPrimitive->Caption = GWorld->Objects[id]->FriendlyName().c_str();

	switch (GWorld->Objects[id]->Primitive)
	{
	case PrimitiveType::None:
	case PrimitiveType::Triangle:
	case PrimitiveType::SmoothTriangle:
        break;
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
	{
		lOMinimum->Visible = false;
		lOMaximum->Visible = false;
		eOMinimum->Visible = false;
		eOMaximum->Visible = false;
		cbOClosed->Visible = false;

		eOObjectFileName->Visible = true;
		lOObjectFileName->Visible = true;

		Model* m = (Model*)GWorld->Objects[id];

		eOObjectFileName->Caption = m->GetFileName().c_str();
		break;
    }
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
	tbShininess->Position = GWorld->Objects[id]->Material->Shininess * 100.0;
	tbSpecular->Position = GWorld->Objects[id]->Material->Specular * 100.0;
	tbTransparency->Position = GWorld->Objects[id]->Material->Transparency * 100.0;

	lMBAmbience->Caption = GWorld->Objects[id]->Material->Ambient;
	lMBDiffuse->Caption = GWorld->Objects[id]->Material->Diffuse;
	lMBReflectivity->Caption = GWorld->Objects[id]->Material->Reflectivity;
	lMBShininess->Caption = GWorld->Objects[id]->Material->Shininess;
	lMBSpecular->Caption = GWorld->Objects[id]->Material->Specular;
	lMBTransparency->Caption = GWorld->Objects[id]->Material->Transparency;

	bool HasPattern = GWorld->Objects[id]->Material->HasPattern;

	lSurfaceColourWarning->Visible = HasPattern;
	tsPattern->TabVisible = HasPattern;
    tsMaterialTransforms->TabVisible = HasPattern;

	bAddPattern->Visible = !HasPattern;

	if (HasPattern)
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
	case __TypeLight:
		break;
	case __TypeObject:
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

		if (lbObjectTransforms->Count != 0)
		{
			lbObjectTransforms->ItemIndex = 0;

            lbObjectTransformsClick(NULL);
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

	BuildPatternTabControls(GWorld->Objects[id]->Material->SurfacePattern->Design,
		GWorld->Objects[id]->Material->SurfacePattern->IncludeNoise);

	eNewTexture->Text = "";
	lTexturePath->Caption = "";
	lTexturePath->Hint = "";

	switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
	{
	case PatternDesign::None:
		break;
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
		ePWidth->Text = p->PatternWidth;
		ePHeight->Text = p->PatternHeight;
		break;
	}
	case PatternDesign::CubeTexture:
	{
		CubeTexture* p = dynamic_cast<CubeTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		lTexturePath->Hint = p->FileName.c_str();
		break;
    }
	case PatternDesign::CubeMultiTexture:
	{
		CubeMultiTexture* p = dynamic_cast<CubeMultiTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		lTexturePath->Hint = p->FileName.c_str();
		break;
	}
	case PatternDesign::CylinderCheckerboard:
	{
		CylinderCheckerboard* p = dynamic_cast<CylinderCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->PatternWidth;
		ePHeight->Text = p->PatternHeight;
		break;
	}
	case PatternDesign::CylinderTexture:
	{
		CylinderTexture* p = dynamic_cast<CylinderTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		lTexturePath->Hint = p->FileName.c_str();
		break;
	}
	case PatternDesign::PlanarTexture:
	{
		PlanarTexture* p = dynamic_cast<PlanarTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		lTexturePath->Hint = p->FileName.c_str();
		break;
	}
	case PatternDesign::SphericalCheckerboard:
	{
		SphericalCheckerboard* p = dynamic_cast<SphericalCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
		ePWidth->Text = p->PatternWidth;
		ePHeight->Text = p->PatternHeight;
		break;
	}
	case PatternDesign::SphericalTexture:
	{
		SphericalTexture* p = dynamic_cast<SphericalTexture*>(GWorld->Objects[id]->Material->SurfacePattern);
		lTexturePath->Caption = p->FileName.c_str();
		lTexturePath->Hint = p->FileName.c_str();
		break;
	}
	}

	if (GWorld->Objects[id]->Material->SurfacePattern->HasTexture)
	{
		tsTexture->TabVisible = true;
		pcMaterialChange(nullptr);
	}
	else
	{
		tsTexture->TabVisible = false;
	}

	if (GWorld->Objects[id]->Material->SurfacePattern->IncludeNoise)
	{
		Pattern* p = GWorld->Objects[id]->Material->SurfacePattern;

		ePFrequency->Text = p->noize->Frequency;
		ePAmplitude->Text = p->noize->Amplitude;
		ePLacunarity->Text = p->noize->Lacunarity;
		ePPersistence->Text = p->noize->Persistence;

		ePScale->Text = p->pscale;
		ePPhase->Text = p->scale;
	}

	cbPNoise->Checked = GWorld->Objects[id]->Material->SurfacePattern->IncludeNoise;
}


void TfrmMain::BuildPatternTabControls(PatternDesign design, bool has_noise)
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

	if (design == PatternDesign::Fractal || has_noise)
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

	if (design == PatternDesign::Perlin1 || design == PatternDesign::Perlin2 || design == PatternDesign::Perlin3 || has_noise)
	{
		ePScale->Visible = true;
		lPScale->Visible = true;

		if (design == PatternDesign::Perlin3 || has_noise)
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

	if (design == PatternDesign::CubeTexture || design == PatternDesign::CubeMultiTexture ||
		design == PatternDesign::CylinderTexture ||
		design == PatternDesign::PlanarTexture ||
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

	// all pattern types that can have a noise addon
	if (design == PatternDesign::Checkerboard || design == PatternDesign::Stripey || design == PatternDesign::CubeCheckerboard ||
		design == PatternDesign::CubeTexture || design == PatternDesign::CubeMultiTexture || design == PatternDesign::CylinderCheckerboard ||
		design == PatternDesign::CylinderTexture || design == PatternDesign::PlanarTexture)
	{
		cbPNoise->Visible = true;
	}
	else
	{
        cbPNoise->Visible = false;
    }
}


void TfrmMain::BuildPatternTransformTab(int id)
{
	lbPatternTransforms->Clear();

	if (GWorld->Objects[id]->Material->SurfacePattern->TransformsCount() != 0)
	{
		for (int t = 0; t < GWorld->Objects[id]->Material->SurfacePattern->TransformsCount(); t++)
		{
			TransformConfiguration tc = GWorld->Objects[id]->Material->SurfacePattern->TransformAt(t);

			lbPatternTransforms->Items->Add(tc.TypeAsString().c_str());
		}

		lbPatternTransforms->ItemIndex = 0;

		lbPatternTransformsClick(NULL);
	}
}


void __fastcall TfrmMain::pcMaterialChange(TObject *Sender)
{
	if (pcMaterial->TabIndex == 2)
	{
		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				if (id != iTexture->Tag)
				{
					if (type == __TypeObject)
					{
						switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
						{
						case PatternDesign::CubeTexture:
						{
							CubeTexture* p = dynamic_cast<CubeTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

							ShowTexture(p->Texture, p->TextureWidth, p->TextureHeight);
							break;
						}
						case PatternDesign::CylinderTexture:
						{
							CylinderTexture* p = dynamic_cast<CylinderTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

							ShowTexture(p->Texture, p->TextureWidth, p->TextureHeight);
							break;
						}
						case PatternDesign::PlanarTexture:
						{
							PlanarTexture* p = dynamic_cast<PlanarTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

							ShowTexture(p->Texture, p->TextureWidth, p->TextureHeight);
							break;
						}
						case PatternDesign::SphericalTexture:
						{
							SphericalTexture* p = dynamic_cast<SphericalTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

							ShowTexture(p->Texture, p->TextureWidth, p->TextureHeight);
							break;
						}
					}
					}

					iTexture->Tag = id;
				}
			}
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


void __fastcall TfrmMain::tbAmbientChange(TObject *Sender)
{
	int id = PTreeObject(tvObjects->Selected->Data)->ID;

	TTrackBar *trackbar = (TTrackBar*)Sender;

	System::UnicodeString value = FloatToStr((double)trackbar->Position / 100);

	switch (trackbar->Tag)
	{
	case 0:
		lMBAmbience->Caption = value;
		break;
	case 1:
		lMBDiffuse->Caption = value;
		break;
	case 2:
		lMBReflectivity->Caption = value;
		break;
	case 4:
		lMBShininess->Caption = value;
		break;
	case 5:
		lMBSpecular->Caption = value;
		break;
	case 6:
		lMBTransparency->Caption = value;
		break;
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
			if (lbObjectTransforms->Items->Count != 0 && lbObjectTransforms->ItemIndex != -1)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbObjectTransforms->ItemIndex);

				std::wstring a = eOTAngle->Text.c_str();

				tc.Angle = stod(a);

				GWorld->Objects[id]->TransformReplaceAt(lbObjectTransforms->ItemIndex, tc);

                // needed to ensure "model" objects update bounding boxes
                GWorld->Objects[id]->PostSetup(id);
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
			if (lbObjectTransforms->Items->Count != 0 && lbObjectTransforms->ItemIndex != -1)
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
	if (selected >= 0)
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
}


void __fastcall TfrmMain::ePTAngleExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			if (lbPatternTransforms->Items->Count != 0 && lbPatternTransforms->ItemIndex != -1)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbPatternTransforms->ItemIndex);

				std::wstring a = ePTAngle->Text.c_str();

				tc.Angle = stod(a);

				GWorld->Objects[id]->Material->SurfacePattern->TransformReplaceAt(lbPatternTransforms->ItemIndex, tc);
			}
		}
	}
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

				if (type == __TypeLight)
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

			if (type == __TypeLight)
			{
				GWorld->Lights[id]->Position.x = eLPositionX->Text.ToDouble();
				GWorld->Lights[id]->Position.y = eLPositionY->Text.ToDouble();
				GWorld->Lights[id]->Position.z = eLPositionZ->Text.ToDouble();
			}
		}
	}
}


void __fastcall TfrmMain::eLSamplesExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeLight)
			{
				int samples = eLSamples->Text.ToIntDef(-1);

				if (samples == -1)
				{
					samples = 8;
					eLSamples->Text = "8";
				}

				AreaLight* al = dynamic_cast<AreaLight*>(GWorld->Lights[id]);

			    al->SetDimensions(GWorld->Lights[id]->uvec, GWorld->Lights[id]->vvec, samples);
			}
		}
	}
}


void __fastcall TfrmMain::ePTXExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			if (lbPatternTransforms->Items->Count != 0 && lbPatternTransforms->ItemIndex != -1)
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
		}
    }
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

				if (type == __TypeObject)
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

		if (type == __TypeObject)
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
	std::wstring file_name = Utility::GetSaveFileName(0);

	if (!file_name.empty())
	{
		GWorld->SaveScene(file_name);
	}
}


void __fastcall TfrmMain::sbPatternChangeClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
				if (cbPatternChangeTo->ItemIndex == 0)  // changed to "none"
				{
					GWorld->Objects[id]->Material->RemovePattern();
				}
				else
				{
					PatternProperties pp;
					pp.FileName = eNewTexture->Text.c_str();

					pp.Colour1 = GWorld->Objects[id]->Material->SurfacePattern->Colours[0];
					pp.Colour2 = GWorld->Objects[id]->Material->SurfacePattern->Colours[1];

					PatternDesign ap = GSceneLoader->PatternFromObject2(GWorld->Objects[id]->Primitive, cbPatternChangeTo->ItemIndex);

					if (ap == PatternDesign::CubeTexture && pp.FileName.find(L'*') != std::wstring::npos)
					{
						ap = PatternDesign::CubeMultiTexture;
					}

					if (ap != PatternDesign::None)
					{
						delete GWorld->Objects[id]->Material->SurfacePattern;

						GWorld->SetObjectPattern(id, ap, pp);
					}
				}

                BuildMaterialPanelFromObject(id);
			}
		}
	}
}


void __fastcall TfrmMain::bSelectNewTextureClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetOpenFileName(1);

	if (!file_name.empty())
	{
		eNewTexture->Text = file_name.c_str();
		eNewTexture->Hint = file_name.c_str();
	}
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

			switch (type)
			{
			case __TypeLight:
				delete GWorld->Lights[id];
				GWorld->Lights.erase(GWorld->Lights.begin() + id);
				PopulateTreeView();
				break;
			case __TypeObject:
				delete GWorld->Objects[id];
				GWorld->Objects.erase(GWorld->Objects.begin() + id);
				PopulateTreeView();
				break;
			}
		}
	}
}


void TfrmMain::AddNewObject(int primitive, int pattern, PatternProperties properties, std::wstring name)
{
	PatternDesign ap = PatternDesign::None;

	switch (pattern)
	{
	case 1:
		switch (primitive)
		{
		case 0:
		case 2:
			ap = PatternDesign::CylinderCheckerboard;
			break;
		case 1:
			ap = PatternDesign::CubeCheckerboard;
			break;
		case 4:
			ap = PatternDesign::Checkerboard;
			break;
		case 5:
			ap = PatternDesign::SphericalCheckerboard;
			break;
		}
		break;
	case 2:
		ap = PatternDesign::Fractal;
		break;
	case 3:
		ap = PatternDesign::Gradient;
		break;
	case 4:
		ap = PatternDesign::Gradient2;
		break;
	case 5:
		ap = PatternDesign::Perlin1;
		break;
	case 6:
		ap = PatternDesign::Perlin2;
		break;
	case 7:
		ap = PatternDesign::Perlin3;
		break;
	case 8:
		ap = PatternDesign::Ring;
		break;
	case 9:
		ap = PatternDesign::Simplex;
		break;
	case 10:
		ap = PatternDesign::Stripey;
		break;
	case 11:
		switch (primitive)
		{
		case 0:
		case 2:
			ap = PatternDesign::CylinderTexture;
			break;
		case 1:
			ap = PatternDesign::CubeTexture;
			break;
		case 4:
			ap = PatternDesign::PlanarTexture;
			break;
		case 5:
			ap = PatternDesign::SphericalTexture;
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

				if (type == __TypeObject)
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

			if (type == __TypeCamera)
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
    GWorld->Cam->CalculatePixelSize();
}


void __fastcall TfrmMain::cbResizeToDisplayClick(TObject *Sender)
{
	if (cbResizeToDisplay->Checked)
	{
		FormResize(NULL);
	}
}


void __fastcall TfrmMain::ePFrequencyExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
				if (GWorld->Objects[id]->Material->SurfacePattern->IncludeNoise)
				{
					GWorld->Objects[id]->Material->SurfacePattern->SetNoise(
						ePFrequency->Text.ToDouble(),
						ePAmplitude->Text.ToDouble(),
						ePLacunarity->Text.ToDouble(),
						ePPersistence->Text.ToDouble(),
						ePScale->Text.ToDouble(),
						ePPhase->Text.ToDouble());
				}

//				Fractal* p = dynamic_cast<Fractal*>(GWorld->Objects[id]->Material->SurfacePattern);

//				p->SetNoise(ePFrequency->Text.ToDouble(),
//					ePAmplitude->Text.ToDouble(),
//					ePLacunarity->Text.ToDouble(),
//					ePPersistence->Text.ToDouble(), 1, 1); // to check, generic code should work for fractal
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

			if (type == __TypeObject)
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

				default:
					ePFrequencyExit(NULL);
					break;
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

			if (type == __TypeObject)
			{
				switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
				{
				case PatternDesign::Perlin3:
				{
					Perlin3* p = dynamic_cast<Perlin3*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->Scale = ePScale->Text.ToDouble();
					break;
				}

				default:
					ePFrequencyExit(NULL);
					break;
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

			if (type == __TypeObject)
			{
				switch (GWorld->Objects[id]->Material->SurfacePattern->Design)
				{
				case PatternDesign::CubeCheckerboard:
				{
					CubeChecker* p = dynamic_cast<CubeChecker*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->PatternWidth = ePWidth->Text.ToDouble();
					p->PatternHeight = ePHeight->Text.ToDouble();
					break;
				}
				case PatternDesign::CylinderCheckerboard:
				{
					CylinderCheckerboard* p = dynamic_cast<CylinderCheckerboard*>(GWorld->Objects[id]->Material->SurfacePattern);
					p->PatternWidth = ePWidth->Text.ToDouble();
					p->PatternHeight = ePHeight->Text.ToDouble();
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
					p->PatternWidth = ePWidth->Text.ToDouble();
					p->PatternHeight = ePHeight->Text.ToDouble();
					break;
				}
				}
			}
		}
	}
}


void __fastcall TfrmMain::cbPNoiseClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
				Pattern* p = GWorld->Objects[id]->Material->SurfacePattern;
				p->IncludeNoise = cbPNoise->Checked;
			}

			ePScale->Visible = cbPNoise->Checked;
			ePPhase->Visible = cbPNoise->Checked;
			ePFrequency->Visible = cbPNoise->Checked;
			ePAmplitude->Visible = cbPNoise->Checked;
			ePLacunarity->Visible = cbPNoise->Checked;
			ePPersistence->Visible = cbPNoise->Checked;

			lPScale->Visible = cbPNoise->Checked;
			lPPhase->Visible = cbPNoise->Checked;
			lPFrequency->Visible = cbPNoise->Checked;
			lPAmplitude->Visible = cbPNoise->Checked;
			lPLacunarity->Visible = cbPNoise->Checked;
			lPPersistence->Visible = cbPNoise->Checked;
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

			if (type == __TypeObject)
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


void __fastcall TfrmMain::cbPatternChangeToChange(TObject *Sender)
{
	if (cbPatternChangeTo->ItemIndex == 11)
	{
		eNewTexture->Visible = true;
		bSelectNewTexture->Visible = true;
	}
	else
	{
		eNewTexture->Visible = false;
		bSelectNewTexture->Visible = false;
    }
}


void __fastcall TfrmMain::bAddPatternClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
				Checkerboard* p = new Checkerboard(false, L"Checkboard");
				p->SetColours(Colour(0.6, 0.6, 0.6), Colour(0.2, 0.2, 0.2));
				GWorld->Objects[id]->Material->SetPattern(p);

				BuildMaterialPanelFromObject(id);
			}
		}
	}
}


void __fastcall TfrmMain::cbIoRListChange(TObject *Sender)
{
	eIoR->Text = IndexOfRefractionValues[cbIoRList->ItemIndex];

    eIoRExit(eIoR);
}


void __fastcall TfrmMain::eIoRExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;

			double ior = eIoR->Text.ToDouble();

			if (ior < 1)
			{
				ior = 1;

                eIoR->Text = "1";
            }

			GWorld->Objects[id]->Material->RefractiveIndex = ior;
		}
	}
}


void TfrmMain::ShowTexture(Colour* data, int width, int height)
{
	TBitmap* bit = new TBitmap();
	bit->PixelFormat = pf24bit;
	bit->Width = width;
	bit->Height = height;

	TRGBTriple *ptr;

	for (int y = 0; y < height; y++)
	{
		ptr = reinterpret_cast<TRGBTriple *>(bit->ScanLine[y]);

		for (int x = 0; x < width; x++)
		{
			ptr[x].rgbtRed = std::floor(data[y * width + x].r * 255);
			ptr[x].rgbtGreen = std::floor(data[y * width + x].g * 255);
			ptr[x].rgbtBlue = std::floor(data[y * width + x].b * 255);
		}
	}

	iTexture->Picture->Assign(bit);

    lTextureDimensions->Caption = IntToStr(width) + " x " + IntToStr(height);

	delete bit;
}


void __fastcall TfrmMain::sbCopyObjectClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
				GWorld->MakeCopyOfObjectAt(id);

				PopulateTreeView();
			}
		}
	}
}


void __fastcall TfrmMain::eONameExit(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
			   GWorld->Objects[id]->Name = eOName->Text;

			   tvObjects->Selected->Text = eOName->Text;
			}
		}
	}
}


void __fastcall TfrmMain::bOpenTextureClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
			int id = PTreeObject(tvObjects->Selected->Data)->ID;
			int type = PTreeObject(tvObjects->Selected->Data)->Type;

			if (type == __TypeObject)
			{
				std::wstring file_name = Utility::GetOpenFileName(3);

                if (!file_name.empty())
				{
					GWorld->ReplaceTexture(id, file_name);

					iTexture->Tag = -1;
                    lTexturePath->Caption = file_name.c_str();

                    pcMaterialChange(nullptr);
                }
			}
		}
	}
}
