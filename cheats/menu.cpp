// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <ShlObj_core.h>
#include <unordered_map>
#include "menu.h"
#include "../constchars.h"
#include "../cheats/misc/logs.h"
#include "tabs.h"

#define ALPHA (ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar| ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)
#define NOALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)

std::vector <std::string> files;
std::vector <std::string> scripts;
std::string editing_script;

auto selected_script = 0;
auto loaded_editing_script = false;

static auto menu_setupped = false;
static auto should_update = true;

IDirect3DTexture9* all_skins[36];

std::string get_wep(int id, int custom_index = -1, bool knife = true)
{
	if (custom_index > -1)
	{
		if (knife)
		{
			switch (custom_index)
			{
			case 0: return crypt_str("weapon_knife");
			case 1: return crypt_str("weapon_bayonet");
			case 2: return crypt_str("weapon_knife_css");
			case 3: return crypt_str("weapon_knife_skeleton");
			case 4: return crypt_str("weapon_knife_outdoor");
			case 5: return crypt_str("weapon_knife_cord");
			case 6: return crypt_str("weapon_knife_canis");
			case 7: return crypt_str("weapon_knife_flip");
			case 8: return crypt_str("weapon_knife_gut");
			case 9: return crypt_str("weapon_knife_karambit");
			case 10: return crypt_str("weapon_knife_m9_bayonet");
			case 11: return crypt_str("weapon_knife_tactical");
			case 12: return crypt_str("weapon_knife_falchion");
			case 13: return crypt_str("weapon_knife_survival_bowie");
			case 14: return crypt_str("weapon_knife_butterfly");
			case 15: return crypt_str("weapon_knife_push");
			case 16: return crypt_str("weapon_knife_ursus");
			case 17: return crypt_str("weapon_knife_gypsy_jackknife");
			case 18: return crypt_str("weapon_knife_stiletto");
			case 19: return crypt_str("weapon_knife_widowmaker");
			}
		}
		else
		{
			switch (custom_index)
			{
			case 0: return crypt_str("ct_gloves"); //-V1037
			case 1: return crypt_str("studded_bloodhound_gloves");
			case 2: return crypt_str("t_gloves");
			case 3: return crypt_str("ct_gloves");
			case 4: return crypt_str("sporty_gloves");
			case 5: return crypt_str("slick_gloves");
			case 6: return crypt_str("leather_handwraps");
			case 7: return crypt_str("motorcycle_gloves");
			case 8: return crypt_str("specialist_gloves");
			case 9: return crypt_str("studded_hydra_gloves");
			}
		}
	}
	else
	{
		switch (id)
		{
		case 0: return crypt_str("knife");
		case 1: return crypt_str("gloves");
		case 2: return crypt_str("weapon_ak47");
		case 3: return crypt_str("weapon_aug");
		case 4: return crypt_str("weapon_awp");
		case 5: return crypt_str("weapon_cz75a");
		case 6: return crypt_str("weapon_deagle");
		case 7: return crypt_str("weapon_elite");
		case 8: return crypt_str("weapon_famas");
		case 9: return crypt_str("weapon_fiveseven");
		case 10: return crypt_str("weapon_g3sg1");
		case 11: return crypt_str("weapon_galilar");
		case 12: return crypt_str("weapon_glock");
		case 13: return crypt_str("weapon_m249");
		case 14: return crypt_str("weapon_m4a1_silencer");
		case 15: return crypt_str("weapon_m4a1");
		case 16: return crypt_str("weapon_mac10");
		case 17: return crypt_str("weapon_mag7");
		case 18: return crypt_str("weapon_mp5sd");
		case 19: return crypt_str("weapon_mp7");
		case 20: return crypt_str("weapon_mp9");
		case 21: return crypt_str("weapon_negev");
		case 22: return crypt_str("weapon_nova");
		case 23: return crypt_str("weapon_hkp2000");
		case 24: return crypt_str("weapon_p250");
		case 25: return crypt_str("weapon_p90");
		case 26: return crypt_str("weapon_bizon");
		case 27: return crypt_str("weapon_revolver");
		case 28: return crypt_str("weapon_sawedoff");
		case 29: return crypt_str("weapon_scar20");
		case 30: return crypt_str("weapon_ssg08");
		case 31: return crypt_str("weapon_sg556");
		case 32: return crypt_str("weapon_tec9");
		case 33: return crypt_str("weapon_ump45");
		case 34: return crypt_str("weapon_usp_silencer");
		case 35: return crypt_str("weapon_xm1014");
		default: return crypt_str("unknown");
		}
	}
}

