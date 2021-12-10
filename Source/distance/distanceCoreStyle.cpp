
#include "distanceCoreStyle.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> FdistanceCoreStyle::StylePtr;

//TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory)
TSharedPtr<ISlateStyle> FindStyle()
{
	//Game/>>>  for Content diretory path
	//FString Path = "/Game/TopDownCPP/UI";
	//	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("CoreStyle"), Path, Path);

	// this method is for loading directly from disk
	// whats the difference? we just dont know.
	FString Path = FPaths::ProjectContentDir() / TEXT("/TopDownCPP/UI/Styles");
	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("WS_DefaultStyle"), Path, Path);

	Style->Set("Red", FLinearColor::Red);
	Style->Set("DefaultPadding", FMargin(15.f));
	Style->Set("BGImg", new IMAGE_BRUSH("BGImg", FVector2D(256.f)));

	//TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("MyCoreStyle"), ScopeToDirectory, ScopeToDirectory);
	// unclear why ScopeToDirectory is here twice, requires a scope to look for in certain location regardless
	// generally theyre the same

	return Style;
}

#undef IMAGE_BRUSH

void FdistanceCoreStyle::Initialize()
{
	Shutdown();

	StylePtr = FindStyle();
	//StylePtr = FindStyle("/Game/TopDownCPP/UI/Styles");
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void FdistanceCoreStyle::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr); // makes Engine aware of existence of this style
		StylePtr.Reset();
	}
}

const ISlateStyle& FdistanceCoreStyle::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}

	return *StylePtr;
}
