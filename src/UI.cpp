#include "UI.h"

void UI::Register() {

    if (!SKSEMenuFramework::IsInstalled()) {
        return;
    }
    Configuration::Example2::Buffer[0] = '\0';
    SKSEMenuFramework::SetSection("Object Manipulation Overhaul Example SKSE");
    SKSEMenuFramework::AddSectionItem("Place item", Example1::Render);
}

void UI::Example1::LookupForm() {
    auto addForm = RE::TESForm::LookupByID(0xC56C4);
    if (addForm) {
        AddBoundObject = addForm->As<RE::TESObjectSTAT>();
    } else {
        AddBoundObject = nullptr;
    }
}

void __stdcall UI::Example1::Render() {
    if (AddBoundObject) {
        if (ImGui::Button("Place Candle")) {
            auto player = RE::PlayerCharacter::GetSingleton();
            if (auto refptr = player->PlaceObjectAtMe(AddBoundObject, false)) {
                if (auto ref = refptr.get()) {
                    ObjectManipulationOverhaul::StartDraggingObject(ref);
                }
            }
        }
    } else {
        ImGui::Text("Form not found");
    }
}