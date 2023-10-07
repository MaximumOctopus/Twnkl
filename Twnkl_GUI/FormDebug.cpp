

#include <vcl.h>
#pragma hdrstop

#include "FormDebug.h"
#include "SceneLoader.h"
#include "World.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDebug *frmDebug;

extern SceneLoader* GSceneLoader;
extern World* GWorld;


__fastcall TfrmDebug::TfrmDebug(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TfrmDebug::FormShow(TObject *Sender)
{
	mLoader->Clear();

	for (int i = 0; i < GSceneLoader->Errors.size(); i++)
	{
		mLoader->Lines->Add(GSceneLoader->Errors[i].c_str());
	}

	mWorld->Clear();

	for (int i = 0; i < GWorld->Errors.size(); i++)
	{
		mWorld->Lines->Add(GWorld->Errors[i].c_str());
	}
}
