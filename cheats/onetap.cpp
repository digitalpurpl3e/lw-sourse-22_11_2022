#include "menu.h"
#include <ShlObj_core.h>
#include "../constchars.h"
#include "../cheats/misc/logs.h"

void otmenu::render_decorationsf()
{
	drawf->AddRect(ImVec2(pf.x + 0, pf.y + 0), ImVec2(pf.x + 845, pf.y + 560), ImColor(59, 59, 59, int(255 * alphamodulatef)), 0, 15, 1.000000);
	drawf->AddLine(ImVec2(pf.x + 0, pf.y + 30), ImVec2(pf.x + 875, pf.y + 30), ImColor(59, 59, 59, int(255 * alphamodulatef)), 1.000000);
	//drawf->AddImage(background, p, p + ImVec2{ 845.000000f, 560.000000f });
	drawf->AddRectFilledMultiColor(ImVec2(pf.x + 100, pf.y + 30), ImVec2(pf.x + 437, pf.y + 31), ImColor(59, 59, 59, 0), ImColor(9, 169, 232, int(230 * alphamodulatef)), ImColor(9, 169, 232, int(230 * alphamodulatef)), ImColor(59, 59, 59, 0));
	drawf->AddRectFilledMultiColor(ImVec2(pf.x + 437, pf.y + 30), ImVec2(pf.x + 745, pf.y + 31), ImColor(9, 169, 232, int(230 * alphamodulatef)), ImColor(59, 59, 59, 0), ImColor(59, 59, 59, 0), ImColor(9, 169, 232, int(230 * alphamodulatef)));
	drawf->AddRectFilled(ImVec2(pf.x + 7, pf.y + 37), ImVec2(pf.x + 85, pf.y + 530), ImColor(12, 12, 12, int(170 * alphamodulatef)), 0, 15);
	drawf->AddRect(ImVec2(pf.x + 7, pf.y + 37), ImVec2(pf.x + 85, pf.y + 530), ImColor(59, 59, 59, int(170 * alphamodulatef)), 0, 15, 1.000000);
	drawf->AddRect(ImVec2(pf.x + 8, pf.y + 38), ImVec2(pf.x + 84, pf.y + 529), ImColor(2, 2, 2, int(170 * alphamodulatef)), 0, 15, 1.000000);
	drawf->AddRectFilled(ImVec2(pf.x + 92, pf.y + 37), ImVec2(pf.x + 838, pf.y + 530), ImColor(12, 12, 12, int(170 * alphamodulatef)), 0, 15);
	drawf->AddRect(ImVec2(pf.x + 92, pf.y + 37), ImVec2(pf.x + 838, pf.y + 530), ImColor(59, 59, 59, int(170 * alphamodulatef)), 0, 15, 1.000000);
	drawf->AddRect(ImVec2(pf.x + 93, pf.y + 38), ImVec2(pf.x + 837, pf.y + 529), ImColor(3, 1, 1, int(170 * alphamodulatef)), 0, 15, 1.000000);
	drawf->AddLine(ImVec2(pf.x + 92, pf.y + 37 + 26), ImVec2(pf.x + 838, pf.y + 37 + 26), ImColor(59, 59, 59, int(150 * alphamodulatef)), 1.000000);
}






void draw_multicomboOT(std::string name, std::vector<int>& variable, const char* labels[], int count, std::string& preview)
{
	static auto howmuchsel = [](std::vector<int> e) -> int {
		int s = 0;
		for (int i = 0; i < e.size(); i++)
			if (e[i])
				s++;


		return s;
	};
	if (ui::BeginComboOT(name.c_str(), (howmuchsel(variable) > 0 ? std::to_string(howmuchsel(variable)) + " selected" : "None").c_str(), ImGuiComboFlags_HeightLarge, count)) // draw start
	{
		ui::BeginGroup();
			for (auto i = 0; i < count; i++)
				ui::SelectableOT(labels[i], (bool*)&variable[i], ImGuiSelectableFlags_DontClosePopups);
		ui::EndGroup();
		ui::EndComboOT();
	}

	preview = crypt_str("None"); // reset preview to use later

}
std::vector <std::string> zzfiles;
std::vector <std::string> zzscripts;
std::string zzediting_script;
IDirect3DTexture9* zzall_skins[36];
static float zpfix = 226;
auto zzselected_script = 0;
auto zzloaded_editing_script = false;

std::string zzget_wep(int id, int custom_index = -1, bool knife = true)
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

IDirect3DTexture9* zzget_skin_preview(const char* weapon_name, const std::string& skin_name, IDirect3DDevice9* device)
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



std::string zzget_config_dir()
{
	std::string folder;
	static TCHAR path[MAX_PATH];

	
	return folder;
}

void zzload_config()
{
	
}

void zzsave_config()
{
	
}

void zzremove_config()
{
	
}

void zzadd_config()
{
	
}













