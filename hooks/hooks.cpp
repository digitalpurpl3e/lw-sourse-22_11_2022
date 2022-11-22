// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "hooks.hpp"

#include <tchar.h>
#include <iostream>
#include <d3d9.h>
#include <dinput.h>


#include "..\cheats\misc\logs.h"
#include "..\cheats\misc\misc.h"
#include "..\cheats\visuals\other_esp.h"
#include "..\cheats\visuals\radar.h"
#include "../ImGui/imgui_freetype.h"

#include "../Bytesa.h"
#include "../cheats/tabs.h"
#include "../cheats/bindsfont.h"
#include "../cheats/WeaponFonts.h"
#include "../cheats/fuck/faprolight.h"
#include "../cheats/fuck/hashes.h"
#include "../cheats/fuck/logo_font.h"
#include "../cheats/fuck/menu_font.h"
#include "../cheats/shonax_font.hpp"


#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment(lib, "freetype.lib")

#include <shlobj.h>
#include <shlwapi.h>
#include <thread>
#include "..\cheats\menu.h"
#include "../Bytesa.h"
#include <cheats/visuals/GrenadePrediction.h>
#include "../cheats/fixedfonts.h"
#include <InventoryChanger/InventoryChanger.h>
auto _visible = true;
static auto d3d_init = false;

