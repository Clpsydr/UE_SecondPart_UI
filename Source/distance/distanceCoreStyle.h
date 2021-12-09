#pragma once

#include "Slate.h"

class DISTANCE_API FdistanceCoreStyle  //its a singleton that should work fine, since its not UObject related
{
public:

	static void Initialize();

	static void Shutdown();

	static const ISlateStyle& Get();

private:

	static TSharedPtr<ISlateStyle> StylePtr;
};