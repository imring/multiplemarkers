#include "main.hpp"
#include "patch.hpp"

#include "CRadar.h"
#include "CAudioEngine.h"

multiplemarkers::multiplemarkers() {
    CMenuManager_AdditionalOptionInput_install();
}

multiplemarkers::~multiplemarkers() {
    CMenuManager_AdditionalOptionInput_uninstall();
}

int multiplemarkers::add(CMenuManager *manager, CVector pos) {
    AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_SELECT, 0.0, 1.0);
    int blip                    = CRadar::SetCoordBlip(BLIP_COORD, pos, 0, BLIP_DISPLAY_BLIPONLY, const_cast<char *>("CODEWAY"));
    manager->m_nTargetBlipIndex = blip; // last blip is current
    CRadar::SetBlipSprite(blip, RADAR_SPRITE_WAYPOINT);

    blips.emplace_back(blip);
    return blip;
}

void multiplemarkers::remove(CMenuManager *manager, int blip) {
    AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_BACK, 0.0, 1.0);
    CRadar::ClearBlip(blip);

    const auto it = std::find(blips.begin(), blips.end(), blip);
    if (it != blips.end()) {
        blips.erase(it);
    }
    if (manager->m_nTargetBlipIndex == blip) { // if the blip was the current, make the previous one current
        manager->m_nTargetBlipIndex = !blips.empty() ? blips.back() : 0;
    }
}

void multiplemarkers::on_mark(CMenuManager *manager) {
    CVector mouse_pos{manager->m_vMousePos.x, manager->m_vMousePos.y, 0};

    if (!blips.empty()) {
        // check if the cursor is on any marker
        for (auto it = blips.begin(); it != blips.end();) {
            const int blip  = *it;
            const int index = CRadar::GetActualBlipArrayIndex(blip);
            if (index == -1) { // invalid?
                it = blips.erase(it);
                continue;
            }

            const float dist = DistanceBetweenPoints(mouse_pos, CRadar::ms_RadarTrace[index].m_vPosition);
            if (dist <= 14.f) {
                remove(manager, blip);
                return;
            }
            ++it;
        }
    }
    add(manager, mouse_pos);
}