namespace INIT
{
	HMODULE Dll;
	HWND Window;
	WNDPROC OldWindow;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//extern IMGUI_IMPL_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace hooks
{
	int rage_weapon = 0;
	int legit_weapon = 0;
	bool menu_open = false;
	bool input_shouldListen = false;

	ButtonCode_t* input_receivedKeyval;

	LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//static auto is_down = true;
		//static auto is_clicked = false;
		//
		//if (GetAsyncKeyState(VK_INSERT))
		//{
		//	is_clicked = false;
		//	is_down = true;
		//}
		//else if (!GetAsyncKeyState(VK_INSERT) && is_down)
		//{
		//	is_clicked = true;
		//	is_down = false;
		//}
		//else
		//{
		//	is_clicked = false;
		//	is_down = false;
		//}
		//
		//if (is_clicked)
		//{
		//	menu_open = !menu_open;
		//
		//	if (menu_open && g_ctx.available())
		//	{
		//		if (g_ctx.globals.current_weapon != -1)
		//		{
		//			if (g_cfg.ragebot.enable)
		//				rage_weapon = g_ctx.globals.current_weapon;
		//			else if (g_cfg.legitbot.enabled)
		//				legit_weapon = g_ctx.globals.current_weapon;
		//		}
		//	}
		//}
		//
		//auto pressed_buttons = false;
		//auto pressed_menu_key = uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MOUSEWHEEL;
		//
		//if (g_ctx.local()->is_alive() && !pressed_menu_key && !g_ctx.globals.focused_on_input)
		//	pressed_buttons = true;
		//
		//if (!pressed_buttons && d3d_init && menu_open && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)/* && !input_shouldListen*/)
		//	return true;
		//
		//if (menu_open && (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_MOUSEMOVE)/* && !input_shouldListen*/)
		//	return false;
		//
		//return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);


		if (uMsg == WM_KEYDOWN)
			if (wParam == VK_INSERT)
			{
				menu_open = !menu_open;

				if (menu_open && g_ctx.available())
				{
					if (g_ctx.globals.current_weapon != -1)
					{
						if (g_cfg.ragebot.enable)
							rage_weapon = g_ctx.globals.current_weapon;
						else if (g_cfg.legitbot.enabled)
							legit_weapon = g_ctx.globals.current_weapon;
					}
				}
			}

		//c_keyhandler::get()->wnd_handler(uMsg, wParam);
		if (menu_open)
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

			if (wParam != 'W' && wParam != 'A' && wParam != 'S' && wParam != 'D' && wParam != VK_SHIFT && wParam != VK_CONTROL && wParam != VK_TAB && wParam != VK_SPACE || ui::GetIO().WantTextInput)
				return true;
		}
		return CallWindowProcA(INIT::OldWindow, hWnd, uMsg, wParam, lParam);

	}

	long __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice)
	{
		static auto original_fn = directx_hook->get_func_address <EndSceneFn> (42);


		return original_fn(pDevice);
	}
	std::map<int, std::string> wellplayfont;
	static int global_shot_fuck = 0;
	void GUI_Init(IDirect3DDevice9* pDevice)
	{
		ui::CreateContext();

		ImGui_ImplWin32_Init(INIT::Window);
		ImGui_ImplDX9_Init(pDevice);

		auto& io = ui::GetIO();
		auto& style = ui::GetStyle();

		style.WindowMinSize = ImVec2(10, 10);
		style.ScrollbarSize = 2.0f;
		style.ScrollbarRounding = 1;
		ImFontConfig m_config;
		m_config.OversampleH = m_config.OversampleV = 3;
		m_config.PixelSnapH = false;

		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x2000, 0x206F, // General Punctuation
			0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
			0x31F0, 0x31FF, // Katakana Phonetic Extensions
			0xFF00, 0xFFEF, // Half-width characters
			0x4e00, 0x9FAF, // CJK Ideograms
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0
		};

		//char windows_directory[MAX_PATH];
		//GetWindowsDirectory(windows_directory, MAX_PATH);
		//
		//auto verdana_directory = (std::string)windows_directory + "\\Fonts\\Verdana.ttf";

		// Menu fonts
		c_menu::get().futura_small = io.Fonts->AddFontFromMemoryTTF((void*)futuramediumc, sizeof(futuramediumc), 15.f, &m_config, ranges);
		c_menu::get().futura = io.Fonts->AddFontFromMemoryTTF((void*)futuramediumc, sizeof(futuramediumc), 17.f, &m_config, ranges);
		c_menu::get().futura_large = io.Fonts->AddFontFromMemoryTTF((void*)futuramediumc, sizeof(futuramediumc), 25.f, &m_config, ranges);
		c_menu::get().gotham = io.Fonts->AddFontFromMemoryTTF((void*)GothamPro, sizeof(GothamPro), 13.f, &m_config, ranges);

		// Icon fonts
		c_menu::get().ico_menu = io.Fonts->AddFontFromMemoryTTF((void*)icomenu, sizeof(icomenu), 20.f, &m_config, io.Fonts->GetGlyphRangesCyrillic());
		c_menu::get().ico_bottom = io.Fonts->AddFontFromMemoryTTF((void*)iconbot, sizeof(iconbot), 20.f, &m_config, io.Fonts->GetGlyphRangesCyrillic());
		c_menu::get().tabs = io.Fonts->AddFontFromMemoryTTF(Evolve, sizeof(Evolve), 32.0f, nullptr, ranges);

		skeet_menu.weapon_font = io.Fonts->AddFontFromMemoryTTF((void*)WeaponzFont, sizeof(WeaponzFont), 17.f, &m_config, ranges);
		skeet_menu.tabs = io.Fonts->AddFontFromMemoryTTF(skeet, 15400, 50.f, &m_config, ranges);
		skeet_menu.f1 = io.Fonts->AddFontFromMemoryTTF(new_shonax_font, 67240, 15.f, &m_config, ranges);
		skeet_menu.f2 = io.Fonts->AddFontFromMemoryTTF(new_shonax_font, 67240, 11.f, &m_config, ranges);
		skeet_menu.f3 = io.Fonts->AddFontFromMemoryTTF(new_shonax_font, 67240, 8.f, &m_config, ranges);



		if (!g_cfg.font.wellplay)
			skeet_menu.newfixedfont = io.Fonts->AddFontFromMemoryTTF(newfixedfont, sizeof(newfixedfont), 13.f, &m_config, ranges);
		else
		{
			static bool op = false;
			if (!op)
			{
				int index = 0;
				for (auto p : g_ctx.fonts_path)
				{
					if (index)
						wellplayfont[index] = p;
					index++;
				}
				op = true;
			}
			skeet_menu.newfixedfont = io.Fonts->AddFontFromFileTTF(wellplayfont[g_cfg.font.wellplay].c_str(), 13.0f);
		}



		D3DXCreateTextureFromFileInMemoryEx(pDevice
			,&wellthatshot, sizeof(wellthatshot),
			4000, 1800, D3DUSAGE_DYNAMIC, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &skeet_menu.image);
		skeet_menu.icons = io.Fonts->AddFontFromMemoryTTF(WeaponzFont, sizeof(WeaponzFont), 15.f, &m_config, io.Fonts->GetGlyphRangesCyrillic());





		neverlosemenu.g_pd3dDevice = pDevice;

		neverlosemenu.tolstiy = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/ariblk.ttf", 40.0f);
		neverlosemenu.ne_takoi_tolstiy = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 13.0f);
		neverlosemenu.ne_takoi_tolstiy2 = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 15.0f);



		static const ImWchar zranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x2000, 0x206F, // General Punctuation
			0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
			0x31F0, 0x31FF, // Katakana Phonetic Extensions
			0xFF00, 0xFFEF, // Half-width characters
			0x4e00, 0x9FAF, // CJK Ideograms
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0,
		};

		ImFontConfig font_cfg{};
		font_cfg.FontDataOwnedByAtlas = false;
		//ui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(sfpro_compressed_data, sfpro_compressed_size, 12, &font_cfg, zranges);

		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		nemesismenu.fff = ui::GetIO().Fonts->AddFontFromMemoryTTF(&faprolight, sizeof faprolight, 16, &icons_config, icon_ranges);


		ImGui_ImplDX9_CreateDeviceObjects();
		InventoryChanger::clearItemIconTextures();
		global_shot_fuck = g_cfg.font.wellplay;



		d3d_init = true;
	}

	void GrenadeWarningSadKitty()
	{
		for (auto i = 64; i < m_entitylist()->GetHighestEntityIndex(); i++)
		{
			auto Entity = reinterpret_cast<player_t*>(m_entitylist()->GetClientEntity(i));

			if (!Entity)
				continue;
			if (!Entity->GetClientClass())
				continue;
			auto ClassID = Entity->GetClientClass()->m_ClassID;
			if (!ClassID)
				continue;

			switch (ClassID) {
			case CBaseCSGrenadeProjectile:
			{
				if (const auto Model = Entity->GetModel(); Model && strstr(Model->name, "flashbang"))
					continue;
				auto& vel = Entity->m_vecVelocity();
				if (vel.x == 0 || vel.y == 0)
					continue;

				GrenadeWarning(Entity, GrenadeWarningType::GW_HE_GRENADE);
				break;
			}

			case CMolotovProjectile:
			{
				auto& vel = Entity->m_vecVelocity();
				if (vel.x == 0 || vel.y == 0)
					continue;

				GrenadeWarning(Entity, GrenadeWarningType::GW_MOLOTOV);
				break;
			}

			}

		}
	}

	long __stdcall hooked_present(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region)
	{
		static auto original = directx_hook->get_func_address <PresentFn> (17);
		g_ctx.local((player_t*)m_entitylist()->GetClientEntity(m_engine()->GetLocalPlayer()), true);

		if (global_shot_fuck != g_cfg.font.wellplay)
			d3d_init = false;

		if (!d3d_init)
			GUI_Init(device);

		IDirect3DVertexDeclaration9* vertex_dec;
		device->GetVertexDeclaration(&vertex_dec);

		IDirect3DVertexShader9* vertex_shader;
		device->GetVertexShader(&vertex_shader);

		c_menu::get().device = device;
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ui::NewFrame();
	

	//	switch (g_ctx.menu_type)
	//	{
	//	case 0:
	//		
			skeet_menu.set_menu_opened(hooks::menu_open);
			skeet_menu.draw();
		

			//SadKitty
			if (g_cfg.esp.grenade_warning)
				GrenadeWarningSadKitty();

			





	//	break;
	//case 1:
	//	c_menu::get().draw(hooks::menu_open);
	//	break;
	//case 2:
	//	if (hooks::menu_open) otmenuv3.render();
	//	break;
	//case 3:
	//	if (hooks::menu_open) nemesismenu.render();
	//	break;
	//case 4:
	//	if (hooks::menu_open) neverlosemenu.render();
	//	break;
	//default:
	//	break;
	//}

		otheresp::get().spread_crosshair(device);

		if (g_ctx.globals.should_update_radar)
			Radar::get().OnMapLoad(m_engine()->GetLevelNameShort(), device);
		else
			Radar::get().Render();

		ui::EndFrame();
		ui::Render();
	
		

		if (device->BeginScene() == D3D_OK)
		{
			ImGui_ImplDX9_RenderDrawData(ui::GetDrawData());
			device->EndScene();
		}
		InventoryChanger::clearUnusedItemIconTextures();
		device->SetVertexShader(vertex_shader);
		device->SetVertexDeclaration(vertex_dec);

		return original(device, src_rect, dest_rect, dest_wnd_override, dirty_region);
	}

	long __stdcall Hooked_EndScene_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		static auto ofunc = directx_hook->get_func_address<EndSceneResetFn>(16);

		if (!d3d_init)
			return ofunc(pDevice, pPresentationParameters);

		ImGui_ImplDX9_InvalidateDeviceObjects();
		InventoryChanger::clearItemIconTextures();
		
		auto hr = ofunc(pDevice, pPresentationParameters);

		if (SUCCEEDED(hr))
		{
		
			ImGui_ImplDX9_CreateDeviceObjects();
		}
			

		return hr;
	}

	DWORD original_getforeignfallbackfontname;
	DWORD original_setupbones;
	DWORD original_doextrabonesprocessing;
	DWORD original_standardblendingrules;
	DWORD original_updateclientsideanimation;
	DWORD original_physicssimulate;
	DWORD original_modifyeyeposition;
	DWORD original_calcviewmodelbob;
	DWORD original_processinterpolatedlist;
	vmthook* player_hook;
	vmthook* directx_hook;
	vmthook* client_hook;
	vmthook* clientstate_hook;
	vmthook* engine_hook;
	vmthook* clientmode_hook;
	vmthook* inputinternal_hook;
	vmthook* renderview_hook;
	vmthook* panel_hook;
	vmthook* modelcache_hook;
	vmthook* materialsys_hook;
	vmthook* modelrender_hook;
	vmthook* surface_hook;
	vmthook* bspquery_hook;
	vmthook* prediction_hook;
	vmthook* trace_hook;
	vmthook* filesystem_hook;
	vmthook* sv_cheats;
	vmthook* effects;
	C_HookedEvents hooked_events;
}