IDirect3DTexture9* get_skin_preview(const char* weapon_name, const std::string& skin_name, IDirect3DDevice9* device)
{
	IDirect3DTexture9* skin_image = nullptr;
	std::string vpk_path;

	if (strcmp(weapon_name, crypt_str("unknown")) && strcmp(weapon_name, crypt_str("knife")) && strcmp(weapon_name, crypt_str("gloves"))) //-V526
	{
		if (skin_name.empty() || skin_name == crypt_str("default"))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/") + std::string(weapon_name) + crypt_str(".png");
		else
			vpk_path = crypt_str("resource/flash/econ/default_generated/") + std::string(weapon_name) + crypt_str("_") + std::string(skin_name) + crypt_str("_light_large.png");
	}
	else
	{
		if (!strcmp(weapon_name, crypt_str("knife")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/weapon_knife.png");
		else if (!strcmp(weapon_name, crypt_str("gloves")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/ct_gloves.png");
		else if (!strcmp(weapon_name, crypt_str("unknown")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/weapon_snowball.png");

	}
	const auto handle = m_basefilesys()->Open(vpk_path.c_str(), crypt_str("r"), crypt_str("GAME"));
	if (handle)
	{
		int file_len = m_basefilesys()->Size(handle);
		char* image = new char[file_len]; //-V121

		m_basefilesys()->Read(image, file_len, handle);
		m_basefilesys()->Close(handle);

		D3DXCreateTextureFromFileInMemory(device, image, file_len, &skin_image);
		delete[] image;
	}

	if (!skin_image)
	{
		std::string vpk_path;

		if (strstr(weapon_name, crypt_str("bloodhound")) != NULL || strstr(weapon_name, crypt_str("hydra")) != NULL)
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/ct_gloves.png");
		else
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/") + std::string(weapon_name) + crypt_str(".png");

		const auto handle = m_basefilesys()->Open(vpk_path.c_str(), crypt_str("r"), crypt_str("GAME"));

		if (handle)
		{
			int file_len = m_basefilesys()->Size(handle);
			char* image = new char[file_len]; //-V121

			m_basefilesys()->Read(image, file_len, handle);
			m_basefilesys()->Close(handle);

			D3DXCreateTextureFromFileInMemory(device, image, file_len, &skin_image);
			delete[] image;
		}
	}

	return skin_image;
}

// setup some styles and colors, window size and bg alpha
// dpi setup
void c_menu::menu_setup(ImGuiStyle& style) //-V688
{
	ui::StyleColorsDark();
	ui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once); // window pos setup
	//ui::SetNextWindowBgAlpha(min(style.Alpha, 0.94f)); // window bg alpha setup

	style.ScrollbarSize = 0.0f;


	// setup skins preview
	for (auto i = 0; i < g_cfg.skins.skinChanger.size(); i++)
		if (!all_skins[i])
			all_skins[i] = get_skin_preview(get_wep(i, (i == 0 || i == 1) ? g_cfg.skins.skinChanger.at(i).definition_override_vector_index : -1, i == 0).c_str(), g_cfg.skins.skinChanger.at(i).skin_name, device); //-V810

	menu_setupped = true; // we dont want to setup menu again
}

// resize current style sizes
void c_menu::dpi_resize(float scale_factor, ImGuiStyle& style) //-V688
{
	
}


std::string get_config_dir()
{
	std::string folder;
	static TCHAR path[MAX_PATH];

	
	return folder;
}

void load_config()
{
	
}

void save_config()
{
	
}

void remove_config()
{
	
}

void add_config()
{
	
}

__forceinline void padding(float x, float y)
{
	//ui::SetCursorPosX(ui::GetCursorPosX() + x * c_menu::get().dpi_scale);
	//ui::SetCursorPosY(ui::GetCursorPosY() + y * c_menu::get().dpi_scale);
}


// title of content child
void child_title(const char* label)
{
	ui::PushFont(c_menu::get().futura_large);
	ui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

	ui::SetCursorPosX(ui::GetCursorPosX() + (12 * c_menu::get().dpi_scale));
	ui::Text(label);

	ui::PopStyleColor();
	ui::PopFont();
}

void draw_combo(const char* name, int& variable, std::vector<const char*> f)
{
	//ui::SetCursorPosX(ui::GetCursorPosX() - 6 * c_menu::get().dpi_scale);
	//ui::Text(name);
	//ui::SetCursorPosX(ui::GetCursorPosX() - 5 * c_menu::get().dpi_scale);
	//ui::SingleSelect(std::string(crypt_str("##COMBO__") + std::string(name)).c_str(), &variable, f);
	ui::SingleSelect(name, &variable, f);
}


void draw_multicombo(std::string name, std::vector<int>& variable, const char* labels[], int count, std::string& preview)
{
	static auto howmuchsel = [](std::vector<int> e) -> int {
		int s = 0;
		for (int i = 0; i < e.size(); i++)
			if (e[i])
				s++;


		return s;
	};
	if (ui::BeginCombo(name.c_str(), (howmuchsel(variable) > 0 ? std::to_string(howmuchsel(variable)) + " selected" : "None").c_str(), ImGuiComboFlags_HeightLarge, count)) // draw start
	{
		
		ui::BeginGroup();
		{

			for (auto i = 0; i < count; i++)
				ui::Selectable(labels[i], (bool*)&variable[i], ImGuiSelectableFlags_DontClosePopups);

		}
		ui::EndGroup();
		

		ui::EndCombo();
	}

	preview = crypt_str("None"); // reset preview to use later

}

bool LabelClick(const char* label, bool* v, const char* unique_id)
{
	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	// The concatoff/on thingies were for my weapon config system so if we're going to make that, we still need this aids.
	char Buf[64];
	_snprintf(Buf, 62, crypt_str("%s"), label);

	char getid[128];
	sprintf_s(getid, 128, crypt_str("%s%s"), label, unique_id);


	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(getid);
	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);

	const ImRect check_bb(window->DC.CursorPos, ImVec2(label_size.y + style.FramePadding.y * 2 + window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y + style.FramePadding.y * 2));
	ui::ItemSize(check_bb, style.FramePadding.y);

	ImRect total_bb = check_bb;

	if (label_size.x > 0)
	{
		ui::SameLine(0, style.ItemInnerSpacing.x);
		const ImRect text_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + style.FramePadding.y), ImVec2(window->DC.CursorPos.x + label_size.x, window->DC.CursorPos.y + style.FramePadding.y + label_size.y));

		ui::ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
	}

	if (!ui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
		*v = !(*v);

	if (*v)
		ui::PushStyleColor(ImGuiCol_Text, ImVec4(126 / 255.f, 131 / 255.f, 219 / 255.f, 1.f));
	if (label_size.x > 0.0f)
		ui::RenderText(ImVec2(check_bb.GetTL().x + 12, check_bb.GetTL().y), Buf);
	if (*v)
		ui::PopStyleColor();

	return pressed;

}






// SEMITABS FUNCTIONS
static ImVec2 p;
void c_menu::draw_ragebot(int child)
{
	static int sub_tab_rage = 0;
	ui::TabButton("General", &sub_tab_rage, 0, 2);
	ui::TabButton("Settings", &sub_tab_rage, 1, 2);
	static bool fuck;
	ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
	
	{
		if (!sub_tab_rage)
		{
			ui::BeginChild(crypt_str("Aimbot"), ImVec2(250, 260));
			{

				ui::Checkbox(crypt_str("Enable"), &g_cfg.ragebot.enable);

				if (g_cfg.ragebot.enable)
					g_cfg.legitbot.enabled = false;

				ui::SliderInt(crypt_str("View"), &g_cfg.ragebot.field_of_view, 1, 180, crypt_str("%d°"));
				ui::Checkbox(crypt_str("Silent aim"), &g_cfg.ragebot.silent_aim);
				ui::Checkbox(crypt_str("Automatic wall"), &g_cfg.ragebot.autowall);
				ui::Checkbox(crypt_str("Aimbot with zeus"), &g_cfg.ragebot.zeus_bot);
				ui::Checkbox(crypt_str("Aimbot with knife"), &g_cfg.ragebot.knife_bot);
				ui::Checkbox(crypt_str("Automatic fire"), &g_cfg.ragebot.autoshoot);
				ui::Checkbox(crypt_str("Automatic scope"), &g_cfg.ragebot.autoscope);
				ui::Checkbox(crypt_str("Pitch desync correction"), &g_cfg.ragebot.pitch_antiaim_correction);
			
				ui::Checkbox(crypt_str("Double tap"), &g_cfg.ragebot.double_tap);

				if (g_cfg.ragebot.double_tap)
				{
					ui::Checkbox(crypt_str("Defensive"), &g_cfg.ragebot.defensive_doubletap);
					ui::Checkbox_keybind("Double tap key", &fuck);
					ui::Keybind("##asdg111111asf", &g_cfg.ragebot.double_tap_key.key, &g_cfg.ragebot.double_tap_key.mode);
					ui::Checkbox(crypt_str("Slow teleport"), &g_cfg.ragebot.slow_teleport);
				}

				ui::Checkbox(crypt_str("Hide shots"), &g_cfg.antiaim.hide_shots);

				if (g_cfg.antiaim.hide_shots)
				{
					ui::Checkbox_keybind("Hide shots key", &fuck);
					ui::Keybind("##asdg111111asf1ads", &g_cfg.antiaim.hide_shots_key.key, &g_cfg.antiaim.hide_shots_key.mode);
					
				}
			}
			ui::EndChild();


			//else
			ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));

			ui::BeginChild(crypt_str("Anti-aim"), ImVec2(250, 260));
			{

				static auto type = 0;

				ui::Checkbox(crypt_str("Enable"), &g_cfg.antiaim.enable);
				draw_combo(crypt_str("Anti-aim type"), g_cfg.antiaim.antiaim_type, antiaim_type);

				if (g_cfg.antiaim.antiaim_type)
				{
					padding(0, 3);
					draw_combo(crypt_str("Desync"), g_cfg.antiaim.desync, desync);

					if (g_cfg.antiaim.desync)
					{
						padding(0, 3);
						draw_combo(crypt_str("LBY type"), g_cfg.antiaim.legit_lby_type, lby_type);

						if (g_cfg.antiaim.desync == 1)
						{
							ui::Checkbox_keybind("Invert desync key", &fuck);
							ui::Keybind("##asdg111111asf1adsas12qw", &g_cfg.antiaim.flip_desync.key, &g_cfg.antiaim.flip_desync.mode);
							
						}
					}
				}
				else
				{
					draw_combo(crypt_str("Movement type"), type, movement_type);
					padding(0, 3);
					draw_combo(crypt_str("Pitch"), g_cfg.antiaim.type[type].pitch, pitch);
					padding(0, 3);
					draw_combo(crypt_str("Yaw"), g_cfg.antiaim.type[type].yaw, yaw);
					padding(0, 3);
					draw_combo(crypt_str("Base angle"), g_cfg.antiaim.type[type].base_angle, baseangle);

					if (g_cfg.antiaim.type[type].yaw)
					{
						ui::SliderInt(g_cfg.antiaim.type[type].yaw == 1 ? crypt_str("Jitter range") : crypt_str("Spin range"), &g_cfg.antiaim.type[type].range, 1, 180);

						if (g_cfg.antiaim.type[type].yaw == 2)
							ui::SliderInt(crypt_str("Spin speed"), &g_cfg.antiaim.type[type].speed, 1, 15);

						padding(0, 3);
					}

					draw_combo(crypt_str("Desync"), g_cfg.antiaim.type[type].desync, desync);

					if (g_cfg.antiaim.type[type].desync)
					{
						if (type == ANTIAIM_STAND)
						{
							padding(0, 3);
							draw_combo(crypt_str("LBY type"), g_cfg.antiaim.lby_type, lby_type);
						}

						if (type != ANTIAIM_STAND || !g_cfg.antiaim.lby_type)
						{
							ui::SliderInt(crypt_str("Desync range"), &g_cfg.antiaim.type[type].desync_range, 1, 60);
							ui::SliderInt(crypt_str("Inverted desync range"), &g_cfg.antiaim.type[type].inverted_desync_range, 1, 60);
							ui::SliderInt(crypt_str("Body lean"), &g_cfg.antiaim.type[type].body_lean, 0, 100);
							ui::SliderInt(crypt_str("Inverted body lean"), &g_cfg.antiaim.type[type].inverted_body_lean, 0, 100);
						}

						if (g_cfg.antiaim.type[type].desync == 1)
						{
							static bool asdg;
							ui::Checkbox_keybind("Invert desync", &asdg);
							ui::Keybind("eryasdgaeg", &g_cfg.antiaim.flip_desync.key, &g_cfg.antiaim.flip_desync.mode);
						
						}
					}


					static bool asdg1; static bool asdg2; static bool asdg3;
					ui::Checkbox_keybind("Manual back", &asdg1);
					ui::Keybind("asfeqrygqwerty", &g_cfg.antiaim.manual_back.key, &g_cfg.antiaim.manual_back.mode);
					ui::Checkbox_keybind("Manual left", &asdg2);
					ui::Keybind("asfeqrygqwertasy", &g_cfg.antiaim.manual_left.key, &g_cfg.antiaim.manual_left.mode);
					ui::Checkbox_keybind("Manual right", &asdg3);
					ui::Keybind("asfeqrygqwertas1y", &g_cfg.antiaim.manual_right.key, &g_cfg.antiaim.manual_right.mode);
					

					

					if (g_cfg.antiaim.manual_back.key > KEY_NONE&& g_cfg.antiaim.manual_back.key < KEY_MAX || g_cfg.antiaim.manual_left.key > KEY_NONE&& g_cfg.antiaim.manual_left.key < KEY_MAX || g_cfg.antiaim.manual_right.key > KEY_NONE&& g_cfg.antiaim.manual_right.key < KEY_MAX)
					{
						ui::Checkbox(crypt_str("Manuals indicator"), &g_cfg.antiaim.flip_indicator, 65);

						static float col[4];
						ui::ColorEdit4Shonax("##invc", &g_cfg.antiaim.flip_indicator_color, ImGuiWindowFlags_NoTitleBar, 44);
					}
				}

			}
			ui::EndChild();
		}
			
			
			
		
	}
	//else
	if (sub_tab_rage)
	{
	std::vector<const char*> rage_weapons = { crypt_str("Revolver / Deagle"), crypt_str("Pistols"), crypt_str("SMGs"), crypt_str("Rifles"), crypt_str("Auto"), crypt_str("Scout"), crypt_str("AWP"), crypt_str("Heavy") };
	//ui::SetNextWindowPos(ImVec2(p.x + 640, p.y + 80));
	ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
		
		{
			
			ui::BeginChild(crypt_str("Weapon"), ImVec2(250, 260));
			{
				
				draw_combo(crypt_str("Current weapon"), hooks::rage_weapon, rage_weapons);
				
				draw_combo(crypt_str("Target selection"), g_cfg.ragebot.weapon[hooks::rage_weapon].selection_type, selection);
				
				draw_multicombo(crypt_str("Hitboxes"), g_cfg.ragebot.weapon[hooks::rage_weapon].hitboxes, hitboxes, ARRAYSIZE(hitboxes), preview);

#if BETA
				ui::Checkbox(crypt_str("Static point scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale);

				if (g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale)
				{
					ui::SliderFloat(crypt_str("Head scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale ? crypt_str("%.2f") : crypt_str("None"));
					ui::SliderFloat(crypt_str("Body scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale ? crypt_str("%.2f") : crypt_str("None"));
				}
#endif

				ui::Checkbox(crypt_str("Enable max misses"), &g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses);

				if (g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses)
					ui::SliderInt(crypt_str("Max misses"), &g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses_amount, 0, 6);

				ui::Checkbox(crypt_str("Prefer safe points"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_safe_points);
				ui::Checkbox(crypt_str("Prefer body aim"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_body_aim);

				static bool f; static bool ff;
				ui::Checkbox_keybind("Force safe points", &f);
				ui::Keybind("t", &g_cfg.ragebot.safe_point_key.key, &g_cfg.ragebot.safe_point_key.mode );

				ui::Checkbox_keybind("Force body aim", &ff);
				ui::Keybind("ff", &g_cfg.ragebot.body_aim_key.key, &g_cfg.ragebot.body_aim_key.mode);

			}
			ui::EndChild();
			
		}
		ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));
		//ui::SetNextWindowPos(ImVec2(p.x + 910, p.y + 80));
		{
			
			ui::BeginChild(crypt_str("Accurancy"), ImVec2(250, 260));
			{
				ui::Checkbox(crypt_str("Automatic stop"), &g_cfg.ragebot.weapon[hooks::rage_weapon].autostop);

				if (g_cfg.ragebot.weapon[hooks::rage_weapon].autostop)
					draw_multicombo(crypt_str("Modifiers"), g_cfg.ragebot.weapon[hooks::rage_weapon].autostop_modifiers, autostop_modifiers, ARRAYSIZE(autostop_modifiers), preview);

				ui::Checkbox(crypt_str("Hitchance"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance);

				if (g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance)
					ui::SliderInt(crypt_str("Hitchance amount"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance_amount, 1, 100);

				if (g_cfg.ragebot.double_tap && hooks::rage_weapon <= 4)
				{
					
					ui::Checkbox(crypt_str("Double tap hitchance"), &g_cfg.ragebot.weapon[hooks::rage_weapon].double_tap_hitchance);

					if (g_cfg.ragebot.weapon[hooks::rage_weapon].double_tap_hitchance)
						ui::SliderInt(crypt_str("Double tap hitchance amount"), &g_cfg.ragebot.weapon[hooks::rage_weapon].double_tap_hitchance_amount, 1, 100);
				}

				ui::SliderInt(crypt_str("Minimum visible damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_visible_damage, 1, 120);

				if (g_cfg.ragebot.autowall)
					ui::SliderInt(crypt_str("Minimum wall damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_damage, 1, 120);

				static bool q;
				ui::Checkbox_keybind("Damage override", &q);
				ui::Keybind("sasgd", &g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key, &g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.mode);
				

				if (g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key > KEY_NONE && g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key < KEY_MAX)
					ui::SliderInt(crypt_str("Minimum override damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_override_damage, 1, 120);

			}
			ui::EndChild();
			
		}
	}
}

void c_menu::draw_legit(int child)
{
	std::vector<const char*> legit_weapons = { crypt_str("Deagle"), crypt_str("Pistols"), crypt_str("Rifles"), crypt_str("SMGs"), crypt_str("Snipers"), crypt_str("Heavy") };
	std::vector<const char*> hitbox_legit = { crypt_str("Nearest"), crypt_str("Head"), crypt_str("Body") };
	ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
	
	{
		
		ui::BeginChild(crypt_str("Legit"), ImVec2(250, 260));
		{
			
			ui::Checkbox(crypt_str("Enable"), &g_cfg.legitbot.enabled);
			static bool asdgq;
			static bool asdgq1;
			
	
			if (g_cfg.legitbot.enabled)
				g_cfg.ragebot.enable = false;
	
			ui::Checkbox(crypt_str("Friendly fire"), &g_cfg.legitbot.friendly_fire);
			ui::Checkbox(crypt_str("Automatic pistols"), &g_cfg.legitbot.autopistol);
	
			ui::Checkbox(crypt_str("Automatic scope"), &g_cfg.legitbot.autoscope);
	
			if (g_cfg.legitbot.autoscope)
				ui::Checkbox(crypt_str("Unscope after shot"), &g_cfg.legitbot.unscope);
	
			ui::Checkbox(crypt_str("Snipers in zoom only"), &g_cfg.legitbot.sniper_in_zoom_only);
	
			ui::Checkbox(crypt_str("Enable in air"), &g_cfg.legitbot.do_if_local_in_air);
			ui::Checkbox(crypt_str("Enable if flashed"), &g_cfg.legitbot.do_if_local_flashed);
			ui::Checkbox(crypt_str("Enable in smoke"), &g_cfg.legitbot.do_if_enemy_in_smoke);
			ui::Checkbox_keybind(crypt_str("Key"), &asdgq);
			ui::Keybind("#sd", &g_cfg.legitbot.key.key, &g_cfg.legitbot.key.mode);
			ui::Checkbox_keybind(crypt_str("Automatic fire key"), &asdgq1);
			ui::Keybind("#q1asgf", &g_cfg.legitbot.autofire_key.key, &g_cfg.legitbot.autofire_key.mode);
			ui::SliderInt(crypt_str("Automatic fire delay"), &g_cfg.legitbot.autofire_delay, 0, 12, (!g_cfg.legitbot.autofire_delay ? crypt_str("None") : (g_cfg.legitbot.autofire_delay == 1 ? crypt_str("%d tick") : crypt_str("%d ticks"))));
	
		}
		ui::EndChild();
	
	
		
	}
	ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));
	{
		
	
		
		ui::BeginChild(crypt_str("Weapon settings"), ImVec2(250, 260));
		{
			
			draw_combo(crypt_str("Current weapon"), hooks::legit_weapon, legit_weapons);
			
			draw_combo(crypt_str("Hitbox"), g_cfg.legitbot.weapon[hooks::legit_weapon].priority, hitbox_legit);
	
			ui::Checkbox(crypt_str("Automatic stop"), &g_cfg.legitbot.weapon[hooks::legit_weapon].auto_stop);
	
			draw_combo(crypt_str("Field of view type"), g_cfg.legitbot.weapon[hooks::legit_weapon].fov_type, LegitFov);
			ui::SliderFloat(crypt_str("Field of view amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].fov, 0.f, 30.f, crypt_str("%.2f"));
	
			
	
			ui::SliderFloat(crypt_str("Silent field of view"), &g_cfg.legitbot.weapon[hooks::legit_weapon].silent_fov, 0.f, 30.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].silent_fov ? crypt_str("None") : crypt_str("%.2f"))); //-V550
	
			
	
			draw_combo(crypt_str("Smooth type"), g_cfg.legitbot.weapon[hooks::legit_weapon].smooth_type, LegitSmooth);
			ui::SliderFloat(crypt_str("Smooth amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].smooth, 1.f, 12.f, crypt_str("%.1f"));
	
			
	
			draw_combo(crypt_str("RCS type"), g_cfg.legitbot.weapon[hooks::legit_weapon].rcs_type, RCSType);
			ui::SliderFloat(crypt_str("RCS amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].rcs, 0.f, 100.f, crypt_str("%.0f%%"), 1.f);
	
			if (g_cfg.legitbot.weapon[hooks::legit_weapon].rcs > 0)
			{
				ui::SliderFloat(crypt_str("RCS custom field of view"), &g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_fov, 0.f, 30.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_fov ? crypt_str("None") : crypt_str("%.2f"))); //-V550
				ui::SliderFloat(crypt_str("RCS Custom smooth"), &g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_smooth, 0.f, 12.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_smooth ? crypt_str("None") : crypt_str("%.1f"))); //-V550
			}
	
			
	
			ui::SliderInt(crypt_str("Automatic wall damage"), &g_cfg.legitbot.weapon[hooks::legit_weapon].awall_dmg, 0, 100, (!g_cfg.legitbot.weapon[hooks::legit_weapon].awall_dmg ? crypt_str("None") : crypt_str("%d")));
			ui::SliderInt(crypt_str("Automatic fire hitchance"), &g_cfg.legitbot.weapon[hooks::legit_weapon].autofire_hitchance, 0, 100, (!g_cfg.legitbot.weapon[hooks::legit_weapon].autofire_hitchance ? crypt_str("None") : crypt_str("%d")));
			ui::SliderFloat(crypt_str("Target switch delay"), &g_cfg.legitbot.weapon[hooks::legit_weapon].target_switch_delay, 0.f, 1.f);
		}
		ui::EndChild();
	
	
		
	}
}



void c_menu::draw_visuals(int child)
{

	static int sub_tab_visual = 0;
	ui::TabButton("General", &sub_tab_visual, 0, 3);
	ui::TabButton("Players", &sub_tab_visual, 1, 3);
	ui::TabButton("Other", &sub_tab_visual, 2, 3);
	
	
	
	if (!sub_tab_visual)
		{
			ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
			ui::BeginChild(crypt_str("General"), ImVec2(250, 260));
			{
				ui::Checkbox(crypt_str("Enable"), &g_cfg.player.enable);

				draw_multicombo(crypt_str("Indicators"), g_cfg.esp.indicators, indicators, ARRAYSIZE(indicators), preview);


				draw_multicombo(crypt_str("Removals"), g_cfg.esp.removals, removals, ARRAYSIZE(removals), preview);

				if (g_cfg.esp.removals[REMOVALS_ZOOM])
					ui::Checkbox(crypt_str("Fix zoom sensivity"), &g_cfg.esp.fix_zoom_sensivity);

				ui::Checkbox(crypt_str("Grenade prediction"), &g_cfg.esp.grenade_prediction, 65);

				ui::ColorEdit4Shonax(crypt_str("##grenpredcolor"), &g_cfg.esp.grenade_prediction_color, ImGuiWindowFlags_NoTitleBar, 44);

				if (g_cfg.esp.grenade_prediction)
				{
					ui::Checkbox(crypt_str("On click"), &g_cfg.esp.on_click, 65);
					ui::ColorEdit4Shonax(crypt_str("##tracergrenpredcolor"), &g_cfg.esp.grenade_prediction_tracer_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				ui::Checkbox(crypt_str("Grenade projectiles"), &g_cfg.esp.projectiles);

				if (g_cfg.esp.projectiles)
					draw_multicombo(crypt_str("Grenade ESP"), g_cfg.esp.grenade_esp, proj_combo, ARRAYSIZE(proj_combo), preview);

				if (g_cfg.esp.grenade_esp[GRENADE_ICON] || g_cfg.esp.grenade_esp[GRENADE_TEXT])
				{
					ui::Text(crypt_str("Color "));

					ui::ColorEdit4Shonax(crypt_str("##projectcolor"), &g_cfg.esp.projectiles_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				if (g_cfg.esp.grenade_esp[GRENADE_BOX])
				{
					ui::Text(crypt_str("Box color "));

					ui::ColorEdit4Shonax(crypt_str("##grenade_box_color"), &g_cfg.esp.grenade_box_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				if (g_cfg.esp.grenade_esp[GRENADE_GLOW])
				{
					ui::Text(crypt_str("Glow color "));

					ui::ColorEdit4Shonax(crypt_str("##grenade_glow_color"), &g_cfg.esp.grenade_glow_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				ui::Checkbox(crypt_str("Fire timer"), &g_cfg.esp.molotov_timer, 65);

				ui::ColorEdit4Shonax(crypt_str("##molotovcolor"), &g_cfg.esp.molotov_timer_color, ImGuiWindowFlags_NoTitleBar, 44);

				ui::Checkbox(crypt_str("Smoke timer"), &g_cfg.esp.smoke_timer, 65);

				ui::ColorEdit4Shonax(crypt_str("##smokecolor"), &g_cfg.esp.smoke_timer_color, ImGuiWindowFlags_NoTitleBar, 44);

				ui::Checkbox(crypt_str("Bomb indicator"), &g_cfg.esp.bomb_timer);
				draw_multicombo(crypt_str("Weapon ESP"), g_cfg.esp.weapon, weaponesp, ARRAYSIZE(weaponesp), preview);

				if (g_cfg.esp.weapon[WEAPON_ICON] || g_cfg.esp.weapon[WEAPON_TEXT] || g_cfg.esp.weapon[WEAPON_DISTANCE])
				{
					ui::Text(crypt_str("Color "));

					ui::ColorEdit4Shonax(crypt_str("##weaponcolor"), &g_cfg.esp.weapon_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				if (g_cfg.esp.weapon[WEAPON_BOX])
				{
					ui::Text(crypt_str("Box color "));

					ui::ColorEdit4Shonax(crypt_str("##weaponboxcolor"), &g_cfg.esp.box_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				if (g_cfg.esp.weapon[WEAPON_GLOW])
				{
					ui::Text(crypt_str("Glow color "));

					ui::ColorEdit4Shonax(crypt_str("##weaponglowcolor"), &g_cfg.esp.weapon_glow_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				if (g_cfg.esp.weapon[WEAPON_AMMO])
				{
					ui::Text(crypt_str("Ammo bar color "));

					ui::ColorEdit4Shonax(crypt_str("##weaponammocolor"), &g_cfg.esp.weapon_ammo_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				ui::Checkbox(crypt_str("Client bullet impacts"), &g_cfg.esp.client_bullet_impacts, 65);

				ui::ColorEdit4Shonax(crypt_str("##clientbulletimpacts"), &g_cfg.esp.client_bullet_impacts_color, ImGuiWindowFlags_NoTitleBar, 44);

				ui::Checkbox(crypt_str("Server bullet impacts"), &g_cfg.esp.server_bullet_impacts, 65);

				ui::ColorEdit4Shonax(crypt_str("##serverbulletimpacts"), &g_cfg.esp.server_bullet_impacts_color, ImGuiWindowFlags_NoTitleBar, 44);

				ui::Checkbox(crypt_str("Local bullet tracers"), &g_cfg.esp.bullet_tracer, 65);

				ui::ColorEdit4Shonax(crypt_str("##bulltracecolor"), &g_cfg.esp.bullet_tracer_color, ImGuiWindowFlags_NoTitleBar, 44);

				ui::Checkbox(crypt_str("Enemy bullet tracers"), &g_cfg.esp.enemy_bullet_tracer, 65);


				ui::ColorEdit4Shonax(crypt_str("##enemybulltracecolor"), &g_cfg.esp.enemy_bullet_tracer_color, ImGuiWindowFlags_NoTitleBar, 44);
				draw_multicombo(crypt_str("Hit marker"), g_cfg.esp.hitmarker, hitmarkers, ARRAYSIZE(hitmarkers), preview);
				ui::Checkbox(crypt_str("Damage marker"), &g_cfg.esp.damage_marker);
				ui::Checkbox(crypt_str("Kill effect"), &g_cfg.esp.kill_effect);

				if (g_cfg.esp.kill_effect)
					ui::SliderFloat(crypt_str("Duration"), &g_cfg.esp.kill_effect_duration, 0.01f, 3.0f);
				static bool a1qsagd;
				ui::Checkbox_keybind("Thirdperson", &a1qsagd);
				ui::Keybind("#q1qq1asgf", &g_cfg.misc.thirdperson_toggle.key, &g_cfg.misc.thirdperson_toggle.mode);

				ui::Checkbox(crypt_str("Thirdperson when spectating"), &g_cfg.misc.thirdperson_when_spectating);

				if (g_cfg.misc.thirdperson_toggle.key > KEY_NONE&& g_cfg.misc.thirdperson_toggle.key < KEY_MAX)
					ui::SliderInt(crypt_str("Thirdperson distance"), &g_cfg.misc.thirdperson_distance, 100, 300);

				ui::SliderInt(crypt_str("Field of view"), &g_cfg.esp.fov, 0, 89);
				ui::Checkbox(crypt_str("Taser range"), &g_cfg.esp.taser_range);
				ui::Checkbox(crypt_str("Show spread"), &g_cfg.esp.show_spread, 65);

				ui::ColorEdit4Shonax(crypt_str("##spredcolor"), &g_cfg.esp.show_spread_color, ImGuiWindowFlags_NoTitleBar, 44);
				ui::Checkbox(crypt_str("Penetration crosshair"), &g_cfg.esp.penetration_reticle);
			}

			ui::EndChild();


			ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));


			ui::BeginChild(crypt_str("View"), ImVec2(250, 150));
			{
				ui::Checkbox(crypt_str("Rare animations"), &g_cfg.skins.rare_animations);
				ui::SliderInt(crypt_str("Viewmodel field of view"), &g_cfg.esp.viewmodel_fov, 0, 89);
				ui::SliderInt(crypt_str("Viewmodel X"), &g_cfg.esp.viewmodel_x, -50, 50);
				ui::SliderInt(crypt_str("Viewmodel Y"), &g_cfg.esp.viewmodel_y, -50, 50);
				ui::SliderInt(crypt_str("Viewmodel Z"), &g_cfg.esp.viewmodel_z, -50, 50);
				ui::SliderInt(crypt_str("Viewmodel roll"), &g_cfg.esp.viewmodel_roll, -180, 180);
			}
			ui::EndChild();
	
		}
		

	if (sub_tab_visual == 2)
		{
			ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
			ui::BeginChild(crypt_str("World"), ImVec2(250, 280));
			{
				ui::Checkbox(crypt_str("Rain"), &g_cfg.esp.rain);
				ui::Checkbox(crypt_str("Full bright"), &g_cfg.esp.bright);

				draw_combo(crypt_str("Skybox"), g_cfg.esp.skybox, skybox);

				ui::Text(crypt_str("Color "));

				ui::ColorEdit4Shonax(crypt_str("##skyboxcolor"), &g_cfg.esp.skybox_color, ImGuiWindowFlags_NoTitleBar, 44);

				if (g_cfg.esp.skybox == 21)
				{
					static char sky_custom[64] = "\0";

					if (!g_cfg.esp.custom_skybox.empty())
						strcpy_s(sky_custom, sizeof(sky_custom), g_cfg.esp.custom_skybox.c_str());

					ui::Text(crypt_str("Name"));
					ui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

					if (ui::InputText(crypt_str("##customsky"), sky_custom, sizeof(sky_custom)))
						g_cfg.esp.custom_skybox = sky_custom;

					ui::PopStyleVar();
				}

				ui::Checkbox(crypt_str("Color modulation"), &g_cfg.esp.nightmode);

				if (g_cfg.esp.nightmode)
				{
					ui::Text(crypt_str("World color "));

					ui::ColorEdit4Shonax(crypt_str("##worldcolor"), &g_cfg.esp.world_color, ImGuiWindowFlags_NoTitleBar, 44);

					ui::Text(crypt_str("Props color "));

					ui::ColorEdit4Shonax(crypt_str("##propscolor"), &g_cfg.esp.props_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				ui::Checkbox(crypt_str("World modulation"), &g_cfg.esp.world_modulation);

				if (g_cfg.esp.world_modulation)
				{
					ui::SliderFloat(crypt_str("Bloom"), &g_cfg.esp.bloom, 0.0f, 750.0f);
					ui::SliderFloat(crypt_str("Exposure"), &g_cfg.esp.exposure, 0.0f, 2000.0f);
					ui::SliderFloat(crypt_str("Ambient"), &g_cfg.esp.ambient, 0.0f, 1500.0f);
				}

				ui::Checkbox(crypt_str("Fog modulation"), &g_cfg.esp.fog);

				if (g_cfg.esp.fog)
				{
					ui::SliderInt(crypt_str("Distance"), &g_cfg.esp.fog_distance, 0, 2500);
					ui::SliderInt(crypt_str("Density"), &g_cfg.esp.fog_density, 0, 100);

					ui::Text(crypt_str("Color "));

					ui::ColorEdit4Shonax(crypt_str("##fogcolor"), &g_cfg.esp.fog_color, ImGuiWindowFlags_NoTitleBar, 44);
				}
			}
			ui::EndChild();


			ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));


			ui::BeginChild(crypt_str("Chams"), ImVec2(250, 280));
			{
				ui::Checkbox(crypt_str("Arms chams"), &g_cfg.esp.arms_chams, 65);

				ui::ColorEdit4Shonax(crypt_str("##armscolor"), &g_cfg.esp.arms_chams_color, ImGuiWindowFlags_NoTitleBar, 44);


				draw_combo(crypt_str("Arms chams material"), g_cfg.esp.arms_chams_type, chamstype);

				if (g_cfg.esp.arms_chams_type != 6)
				{
					ui::Checkbox(crypt_str("Arms double material "), &g_cfg.esp.arms_double_material, 65);

					ui::ColorEdit4Shonax(crypt_str("##armsdoublematerial"), &g_cfg.esp.arms_double_material_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				ui::Checkbox(crypt_str("Arms animated material "), &g_cfg.esp.arms_animated_material, 65);

				ui::ColorEdit4Shonax(crypt_str("##armsanimatedmaterial"), &g_cfg.esp.arms_animated_material_color, ImGuiWindowFlags_NoTitleBar, 44);



				ui::Checkbox(crypt_str("Weapon chams"), &g_cfg.esp.weapon_chams, 65);

				ui::ColorEdit4Shonax(crypt_str("##weaponchamscolors"), &g_cfg.esp.weapon_chams_color, ImGuiWindowFlags_NoTitleBar, 44);

				draw_combo(crypt_str("Weapon chams material"), g_cfg.esp.weapon_chams_type, chamstype);

				if (g_cfg.esp.weapon_chams_type != 6)
				{
					ui::Checkbox(crypt_str("Double material "), &g_cfg.esp.weapon_double_material, 65);

					ui::ColorEdit4Shonax(crypt_str("##weapondoublematerial"), &g_cfg.esp.weapon_double_material_color, ImGuiWindowFlags_NoTitleBar, 44);
				}

				ui::Checkbox(crypt_str("Animated material "), &g_cfg.esp.weapon_animated_material, 65);

				ui::ColorEdit4Shonax(crypt_str("##weaponanimatedmaterial"), &g_cfg.esp.weapon_animated_material_color, ImGuiWindowFlags_NoTitleBar, 44);

			}

			ui::EndChild();
			
				
		
			
			
		}
	
	
	if (sub_tab_visual == 1)
		draw_players(0);
		
	
}


void c_menu::draw_players(int child)
{
	
	
	
	ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 380));

	ui::BeginChild(crypt_str("Players section"), ImVec2(250, 60));
	{
		draw_combo(crypt_str("Chose"), players_section, {"Enemy", "Team", "Local"});
	}
	ui::EndChild();
	
	
	
	auto player = players_section;
	


	
	
	
		ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
		ui::BeginChild(crypt_str("ESP"), ImVec2(250, 260));
		{
	
			ui::Checkbox(crypt_str("Enable"), &g_cfg.player.enable);
	
			if (player == ENEMY)
			{
				ui::Checkbox(crypt_str("OOF arrows"), &g_cfg.player.arrows, 65);
				
				ui::ColorEdit4Shonax(crypt_str("##arrowscolor"), &g_cfg.player.arrows_color, ImGuiWindowFlags_NoTitleBar, 44);
	
				if (g_cfg.player.arrows)
				{
					ui::SliderInt(crypt_str("Arrows distance"), &g_cfg.player.distance, 1, 100);
					ui::SliderInt(crypt_str("Arrows size"), &g_cfg.player.size, 1, 100);
				}
			}
	
			ui::Checkbox(crypt_str("Bounding box"), &g_cfg.player.type[player].box, 65);
			ui::ColorEdit4Shonax(crypt_str("##boxcolor"), &g_cfg.player.type[player].box_color, ImGuiWindowFlags_NoTitleBar, 44);
			ui::Checkbox(crypt_str("Name"), &g_cfg.player.type[player].name, 65);
			ui::ColorEdit4Shonax(crypt_str("##namecolor"), &g_cfg.player.type[player].name_color, ImGuiWindowFlags_NoTitleBar, 44);
			ui::Checkbox(crypt_str("Health bar"), &g_cfg.player.type[player].health);
			ui::Checkbox(crypt_str("Health color"), &g_cfg.player.type[player].custom_health_color, 65);
			ui::ColorEdit4Shonax(crypt_str("##healthcolor"), &g_cfg.player.type[player].health_color, ImGuiWindowFlags_NoTitleBar, 44);
	
			for (auto i = 0, j = 0; i < ARRAYSIZE(flags); i++)
			{
				if (g_cfg.player.type[player].flags[i])
				{
					if (j)
						preview += crypt_str(", ") + (std::string)flags[i];
					else
						preview = flags[i];
	
					j++;
				}
			}
	
			draw_multicombo(crypt_str("Flags"), g_cfg.player.type[player].flags, flags, ARRAYSIZE(flags), preview);
			draw_multicombo(crypt_str("Weapon"), g_cfg.player.type[player].weapon, weaponplayer, ARRAYSIZE(weaponplayer), preview);
	
	
			if (g_cfg.player.type[player].weapon[WEAPON_ICON] || g_cfg.player.type[player].weapon[WEAPON_TEXT])
			{
				ui::Text(crypt_str("Color "));
				
				ui::ColorEdit4Shonax(crypt_str("##weapcolor"), &g_cfg.player.type[player].weapon_color, ImGuiWindowFlags_NoTitleBar, 44);
			}
	
			ui::Checkbox(crypt_str("Skeleton"), &g_cfg.player.type[player].skeleton, 65);
			
			ui::ColorEdit4Shonax(crypt_str("##skeletoncolor"), &g_cfg.player.type[player].skeleton_color, ImGuiWindowFlags_NoTitleBar, 44);
	
			ui::Checkbox(crypt_str("Ammo bar"), &g_cfg.player.type[player].ammo, 65);
			
			ui::ColorEdit4Shonax(crypt_str("##ammocolor"), &g_cfg.player.type[player].ammobar_color, ImGuiWindowFlags_NoTitleBar, 44);
	
			ui::Checkbox(crypt_str("Footsteps"), &g_cfg.player.type[player].footsteps, 65);
			
			ui::ColorEdit4Shonax(crypt_str("##footstepscolor"), &g_cfg.player.type[player].footsteps_color, ImGuiWindowFlags_NoTitleBar, 44);
	
			if (g_cfg.player.type[player].footsteps)
			{
				ui::SliderInt(crypt_str("Thickness"), &g_cfg.player.type[player].thickness, 1, 10);
				ui::SliderInt(crypt_str("Radius"), &g_cfg.player.type[player].radius, 50, 500);
			}
	
			if (player == ENEMY || player == TEAM)
			{
				ui::Checkbox(crypt_str("Snap lines"), &g_cfg.player.type[player].snap_lines, 65);
				
				ui::ColorEdit4Shonax(crypt_str("##snapcolor"), &g_cfg.player.type[player].snap_lines_color, ImGuiWindowFlags_NoTitleBar, 44);
	
				if (player == ENEMY)
				{
					if (g_cfg.ragebot.enable)
					{
						ui::Checkbox(crypt_str("Aimbot points"), &g_cfg.player.show_multi_points, 65);
						
						ui::ColorEdit4Shonax(crypt_str("##showmultipointscolor"), &g_cfg.player.show_multi_points_color, ImGuiWindowFlags_NoTitleBar, 44);
					}
	
					ui::Checkbox(crypt_str("Aimbot hitboxes"), &g_cfg.player.lag_hitbox, 65);
					
					ui::ColorEdit4Shonax(crypt_str("##lagcompcolor"), &g_cfg.player.lag_hitbox_color, ImGuiWindowFlags_NoTitleBar, 44);
				}
			}
			else
			{
				draw_combo(crypt_str("Player model T"), g_cfg.player.player_model_t, player_model_t);
				padding(0, 3);
				draw_combo(crypt_str("Player model CT"), g_cfg.player.player_model_ct, player_model_ct);
			}
	
		}
		ui::EndChild();
		
	
	
		ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));
		ui::BeginChild(crypt_str("Model"), ImVec2(250, 260));
		{
			
			if (player == LOCAL)
				draw_combo(crypt_str("Type"), g_cfg.player.local_chams_type, local_chams_type);
	
			if (player != LOCAL || !g_cfg.player.local_chams_type)
				draw_multicombo(crypt_str("Chams"), g_cfg.player.type[player].chams, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? chamsvisact : chamsvis, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? ARRAYSIZE(chamsvisact) : ARRAYSIZE(chamsvis), preview);
	
			if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] || player == LOCAL && g_cfg.player.local_chams_type) //-V648
			{
				if (player == LOCAL && g_cfg.player.local_chams_type)
				{
					ui::Checkbox(crypt_str("Enable desync chams"), &g_cfg.player.fake_chams_enable);
					ui::Checkbox(crypt_str("Visualize lag"), &g_cfg.player.visualize_lag);
					ui::Checkbox(crypt_str("Layered"), &g_cfg.player.layered);
	
					draw_combo(crypt_str("Player chams material"), g_cfg.player.fake_chams_type, chamstype);
	
					ui::Text(crypt_str("Color "));
				
					ui::ColorEdit4Shonax(crypt_str("##fakechamscolor"), &g_cfg.player.fake_chams_color, ImGuiWindowFlags_NoTitleBar, 44);
	
					if (g_cfg.player.fake_chams_type != 6)
					{
						ui::Checkbox(crypt_str("Double material "), &g_cfg.player.fake_double_material);
						
						ui::ColorEdit4Shonax(crypt_str("##doublematerialcolor"), &g_cfg.player.fake_double_material_color, ImGuiWindowFlags_NoTitleBar, 44);
					}
	
					ui::Checkbox(crypt_str("Animated material"), &g_cfg.player.fake_animated_material, 65);
				
					ui::ColorEdit4Shonax(crypt_str("##animcolormat"), &g_cfg.player.fake_animated_material_color, ImGuiWindowFlags_NoTitleBar, 44);
				}
				else
				{
					draw_combo(crypt_str("Player chams material"), g_cfg.player.type[player].chams_type, chamstype);
	
					if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE])
					{
						ui::Text(crypt_str("Visible "));
						
						ui::ColorEdit4Shonax(crypt_str("##chamsvisible"), &g_cfg.player.type[player].chams_color, ImGuiWindowFlags_NoTitleBar, 44);
					}
	
					if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] && g_cfg.player.type[player].chams[PLAYER_CHAMS_INVISIBLE])
					{
						ui::Text(crypt_str("Invisible "));
						
						ui::ColorEdit4Shonax(crypt_str("##chamsinvisible"), &g_cfg.player.type[player].xqz_color, ImGuiWindowFlags_NoTitleBar, 44);
					}
	
					if (g_cfg.player.type[player].chams_type != 6)
					{
						ui::Checkbox(crypt_str("Double material "), &g_cfg.player.type[player].double_material, 65);
						
						ui::ColorEdit4Shonax(crypt_str("##doublematerialcolor"), &g_cfg.player.type[player].double_material_color, ImGuiWindowFlags_NoTitleBar, 44);
					}
	
					ui::Checkbox(crypt_str("Animated material"), &g_cfg.player.type[player].animated_material, 65);
					
					ui::ColorEdit4Shonax(crypt_str("##animcolormat"), &g_cfg.player.type[player].animated_material_color, ImGuiWindowFlags_NoTitleBar, 44);
	
					if (player == ENEMY)
					{
						ui::Checkbox(crypt_str("Backtrack chams"), &g_cfg.player.backtrack_chams);
	
						if (g_cfg.player.backtrack_chams)
						{
							draw_combo(crypt_str("Backtrack chams material"), g_cfg.player.backtrack_chams_material, chamstype);
	
							ui::Text(crypt_str("Color "));
							
							ui::ColorEdit4Shonax(crypt_str("##backtrackcolor"), &g_cfg.player.backtrack_chams_color, ImGuiWindowFlags_NoTitleBar, 44);
						}
					}
				}
			}
	
			if (player == ENEMY || player == TEAM)
			{
				ui::Checkbox(crypt_str("Ragdoll chams"), &g_cfg.player.type[player].ragdoll_chams);
	
				if (g_cfg.player.type[player].ragdoll_chams)
				{
					draw_combo(crypt_str("Ragdoll chams material"), g_cfg.player.type[player].ragdoll_chams_material, chamstype);
	
					ui::Text(crypt_str("Color "));
				
					ui::ColorEdit4Shonax(crypt_str("##ragdollcolor"), &g_cfg.player.type[player].ragdoll_chams_color, ImGuiWindowFlags_NoTitleBar, 44);
				}
			}
			else if (!g_cfg.player.local_chams_type)
			{
				ui::Checkbox(crypt_str("Transparency in scope"), &g_cfg.player.transparency_in_scope);
	
				if (g_cfg.player.transparency_in_scope)
					ui::SliderFloat(crypt_str("Alpha"), &g_cfg.player.transparency_in_scope_amount, 0.0f, 1.0f);
			}
	
			
	
			ui::Checkbox(crypt_str("Glow"), &g_cfg.player.type[player].glow);
	
			if (g_cfg.player.type[player].glow)
			{
				draw_combo(crypt_str("Glow type"), g_cfg.player.type[player].glow_type, glowtype);
				ui::Text(crypt_str("Color "));
				
				ui::ColorEdit4Shonax(crypt_str("##glowcolor"), &g_cfg.player.type[player].glow_color, ImGuiWindowFlags_NoTitleBar, 44);
			}
	
		}
		ui::EndChild();
		
	
}




void c_menu::draw_misc(int child)
{
	static int sub_tab_misc = 0;
	ui::TabButton("General", &sub_tab_misc, 0, 4);
	ui::TabButton("Other", &sub_tab_misc, 1, 4);
	ui::TabButton("Settings", &sub_tab_misc, 2, 4);
	ui::TabButton("Player list", &sub_tab_misc, 3, 4);
	
	if (!sub_tab_misc)
	{
		ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
		ui::BeginChild(crypt_str("General"), ImVec2(250, 260));
		{
			ui::Checkbox(crypt_str("Anti-untrusted"), &g_cfg.misc.anti_untrusted);
			ui::Checkbox(crypt_str("Rank reveal"), &g_cfg.misc.rank_reveal);
			ui::Checkbox(crypt_str("Unlock inventory access"), &g_cfg.misc.inventory_access);
			ui::Checkbox(crypt_str("Gravity ragdolls"), &g_cfg.misc.ragdolls);
			ui::Checkbox(crypt_str("Preserve killfeed"), &g_cfg.esp.preserve_killfeed);
			ui::Checkbox(crypt_str("Aspect ratio"), &g_cfg.misc.aspect_ratio);

			if (g_cfg.misc.aspect_ratio)
			{

				ui::SliderFloat(crypt_str("Amount"), &g_cfg.misc.aspect_ratio_amount, 1.0f, 2.0f);
			}

			//
			ui::Checkbox(crypt_str("Fake lag"), &g_cfg.antiaim.fakelag);
			if (g_cfg.antiaim.fakelag)
			{
				draw_combo(crypt_str("Fake lag type"), g_cfg.antiaim.fakelag_type, fakelags);
				ui::SliderInt(crypt_str("Limit"), &g_cfg.antiaim.fakelag_amount, 1, 16);

				draw_multicombo(crypt_str("Fake lag triggers"), g_cfg.antiaim.fakelag_enablers, lagstrigger, ARRAYSIZE(lagstrigger), preview);

				auto enabled_fakelag_triggers = false;

				for (auto i = 0; i < ARRAYSIZE(lagstrigger); i++)
					if (g_cfg.antiaim.fakelag_enablers[i])
						enabled_fakelag_triggers = true;

				if (enabled_fakelag_triggers)
					ui::SliderInt(crypt_str("Triggers limit"), &g_cfg.antiaim.triggers_fakelag_amount, 1, 16);
			}
		}
		ui::EndChild();




		ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));
		ui::BeginChild(crypt_str("Information"), ImVec2(250, 260));
		{

			ui::Checkbox(crypt_str("Watermark"), &g_cfg.menu.watermark);
			ui::Checkbox(crypt_str("Spectators list"), &g_cfg.misc.spectators_list);
			draw_combo(crypt_str("Hitsound"), g_cfg.esp.hitsound, sounds);
			ui::Checkbox(crypt_str("Killsound"), &g_cfg.esp.killsound);
			draw_multicombo(crypt_str("Logs"), g_cfg.misc.events_to_log, events, ARRAYSIZE(events), preview);
			padding(0, 3);
			draw_multicombo(crypt_str("Logs output"), g_cfg.misc.log_output, events_output, ARRAYSIZE(events_output), preview);

			if (g_cfg.misc.events_to_log[EVENTLOG_HIT] || g_cfg.misc.events_to_log[EVENTLOG_ITEM_PURCHASES] || g_cfg.misc.events_to_log[EVENTLOG_BOMB])
			{
				ui::Text(crypt_str("Color "));

				ui::ColorEdit4Shonax(crypt_str("##logcolor"), &g_cfg.misc.log_color, ImGuiWindowFlags_NoTitleBar, 4);
			}

			ui::Checkbox(crypt_str("Show CS:GO logs"), &g_cfg.misc.show_default_log);

		}
		ui::EndChild();
		
	
	
			
		
	
	}
	if (sub_tab_misc == 1)
	{
		
		ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
		ui::BeginChild(crypt_str("Movement"), ImVec2(250, 260));
		{

			ui::Checkbox(crypt_str("Automatic jump"), &g_cfg.misc.bunnyhop);
			draw_combo(crypt_str("Automatic strafes"), g_cfg.misc.airstrafe, strafes);
			ui::Checkbox(crypt_str("Crouch in air"), &g_cfg.misc.crouch_in_air);
			ui::Checkbox(crypt_str("Fast stop"), &g_cfg.misc.fast_stop);
			ui::Checkbox(crypt_str("Slide walk"), &g_cfg.misc.slidewalk);
			//
			ui::Checkbox(crypt_str("No duck cooldown"), &g_cfg.misc.noduck);
			static bool asdg;
			if (g_cfg.misc.noduck)
			{
				
				ui::Checkbox_keybind("Fake duck", &asdg);
				ui::Keybind("a1eryasdgaeg", &g_cfg.misc.fakeduck_key.key, &g_cfg.misc.fakeduck_key.mode);
			}
		
			ui::Checkbox_keybind("Slow walk", &asdg);
			ui::Keybind("a1eryasdgaeg1", &g_cfg.misc.slowwalk_key.key, &g_cfg.misc.slowwalk_key.mode);
			ui::Checkbox_keybind("Auto peek", &asdg);
			ui::Keybind("a1eryasdgaeg2", &g_cfg.misc.automatic_peek.key, &g_cfg.misc.automatic_peek.mode);
			ui::Checkbox_keybind("Edge jump", &asdg);
			ui::Keybind("Edgesadgjump", &g_cfg.misc.edge_jump.key, &g_cfg.misc.edge_jump.mode);
	
			

		}
		ui::EndChild();

		ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));

		ui::BeginChild(crypt_str("Extra"), ImVec2(250, 260));
		{

			ui::Checkbox(crypt_str("Anti-screenshot"), &g_cfg.misc.anti_screenshot);
			ui::Checkbox(crypt_str("Clantag"), &g_cfg.misc.clantag_spammer);
			ui::Checkbox(crypt_str("Chat spam"), &g_cfg.misc.chat);
			ui::Checkbox(crypt_str("Enable buybot"), &g_cfg.misc.buybot_enable);

			if (g_cfg.misc.buybot_enable)
			{
				draw_combo(crypt_str("Snipers"), g_cfg.misc.buybot1, mainwep);

				draw_combo(crypt_str("Pistols"), g_cfg.misc.buybot2, secwep);

				draw_multicombo(crypt_str("Other"), g_cfg.misc.buybot3, grenades, ARRAYSIZE(grenades), preview);
			}
		}

		ui::EndChild();

		
		
	}


	if (sub_tab_misc == 2)
		draw_settings(0);
	
	if (sub_tab_misc == 3)
		draw_player_list(0);
}

void c_menu::draw_settings(int child)
{

	
	
	
}

void c_menu::draw_lua(int child)
{
	ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
	{
		
	
		
	}
	ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));
	{
		
		
		
	}
}


void c_menu::draw_radar(int child)
{
	if (!child)
	{
		ui::BeginChild(crypt_str("##RADAR_FIRST"), ImVec2(250, (child_height - 35) * dpi_scale));
		{
			ui::Checkbox(crypt_str("Enable radar"), &g_cfg.misc.ingame_radar);
			ui::Checkbox(crypt_str("Render local"), &g_cfg.radar.render_local);
			ui::Checkbox(crypt_str("Render enemy"), &g_cfg.radar.render_enemy);
			ui::Checkbox(crypt_str("Render team"), &g_cfg.radar.render_team);
			ui::Checkbox(crypt_str("Show planted c4"), &g_cfg.radar.render_planted_c4);
			ui::Checkbox(crypt_str("Show dropped c4"), &g_cfg.radar.render_dropped_c4);
			ui::Checkbox(crypt_str("Show health"), &g_cfg.radar.render_health);
		}
		ui::EndChild();

	}
}

void c_menu::draw_player_list(int child)
{
	
	static std::vector <Player_list_data> players;
	
	if (!g_cfg.player_list.refreshing)
	{
		players.clear();
	
		for (auto player : g_cfg.player_list.players)
			players.emplace_back(player);
	}
	
	static auto current_player = 0;
	
	if (!child)
	{
		ui::SetNextWindowPos(ImVec2(p.x + 100, p.y + 80));
		ui::BeginChild(crypt_str("Player list"), ImVec2(250, 260));
		{
	
			if (!players.empty())
			{
				std::vector <std::string> player_names;
	
				for (auto player : players)
					player_names.emplace_back(player.name);
	
				
				ui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
				ui::ListBoxConfigArray(crypt_str("##PLAYERLIST"), &current_player, player_names, 14);
				ui::PopStyleVar();
			
			}
	
		}
		ui::EndChild();
		
	}
	
	{
		ui::SetNextWindowPos(ImVec2(p.x + 370, p.y + 80));
		ui::BeginChild(crypt_str("Settings"), ImVec2(250, 260));
		{
	
			if (!players.empty())
			{
				if (current_player >= players.size())
					current_player = players.size() - 1; //-V103
	
				ui::Checkbox(crypt_str("White list"), &g_cfg.player_list.white_list[players.at(current_player).i]); //-V106 //-V807
	
				if (!g_cfg.player_list.white_list[players.at(current_player).i]) //-V106
				{
					ui::Checkbox(crypt_str("High priority"), &g_cfg.player_list.high_priority[players.at(current_player).i]); //-V106
					ui::Checkbox(crypt_str("Force safe points"), &g_cfg.player_list.force_safe_points[players.at(current_player).i]); //-V106
					ui::Checkbox(crypt_str("Force body aim"), &g_cfg.player_list.force_body_aim[players.at(current_player).i]); //-V106
					ui::Checkbox(crypt_str("Low delta"), &g_cfg.player_list.low_delta[players.at(current_player).i]); //-V106
				}
			}
	
		}
		ui::EndChild();
		
	}
}




void c_menu::draw_skins()
{
	// hey stewen, what r u doing there? he, hm heee, DRUGS
	static bool drugs = false;

	// some animation logic(switch)
	static bool active_animation = false;
	static bool preview_reverse = false;
	static float switch_alpha = 1.f;
	static int next_id = -1;
	if (active_animation)
	{
		if (preview_reverse)
		{
			if (switch_alpha == 1.f) //-V550
			{
				preview_reverse = false;
				active_animation = false;
			}

			switch_alpha = math::clamp(switch_alpha + (4.f * ui::GetIO().DeltaTime), 0.01f, 1.f);
		}
		else
		{
			if (switch_alpha == 0.01f) //-V550
			{
				preview_reverse = true;
			}

			switch_alpha = math::clamp(switch_alpha - (4.f * ui::GetIO().DeltaTime), 0.01f, 1.f);
		}
	}
	else
		switch_alpha = math::clamp(switch_alpha + (4.f * ui::GetIO().DeltaTime), 0.0f, 1.f);


	
}

void c_menu::draw(bool is_open)
{
	static auto w = 0, h = 0, current_h = 0;
	m_engine()->GetScreenSize(w, current_h);

	if (h != current_h)
	{
		if (h)
			update_scripts = true;

		h = current_h;
		update_dpi = true;
	}

	// animation related code
	static float m_alpha = 0.0002f;
	m_alpha = math::clamp(m_alpha + (3.f * ui::GetIO().DeltaTime * (is_open ? 1.f : -1.f)), 0.0001f, 1.f);

	// set alpha in class to use later in widgets
	public_alpha = m_alpha;

	if (m_alpha <= 0.0001f)
		return;

	// set new alpha
	ui::PushStyleVar(ImGuiStyleVar_Alpha, m_alpha);

	// setup colors and some styles
	if (!menu_setupped)
		menu_setup(ui::GetStyle());

	ui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(ui::GetStyle().Colors[ImGuiCol_ScrollbarGrab].x, ui::GetStyle().Colors[ImGuiCol_ScrollbarGrab].y, ui::GetStyle().Colors[ImGuiCol_ScrollbarGrab].z, m_alpha));

	// default menu size
	const int x = 730, y = 480;

	// last active tab to switch effect & reverse alpha & preview alpha
	// IMPORTANT: DO TAB SWITCHING BY LAST_TAB!!!!!
	static int last_tab = active_tab;
	static bool preview_reverse = false;

	// start menu render
	
	ui::Begin(crypt_str("SHONAX-PROJECT.ru"), nullptr, ImGuiWindowFlags_NoDecoration);
	{
		p = ui::GetCursorScreenPos();
		static int tab = 0;
		ui::TabButton_icon("RAGE", "A", &tab, 0, 6);
		ui::TabButton_icon("LEGIT", "B", &tab, 1, 6);
		ui::TabButton_icon("VISUALS", "E", &tab, 2, 6);
		ui::TabButton_icon("MISC", "D", &tab, 3, 6);
		ui::TabButton_icon("SKINS", "I", &tab, 4, 6);
		ui::TabButton_icon("SCRIPTS", "G", &tab, 5, 6);
		if (tab == 0) draw_ragebot(0);
		if (tab == 1) draw_legit(0);
		if (tab == 2) draw_visuals(0);
		if (tab == 3) draw_misc(0);
		if (tab == 4) draw_skins();
		if (tab == 5) draw_lua(0);
	}
	ui::End();

	ui::PopStyleColor();
	ui::PopStyleVar();
}









std::array < Vector4D, 6 > aWhiteArray =
{
	Vector4D(0.4f, 0.4f, 0.4f, 1.0f),
	Vector4D(0.4f, 0.4f, 0.4f, 1.0f),
	Vector4D(0.4f, 0.4f, 0.4f, 1.0f),
	Vector4D(0.4f, 0.4f, 0.4f, 1.0f),
	Vector4D(0.4f, 0.4f, 0.4f, 1.0f),
	Vector4D(0.4f, 0.4f, 0.4f, 1.0f),
};

std::array < float_t, 3 > aColorModulation =
{
	1.0f,
	1.0f,
	1.0f
};


__forceinline void AngleMatrix(const QAngle& angView, matrix3x4_t& matOutput, const Vector& vecOrigin)
{
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos(&sp, &cp, DEG2RAD(angView.pitch));
	DirectX::XMScalarSinCos(&sy, &cy, DEG2RAD(angView.yaw));
	DirectX::XMScalarSinCos(&sr, &cr, DEG2RAD(angView.roll));

	matOutput.SetForward(Vector(cp * cy, cp * sy, -sp));

	const float crcy = cr * cy;
	const float crsy = cr * sy;
	const float srcy = sr * cy;
	const float srsy = sr * sy;

	matOutput.SetLeft(Vector(sp * srcy - crsy, sp * srsy + crcy, sr * cp));
	matOutput.SetUp(Vector(sp * crcy + srsy, sp * crsy - srcy, cr * cp));
	matOutput.SetOrigin(vecOrigin);
}




static const char* player_model_index_all[] =
{
	"models/player/custom_player/legacy/tm_phoenix_variantf.mdl",
	"models/player/custom_player/legacy/tm_phoenix_varianth.mdl",
	"models/player/custom_player/legacy/tm_leet_variantg.mdl",
	"models/player/custom_player/legacy/tm_balkan_varianti.mdl",
	"models/player/custom_player/legacy/tm_leet_varianth.mdl",
	"models/player/custom_player/legacy/tm_phoenix_variantg.mdl",
	"models/player/custom_player/legacy/tm_balkan_variantf.mdl",
	"models/player/custom_player/legacy/tm_balkan_variantj.mdl",
	"models/player/custom_player/legacy/tm_leet_varianti.mdl",
	"models/player/custom_player/legacy/tm_balkan_variantg.mdl",
	"models/player/custom_player/legacy/tm_balkan_varianth.mdl",
	"models/player/custom_player/legacy/tm_leet_variantf.mdl",
	"models/player/custom_player/legacy/ctm_st6_variante.mdl",
	"models/player/custom_player/legacy/ctm_st6_variantk.mdl",
	"models/player/custom_player/legacy/ctm_fbi_variantf.mdl",
	"models/player/custom_player/legacy/ctm_sas_variantf.mdl",
	"models/player/custom_player/legacy/ctm_fbi_variantg.mdl",
	"models/player/custom_player/legacy/ctm_st6_variantg.mdl",
	"models/player/custom_player/legacy/ctm_st6_variantm.mdl",
	"models/player/custom_player/legacy/ctm_st6_varianti.mdl",
	"models/player/custom_player/legacy/ctm_fbi_variantb.mdl"
};
IMaterial* fCreateMaterial(bool lit, const std::string& material_data)
{
	static auto created = 0;
	std::string type = lit ? crypt_str("VertexLitGeneric") : crypt_str("UnlitGeneric");

	auto matname = crypt_str("legendware_") + std::to_string(created);
	++created;

	auto keyValues = new KeyValues(matname.c_str());
	static auto key_values_address = util::FindSignature(crypt_str("client.dll"), crypt_str("55 8B EC 51 33 C0 C7 45"));

	using KeyValuesFn = void(__thiscall*)(void*, const char*);
	reinterpret_cast <KeyValuesFn> (key_values_address)(keyValues, type.c_str());

	static auto load_from_buffer_address = util::FindSignature(crypt_str("client.dll"), crypt_str("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89"));
	using LoadFromBufferFn = void(__thiscall*)(void*, const char*, const char*, void*, const char*, void*);

	reinterpret_cast <LoadFromBufferFn> (load_from_buffer_address)(keyValues, matname.c_str(), material_data.c_str(), nullptr, nullptr, nullptr);

	auto material = m_materialsystem()->CreateMaterial(matname.c_str(), keyValues);
	material->IncrementReferenceCount();

	return material;
}
void ApplyMaterial(int32_t iMaterial, bool bIgnoreZ, Color aColor, bool bCustom, bool bShotChams)
{
	IMaterial* pRenderMaterial = nullptr;


	static IMaterial* materials[] =
	{
		fCreateMaterial(true, crypt_str(R"#("VertexLitGeneric"
			{
				"$basetexture"				"vgui/white"
				"$ignorez"					"0"
				"$envmap"					" "
				"$nofog"					"1"
				"$model"					"1"
				"$nocull"					"0"
				"$selfillum"				"1"
				"$halflambert"				"1"
				"$znearer"					"0"
				"$flat"						"0"
				"$wireframe"				"0"
			}
		)#")),
		fCreateMaterial(true, crypt_str(R"#("VertexLitGeneric" 
			{
				"$basetexture"				"vgui/white" 
				"$ignorez"					"0" 
				"$envmap"					"env_cubemap" 
				"$normalmapalphaenvmapmask" "1" 
				"$envmapcontrast"			"1" 
				"$nofog"					"1" 
				"$model"					"1" 
				"$nocull" 					"0" 
				"$selfillum" 				"1" 
				"$halflambert"				"1" 
				"$znearer" 					"0" 
				"$flat" 					"1"
		        "$wireframe"				"0"
			}
		)#")),
		fCreateMaterial(false, crypt_str(R"#("UnlitGeneric"
			{
				"$basetexture"				"vgui/white"
				"$ignorez"					"0"
				"$envmap"					" "
				"$nofog"					"1"
				"$model"					"1"
				"$nocull"					"0"
				"$selfillum"				"1"
				"$halflambert"				"1"
				"$znearer"					"0"
				"$flat"						"1"
				"$wireframe"				"0"
			}
		)#")),
		m_materialsystem()->FindMaterial(crypt_str("models/inventory_items/dogtags/dogtags_outline"), nullptr), //-V807
		m_materialsystem()->FindMaterial(crypt_str("models/inventory_items/trophy_majors/crystal_clear"), nullptr),
		m_materialsystem()->FindMaterial(crypt_str("models/inventory_items/cologne_prediction/cologne_prediction_glass"), nullptr),
		m_materialsystem()->FindMaterial(crypt_str("dev/glow_armsrace.vmt"), nullptr),
		m_materialsystem()->FindMaterial(crypt_str("models/inventory_items/wildfire_gold/wildfire_gold_detail"), nullptr),
		fCreateMaterial(true, crypt_str(R"#("VertexLitGeneric" 
			{ 
				"$additive"					"1" 
				"$envmap"					"models/effects/cube_white" 
				"$envmaptint"				"[1 1 1]" 
				"$envmapfresnel"			"1" 
				"$envmapfresnelminmaxexp" 	"[0 1 2]" 
				"$alpha" 					"0.8" 
			}
		)#")),
		fCreateMaterial(true, crypt_str(R"#("VertexLitGeneric"
		    {
		        "$basetexture"				"dev/zone_warning"
		        "$additive"					"1"
		        "$envmap"					"editor/cube_vertigo"
		        "$envmaptint"				"[0 0.5 0.55]"
		        "$envmapfresnel"			"1"
		        "$envmapfresnelminmaxexp"   "[0.00005 0.6 6]"
		        "$alpha"					"1"
   
		        Proxies
		        {
		            TextureScroll
		            {
		                "texturescrollvar"			"$baseTextureTransform"
		                "texturescrollrate"			"0.25"
		                "texturescrollangle"		"270"
		            }
		            Sine
		            {
		                "sineperiod"				"2"
		                "sinemin"					"0.1"
		                "resultVar"					"$envmapfresnelminmaxexp[1]"
		            }
		        }
		    }
		)#"))
	};


	pRenderMaterial = materials[iMaterial];


	bool bHasBeenFound = false;
	if (!pRenderMaterial)
		return;

	IMaterialVar* pMaterialVar = pRenderMaterial->FindVar(("$envmaptint"), &bHasBeenFound);
	if (!pMaterialVar)
		return;

	if (bHasBeenFound && iMaterial > 1)
		pMaterialVar->set_vec_value(aColor.r() / 255.0f, aColor.g() / 255.0f, aColor.b() / 255.0f);

	const float aBlendColor[3]
		=
	{
		(float_t)(aColor.r()) / 255.0f,
		(float_t)(aColor.g()) / 255.0f,
		(float_t)(aColor.b()) / 255.0f
	};

	pRenderMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, bIgnoreZ && !bCustom);
	if (bCustom)
	{
		pRenderMaterial->ColorModulate(aColor.r() / 255.0f, aColor.g() / 255.0f, aColor.b() / 255.0f);
		pRenderMaterial->AlphaModulate(aColor.a() / 255.0f);

		return m_StudioRender->ForcedMaterialOverride(pRenderMaterial);
	}

	pRenderMaterial->ColorModulate(1.0f, 1.0f, 1.0f);
	pRenderMaterial->AlphaModulate(1.0f);

	if (bShotChams)
	{
		m_renderview()->SetColorModulation(aBlendColor);
		m_renderview()->SetBlend(aColor.a() / 255.0f);
		return m_modelrender()->ForcedMaterialOverride(pRenderMaterial);
	}

	m_renderview()->SetColorModulation(aBlendColor);
	m_renderview()->SetBlend(aColor.a() / 255.0f);
	return m_modelrender()->ForcedMaterialOverride(pRenderMaterial);
}


void C_DrawModel::Instance()
{
	if (!hooks::menu_open)
		return;

	if (!m_PreviewTexture)
	{

		m_materialsystem()->BeginRenderTargetAllocation();

		m_PreviewTexture = m_materialsystem()->CreateNamedRenderTargetTextureEx(
			("Preview"),
			350, 575,
			RT_SIZE_NO_CHANGE,
			m_materialsystem()->GetBackBufferFormat(),
			MATERIAL_RT_DEPTH_SHARED,
			TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
			0x00000001
		);

		m_materialsystem()->FinishRenderTargetAllocation();
	}

	if (!m_CubemapTexture)
		m_CubemapTexture = m_materialsystem()->FindTexture(("editor/cubemap.hdr"), (TEXTURE_GROUP_CUBE_MAP));
	static auto m_CreateModel = util::FindSignature("client.dll", "53 8B D9 56 57 8D 4B 04 C7 03 ? ? ? ? E8 ? ? ? ? 6A");
	auto CreateModel = reinterpret_cast<void(__thiscall*)(void*)>(m_CreateModel);
	if (!m_PreviewModel)
	{
		m_PreviewModel = static_cast<C_MergedMDL*>(m_memalloc()->Alloc(0x75C));
		CreateModel(m_PreviewModel);
		m_PreviewModel->SetMDL(("models/player/custom_player/uiplayer/animset_uiplayer_buymenu.mdl"));
		m_PreviewModel->SetMergedMDL(("models/player/custom_player/legacy/tm_jungle_raider_variante.mdl"));
		m_PreviewModel->SetMergedMDL(("models/weapons/w_pist_deagle.mdl"));
		m_PreviewModel->SetSequence(32, false);
		m_PreviewModel->SetupBonesForAttachmentQueries();
	}

	m_PreviewModel->RootMDL.flTime += m_globals()->m_frametime / 2.0f;

	m_ViewSetup.iX = 0;
	m_ViewSetup.iY = 0;
	m_ViewSetup.iWidth = 350;
	m_ViewSetup.iHeight = 575;
	m_ViewSetup.bOrtho = false;
	m_ViewSetup.flFOV = 70.f;
	m_ViewSetup.vecOrigin = Vector(-65.0f, 2.0f, 50);
	m_ViewSetup.angView = QAngle(0, 0, 0);
	m_ViewSetup.flNearZ = 7.0f;
	m_ViewSetup.flFarZ = 1000.f;
	m_ViewSetup.bDoBloomAndToneMapping = true;

	CMatRenderContextPtr pRenderContext(m_materialsystem());

	pRenderContext->PushRenderTargetAndViewport();
	pRenderContext->SetRenderTarget(m_PreviewTexture);

	pRenderContext->BindLocalCubemap(m_CubemapTexture);
	pRenderContext->SetLightingOrigin(-65.0f, 2.0f, 50.0f);
	pRenderContext->SetIntRenderingParameter(10, 0);

	Frustum dummyFrustum;
	enum ahdf
	{
		VIEW_CLEAR_COLOR = 0x1,
		VIEW_CLEAR_DEPTH = 0x2,
		VIEW_CLEAR_FULL_TARGET = 0x4,
		VIEW_NO_DRAW = 0x8,
		VIEW_CLEAR_OBEY_STENCIL = 0x10,
		VIEW_CLEAR_STENCIL = 0x20,
	};
	m_renderview()->Push3DView(pRenderContext, m_ViewSetup, VIEW_CLEAR_COLOR | VIEW_CLEAR_DEPTH | VIEW_CLEAR_STENCIL, m_PreviewTexture, dummyFrustum);

	pRenderContext->ClearColor4ub(false, false, false, false);
	pRenderContext->ClearBuffers(true, true, true);
	pRenderContext->SetAmbientLightCube(aWhiteArray.data());

	//m_StudioRender->SetAmbientLightColors(aWhiteArray.data());
	//m_StudioRender->SetLocalLights(0, nullptr);

	matrix3x4_t matPlayerView = { };
	AngleMatrix(QAngle(0, -180, 0), matPlayerView, Vector(0, 0, 0));

	auto fix = g_cfg.player.type[0].chams_type == 3 || g_cfg.player.type[0].chams_type == 5 || g_cfg.player.type[0].chams_type == 6 || g_cfg.player.type[0].chams_type == 8;

	m_modelrender()->SuppressEngineLighting(true);
	if (g_cfg.player.type[0].chams[PLAYER_CHAMS_VISIBLE] && !fix && !g_cfg.player.type[0].double_material && !g_cfg.player.type[0].animated_material)
		ApplyMaterial(g_cfg.player.type[0].chams_type, false, Color(g_cfg.player.type[0].chams_color), true, false);
	else
		if (g_cfg.player.type[0].chams[PLAYER_CHAMS_VISIBLE] && (fix || g_cfg.player.type[0].double_material || g_cfg.player.type[0].animated_material))
			ApplyMaterial(0, false, Color(g_cfg.player.type[0].chams_color.r(), g_cfg.player.type[0].chams_color.g(), g_cfg.player.type[0].chams_color.b(), g_cfg.player.type[0].chams_color.a() - 1), true, false);

	m_PreviewModel->Draw(matPlayerView);

	if (fix)
	{
		ApplyMaterial(g_cfg.player.type[0].chams_type, true, Color(g_cfg.player.type[0].chams_color), true, true);
		m_PreviewModel->Draw(matPlayerView);
	}

	if (g_cfg.player.type[0].double_material)
	{
		ApplyMaterial(6, true, Color(g_cfg.player.type[0].double_material_color), true, true);
		m_PreviewModel->Draw(matPlayerView);
	}

	if (g_cfg.player.type[0].animated_material)
	{
		ApplyMaterial(9, true, Color(g_cfg.player.type[0].animated_material_color), true, true);
		m_PreviewModel->Draw(matPlayerView);
	}


	m_modelrender()->SuppressEngineLighting(false);

	m_renderview()->PopView(pRenderContext, dummyFrustum);
	pRenderContext->BindLocalCubemap(nullptr);

	pRenderContext->PopRenderTargetAndViewport();
	pRenderContext->Release();
}

void C_MergedMDL::SetupBonesForAttachmentQueries()
{
	static auto m_SetupBonesForAttachmentQueries = util::FindSignature("client.dll", ("55 8B EC 83 EC 14 83 3D ? ? ? ? ? 53"));
	return ((void(__thiscall*)(void*))(m_SetupBonesForAttachmentQueries))(this);
}

bool& IMaterialSystem::DisableRenderTargetAllocationForever()
{
	static auto m_DisableRenderTargetAllocationForever = util::FindSignature("client.dll", ("80 B9 ? ? ? ? ? 74 0F")) + 0x2;
	return *reinterpret_cast<bool*>(reinterpret_cast<std::uintptr_t>(this) + m_DisableRenderTargetAllocationForever);
}

void C_MergedMDL::SetMergedMDL(const char* szModelPath, CCustomMaterialOwner* pCustomMaterialOwner, void* pProxyData)
{
	static auto m_SetMergedMDL = util::FindSignature("client.dll", ("55 8B EC 57 8B F9 8B 0D ? ? ? ? 85 C9 75"));
	return ((void(__thiscall*)(void*, const char*, CCustomMaterialOwner*, void*, bool))(m_SetMergedMDL))(this, szModelPath, pCustomMaterialOwner, pProxyData, false);
}