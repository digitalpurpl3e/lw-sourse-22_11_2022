#pragma once
#include <concepts>
#include <cwctype>
#include <mutex>
#include <numbers>
#include <random>
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>



enum class Team {
    None = 0,
    Spectators,
    TT,
    CT
};


enum class WeaponId : short {
    None = 0,
    Deagle = 1,
    Elite,
    Fiveseven,
    Glock,
    Ak47 = 7,
    Aug,
    Awp,
    Famas,
    G3SG1,
    GalilAr = 13,
    M249,
    M4A1 = 16,
    Mac10,
    P90 = 19,
    ZoneRepulsor,
    Mp5sd = 23,
    Ump45,
    Xm1014,
    Bizon,
    Mag7,
    Negev,
    Sawedoff,
    Tec9,
    Taser,
    Hkp2000,
    Mp7,
    Mp9,
    Nova,
    P250,
    Shield,
    Scar20,
    Sg553,
    Ssg08,
    GoldenKnife,
    Knife,
    Flashbang = 43,
    HeGrenade,
    SmokeGrenade,
    Molotov,
    Decoy,
    IncGrenade,
    C4,
    Healthshot = 57,
    KnifeT = 59,
    M4a1_s,
    Usp_s,
    Cz75a = 63,
    Revolver,
    TaGrenade = 68,
    Axe = 75,
    Hammer,
    Spanner = 78,
    GhostKnife = 80,
    Firebomb,
    Diversion,
    FragGrenade,
    Snowball,
    BumpMine,
    Bayonet = 500,
    ClassicKnife = 503,
    Flip = 505,
    Gut,
    Karambit,
    M9Bayonet,
    Huntsman,
    Falchion = 512,
    Bowie = 514,
    Butterfly,
    Daggers,
    Paracord,
    SurvivalKnife,
    Ursus = 519,
    Navaja,
    NomadKnife,
    Stiletto = 522,
    Talon,
    SkeletonKnife = 525,
    NameTag = 1200,
    Sticker = 1209,
    MusicKit = 1314,
    SealedGraffiti = 1348,
    Graffiti = 1349,
    OperationHydraPass = 1352,
    CSGOWeaponCase = 4001,
    Esports2013Case = 4002,
    OperationBravoCase = 4003,
    CSGOWeaponCase2 = 4004,
    Esports2013WinterCase = 4005,
    WinterOffensiveCase = 4009,
    CSGOWeaponCase3 = 4010,
    OperationPhoenixCase = 4011,
    HuntsmanCase = 4017,
    OperationBreakoutCase = 4018,
    Esports2014SummerCase = 4019,
    OperationVanguardCase = 4029,
    ChromaCase = 4061,
    Chroma2Case = 4089,
    FalchionCase = 4091,
    ShadowCase = 4138,
    RevolverCase = 4186,
    OperationWildfireCase = 4187,
    Chroma3Case = 4233,
    GammaCase = 4236,
    Gamma2Case = 4281,
    GloveCase = 4288,
    SpectrumCase = 4351,
    OperationHydraCase = 4352,
    BronzeOperationHydraCoin = 4353,
    Spectrum2Case = 4403,
    ClutchCase = 4471,
    HorizonCase = 4482,
    DangerZoneCase = 4548,
    PrismaCase = 4598,
    Patch = 4609,
    ShatteredWebCase = 4620,
    Berlin2019SouvenirToken = 4628,
    CS20Case = 4669,
    Prisma2Case = 4695,
    FractureCase = 4698,
    GloveStuddedBrokenfang = 4725,
    OperationBrokenFangCase = 4717,
    SnakebiteCase = 4747,
    OperationRiptideCase = 4790,
    Stockholm2021SouvenirToken = 4802,
    DreamsAndNightmaresCase = 4818,
    GloveStuddedBloodhound = 5027,
    GloveT,
    GloveCT,
    GloveSporty,
    GloveSlick,
    GloveLeatherWrap,
    GloveMotorcycle,
    GloveSpecialist,
    GloveHydra
};


namespace Helpers
{
    //unsigned int calculateColor(Color4 color) noexcept;
   // unsigned int calculateColor(Color3 color) noexcept;
   // unsigned int calculateColor(int r, int g, int b, int a) noexcept;
    void setAlphaFactor(float newAlphaFactor) noexcept;
    float getAlphaFactor() noexcept;
    void convertHSVtoRGB(float h, float s, float v, float& outR, float& outG, float& outB) noexcept;
    void healthColor(float fraction, float& outR, float& outG, float& outB) noexcept;
    unsigned int healthColor(float fraction) noexcept;