void __fastcall hooks::hooked_setkeycodestate(void* thisptr, void* edx, ButtonCode_t code, bool bDown)
{
	static auto original_fn = inputinternal_hook->get_func_address <SetKeyCodeState_t> (91);

	if (input_shouldListen && bDown)
	{
		input_shouldListen = false;

		if (input_receivedKeyval)
			*input_receivedKeyval = code;
	}

	return original_fn(thisptr, code, bDown);
}

void __fastcall hooks::hooked_setmousecodestate(void* thisptr, void* edx, ButtonCode_t code, MouseCodeState_t state)
{
	static auto original_fn = inputinternal_hook->get_func_address <SetMouseCodeState_t> (92);

	if (input_shouldListen && state == BUTTON_PRESSED)
	{
		input_shouldListen = false;

		if (input_receivedKeyval)
			*input_receivedKeyval = code;
	}

	return original_fn(thisptr, code, state);
}


int __fastcall hooks::hk_sv_teamid_overhead_get_bool(const PVOID con_var, void* edx)
{
	static auto ofunc = sv_cheats->get_func_address<svc_get_bool_t>(13);

	static auto ret_to_process_input = util::FindSignature("client.dll", "85 C0 74 0D E8 ? ? ? ?");

	auto ret_addr = uintptr_t(_ReturnAddress());

	//if (!shonax_cfg->visuals.unlock_fix)
	//	return 0;

	if (ret_addr != ret_to_process_input)
		return ofunc(con_var);

	uintptr_t cur_fp, prev_fp;
	__asm
	{
		/// Get current frame pointer
		mov cur_fp, ebp
	}

	/// Go up stack frame
	prev_fp = *reinterpret_cast<uintptr_t*>(cur_fp);

	/// Set spectator mode to true
	*reinterpret_cast<bool*>(prev_fp - 0x192) = true;

	/// Increase distance
	static auto cl_teamid_overhead_maxdist_spec = m_cvar()->FindVar("cl_teamid_overhead_maxdist_spec");
	cl_teamid_overhead_maxdist_spec->SetValue(INT_MAX);

	/// Set prerequisite
	static auto cl_teamid_overhead_mode = m_cvar()->FindVar("cl_teamid_overhead_mode");
	cl_teamid_overhead_mode->SetValue(2);

	return 1;
}

