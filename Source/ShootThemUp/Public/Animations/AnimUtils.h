#pragma once

class AnimUtils
{
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* AnimMontage)
	{
		if(!AnimMontage) return nullptr;

		const auto Notifies = AnimMontage->Notifies;
		for(auto NotifyEvents : Notifies)
		{
			auto AnimNotify = Cast<T>(NotifyEvents.Notify);
			if(AnimNotify) return AnimNotify;
		}

		return nullptr;
	}
};
