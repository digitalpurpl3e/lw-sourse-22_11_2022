#include "..\..\includes.hpp"

class Vector;
class QAngle;
class CViewSetup;

enum ACT
{
	ACT_NONE,
	ACT_THROW,
	ACT_LOB,
	ACT_DROP,
};

class GrenadePrediction : public singleton<GrenadePrediction>
{
private:
	std::vector<Vector> path;
	std::vector<std::pair<Vector, Color>> others;
	int type = 0;
	int act = 0;

	void Setup(Vector& vecSrc, Vector& vecThrow, const Vector& viewangles);
	void Simulate(CViewSetup* setup);

	int Step(Vector& vecSrc, Vector& vecThrow, int tick, float interval);
	bool CheckDetonate(const Vector& vecThrow, const trace_t& tr, int tick, float interval);

	void TraceHull(Vector& src, Vector& end, trace_t& tr);
	void AddGravityMove(Vector& move, Vector& vel, float frametime, bool onground);
	void PushEntity(Vector& src, const Vector& move, trace_t& tr);
	void ResolveFlyCollisionCustom(trace_t& tr, Vector& vecVelocity, const Vector& move, float interval);
	int PhysicsClipVelocity(const Vector& in, const Vector& normal, Vector& out, float overbounce);
public:
	void Tick(int buttons);
	void View(CViewSetup* setup, weapon_t* weapon);
	void Paint();
};





enum GrenadeWarningType {
    GW_HE_GRENADE = 0,
    GW_MOLOTOV = 1
};

#define GW_HIT != 1.0f
#define GW_PREDICT_INTERVAL 4
#define GW_VELOCITY_TO_MOVE_FRACTION 0.015f
#define GW_GRAVITY 0.0712f
class GrenadeWarning {
    ImU32 GetU32(Color _color)
    {
        return ((_color.a() & 0xff) << 24) + ((_color.b() & 0xff) << 16) + ((_color.g() & 0xff) << 8)
            + (_color.r() & 0xff);
    }
    float DrawString(ImVec2 pos, Color color, bool center, bool outline, ImFont* pFont, const std::string& text, float size = 17)
    {
        ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, text.c_str());
        if (!pFont->ContainerAtlas) return 0.f;
        ui::GetOverlayDrawList()->PushTextureID(pFont->ContainerAtlas->TexID);

        if (center)
            pos.x -= textSize.x / 2.0f;

        if (outline) {
            ui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x + 1, pos.y + 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
            ui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x - 1, pos.y - 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
            ui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x + 1, pos.y - 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
            ui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x - 1, pos.y + 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
        }

        ui::GetOverlayDrawList()->AddText(pFont, size, pos, GetU32(color), text.c_str());

        ui::GetOverlayDrawList()->PopTextureID();

        return pos.y + textSize.y;
    }
public:
    GrenadeWarning(player_t* Entity, GrenadeWarningType Type) {
        switch (Type) {
        case GW_HE_GRENADE:
            PredictHENade(Entity, Entity->m_vecOrigin(), Entity->m_vecVelocity());
            Distance = g_ctx.local()->m_vecOrigin().DistTo(End);
            safe = Distance > 350;
            RenderHeProjectile();
            RenderTrail();
            break;
        case GW_MOLOTOV:
            PredictMolotoveNade(Entity, Entity->m_vecOrigin(), Entity->m_vecVelocity());
            Distance = g_ctx.local()->m_vecOrigin().DistTo(End);
            safe = Distance > 200;
            RenderIncProjectile();
            RenderTrail();
            break;
        }
    }
