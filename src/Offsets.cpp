#include "src/Offsets.h"

#include <Windows.h>

#include <filesystem>
#include <format>

#include "src/Pe.h"
#include "src/SigScanner.h"
#include "src/Signatures.h"

namespace hitman_randomizer {

[[noreturn]] void offsetSearchFailed() {
    MessageBoxA(NULL, "Signature scanning failed. The current game version might not be supported.", "", NULL);
    ExitProcess(0);
}

void* getOffsetByName(const std::string& name) {
    SigScanner scanner;
    auto off = scanner.find(Signatures::locators[name].signature) + Signatures::locators[name].offset;
    if(off < 0)
        offsetSearchFailed();
    return reinterpret_cast<void*>(off);
}

// TODO: Reintroduce signature scanning here. It was previously removed because of major
// signature changed introduced with Hitman update 3.30. (Inlining, NPC/WorldItem spawn
// merge). If the new layout turns out to be stable, sig scanning should be reintroduced.
GameOffsets::GameOffsets() {
    switch(getVersion()) {
    case GameVersion::H3DX12_EGS_WOA: {
        // Hitman 3 3.200.0 EGS offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140db1b90);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140db2180);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407dbb03);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400e0241);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x140236544);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140dac1ba);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d841c8);
    } break;

    case GameVersion::H3DX12_STEAM_WOA: {
        // Hitman 3 3.200.0 Steam offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140db1b90);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140db2180);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407dbb03);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400e0241);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x140236544);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140dac1ba);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d841c8);
    } break;

    case GameVersion::H3DX12_STEAM_WOA_VARIANT: {
        // Hitman 3 3.200.0 Steam variant offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140db1b90);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140db2180);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407dbb03);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400e0241);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x140236544);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140dac1ba);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d841c8);
    } break;

    default:
        MessageBoxA(NULL,std::format("The Randomizer Mod does not recognize this version of Hitman with PE timestamp {:X}.\n"
                                "Supported versions are:\n\n"
                                "- Hitman 3 Steam 3.200.0 (0x667E6CAA) (0x667E69CF)\n""- Hitman 3 EGS 3.200.0 (0x666298F6)\n",
                                PE::getTimestamp())
                    .c_str(),
                    "Randomizer Mod Failure", NULL);
        ExitProcess(0);
    }
}

const GameOffsets* GameOffsets::instance() {
    static GameOffsets instance;
    return &instance;
}

void* GameOffsets::getPushItem0() const {
    return offsets.pPushItem0;
}
void* GameOffsets::getPushItem1() const {
    return offsets.pPushItem1;
}
void* GameOffsets::getPushWorldInventoryDetour() const {
    return offsets.pPushWorldInventoryDetour;
}
void* GameOffsets::getPushNPCInventoryDetour() const {
    return offsets.pPushNPCInventoryDetour;
}
void* GameOffsets::getPushHeroInventoryDetour() const {
    return offsets.pPushHeroInventoryDetour;
}
void* GameOffsets::getPushStashInventoryDetour() const {
    return offsets.pPushStashInventoryDetour;
}
void** GameOffsets::getZEntitySceneContext_LoadScene() const {
    return offsets.pZEntitySceneContext_LoadScene;
}

}