__declspec (naked) void __stdcall hooks::TEFireBulletsPostDataUpdate_h(DataUpdateType_t updateType)
{
	__asm
	{
		push[esp + 4]
		push ecx
		call hooks::FireBullets_PostDataUpdate
		retn 4
	}
}


#include "../cheats/lagcompensation/animation_system.h"
void __stdcall hooks::FireBullets_PostDataUpdate(C_TEFireBullets* thisptr, DataUpdateType_t updateType)
{
	const auto local = g_ctx.local();
	static auto _FireBullets = effects->get_func_address<FireBullets_t>(7);

	if (!m_engine()->IsInGame() || !m_engine()->IsConnected())
		return _FireBullets(thisptr, updateType);

	if (/*config.rage.enabled &&*/ thisptr /* && shonax_cfg->visuals.show_on_shot_hitboxes*/)
	{
		int iPlayer = thisptr->m_iPlayer + 1;

		if (iPlayer < 64)
		{
			auto player = (player_t*)m_entitylist()->GetClientEntity(iPlayer);

			if (!player->is_enemy() || !player->is_alive() || player->m_bGunGameImmunity())
				return _FireBullets(thisptr, updateType);

			matrix3x4_t animation_matrix[128];
			matrix3x4_t setup_bones_matrix[128];

			auto animations = player_records[iPlayer];

			if (player->setup_bones_fixed(setup_bones_matrix, BONE_USED_BY_ANYTHING))
			{
				const auto model = player->GetModel();

				if (!model)
					return _FireBullets(thisptr, updateType);

				const auto hdr = m_modelinfo()->GetStudioModel(model);

				if (!hdr)
					return _FireBullets(thisptr, updateType);

				if (!animations.empty())
					return _FireBullets(thisptr, updateType);

				std::memcpy(animation_matrix, animations.front().matrixes_data.main, sizeof(animations.front().bone_count));

				const auto set = hdr->pHitboxSet(0);

				if (set)
				{
					for (auto i = 0; i < set->numhitboxes; i++)
					{
						const auto hitbox = set->pHitbox(i);

						if (!hitbox)
							continue;

						if (hitbox->radius == -1.0f)
						{
							const auto position = math::matrix_position(animation_matrix[hitbox->bone]);
							const auto position_actual = math::matrix_position(setup_bones_matrix[hitbox->bone]);

							const auto roation = math::angle_matrix(hitbox->rotation);

							auto transform = math::multiply_matrix(animation_matrix[hitbox->bone], roation);
							auto transform_actual = math::multiply_matrix(setup_bones_matrix[hitbox->bone], roation);

							const auto angles = math::matrix_angles(transform);
							const auto angles_actual = math::matrix_angles(transform_actual);

							m_debugoverlay()->AddBoxOverlay(position, hitbox->bbmin, hitbox->bbmax, angles, 255, 0, 0, 150, 0.8f);
							m_debugoverlay()->AddBoxOverlay(position_actual, hitbox->bbmin, hitbox->bbmax, angles_actual, 0, 0, 255, 150, 0.8f);
						}
						else
						{
							Vector min, max, min_actual, max_actual;

							math::vector_transform(hitbox->bbmin, animation_matrix[hitbox->bone], min);
							math::vector_transform(hitbox->bbmax, animation_matrix[hitbox->bone], max);

							math::vector_transform(hitbox->bbmin, setup_bones_matrix[hitbox->bone], min_actual);
							math::vector_transform(hitbox->bbmax, setup_bones_matrix[hitbox->bone], max_actual);

							m_debugoverlay()->AddCapsuleOverlay(min, max, hitbox->radius, 255, 0, 0, 150, 0.8f);
							m_debugoverlay()->AddCapsuleOverlay(min_actual, max_actual, hitbox->radius, 0, 0, 255, 150, 0.8f);
						}
					}
				}
			}
		}
	}

	_FireBullets(thisptr, updateType);

}
