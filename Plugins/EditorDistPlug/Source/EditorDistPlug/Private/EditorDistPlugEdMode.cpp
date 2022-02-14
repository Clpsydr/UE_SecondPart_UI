// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorDistPlugEdMode.h"
#include "EditorDistPlugEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FEditorDistPlugEdMode::EM_EditorDistPlugEdModeId = TEXT("EM_EditorDistPlugEdMode");

FEditorDistPlugEdMode::FEditorDistPlugEdMode()
{

}

FEditorDistPlugEdMode::~FEditorDistPlugEdMode()
{

}

void FEditorDistPlugEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FEditorDistPlugEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FEditorDistPlugEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FEditorDistPlugEdMode::UsesToolkits() const
{
	return true;
}




