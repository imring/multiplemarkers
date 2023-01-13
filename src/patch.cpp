#include <xbyak/xbyak.h>
#include <plugin.h>

#include "main.hpp"
#include "patch.hpp"

std::uint8_t        *CMenuManager_AdditionalOptionInput_original = nullptr;
const std::uintptr_t CMenuManager_AdditionalOptionInput_hook     = 0x577564;
const std::uintptr_t CMenuManager_AdditionalOptionInput_jump     = 0x5775E5;

void CMenuManager_AdditionalOptionInput_install() {
    using namespace Xbyak::util;
    static auto code_gen = std::make_unique<Xbyak::CodeGenerator>();
    code_gen->reset();

    code_gen->mov(ecx, std::bit_cast<std::uintptr_t>(&main_plugin));
    code_gen->push(esi);
    code_gen->call(std::bit_cast<void *>(&multiplemarkers::on_mark));
    code_gen->jmp(std::bit_cast<void *>(CMenuManager_AdditionalOptionInput_jump));

    if (!CMenuManager_AdditionalOptionInput_original) {
        CMenuManager_AdditionalOptionInput_original = new std::uint8_t[5];
        plugin::patch::GetRaw(CMenuManager_AdditionalOptionInput_hook, CMenuManager_AdditionalOptionInput_original, 5);
    }
    void *jump = const_cast<std::uint8_t *>(code_gen->getCode());
    plugin::patch::RedirectJump(CMenuManager_AdditionalOptionInput_hook, jump);
}

void CMenuManager_AdditionalOptionInput_uninstall() {
    if (CMenuManager_AdditionalOptionInput_original) {
        plugin::patch::SetRaw(CMenuManager_AdditionalOptionInput_hook, CMenuManager_AdditionalOptionInput_original, 5);

        delete[] CMenuManager_AdditionalOptionInput_original;
        CMenuManager_AdditionalOptionInput_original = nullptr;
    }
}