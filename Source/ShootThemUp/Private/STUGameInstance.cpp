// Shoot Them Up Game. All Right Reserved

#include "STUGameInstance.h"
#include "STUSoundFunctionLib.h"

void USTUGameInstance::ToggleVolume()
{
	if(!MasterSoundClass) return;

	USTUSoundFunctionLib::ToggleSoundClassVolume(MasterSoundClass);
}
