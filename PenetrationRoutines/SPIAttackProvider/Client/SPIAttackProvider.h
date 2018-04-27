#pragma once;
#include <string>
#include <map>
#include <vector>
#include "../../../Core/MemWarsCore.h"
#include "../../../AttackServices/SystemProcessInjectionAttack/StealthyMemManipulatorClient.h"
#include "../../../AttackServices/SystemProcessInjectionAttack/StealthyMemManipulatorGetHandleId.h"
#include "../../AttackProvider/AttackProvider.h"

#define MAX_VAL_SIZE 255

class SPIAttackProvider : AttackProvider {
public:
    BOOL Init(wstring targetProcess, wstring pivotProcess);
    BOOL ReadProcessMemory(void* address, void* readBuf, SIZE_T readSize, SIZE_T* bytesRead = NULL);
    BOOL WriteProcessMemory(void* address, void* writeBuf, SIZE_T writeSize, SIZE_T* bytesWritten = NULL);
protected:
    wstring pivotProcess;
    wstring targetProcess;
    StealthyMemClient smc;
};


/*
Strings of interest:
lua_*
get_*
get_unit_data
mTarget*
unit_position
unit_indices
unit_rotation
local_rotation
local_position
set_local_position
world_pose
world_rotation
world_position
set_local_pose
update_position_lookup
*/