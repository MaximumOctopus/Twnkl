
#pragma package(smart_init)
#pragma resource "*.dfm"

#include <vcl.h>

#include "main.h"

#include "Renderer.h"
#include "SceneLoader.h"
#include "Utility.h"
#include "World.h"

#include "FormColourDialog.h"

TForm1 *Form1;

extern World* GWorld;
extern SceneLoader* GSceneLoader;


typedef struct TreeObject
{
	int Type = 0;
	int ID = 0;
} TTreeObject;

typedef TTreeObject* PTreeObject;

TTreeObject *TTreeObjectPtr;

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	GWorld = new World(0, 0, 1.152);

	GSceneLoader = new SceneLoader();
}


void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	delete GSceneLoader;
	delete GWorld;
}


void __fastcall TForm1::bOpenSceneClick(TObject *Sender)
{
	std::wstring file_name = Utility::GetFileName();

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
			}
			else
			{
				bRender->Enabled = false;
            }
        }
    }
}


void __fastcall TForm1::bRenderClick(TObject *Sender)
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


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
//
}


void __fastcall TForm1::tvObjectsClick(TObject *Sender)
{
	if (tvObjects->Selected != NULL)
	{
		if (tvObjects->Selected->Data != NULL)
		{
            ConfigureTabLayoutFor(PTreeObject(tvObjects->Selected->Data)->Type);

			switch (PTreeObject(tvObjects->Selected->Data)->Type)
			{
			case 0:         // camera
				break;
			case 1:         // light
				break;
			case 2:         // object
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;
				int type = PTreeObject(tvObjects->Selected->Data)->Type;

				BuildMaterialPanelFromObject(id);
				BuildTransformTab(type, id);
				break;
			}
			}
		}
	}
}


void __fastcall TForm1::sMaterialColourMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
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


void TForm1::ConfigureTabLayoutFor(int type)
{
	switch (type)
	{
	case 0:         // camera
		tsCamera->TabVisible = true;
		tsLight->TabVisible = false;
		tsMaterial->TabVisible = false;
		break;
	case 1:         // light
		tsCamera->TabVisible = false;
		tsLight->TabVisible = true;
		tsMaterial->TabVisible = false;
		break;
	case 2:         // object
		tsCamera->TabVisible = false;
		tsLight->TabVisible = false;
		tsMaterial->TabVisible = true;
		break;
	}
}


void TForm1::PopulateTreeView()
{
	tvObjects->Items->Clear();

	TTreeNode* lights = tvObjects->Items->Add(NULL, "Lights");
	TTreeNode* objects = tvObjects->Items->Add(NULL, "Objects");

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


void TForm1::BuildMaterialPanelFromObject(int id)
{
	sMaterialColour->Brush->Color = TColor(GWorld->Objects[id]->Material->SurfaceColour.ToIntBGR());

	tbAmbient->Position = GWorld->Objects[id]->Material->Ambient * 100.0;
	tbDiffuse->Position = GWorld->Objects[id]->Material->Diffuse * 100.0;
	tbReflectivity->Position = GWorld->Objects[id]->Material->Reflectivity * 100.0;
	//tbIoR->Position = GWorld->Objects[id]->Material->Ambient * 100.0;
	tbShininess->Position = GWorld->Objects[id]->Material->Shininess * 100.0;
	tbSpecular->Position = GWorld->Objects[id]->Material->Specular * 100.0;
	tbTransparency->Position = GWorld->Objects[id]->Material->Transparency * 100.0;

	if (GWorld->Objects[id]->Material->HasPattern)
	{
		sPatternColour1->Brush->Color = TColor(GWorld->Objects[id]->Material->SurfacePattern->Colours[0].ToIntBGR());
		sPatternColour2->Brush->Color = TColor(GWorld->Objects[id]->Material->SurfacePattern->Colours[1].ToIntBGR());
	}
	else
	{

	}

	lSurfaceColourWarning->Visible = GWorld->Objects[id]->Material->HasPattern;
}


void TForm1::BuildTransformTab(int type, int id)
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


void __fastcall TForm1::sPatternColour1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (frmColourDialog->ShowModal() == mrOk)
	{
		if (tvObjects->Selected != NULL)
		{
			if (tvObjects->Selected->Data != NULL)
			{
				int id = PTreeObject(tvObjects->Selected->Data)->ID;

				TShape *shape = (TShape*)Sender;

				shape->Brush->Color = TColor(frmColourDialog->SelectedColour);

				GWorld->Objects[id]->Material->SurfacePattern->Colours[shape->Tag].FromIntBGR(frmColourDialog->SelectedColour);
			}
		}
	}
}


void __fastcall TForm1::tbAmbientExit(TObject *Sender)
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


void __fastcall TForm1::lbObjectTransformsClick(TObject *Sender)
{
	if (lbObjectTransforms->SelCount != 0)
	{
		int id = PTreeObject(tvObjects->Selected->Data)->ID;
		int type = PTreeObject(tvObjects->Selected->Data)->Type;

		UpdateTransformTab(type, id, lbObjectTransforms->ItemIndex);
	}
}


void TForm1::UpdateTransformTab(int type, int id, int selected)
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


void __fastcall TForm1::eOTAngleExit(TObject *Sender)
{
	int id = PTreeObject(tvObjects->Selected->Data)->ID;
	int type = PTreeObject(tvObjects->Selected->Data)->Type;

	TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbObjectTransforms->ItemIndex);

	std::wstring a = eOTAngle->Text.c_str();

	tc.Angle = stod(a);

	GWorld->Objects[id]->TransformReplaceAt(lbObjectTransforms->ItemIndex, tc);
}


void __fastcall TForm1::eOTXExit(TObject *Sender)
{
	int id = PTreeObject(tvObjects->Selected->Data)->ID;
	int type = PTreeObject(tvObjects->Selected->Data)->Type;

	TransformConfiguration tc = GWorld->Objects[id]->TransformAt(lbObjectTransforms->ItemIndex);

	tc.XYZ.x = eOTX->Text.ToDouble();
	tc.XYZ.y = eOTY->Text.ToDouble();
	tc.XYZ.z = eOTZ->Text.ToDouble();

	GWorld->Objects[id]->TransformReplaceAt(lbObjectTransforms->ItemIndex, tc);
}
