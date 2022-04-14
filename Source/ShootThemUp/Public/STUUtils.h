#pragma once

class STUUtils
{
public:
	template<class T>
	static T* GetSTUPlayerComponent(APawn* Pawn)
	{		
		if(!Pawn)return nullptr;

		const auto Component = Pawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};