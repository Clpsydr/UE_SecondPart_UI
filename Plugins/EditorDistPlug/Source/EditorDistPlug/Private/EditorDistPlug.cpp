// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorDistPlug.h"
#include "EditorDistPlugEdMode.h"

#define LOCTEXT_NAMESPACE "FEditorDistPlugModule"

void FEditorDistPlugModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FEditorDistPlugEdMode>(FEditorDistPlugEdMode::EM_EditorDistPlugEdModeId, LOCTEXT("EditorDistPlugEdModeName", "EditorDistPlugEdMode"), FSlateIcon(), true);
}

void FEditorDistPlugModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FEditorDistPlugEdMode::EM_EditorDistPlugEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorDistPlugModule, EditorDistPlug)