private:
    void PredictHENade(player_t* Nade, Vector Origin, Vector Velocity) {

        int LogTimer = 0;
        trace_t Trace;
        Vector Current = Origin;
        Vector Move = Velocity * GW_VELOCITY_TO_MOVE_FRACTION;
        for (unsigned int i = 0; i < 109 - Nade->GetBody(); ++i)
        {
            Move.z -= GW_GRAVITY;
            CheckCollision(Current, Move, Trace);
            if (Trace.fraction GW_HIT || LogTimer % GW_PREDICT_INTERVAL == 0)
                Path.push_back(Current);
            Current += Move;
            LogTimer++;
            if (Trace.fraction GW_HIT)
                break;
        }
        End = Current;
    }



    void PredictMolotoveNade(player_t* Nade, Vector Origin, Vector Velocity) {
        int LogTimer = 0;
        trace_t Trace;
        Vector Current = Origin;
        Vector Move = Velocity * GW_VELOCITY_TO_MOVE_FRACTION;
        for (unsigned int i = 0; i < 130 - Nade->GetBody(); ++i)
        {
            Move.z -= GW_GRAVITY;
            CheckCollision(Current, Move, Trace);
            if (Trace.fraction GW_HIT || LogTimer % GW_PREDICT_INTERVAL == 0)
                Path.push_back(Current);
            Current += Move;
            LogTimer++;
            if (Trace.fraction GW_HIT)
                break;
        }
        End = Current;
    }

    void CheckCollision(Vector& Source, const Vector& Move, trace_t& Trace)
    {

        Vector vecAbsEnd = Source;
        vecAbsEnd += Move;


        TraceHull(Source, vecAbsEnd, Trace);
    }
    void TraceHull(Vector& Source, Vector& end, trace_t& Trace)
    {
        static CTraceFilterWorldAndPropsOnly filter;
        Ray_t init;
        init.Init(Source, end, Vector(-2.0f, -2.0f, -2.0f), Vector(2.0f, 2.0f, 2.0f));
        m_trace()->TraceRay(init, 0x200400B, &filter, &Trace);
    }
    void GradientLine(Vector Start, Vector End, Color inner, Color outer, float thickness) {
        Vector Last, Cur;
        math::world_to_screen(Start, Last);
        math::world_to_screen(End, Cur);

        if (Cur.x != 0 && Cur.y != 0 && Last.x != 0 && Last.y != 0 && Cur.x <= 1920 && Last.x <= 1920 && Cur.y <= 1080 && Last.y <= 1080) {

           
            ui::GetOverlayDrawList()->AddQuadFilled(ImVec2(Last.x, Last.y), ImVec2(Cur.x, Cur.y), ImVec2(Cur.x + thickness, Cur.y + thickness), ImVec2(Last.x + thickness, Last.y + thickness),
                IM_COL32(255,0,0,255));

            ui::GetOverlayDrawList()->AddQuadFilled(ImVec2(Last.x, Last.y), ImVec2(Cur.x, Cur.y), ImVec2(Cur.x - thickness, Cur.y - thickness), ImVec2(Last.x - thickness, Last.y - thickness),
                IM_COL32(255, 0, 0, 255));

            ui::GetOverlayDrawList()->AddQuadFilled(ImVec2(Last.x, Last.y), ImVec2(Cur.x, Cur.y), ImVec2(Cur.x + thickness, Cur.y - thickness), ImVec2(Last.x + thickness, Last.y - thickness),
                IM_COL32(255, 0, 0, 255));

            ui::GetOverlayDrawList()->AddQuadFilled(ImVec2(Last.x, Last.y), ImVec2(Cur.x, Cur.y), ImVec2(Cur.x - thickness, Cur.y + thickness), ImVec2(Last.x - thickness, Last.y + thickness),
                IM_COL32(255, 0, 0, 255));
        }
    }
    void DrawBeam(Vector S, Vector E, Color color, float W) {
        GradientLine(S, E, Color(color[0], color[1], color[2], color[3] * 0.33333333), Color(color[0], color[1], color[2], 0), W);
    }
    void RenderTrail() {

        Vector Last;
        for (auto& Cur : Path) {
            if (Last.IsZero())
            {
                Last = Cur;
                continue;
            }
            DrawBeam(Last, Cur, Color(170, 170, 255, 200), 4.3f);
            Last = Cur;
        }
    }
    void RotatePoint(Vector2D& point, Vector2D origin, bool clockwise, float angle) {
        Vector2D delta = point - origin;
        Vector2D rotated;

        if (clockwise) {
            rotated = Vector2D(delta.x * cos(angle) - delta.y * sin(angle), delta.x * sin(angle) + delta.y * cos(angle));
        }
        else {
            rotated = Vector2D(delta.x * sin(angle) - delta.y * cos(angle), delta.x * cos(angle) + delta.y * sin(angle));
        }

        point = rotated + origin;
    }
    void RenderHeProjectile();
    void RenderIncProjectile();
    bool safe;
    float Distance;
    Vector End;
    std::vector<Vector> Path;

};

