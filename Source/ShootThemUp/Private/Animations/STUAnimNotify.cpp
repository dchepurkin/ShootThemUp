// Shoot Them Up Game. All Right Reserved


#include "Animations/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (!MeshComp || !Animation)
        return;

    OnNotify.Broadcast(MeshComp);

    Super::Notify(MeshComp, Animation);
}
