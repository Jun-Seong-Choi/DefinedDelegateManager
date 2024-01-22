#pragma once

#include "CoreMinimal.h"
#include "DefinedDelegateManager.generated.h"

#define BIND( Syntax )\
{\
    Syntax;\
}
#define DISPATCH( Name, ... )\
{\
    UDefinedDelegateManager::Myself->Name.Broadcast( __VA_ARGS__ );\
}
#define REMOVE( Name, DelegateHandle )\
if(DelegateHandle.IsValid() && UDefinedDelegateManager::Myself)\
{\
    UDefinedDelegateManager::Myself->Name.Remove( DelegateHandle );\
}
#define CLEAR( Name )\
if(UDefinedDelegateManager::Myself)\
{\
    UDefinedDelegateManager::Myself->Name.Clear();\
}

#define DEFINE_TYPE( Name )   FDelegate##Name
#define DEFINE_NAME( Name )   DEFINE_TYPE( Name )   Name

#define DECLARE_DELEGATE_IMPLEMENT( Name, ... ) typedef TMulticastDelegate<void(__VA_ARGS__)>   DEFINE_TYPE( Name ); DEFINE_NAME( Name )

#define BIND_OBJECT( Name, Object, Function, ... )   BIND( UDefinedDelegateManager::Myself->Name.IsBoundToObject( Object ) ? FDelegateHandle() : UDefinedDelegateManager::Myself->Name.AddUObject( Object, Function, ##__VA_ARGS__ ) )
#define BIND_SHARED( Name, Object, Function, ... )   BIND( UDefinedDelegateManager::Myself->Name.IsBoundToObject( Object ) ? FDelegateHandle() : UDefinedDelegateManager::Myself->Name.AddSP( Object, Function, ##__VA_ARGS__ ) )

UCLASS()
class UDefinedDelegateManager : public UObject
{
    GENERATED_BODY()
public:
    static UDefinedDelegateManager* Myself;

public:
    UDefinedDelegateManager() { UDefinedDelegateManager::Myself = this; }
    ~UDefinedDelegateManager() { UDefinedDelegateManager::Myself = nullptr; }

public:

    // DECLARE_DELEGATE_IMPLEMENT(Delegate-Name, Delegate-Arguments);
};

UDefinedDelegateManager* UDefinedDelegateManager::Myself = nullptr;
