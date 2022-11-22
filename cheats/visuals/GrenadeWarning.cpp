#include "GrenadePrediction.h"
#include "../menu.h"

void GrenadeWarning::RenderHeProjectile() {
    Vector Screen;
    if (math::world_to_screen(End, Screen))
    {
        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen.x, Screen.y), 26 - 10 + 5, safe ? IM_COL32(170, 170, 255, 190) : IM_COL32(255, 44, 20, 255), 35);
        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen.x, Screen.y), 26 - 10, IM_COL32(2, 9, 46, 200), 35);
        DrawString(ImVec2(Screen.x + 1, Screen.y - 1), Color(255, 255, 255, 255), true, false, skeet_menu.weapon_font, "j");
    }
    else if (Distance <= 450) {


        Vector dir;
        m_engine()->GetViewAngles(dir);

        float ViewAngle = dir.y;

        if (ViewAngle < 0.f)
        {
            ViewAngle += 360.f;
        }
        ViewAngle = DEG2RAD(ViewAngle);

        auto TowardsAngle = math::calculate_angle(g_ctx.local()->m_vecOrigin(), End);
        TowardsAngle.Normalized();

        if (TowardsAngle.y < 0.f) {
            TowardsAngle.y += 360.f;
        }
        TowardsAngle.y = DEG2RAD(TowardsAngle.y);
        TowardsAngle.y -= ViewAngle;
        Vector2D Screen2;
        Screen2 = Vector2D(1920 / 2 - ((1920 / 1920) * 340), 1080 / 2 - ((1080 / 1080) * 340));
        RotatePoint(Screen2, Vector2D(1920 / 2, 1080 / 2), false, TowardsAngle.y);

        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen2.x, Screen2.y), 26 - 10 + 5, safe ? IM_COL32(170, 170, 255, 190) : IM_COL32(255, 44, 20, 255), 35);
        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen2.x, Screen2.y), 26 - 10, IM_COL32(2, 9, 46, 200), 35);
        DrawString(ImVec2(Screen2.x + 1, Screen2.y - 1), Color(255, 255, 255, 255), true, false, skeet_menu.weapon_font, "j");
    }
}
void GrenadeWarning::RenderIncProjectile() {
    Vector Screen;
    if (math::world_to_screen(End, Screen))
    {

        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen.x, Screen.y), 26 - 10 + 5, safe ? IM_COL32(170, 170, 255, 190) : IM_COL32(255, 44, 20, 255), 35);
        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen.x, Screen.y), 26 - 10, IM_COL32(2, 9, 46, 200), 35);
        DrawString(ImVec2(Screen.x + 1, Screen.y - 1), Color(255, 255, 255, 255), true, false, skeet_menu.weapon_font, "l");

    }
    else if (Distance <= 735) {

        Vector dir;
        m_engine()->GetViewAngles(dir);

        float ViewAngle = dir.y;

        if (ViewAngle < 0.f)
        {
            ViewAngle += 360.f;
        }
        ViewAngle = DEG2RAD(ViewAngle);

        auto TowardsAngle = math::calculate_angle(g_ctx.local()->m_vecOrigin(), End);
        TowardsAngle.Normalized();

        if (TowardsAngle.y < 0.f) {
            TowardsAngle.y += 360.f;
        }
        TowardsAngle.y = DEG2RAD(TowardsAngle.y);
        TowardsAngle.y -= ViewAngle;
        Vector2D Screen2;
        Screen2 = Vector2D(1920 / 2 - ((1920 / 1920) * 340), 1080 / 2 - ((1920 / 1080) * 340));
        RotatePoint(Screen2, Vector2D(1920 / 2, 1080 / 2), false, TowardsAngle.y);

        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen2.x, Screen2.y), 26 - 10 + 5, safe ? IM_COL32(170, 170, 255, 190) : IM_COL32(255, 44, 20, 255), 35);
        ui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Screen2.x, Screen2.y), 26 - 10, IM_COL32(2, 9, 46, 200), 35);
        DrawString(ImVec2(Screen2.x + 1, Screen2.y - 1), Color(255, 255, 255, 255), true, false, skeet_menu.weapon_font, "l");
    }
}