void otmenu::render()
{
	std::string preview = crypt_str("None");
	static bool window_set = false;
	static int windowsize_x = 575;
	static int windowsize_y = 465;
	static int oldwindowsize_x = 500;
	static int oldwindowsize_y = 400;
	static int speed = 5;
	static bool finish = false;
	static bool sub_tabs = false;

	if (windowsize_x != oldwindowsize_x)
	{
		if (windowsize_x > oldwindowsize_x)
		{
			windowsize_x -= speed;
		}
		if (windowsize_x < oldwindowsize_x)
		{
			windowsize_x += speed;
		}
	}
	if (windowsize_y != oldwindowsize_y)
	{
		if (windowsize_y > oldwindowsize_y)
		{
			windowsize_y -= speed;
		}
		if (windowsize_y < oldwindowsize_y)
		{
			windowsize_y += speed;
		}
	}
	if (windowsize_x == oldwindowsize_x && windowsize_y == oldwindowsize_y)
	{
		finish = true;
	}
	else
	{
		finish = false;
	}

	if (hooks::menu_open && alphamodulatef <= 1.f)
		alphamodulatef += 0.05f;
	else if (!hooks::menu_open && alphamodulatef >= 0.f)
	{
		alphamodulatef -= 0.05f;
	}

	ImGuiStyle* style = &ui::GetStyle();
	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(117, 187, 253, 255);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(32, 143, 253, 255);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(89, 171, 253, 255);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(89, 171, 253, 255);


	style->ScrollbarSize = 2;
	style->ScrollbarRounding = 2;
	ui::PushFont(skeet_menu.f2);
	ui::SetNextWindowSizeConstraints(ImVec2(windowsize_x, windowsize_y), ImVec2(windowsize_x, windowsize_y));
	ui::BeginOT("Onetap", 0, ImGuiWindowFlags_NoCollapse || ImGuiWindowFlags_NoScrollbar || ImGuiWindowFlags_NoTitleBar || ImGuiWindowFlags_NoResize);
	{
		auto wp = ui::GetWindowPos();
		auto ws = ui::GetWindowSize();
		static int tab = 0;
		static int sub_rage = 0;
		static int sub_legit = 0;
		static int sub_visuals = 0;
		static int sub_misc = 0;
		static int sub_skins = 0;

		ui::TabButtonOT("Legit", &tab, 0, 5);
		ui::TabButtonOT("Rage", &tab, 1, 5);
		ui::TabButtonOT("Visuals", &tab, 2, 5);
		ui::TabButtonOT("Skins", &tab, 3, 5);
		ui::TabButtonOT("Misc", &tab, 4, 5);


		auto defsize = ImVec2(370, 350);
		auto def_pos = ImVec2(wp.x + 160, wp.y + 80);

		static int alphas = 0;

		if (finish == true)
		{
			alphas += 5;
		}
		else
		{
			alphas = 0;
		}
		ui::GetStyle().secondalpha = alphas;
		if (tab == 0)
		{
			oldwindowsize_x = 575;
			oldwindowsize_y = 620;

			if (finish == true)
			{
				ui::GetWindowDrawList()->AddRectFilled(ImVec2(wp.x + 15, wp.y + 80), ImVec2(wp.x + ws.x - 15, wp.y + 130), ImColor(32, 32, 38, alphas), 5);
				ui::GetWindowDrawList()->AddRect(ImVec2(wp.x + 15, wp.y + 80), ImVec2(wp.x + ws.x - 15, wp.y + 130), ImColor(46, 48, 56, alphas), 5);

				ui::TabButton_littOT("General", "q", &sub_legit, 0, 7, skeet_menu.icons);
				ui::TabButton_littOT("R8", "J", &sub_legit, 1, 7, skeet_menu.icons);
				ui::TabButton_littOT("Pistol", "C", &sub_legit, 2, 7, skeet_menu.icons);
				ui::TabButton_littOT("Rifle", "W", &sub_legit, 3, 7, skeet_menu.icons);
				ui::TabButton_littOT("Smg", "N", &sub_legit, 4, 7, skeet_menu.icons);

				ui::TabButton_littOT("Snipers", "Z", &sub_legit, 5, 7, skeet_menu.icons);
				ui::TabButton_littOT("Heavy", "d", &sub_legit, 6, 7, skeet_menu.icons);

				static float slid;
				if (sub_legit)
					hooks::legit_weapon = sub_legit - 1;
					
				

			
					ui::SetNextWindowPos(ImVec2(wp.x + 15, wp.y + 145));
					ui::BeginChildOT("General", ImVec2(260, 410));
					{

						ui::CheckboxOT(crypt_str("Enable"), &g_cfg.legitbot.enabled); ui::Spacing();


						if (g_cfg.legitbot.enabled)
							g_cfg.ragebot.enable = false;

						ui::CheckboxOT(crypt_str("Friendly fire"), &g_cfg.legitbot.friendly_fire); ui::Spacing();
						ui::CheckboxOT(crypt_str("Automatic pistols"), &g_cfg.legitbot.autopistol); ui::Spacing();

						ui::CheckboxOT(crypt_str("Automatic scope"), &g_cfg.legitbot.autoscope); ui::Spacing();

						if (g_cfg.legitbot.autoscope)
						{
							ui::CheckboxOT(crypt_str("Unscope after shot"), &g_cfg.legitbot.unscope); ui::Spacing();
						}

						ui::CheckboxOT(crypt_str("Snipers in zoom only"), &g_cfg.legitbot.sniper_in_zoom_only); ui::Spacing();

						ui::CheckboxOT(crypt_str("Enable in air"), &g_cfg.legitbot.do_if_local_in_air); ui::Spacing();
						ui::CheckboxOT(crypt_str("Enable if flashed"), &g_cfg.legitbot.do_if_local_flashed); ui::Spacing();
						ui::CheckboxOT(crypt_str("Enable in smoke"), &g_cfg.legitbot.do_if_enemy_in_smoke); ui::Spacing();
						ui::Text("Key");
						ui::KeybindSkeet("#sd", &g_cfg.legitbot.key.key, &g_cfg.legitbot.key.mode);
						ui::Text("Key autofire");
						ui::KeybindSkeet("#q1asgf", &g_cfg.legitbot.autofire_key.key, &g_cfg.legitbot.autofire_key.mode);
						ui::SliderIntOT(crypt_str("Automatic fire delay"), &g_cfg.legitbot.autofire_delay, 0, 12, (!g_cfg.legitbot.autofire_delay ? crypt_str("None") : (g_cfg.legitbot.autofire_delay == 1 ? crypt_str("%.0f") : crypt_str("%.0f"))));


					}
					ui::EndChildOT();

					
					ui::SetNextWindowPos(ImVec2(wp.x + 300, wp.y + 145));
					ui::BeginChildOT("Weapon Config", ImVec2(260, 410));
					{

						if (sub_legit)
						{
							std::vector<const char*> hitbox_legit = { crypt_str("Nearest"), crypt_str("Head"), crypt_str("Body") };
							ui::ComboOT(crypt_str("Hitbox"), &g_cfg.legitbot.weapon[hooks::legit_weapon].priority, hitbox_legit);

							ui::CheckboxOT(crypt_str("Automatic stop"), &g_cfg.legitbot.weapon[hooks::legit_weapon].auto_stop);

							ui::ComboOT(crypt_str("Field of view type"), &g_cfg.legitbot.weapon[hooks::legit_weapon].fov_type, LegitFov);//"%.0f"
							ui::SliderFloatOT(crypt_str("Field of view amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].fov, 0.f, 30.f, crypt_str("%.0f"));



							ui::SliderFloatOT(crypt_str("Silent field of view"), &g_cfg.legitbot.weapon[hooks::legit_weapon].silent_fov, 0.f, 30.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].silent_fov ? crypt_str("None") : crypt_str("%.0f"))); //-V550



							ui::ComboOT(crypt_str("Smooth type"), &g_cfg.legitbot.weapon[hooks::legit_weapon].smooth_type, LegitSmooth);
							ui::SliderFloatOT(crypt_str("Smooth amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].smooth, 1.f, 12.f, crypt_str("%.0f"));



							ui::ComboOT(crypt_str("RCS type"), &g_cfg.legitbot.weapon[hooks::legit_weapon].rcs_type, RCSType);
							ui::SliderFloatOT(crypt_str("RCS amount"), &g_cfg.legitbot.weapon[hooks::legit_weapon].rcs, 0.f, 100.f, crypt_str("%.0f%%"), 1.f);

							if (g_cfg.legitbot.weapon[hooks::legit_weapon].rcs > 0)
							{
								ui::SliderFloatOT(crypt_str("RCS custom field of view"), &g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_fov, 0.f, 30.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_fov ? crypt_str("None") : crypt_str("%.0f"))); //-V550
								ui::SliderFloatOT(crypt_str("RCS Custom smooth"), &g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_smooth, 0.f, 12.f, (!g_cfg.legitbot.weapon[hooks::legit_weapon].custom_rcs_smooth ? crypt_str("None") : crypt_str("%.0f"))); //-V550
							}



							ui::SliderIntOT(crypt_str("Automatic wall damage"), &g_cfg.legitbot.weapon[hooks::legit_weapon].awall_dmg, 0, 100, (!g_cfg.legitbot.weapon[hooks::legit_weapon].awall_dmg ? crypt_str("None") : crypt_str("%.0f")));
							ui::SliderIntOT(crypt_str("Automatic fire hitchance"), &g_cfg.legitbot.weapon[hooks::legit_weapon].autofire_hitchance, 0, 100, (!g_cfg.legitbot.weapon[hooks::legit_weapon].autofire_hitchance ? crypt_str("None") : crypt_str("%.0f")));
							ui::SliderFloatOT(crypt_str("Target switch delay"), &g_cfg.legitbot.weapon[hooks::legit_weapon].target_switch_delay, 0.f, 1.f, "%.0f");
						}
						

					}
					ui::EndChildOT();



					
				



			}
		}
		if (tab == 1)
		{
			oldwindowsize_x = 575;
			oldwindowsize_y = 820;
			if (finish == true)
			{
				ui::GetWindowDrawList()->AddRectFilled(ImVec2(wp.x + 15, wp.y + 80), ImVec2(wp.x + ws.x - 15, wp.y + 130), ImColor(32, 32, 38, alphas), 5);
				ui::GetWindowDrawList()->AddRect(ImVec2(wp.x + 15, wp.y + 80), ImVec2(wp.x + ws.x - 15, wp.y + 130), ImColor(46, 48, 56, alphas), 5);

				ui::TabButton_littOT("General", "q", &sub_rage, 0, 9, skeet_menu.icons);
				ui::TabButton_littOT("R8", "J", &sub_rage, 1, 9, skeet_menu.icons);
				ui::TabButton_littOT("Pistol", "C", &sub_rage, 2, 9, skeet_menu.icons);
				ui::TabButton_littOT("SMG", "N", &sub_rage, 3, 9, skeet_menu.icons);
				ui::TabButton_littOT("Rifle", "W", &sub_rage, 4, 9, skeet_menu.icons);
				ui::TabButton_littOT("Autosniper", "X", &sub_rage, 5, 9, skeet_menu.icons);
				ui::TabButton_littOT("Scout", "a", &sub_rage, 6, 9, skeet_menu.icons);

				ui::TabButton_littOT("Awp", "Z", &sub_rage, 7, 9, skeet_menu.icons);
				ui::TabButton_littOT("Heavy", "f", &sub_rage, 8, 9, skeet_menu.icons);

				hooks::rage_weapon = sub_rage - 1;

				ui::SetNextWindowPos(ImVec2(wp.x + 15, wp.y + 145));
				ui::BeginChildOT("General", ImVec2(260, 290));
				{
					ui::CheckboxOT(crypt_str("Enable"), &g_cfg.ragebot.enable); ui::Spacing();

					if (g_cfg.ragebot.enable)
						g_cfg.legitbot.enabled = false;

					ui::SliderIntOT(crypt_str("View"), &g_cfg.ragebot.field_of_view, 1, 180, crypt_str("%.0f"));
					ui::CheckboxOT(crypt_str("Silent aim"), &g_cfg.ragebot.silent_aim); ui::Spacing();
					ui::CheckboxOT(crypt_str("Automatic wall"), &g_cfg.ragebot.autowall); ui::Spacing();
					ui::CheckboxOT(crypt_str("Aimbot with zeus"), &g_cfg.ragebot.zeus_bot); ui::Spacing();
					ui::CheckboxOT(crypt_str("Aimbot with knife"), &g_cfg.ragebot.knife_bot); ui::Spacing();
					ui::CheckboxOT(crypt_str("Automatic fire"), &g_cfg.ragebot.autoshoot); ui::Spacing();
					ui::CheckboxOT(crypt_str("Automatic scope"), &g_cfg.ragebot.autoscope); ui::Spacing();
					ui::CheckboxOT(crypt_str("Pitch desync correction"), &g_cfg.ragebot.pitch_antiaim_correction); ui::Spacing();

					ui::CheckboxOT(crypt_str("Double tap"), &g_cfg.ragebot.double_tap); ui::Spacing();

					if (g_cfg.ragebot.double_tap)
					{
						ui::Text("Double tap key");
						ui::KeybindSkeet("##asdg111111asf", &g_cfg.ragebot.double_tap_key.key, &g_cfg.ragebot.double_tap_key.mode);
						ui::CheckboxOT(crypt_str("Slow teleport"), &g_cfg.ragebot.slow_teleport); ui::Spacing();
					}

					ui::CheckboxOT(crypt_str("Hide shots"), &g_cfg.antiaim.hide_shots); ui::Spacing();

					if (g_cfg.antiaim.hide_shots)
					{
						ui::Text("Hide shots key");
						ui::KeybindSkeet("##asdg111111asf1ads", &g_cfg.antiaim.hide_shots_key.key, &g_cfg.antiaim.hide_shots_key.mode);

					}


					ui::Text("Force safe points");
					ui::KeybindSkeet("##aq1wt", &g_cfg.ragebot.safe_point_key.key, &g_cfg.ragebot.safe_point_key.mode);

					ui::Text("Force body aim");
					ui::KeybindSkeet("##ff", &g_cfg.ragebot.body_aim_key.key, &g_cfg.ragebot.body_aim_key.mode);

				}
				ui::EndChildOT();


				ui::SetNextWindowPos(ImVec2(wp.x + 300, wp.y + 145));
				ui::BeginChildOT("Weapon Config", ImVec2(260, 290));
				{

					if (sub_rage)
					{
						ui::ComboOT(crypt_str("Target selection"), &g_cfg.ragebot.weapon[hooks::rage_weapon].selection_type, selection);

						draw_multicomboOT(crypt_str("Hitboxes"), g_cfg.ragebot.weapon[hooks::rage_weapon].hitboxes, hitboxes, ARRAYSIZE(hitboxes), preview);

						ui::CheckboxOT(crypt_str("Static point scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale); ui::Spacing();

						if (g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale)
						{
							ui::SliderFloatOT(crypt_str("Head scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale ? crypt_str("%.0f") : crypt_str("None"));
							ui::SliderFloatOT(crypt_str("Body scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale ? crypt_str("%.0f") : crypt_str("None"));
						}

						ui::CheckboxOT(crypt_str("Enable max misses"), &g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses); ui::Spacing();

						if (g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses)
							ui::SliderIntOT(crypt_str("Max misses"), &g_cfg.ragebot.weapon[hooks::rage_weapon].max_misses_amount, 0, 6, "%.0f");

						ui::CheckboxOT(crypt_str("Prefer safe points"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_safe_points); ui::Spacing();
						ui::CheckboxOT(crypt_str("Prefer body aim"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_body_aim); ui::Spacing();





						ui::CheckboxOT(crypt_str("Automatic stop"), &g_cfg.ragebot.weapon[hooks::rage_weapon].autostop); ui::Spacing();

						if (g_cfg.ragebot.weapon[hooks::rage_weapon].autostop)
							draw_multicomboOT(crypt_str("Modifiers"), g_cfg.ragebot.weapon[hooks::rage_weapon].autostop_modifiers, autostop_modifiers, ARRAYSIZE(autostop_modifiers), preview);

						ui::CheckboxOT(crypt_str("Hitchance"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance); ui::Spacing();

						if (g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance)
							ui::SliderIntOT(crypt_str("Hitchance amount"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance_amount, 1, 100, "%.0f");

						if (g_cfg.ragebot.double_tap && hooks::rage_weapon <= 4)
						{
							ui::CheckboxOT(crypt_str("Double tap hitchance"), &g_cfg.ragebot.weapon[hooks::rage_weapon].double_tap_hitchance); ui::Spacing();

							if (g_cfg.ragebot.weapon[hooks::rage_weapon].double_tap_hitchance)
								ui::SliderIntOT(crypt_str("Double tap hitchance amount"), &g_cfg.ragebot.weapon[hooks::rage_weapon].double_tap_hitchance_amount, 1, 100, "%.0f");
						}

						ui::SliderIntOT(crypt_str("Minimum visible damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_visible_damage, 1, 120, "%.0f");

						if (g_cfg.ragebot.autowall)
							ui::SliderIntOT(crypt_str("Minimum wall damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_damage, 1, 120, "%.0f");


						ui::Text("Damage override");
						ui::KeybindSkeet("##sasgd", &g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key, &g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.mode);


						if (g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key > KEY_NONE&& g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key < KEY_MAX)
							ui::SliderIntOT(crypt_str("Minimum override damage"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_override_damage, 1, 120, "%.0f");


					}


				}
				ui::EndChildOT();




				ui::SetNextWindowPos(ImVec2(wp.x + 15, wp.y + 145 + 300));

				ui::BeginChildOT("Anti-aim", ImVec2(260, 290));
				{
					
					static auto type = 0;

					ui::CheckboxOT(crypt_str("Enable"), &g_cfg.antiaim.enable); ui::Spacing();
					ui::ComboOT(crypt_str("Anti-aim type"), &g_cfg.antiaim.antiaim_type, antiaim_type);

					if (g_cfg.antiaim.antiaim_type)
					{

						ui::ComboOT(crypt_str("Desync"), &g_cfg.antiaim.desync, desync);

						if (g_cfg.antiaim.desync)
						{

							ui::ComboOT(crypt_str("LBY type"), &g_cfg.antiaim.legit_lby_type, lby_type);

							if (g_cfg.antiaim.desync == 1)
							{
								ui::Text("Invert desync key");
								ui::KeybindSkeet("##asdg111111asf1adsas12qw", &g_cfg.antiaim.flip_desync.key, &g_cfg.antiaim.flip_desync.mode);

							}
						}
					}
					else
					{
						ui::ComboOT(crypt_str("Movement type"), &type, movement_type);

						ui::ComboOT(crypt_str("Pitch"), &g_cfg.antiaim.type[type].pitch, pitch);

						ui::ComboOT(crypt_str("Yaw"), &g_cfg.antiaim.type[type].yaw, yaw);

						ui::ComboOT(crypt_str("Base angle"), &g_cfg.antiaim.type[type].base_angle, baseangle);

						if (g_cfg.antiaim.type[type].yaw)
						{
							ui::SliderIntOT(g_cfg.antiaim.type[type].yaw == 1 ? crypt_str("Jitter range") : crypt_str("Spin range"), &g_cfg.antiaim.type[type].range, 1, 180, "%0.f");

							if (g_cfg.antiaim.type[type].yaw == 2)
								ui::SliderIntOT(crypt_str("Spin speed"), &g_cfg.antiaim.type[type].speed, 1, 15, "%0.f");


						}

						ui::ComboOT(crypt_str("Desync"), &g_cfg.antiaim.type[type].desync, desync);

						if (g_cfg.antiaim.type[type].desync)
						{
							if (type == ANTIAIM_STAND)
							{

								ui::ComboOT(crypt_str("LBY type"), &g_cfg.antiaim.lby_type, lby_type);
							}

							if (type != ANTIAIM_STAND || !g_cfg.antiaim.lby_type)
							{
								ui::SliderIntOT(crypt_str("Desync range"), &g_cfg.antiaim.type[type].desync_range, 1, 60, "%0.f");
								ui::SliderIntOT(crypt_str("Inverted desync range"), &g_cfg.antiaim.type[type].inverted_desync_range, 1, 60, "%0.f");
								ui::SliderIntOT(crypt_str("Body lean"), &g_cfg.antiaim.type[type].body_lean, 0, 100, "%0.f");
								ui::SliderIntOT(crypt_str("Inverted body lean"), &g_cfg.antiaim.type[type].inverted_body_lean, 0, 100, "%0.f");
							}

							if (g_cfg.antiaim.type[type].desync == 1)
							{
								static bool asdg;
								ui::Text("Invert desync");
								ui::KeybindSkeet("##eryasdgaeg", &g_cfg.antiaim.flip_desync.key, &g_cfg.antiaim.flip_desync.mode);

							}
						}



						ui::Text("Manual back");
						ui::KeybindSkeet("asfeqrygqwerty", &g_cfg.antiaim.manual_back.key, &g_cfg.antiaim.manual_back.mode);
						ui::Text("Manual left");
						ui::KeybindSkeet("asfeqrygqwertasy", &g_cfg.antiaim.manual_left.key, &g_cfg.antiaim.manual_left.mode);
						ui::Text("Manual right");
						ui::KeybindSkeet("asfeqrygqwertas1y", &g_cfg.antiaim.manual_right.key, &g_cfg.antiaim.manual_right.mode);




						if (g_cfg.antiaim.manual_back.key > KEY_NONE&& g_cfg.antiaim.manual_back.key < KEY_MAX || g_cfg.antiaim.manual_left.key > KEY_NONE&& g_cfg.antiaim.manual_left.key < KEY_MAX || g_cfg.antiaim.manual_right.key > KEY_NONE&& g_cfg.antiaim.manual_right.key < KEY_MAX)
						{
							ui::CheckboxOT(crypt_str("Manuals indicator"), &g_cfg.antiaim.flip_indicator); ui::Spacing();

							static float col[4];
							ui::ColorEdit4Fix("##invc", &g_cfg.antiaim.flip_indicator_color, ImGuiWindowFlags_NoTitleBar);
						}
					}
				}
				ui::EndChildOT();

				ui::SetNextWindowPos(ImVec2(wp.x + 300, wp.y + 145 + 300));


				ui::BeginChildOT("Fakelags", ImVec2(260, 250));
				{
					ui::CheckboxOT(crypt_str("Fake lag"), &g_cfg.antiaim.fakelag); ui::Spacing();
					if (g_cfg.antiaim.fakelag)
					{
						ui::ComboOT(crypt_str("Fake lag type"), &g_cfg.antiaim.fakelag_type, fakelags);
						ui::SliderIntOT(crypt_str("Limit"), &g_cfg.antiaim.fakelag_amount, 1, 16, "%0.f");

						draw_multicomboOT(crypt_str("Fake lag triggers"), g_cfg.antiaim.fakelag_enablers, lagstrigger, ARRAYSIZE(lagstrigger), preview);

						auto enabled_fakelag_triggers = false;

						for (auto i = 0; i < ARRAYSIZE(lagstrigger); i++)
							if (g_cfg.antiaim.fakelag_enablers[i])
								enabled_fakelag_triggers = true;

						if (enabled_fakelag_triggers)
							ui::SliderIntOT(crypt_str("Triggers limit"), &g_cfg.antiaim.triggers_fakelag_amount, 1, 16, "%0.f");
					}

					ui::CheckboxOT(crypt_str("No duck cooldown"), &g_cfg.misc.noduck); ui::Spacing();

					if (g_cfg.misc.noduck)
					{
						ui::Text("Fake duck");
						ui::KeybindSkeet("a1eryasdgaeg", &g_cfg.misc.fakeduck_key.key, &g_cfg.misc.fakeduck_key.mode);
					}

					ui::Text("Slow walk");
					ui::KeybindSkeet("a1eryasdgaeg1", &g_cfg.misc.slowwalk_key.key, &g_cfg.misc.slowwalk_key.mode);
					ui::Text("Auto peek");
					ui::KeybindSkeet("a1eryasdgaeg2", &g_cfg.misc.automatic_peek.key, &g_cfg.misc.automatic_peek.mode);
					ui::Text("Edge jump");
					ui::KeybindSkeet("Edgesadgjump", &g_cfg.misc.edge_jump.key, &g_cfg.misc.edge_jump.mode);

				}
				ui::EndChildOT();


			}
		}







	







		if (tab == 2)
		{
			oldwindowsize_x = 575;
			oldwindowsize_y = 620;
			static int visual_sub = 0;
			



			if (finish == true)
			{
				ui::GetWindowDrawList()->AddRectFilled(ImVec2(wp.x + 15, wp.y + 80), ImVec2(wp.x + ws.x - 15, wp.y + 130), ImColor(32, 32, 38, alphas), 5);
				ui::GetWindowDrawList()->AddRect(ImVec2(wp.x + 15, wp.y + 80), ImVec2(wp.x + ws.x - 15, wp.y + 130), ImColor(46, 48, 56, alphas), 5);

				ui::TabButton_littOT("Enemy", "", &visual_sub, 0, 7, skeet_menu.icons);
				ui::TabButton_littOT("Team", "", &visual_sub, 1, 7, skeet_menu.icons);
				ui::TabButton_littOT("Local", "", &visual_sub, 2, 7, skeet_menu.icons);
				ui::TabButton_littOT("Effects", "", &visual_sub, 3, 7, skeet_menu.icons);
				ui::TabButton_littOT("Other", "", &visual_sub, 4, 7, skeet_menu.icons);



				static float slid;
				if (sub_legit)
					hooks::legit_weapon = sub_legit - 1;

				static std::string valuable_shit1, valuable_shit2;
				static int player = 0;
				if (visual_sub < 3)
				{
					player = visual_sub;
					valuable_shit1 = "Visuals";
					valuable_shit2 = "Colored models";
				}
				else if (visual_sub == 3)
				{
					valuable_shit1 = "Some";
					valuable_shit2 = "No";
				}
				else if (visual_sub == 4)
				{
					valuable_shit1 = "Effects";
					valuable_shit2 = "Other";
				}

				ui::SetNextWindowPos(ImVec2(wp.x + 15, wp.y + 145));
				ui::BeginChildOT(valuable_shit1.c_str(), ImVec2(260, 410));
				{
					if (visual_sub < 3)
					{
						ui::CheckboxOT(crypt_str("Bounding box"), &g_cfg.player.type[player].box);
						ui::ColorEdit4Fix(crypt_str("##boxcolor"), &g_cfg.player.type[player].box_color, ImGuiWindowFlags_NoTitleBar);
						ui::CheckboxOT(crypt_str("Name"), &g_cfg.player.type[player].name);
						ui::ColorEdit4Fix(crypt_str("##namecolor"), &g_cfg.player.type[player].name_color, ImGuiWindowFlags_NoTitleBar);
						ui::CheckboxOT(crypt_str("Health bar"), &g_cfg.player.type[player].health);
						ui::CheckboxOT(crypt_str("Health color"), &g_cfg.player.type[player].custom_health_color);
						ui::ColorEdit4Fix(crypt_str("##healthcolor"), &g_cfg.player.type[player].health_color, ImGuiWindowFlags_NoTitleBar);



						draw_multicomboOT(crypt_str("Flags"), g_cfg.player.type[player].flags, flags, ARRAYSIZE(flags), preview);
						draw_multicomboOT(crypt_str("Weapon"), g_cfg.player.type[player].weapon, weaponplayer, ARRAYSIZE(weaponplayer), preview);


						if (g_cfg.player.type[player].weapon[WEAPON_ICON] || g_cfg.player.type[player].weapon[WEAPON_TEXT])
						{
							ui::Text(crypt_str("Color"));

							ui::ColorEdit4Fix(crypt_str("##weapcolor"), &g_cfg.player.type[player].weapon_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("Skeleton"), &g_cfg.player.type[player].skeleton);

						ui::ColorEdit4Fix(crypt_str("##skeletoncolor"), &g_cfg.player.type[player].skeleton_color, ImGuiWindowFlags_NoTitleBar);

						ui::CheckboxOT(crypt_str("Ammo bar"), &g_cfg.player.type[player].ammo);

						ui::ColorEdit4Fix(crypt_str("##ammocolor"), &g_cfg.player.type[player].ammobar_color, ImGuiWindowFlags_NoTitleBar);

						ui::CheckboxOT(crypt_str("Footsteps"), &g_cfg.player.type[player].footsteps);

						ui::ColorEdit4Fix(crypt_str("##footstepscolor"), &g_cfg.player.type[player].footsteps_color, ImGuiWindowFlags_NoTitleBar);

						if (g_cfg.player.type[player].footsteps)
						{
							ui::SliderIntOT(crypt_str("Thickness"), &g_cfg.player.type[player].thickness, 1, 10, "%.0f");
							ui::SliderIntOT(crypt_str("Radius"), &g_cfg.player.type[player].radius, 50, 500, "%.0f");
						}

						if (player == ENEMY || player == TEAM)
						{
							ui::CheckboxOT(crypt_str("Snap lines"), &g_cfg.player.type[player].snap_lines);

							ui::ColorEdit4Fix(crypt_str("##snapcolor"), &g_cfg.player.type[player].snap_lines_color, ImGuiWindowFlags_NoTitleBar);

							if (player == ENEMY)
							{
								if (g_cfg.ragebot.enable)
								{
									ui::CheckboxOT(crypt_str("Aimbot points"), &g_cfg.player.show_multi_points);

									ui::ColorEdit4Fix(crypt_str("##showmultipointscolor"), &g_cfg.player.show_multi_points_color, ImGuiWindowFlags_NoTitleBar);
								}

								ui::CheckboxOT(crypt_str("Aimbot hitboxes"), &g_cfg.player.lag_hitbox);

								ui::ColorEdit4Fix(crypt_str("##lagcompcolor"), &g_cfg.player.lag_hitbox_color, ImGuiWindowFlags_NoTitleBar);
							}
						}
						else
						{
							ui::ComboOT(crypt_str("Player model T"), &g_cfg.player.player_model_t, player_model_t);

							ui::ComboOT(crypt_str("Player model CT"), &g_cfg.player.player_model_ct, player_model_ct);
						}





						if (player == ENEMY)
						{
							ui::CheckboxOT(crypt_str("OOF arrows"), &g_cfg.player.arrows);

							ui::ColorEdit4Fix(crypt_str("##arrowscolor"), &g_cfg.player.arrows_color, ImGuiWindowFlags_NoTitleBar);

							if (g_cfg.player.arrows)
							{
								ui::SliderIntOT(crypt_str("Arrows distance"), &g_cfg.player.distance, 1, 100, "%.0f");
								ui::SliderIntOT(crypt_str("Arrows size"), &g_cfg.player.size, 1, 100, "%.0f");
							}
						}
					}
					else if (visual_sub == 3)
					{
						ui::CheckboxOT(crypt_str("Rare animations"), &g_cfg.skins.rare_animations); ui::Spacing();
						ui::SliderIntOT(crypt_str("Viewmodel field of view"), &g_cfg.esp.viewmodel_fov, 0, 89, "%.0f");
						ui::SliderIntOT(crypt_str("Viewmodel X"), &g_cfg.esp.viewmodel_x, -50, 50, "%.0f");
						ui::SliderIntOT(crypt_str("Viewmodel Y"), &g_cfg.esp.viewmodel_y, -50, 50, "%.0f");
						ui::SliderIntOT(crypt_str("Viewmodel Z"), &g_cfg.esp.viewmodel_z, -50, 50, "%.0f");
						ui::SliderIntOT(crypt_str("Viewmodel roll"), &g_cfg.esp.viewmodel_roll, -180, 180, "%.0f");




						ui::CheckboxOT(crypt_str("Rain"), &g_cfg.esp.rain); ui::Spacing();
						ui::CheckboxOT(crypt_str("Full bright"), &g_cfg.esp.bright); ui::Spacing();

						ui::ComboOT(crypt_str("Skybox"), &g_cfg.esp.skybox, skybox);

						ui::Text(crypt_str("Color"));

						ui::ColorEdit4Fix(crypt_str("##skyboxcolor"), &g_cfg.esp.skybox_color, ImGuiWindowFlags_NoTitleBar);

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

					}
					else if (visual_sub == 4)
					{
						draw_multicomboOT(crypt_str("Indicators"), g_cfg.esp.indicators, indicators, ARRAYSIZE(indicators), preview);


						draw_multicomboOT(crypt_str("Removals"), g_cfg.esp.removals, removals, ARRAYSIZE(removals), preview);

						if (g_cfg.esp.removals[REMOVALS_ZOOM])
						{
							ui::CheckboxOT(crypt_str("Fix zoom sensivity"), &g_cfg.esp.fix_zoom_sensivity); ui::Spacing();
						}

						ui::CheckboxOT(crypt_str("Grenade prediction"), &g_cfg.esp.grenade_prediction);

						ui::ColorEdit4Fixed("##box_color", &g_cfg.esp.grenade_prediction_color, ImGuiWindowFlags_NoTitleBar);

						if (g_cfg.esp.grenade_prediction)
						{
							ui::CheckboxSkeet(crypt_str("On click"), &g_cfg.esp.on_click);
							ui::ColorEdit4Fixed(crypt_str("##tracergrenpredcolor"), &g_cfg.esp.grenade_prediction_tracer_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("Grenade projectiles"), &g_cfg.esp.projectiles); ui::Spacing();

						if (g_cfg.esp.projectiles)
							draw_multicomboOT(crypt_str("Grenade ESP"), g_cfg.esp.grenade_esp, proj_combo, ARRAYSIZE(proj_combo), preview);

						if (g_cfg.esp.grenade_esp[GRENADE_ICON] || g_cfg.esp.grenade_esp[GRENADE_TEXT])
						{
							ui::Text(crypt_str("Color"));

							ui::ColorEdit4Fixed(crypt_str("##projectcolor"), &g_cfg.esp.projectiles_color, ImGuiWindowFlags_NoTitleBar);
						}

						if (g_cfg.esp.grenade_esp[GRENADE_BOX])
						{
							ui::Text(crypt_str("Box color"));

							ui::ColorEdit4Fixed(crypt_str("##grenade_box_color"), &g_cfg.esp.grenade_box_color, ImGuiWindowFlags_NoTitleBar);
						}

						if (g_cfg.esp.grenade_esp[GRENADE_GLOW])
						{
							ui::Text(crypt_str("Glow color"));

							ui::ColorEdit4Fixed(crypt_str("##grenade_glow_color"), &g_cfg.esp.grenade_glow_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("Fire timer"), &g_cfg.esp.molotov_timer);

						ui::ColorEdit4Fixed(crypt_str("##molotovcolor"), &g_cfg.esp.molotov_timer_color, ImGuiWindowFlags_NoTitleBar);

						ui::CheckboxOT(crypt_str("Smoke timer"), &g_cfg.esp.smoke_timer);

						ui::ColorEdit4Fixed(crypt_str("##smokecolor"), &g_cfg.esp.smoke_timer_color, ImGuiWindowFlags_NoTitleBar);

					}

				}
				ui::EndChildOT();


				ui::SetNextWindowPos(ImVec2(wp.x + 300, wp.y + 145));
				ui::BeginChildOT(valuable_shit2.c_str(), ImVec2(260, 410));
				{

					if (visual_sub < 3)
					{
						if (player == LOCAL)
							ui::ComboOT(crypt_str("Type"), &g_cfg.player.local_chams_type, local_chams_type);

						if (player != LOCAL || !g_cfg.player.local_chams_type)
							draw_multicomboOT(crypt_str("Chams"), g_cfg.player.type[player].chams, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? chamsvisact : chamsvis, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? ARRAYSIZE(chamsvisact) : ARRAYSIZE(chamsvis), preview);

						if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] || player == LOCAL && g_cfg.player.local_chams_type) //-V648
						{
							if (player == LOCAL && g_cfg.player.local_chams_type)
							{
								ui::CheckboxOT(crypt_str("Enable desync chams"), &g_cfg.player.fake_chams_enable); ui::Spacing();
								ui::CheckboxOT(crypt_str("Visualize lag"), &g_cfg.player.visualize_lag); ui::Spacing();
								ui::CheckboxOT(crypt_str("Layered"), &g_cfg.player.layered); ui::Spacing();

								ui::ComboOT(crypt_str("Player chams material"), &g_cfg.player.fake_chams_type, chamstype);

								ui::Text(crypt_str("Color "));

								ui::ColorEdit4Fix(crypt_str("##fakechamscolor"), &g_cfg.player.fake_chams_color, ImGuiWindowFlags_NoTitleBar);

								if (g_cfg.player.fake_chams_type != 6)
								{
									ui::CheckboxOT(crypt_str("Double material "), &g_cfg.player.fake_double_material);

									ui::ColorEdit4Fix(crypt_str("##doublematerialcolor"), &g_cfg.player.fake_double_material_color, ImGuiWindowFlags_NoTitleBar);
								}

								ui::CheckboxOT(crypt_str("Animated material"), &g_cfg.player.fake_animated_material);

								ui::ColorEdit4Fix(crypt_str("##animcolormat"), &g_cfg.player.fake_animated_material_color, ImGuiWindowFlags_NoTitleBar);
							}
							else
							{
								ui::ComboOT(crypt_str("Player chams material"), &g_cfg.player.type[player].chams_type, chamstype);

								if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE])
								{
									ui::Text(crypt_str("Visible"));

									ui::ColorEdit4Fix(crypt_str("##chamsvisible"), &g_cfg.player.type[player].chams_color, ImGuiWindowFlags_NoTitleBar);
								}

								if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] && g_cfg.player.type[player].chams[PLAYER_CHAMS_INVISIBLE])
								{
									ui::Text(crypt_str("Invisible"));

									ui::ColorEdit4Fix(crypt_str("##chamsinvisible"), &g_cfg.player.type[player].xqz_color, ImGuiWindowFlags_NoTitleBar);
								}

								if (g_cfg.player.type[player].chams_type != 6)
								{
									ui::CheckboxOT(crypt_str("Double material "), &g_cfg.player.type[player].double_material);

									ui::ColorEdit4Fix(crypt_str("##doublematerialcolor"), &g_cfg.player.type[player].double_material_color, ImGuiWindowFlags_NoTitleBar);
								}

								ui::CheckboxOT(crypt_str("Animated material"), &g_cfg.player.type[player].animated_material);

								ui::ColorEdit4Fix(crypt_str("##animcolormat"), &g_cfg.player.type[player].animated_material_color, ImGuiWindowFlags_NoTitleBar);

								if (player == ENEMY)
								{
									ui::CheckboxOT(crypt_str("Backtrack chams"), &g_cfg.player.backtrack_chams); ui::Spacing();

									if (g_cfg.player.backtrack_chams)
									{
										ui::ComboOT(crypt_str("Backtrack chams material"), &g_cfg.player.backtrack_chams_material, chamstype);

										ui::Text(crypt_str("Color"));

										ui::ColorEdit4Fix(crypt_str("##backtrackcolor"), &g_cfg.player.backtrack_chams_color, ImGuiWindowFlags_NoTitleBar);
									}
								}
							}
						}

						if (player == ENEMY || player == TEAM)
						{
							ui::CheckboxOT(crypt_str("Ragdoll chams"), &g_cfg.player.type[player].ragdoll_chams); ui::Spacing();

							if (g_cfg.player.type[player].ragdoll_chams)
							{
								ui::ComboOT(crypt_str("Ragdoll chams material"), &g_cfg.player.type[player].ragdoll_chams_material, chamstype);

								ui::Text(crypt_str("Color"));

								ui::ColorEdit4Fix(crypt_str("##ragdollcolor"), &g_cfg.player.type[player].ragdoll_chams_color, ImGuiWindowFlags_NoTitleBar);
							}
						}
						else if (!g_cfg.player.local_chams_type)
						{
							ui::CheckboxOT(crypt_str("Transparency in scope"), &g_cfg.player.transparency_in_scope); ui::Spacing();

							if (g_cfg.player.transparency_in_scope)
								ui::SliderFloatOT(crypt_str("Alpha"), &g_cfg.player.transparency_in_scope_amount, 0.0f, 1.0f, "%.0f");
						}



						ui::CheckboxOT(crypt_str("Glow"), &g_cfg.player.type[player].glow); ui::Spacing();

						if (g_cfg.player.type[player].glow)
						{
							ui::ComboOT(crypt_str("Glow type"), &g_cfg.player.type[player].glow_type, glowtype);
							ui::Text(crypt_str("Color"));

							ui::ColorEdit4Fix(crypt_str("##glowcolor"), &g_cfg.player.type[player].glow_color, ImGuiWindowFlags_NoTitleBar);
						}




						ui::CheckboxOT(crypt_str("Arms chams"), &g_cfg.esp.arms_chams);

						ui::ColorEdit4Fix(crypt_str("##armscolor"), &g_cfg.esp.arms_chams_color, ImGuiWindowFlags_NoTitleBar);


						ui::ComboOT(crypt_str("Arms chams material"), &g_cfg.esp.arms_chams_type, chamstype);

						if (g_cfg.esp.arms_chams_type != 6)
						{
							ui::CheckboxOT(crypt_str("Arms double material "), &g_cfg.esp.arms_double_material);

							ui::ColorEdit4Fix(crypt_str("##armsdoublematerial"), &g_cfg.esp.arms_double_material_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("Arms animated material "), &g_cfg.esp.arms_animated_material);

						ui::ColorEdit4Fix(crypt_str("##armsanimatedmaterial"), &g_cfg.esp.arms_animated_material_color, ImGuiWindowFlags_NoTitleBar);



						ui::CheckboxOT(crypt_str("Weapon chams"), &g_cfg.esp.weapon_chams);

						ui::ColorEdit4Fix(crypt_str("##weaponchamscolors"), &g_cfg.esp.weapon_chams_color, ImGuiWindowFlags_NoTitleBar);

						ui::ComboOT(crypt_str("Weapon chams material"), &g_cfg.esp.weapon_chams_type, chamstype);

						if (g_cfg.esp.weapon_chams_type != 6)
						{
							ui::CheckboxOT(crypt_str("Double material "), &g_cfg.esp.weapon_double_material);

							ui::ColorEdit4Fix(crypt_str("##weapondoublematerial"), &g_cfg.esp.weapon_double_material_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("Animated material "), &g_cfg.esp.weapon_animated_material);

						ui::ColorEdit4Fix(crypt_str("##weaponanimatedmaterial"), &g_cfg.esp.weapon_animated_material_color, ImGuiWindowFlags_NoTitleBar);



					}
					else if (visual_sub == 3)
					{

						ui::CheckboxOT(crypt_str("Color modulation"), &g_cfg.esp.nightmode); ui::Spacing();
						if (g_cfg.esp.nightmode)
						{
							ui::Text(crypt_str("World color"));

							ui::ColorEdit4Fix(crypt_str("##worldcolor"), &g_cfg.esp.world_color, ImGuiWindowFlags_NoTitleBar);

							ui::Text(crypt_str("Props color"));

							ui::ColorEdit4Fix(crypt_str("##propscolor"), &g_cfg.esp.props_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("World modulation"), &g_cfg.esp.world_modulation); ui::Spacing();

						if (g_cfg.esp.world_modulation)
						{
							ui::SliderFloatOT(crypt_str("Bloom"), &g_cfg.esp.bloom, 0.0f, 750.0f, "%.0f");
							ui::SliderFloatOT(crypt_str("Exposure"), &g_cfg.esp.exposure, 0.0f, 2000.0f, "%.0f");
							ui::SliderFloatOT(crypt_str("Ambient"), &g_cfg.esp.ambient, 0.0f, 1500.0f, "%.0f");
						}

						ui::CheckboxOT(crypt_str("Fog modulation"), &g_cfg.esp.fog);

						if (g_cfg.esp.fog)
						{
							ui::SliderIntOT(crypt_str("Distance"), &g_cfg.esp.fog_distance, 0, 2500, "%.0f");
							ui::SliderIntOT(crypt_str("Density"), &g_cfg.esp.fog_density, 0, 100, "%.0f");

							ui::Text(crypt_str("Color"));

							ui::ColorEdit4Fix(crypt_str("##fogcolor"), &g_cfg.esp.fog_color, ImGuiWindowFlags_NoTitleBar);
						}



					}
					else if (visual_sub == 4)
					{
						ui::CheckboxOT(crypt_str("Bomb indicator"), &g_cfg.esp.bomb_timer); ui::Spacing();
						draw_multicomboOT(crypt_str("Weapon ESP"), g_cfg.esp.weapon, weaponesp, ARRAYSIZE(weaponesp), preview);

						if (g_cfg.esp.weapon[WEAPON_ICON] || g_cfg.esp.weapon[WEAPON_TEXT] || g_cfg.esp.weapon[WEAPON_DISTANCE])
						{
							ui::Text(crypt_str("Color"));

							ui::ColorEdit4Fixed(crypt_str("##weaponcolor"), &g_cfg.esp.weapon_color, ImGuiWindowFlags_NoTitleBar);
						}

						if (g_cfg.esp.weapon[WEAPON_BOX])
						{
							ui::Text(crypt_str("Box color"));

							ui::ColorEdit4Fixed(crypt_str("##weaponboxcolor"), &g_cfg.esp.box_color, ImGuiWindowFlags_NoTitleBar);
						}

						if (g_cfg.esp.weapon[WEAPON_GLOW])
						{
							ui::Text(crypt_str("Glow color"));

							ui::ColorEdit4Fixed(crypt_str("##weaponglowcolor"), &g_cfg.esp.weapon_glow_color, ImGuiWindowFlags_NoTitleBar);
						}

						if (g_cfg.esp.weapon[WEAPON_AMMO])
						{
							ui::Text(crypt_str("Ammo bar color"));

							ui::ColorEdit4Fixed(crypt_str("##weaponammocolor"), &g_cfg.esp.weapon_ammo_color, ImGuiWindowFlags_NoTitleBar);
						}

						ui::CheckboxOT(crypt_str("Client bullet impacts"), &g_cfg.esp.client_bullet_impacts);

						ui::ColorEdit4Fixed(crypt_str("##clientbulletimpacts"), &g_cfg.esp.client_bullet_impacts_color, ImGuiWindowFlags_NoTitleBar);

						ui::CheckboxOT(crypt_str("Server bullet impacts"), &g_cfg.esp.server_bullet_impacts);

						ui::ColorEdit4Fixed(crypt_str("##serverbulletimpacts"), &g_cfg.esp.server_bullet_impacts_color, ImGuiWindowFlags_NoTitleBar);

						ui::CheckboxOT(crypt_str("Local bullet tracers"), &g_cfg.esp.bullet_tracer);

						ui::ColorEdit4Fixed(crypt_str("##bulltracecolor"), &g_cfg.esp.bullet_tracer_color, ImGuiWindowFlags_NoTitleBar);

						ui::CheckboxOT(crypt_str("Enemy bullet tracers"), &g_cfg.esp.enemy_bullet_tracer);


						ui::ColorEdit4Fixed(crypt_str("##enemybulltracecolor"), &g_cfg.esp.enemy_bullet_tracer_color, ImGuiWindowFlags_NoTitleBar);
						draw_multicomboOT(crypt_str("Hit marker"), g_cfg.esp.hitmarker, hitmarkers, ARRAYSIZE(hitmarkers), preview);
						ui::CheckboxOT(crypt_str("Damage marker"), &g_cfg.esp.damage_marker); ui::Spacing();
						ui::CheckboxOT(crypt_str("Kill effect"), &g_cfg.esp.kill_effect); ui::Spacing();

						if (g_cfg.esp.kill_effect)
							ui::SliderFloatOT(crypt_str("Duration"), &g_cfg.esp.kill_effect_duration, 0.01f, 3.0f, "%.0f");
						static bool a1qsagd;
						ui::Text("Thirdperson");
						ui::KeybindSkeet("#q1qq1asgf", &g_cfg.misc.thirdperson_toggle.key, &g_cfg.misc.thirdperson_toggle.mode);

						ui::CheckboxOT(crypt_str("Thirdperson when spectating"), &g_cfg.misc.thirdperson_when_spectating); ui::Spacing();

						if (g_cfg.misc.thirdperson_toggle.key > KEY_NONE&& g_cfg.misc.thirdperson_toggle.key < KEY_MAX)
							ui::SliderIntOT(crypt_str("Thirdperson distance"), &g_cfg.misc.thirdperson_distance, 100, 300, "%.0f");

						ui::SliderIntOT(crypt_str("Field of view"), &g_cfg.esp.fov, 0, 89, "%.0f");
						ui::CheckboxOT(crypt_str("Taser range"), &g_cfg.esp.taser_range); ui::Spacing();
						ui::CheckboxOT(crypt_str("Show spread"), &g_cfg.esp.show_spread); ui::Spacing();

						ui::ColorEdit4Fixed(crypt_str("##spredcolor"), &g_cfg.esp.show_spread_color, ImGuiWindowFlags_NoTitleBar);
						ui::CheckboxOT(crypt_str("Penetration crosshair"), &g_cfg.esp.penetration_reticle);


					}





				}
				ui::EndChildOT();








			}



		}





	





	}
	ui::PopFont();
	ui::EndOT();
	
}