    constexpr auto units2meters(float units) noexcept
    {
        return units * 0.0254f;
    }

    //ImWchar* getFontGlyphRanges() noexcept;

    constexpr std::uint8_t utf8SeqLen(char firstByte) noexcept
    {
        return (firstByte & 0x80) == 0x00 ? 1 :
            (firstByte & 0xE0) == 0xC0 ? 2 :
            (firstByte & 0xF0) == 0xE0 ? 3 :
            (firstByte & 0xF8) == 0xF0 ? 4 :
            0;
    }

    std::wstring toWideString(const std::string& str) noexcept;

    bool decodeVFONT(std::vector<char>& buffer) noexcept;
    std::vector<char> loadBinaryFile(const std::string& path) noexcept;

    template <typename T> constexpr auto deg2rad(T degrees) noexcept { return degrees * (std::numbers::pi_v<T> / static_cast<T>(180)); }
    template <typename T> constexpr auto rad2deg(T radians) noexcept { return radians * (static_cast<T>(180) / std::numbers::pi_v<T>); }

    [[nodiscard]] std::size_t calculateVmtLength(const std::uintptr_t* vmt) noexcept;

    constexpr auto isKnife(WeaponId id) noexcept
    {
        return (id >= WeaponId::Bayonet && id <= WeaponId::SkeletonKnife) || id == WeaponId::KnifeT || id == WeaponId::Knife;
    }

    constexpr auto isSouvenirToken(WeaponId id) noexcept
    {
        switch (id) {
        case WeaponId::Berlin2019SouvenirToken:
        case WeaponId::Stockholm2021SouvenirToken:
            return true;
        default:
            return false;
        }
    }

    //bool worldToScreen(const Vector& worldPosition, ImVec2& screenPosition) noexcept;
   // bool worldToScreenPixelAligned(const Vector& worldPosition, ImVec2& screenPosition) noexcept;

    [[nodiscard]] constexpr auto isMP5LabRats(WeaponId weaponID, int paintKit) noexcept
    {
        return weaponID == WeaponId::Mp5sd && paintKit == 800;
    }

    class RandomGenerator {
    public:
        template <std::integral T>
        [[nodiscard]] static T random(T min, T max) noexcept
        {
            std::scoped_lock lock{ mutex };
            return std::uniform_int_distribution{ min, max }(gen);
        }

        template <std::floating_point T>
        [[nodiscard]] static T random(T min, T max) noexcept
        {
            std::scoped_lock lock{ mutex };
            return std::uniform_real_distribution{ min, max }(gen);
        }

        template <typename T>
        [[nodiscard]] static std::enable_if_t<std::is_enum_v<T>, T> random(T min, T max) noexcept
        {
            return static_cast<T>(random(static_cast<std::underlying_type_t<T>>(min), static_cast<std::underlying_type_t<T>>(max)));
        }
    private:
        inline static std::mt19937 gen{ std::random_device{}() };
        inline static std::mutex mutex;
    };

    template <typename T>
    [[nodiscard]] T random(T min, T max) noexcept
    {
        return RandomGenerator::random(min, max);
    }

    class ToUpperConverter {
    public:
        std::wstring_view toUpper(std::wstring_view string)
        {
            assert(string.length() < buffer.size());
            std::size_t length = 0;
            for (auto c : string)
                buffer[length++] = toUpper(c);
            buffer[length] = '\0';
            return { buffer.data(), length };
        }

    private:
        wchar_t toUpper(wchar_t c)
        {
            if (c >= 'a' && c <= 'z') {
                return c - ('a' - 'A');
            }
            else if (c > 127) {
                if (const auto it = cache.find(c); it != cache.end()) {
                    return it->second;
                }
                else {
                    const auto upper = std::towupper(c);
                    cache.emplace(c, upper);
                    return upper;
                }
            }
            return c;
        }

        std::unordered_map<wchar_t, wchar_t> cache;
        std::array<wchar_t, 4096> buffer;
    };
}
enum class FrameStage {
    UNDEFINED = -1,
    START,
    NET_UPDATE_START,
    NET_UPDATE_POSTDATAUPDATE_START,
    NET_UPDATE_POSTDATAUPDATE_END,
    NET_UPDATE_END,
    RENDER_START,
    RENDER_END
};
