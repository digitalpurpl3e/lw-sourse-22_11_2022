// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "configs.h"
#include "base64.h"
#include "..\includes.hpp"
#include "..\utils\util.hpp"
#include <shlobj.h>
#include <InventoryChanger/Inventory/Structs.h>
#include <InventoryChanger/Backend/BackendSimulator.h>
#include "../InventoryChanger/GameItems/Lookup.h"
#include "../InventoryChanger/Inventory/Item.h"
#include <InventoryChanger/BackendResponseHandler.h>
#include <InventoryChanger/fucking lazy.h>

std::unordered_map <std::string, float[4]> colors;

C_ConfigManager* cfg_manager = new C_ConfigManager();
Config g_cfg;

item_setting* get_by_definition_index(const int definition_index)
{
	auto it = std::find_if(std::begin(g_cfg.skins.skinChanger), std::end(g_cfg.skins.skinChanger), [definition_index](const item_setting& e)
	{
		return e.itemId == definition_index;
	});

	return it == std::end(g_cfg.skins.skinChanger) ? nullptr : &*it;
}

void C_ConfigManager::setup()
{


	setup_item(&g_cfg.font.wellplay, 0, crypt_str("font.wellplay"));

	setup_item(&g_cfg.ragebot.defensive_doubletap, false, crypt_str("Ragebot.defensive_doubletap"));


	setup_item(&g_cfg.esp.grenade_warning, false, crypt_str("Visuals.GrenadeWarning"));
	setup_item(&g_cfg.misc.server_hitbox, false, crypt_str("Misc.server_hitbox"));

	setup_item(&g_cfg.legitbot.enabled, false, crypt_str("Legitbot.enabled"));
	setup_item(&g_cfg.legitbot.friendly_fire, false, crypt_str("Legitbot.friendly_fire"));
	setup_item(&g_cfg.legitbot.autopistol, false, crypt_str("Legitbot.autopistol"));
	setup_item(&g_cfg.legitbot.autoscope, false, crypt_str("Legitbot.autoscope"));
	setup_item(&g_cfg.legitbot.unscope, false, crypt_str("Legitbot.unscope"));
	setup_item(&g_cfg.legitbot.sniper_in_zoom_only, false, crypt_str("Legitbot.sniper_in_zoom_only"));
	setup_item(&g_cfg.legitbot.do_if_local_flashed, false, crypt_str("Legitbot.do_if_local_flashed"));
	setup_item(&g_cfg.legitbot.do_if_local_in_air, false, crypt_str("Legitbot.do_if_local_in_air"));
	setup_item(&g_cfg.legitbot.do_if_enemy_in_smoke, false, crypt_str("Legitbot.do_if_enemy_in_smoke"));
	setup_item(&g_cfg.legitbot.autofire_delay, 0, crypt_str("Legitbot.autofire_delay"));
	setup_item(&g_cfg.legitbot.autofire_key, key_bind(HOLD), crypt_str("Legitbot.autofire_key"));
	setup_item(&g_cfg.legitbot.key, key_bind(HOLD), crypt_str("Legitbot.key"));

	for (auto i = 0; i < 5; i++)
	{
		setup_item(&g_cfg.legitbot.weapon[i].priority, 0, std::to_string(i) + crypt_str("Legitbot.rcs"));
		setup_item(&g_cfg.legitbot.weapon[i].auto_stop, false, std::to_string(i) + crypt_str("Legitbot.auto_stop"));
		setup_item(&g_cfg.legitbot.weapon[i].fov_type, 0, std::to_string(i) + crypt_str("Legitbot.fov_type"));
		setup_item(&g_cfg.legitbot.weapon[i].fov, 0.0f, std::to_string(i) + crypt_str("Legitbot.fov"));
		setup_item(&g_cfg.legitbot.weapon[i].smooth_type, 0, std::to_string(i) + crypt_str("Legitbot.smooth_type"));
		setup_item(&g_cfg.legitbot.weapon[i].smooth, 1.0f, std::to_string(i) + crypt_str("Legitbot.smooth"));
		setup_item(&g_cfg.legitbot.weapon[i].silent_fov, 0.0f, std::to_string(i) + crypt_str("Legitbot.silent_fov"));
		setup_item(&g_cfg.legitbot.weapon[i].rcs_type, 0, std::to_string(i) + crypt_str("Legitbot.rcs_type"));
		setup_item(&g_cfg.legitbot.weapon[i].rcs, 0.0f, std::to_string(i) + crypt_str("Legitbot.rcs"));
		setup_item(&g_cfg.legitbot.weapon[i].custom_rcs_smooth, 0.0f, std::to_string(i) + crypt_str("Legitbot.custom_rcs_smooth"));
		setup_item(&g_cfg.legitbot.weapon[i].custom_rcs_fov, 0.0f, std::to_string(i) + crypt_str("Legitbot.custom_rcs_fov"));
		setup_item(&g_cfg.legitbot.weapon[i].awall_dmg, 0, std::to_string(i) + crypt_str("Legitbot.awall_dmg"));
		setup_item(&g_cfg.legitbot.weapon[i].target_switch_delay, 0.0f, std::to_string(i) + crypt_str("Legitbot.target_switch_delay"));
		setup_item(&g_cfg.legitbot.weapon[i].autofire_hitchance, 0, std::to_string(i) + crypt_str("Legitbot.autofire_hitchance"));
	}

	setup_item(&g_cfg.ragebot.enable, false, crypt_str("Ragebot.enable"));
	setup_item(&g_cfg.ragebot.silent_aim, false, crypt_str("Ragebot.silent_aim"));
	setup_item(&g_cfg.ragebot.field_of_view, 1, crypt_str("Ragebot.fov"));
	setup_item(&g_cfg.ragebot.autowall, false, crypt_str("Ragebot.autowall"));
	setup_item(&g_cfg.ragebot.zeus_bot, false, crypt_str("Ragebot.zeus_bot"));
	setup_item(&g_cfg.ragebot.knife_bot, false, crypt_str("Ragebot.knife_bot"));
	setup_item(&g_cfg.ragebot.autoshoot, false, crypt_str("Ragebot.autoshoot"));
	setup_item(&g_cfg.ragebot.double_tap, false, crypt_str("Ragebot.double_tap"));
	setup_item(&g_cfg.ragebot.slow_teleport, false, crypt_str("Ragebot.slow_teleport"));
	setup_item(&g_cfg.ragebot.double_tap_key, key_bind(TOGGLE), crypt_str("Ragebot.double_tap_key"));
	setup_item(&g_cfg.ragebot.autoscope, false, crypt_str("Ragebot.autoscope"));
	setup_item(&g_cfg.ragebot.safe_point_key, key_bind(HOLD), crypt_str("Ragebot.safe_point_key"));
	setup_item(&g_cfg.ragebot.body_aim_key, key_bind(HOLD), crypt_str("Ragebot.body_aim_key"));
	setup_item(&g_cfg.ragebot.pitch_antiaim_correction, false, crypt_str("Ragebot.pitch_antiaim_correction"));

	for (auto i = 0; i < 8; i++)
	{
		setup_item(&g_cfg.ragebot.weapon[i].selection_type, 0, std::to_string(i) + crypt_str("Ragebot.selection_type"));
		setup_item(&g_cfg.ragebot.weapon[i].autostop, false, std::to_string(i) + crypt_str("Ragebot_automaticstop"));
		setup_item(&g_cfg.ragebot.weapon[i].autostop_modifiers, 6, std::to_string(i) + crypt_str("Ragebot.autostop_conditions"));
		setup_item(&g_cfg.ragebot.weapon[i].double_tap_hitchance, false, std::to_string(i) + crypt_str("Ragebot.double_tap_hitchance"));
		setup_item(&g_cfg.ragebot.weapon[i].double_tap_hitchance_amount, 1, std::to_string(i) + crypt_str("Ragebot.double_tap_hitchance_amount"));
		setup_item(&g_cfg.ragebot.weapon[i].hitchance, false, std::to_string(i) + crypt_str("Ragebot.hitchance"));
		setup_item(&g_cfg.ragebot.weapon[i].hitchance_amount, 1, std::to_string(i) + crypt_str("Ragebot.hitchance_amount"));
		setup_item(&g_cfg.ragebot.weapon[i].minimum_visible_damage, 1, std::to_string(i) + crypt_str("Ragebot.minimum_visible_damage"));
		setup_item(&g_cfg.ragebot.weapon[i].minimum_damage, 1, std::to_string(i) + crypt_str("Ragebot.minimum_damage"));
		setup_item(&g_cfg.ragebot.weapon[i].damage_override_key, key_bind(HOLD), std::to_string(i) + crypt_str("Ragebot.damage_override_key"));
		setup_item(&g_cfg.ragebot.weapon[i].minimum_override_damage, 1, std::to_string(i) + crypt_str("Ragebot.minimum_override_damage"));
		setup_item(&g_cfg.ragebot.weapon[i].hitboxes, 9, std::to_string(i) + crypt_str("Ragebot.hitboxes"));
		setup_item(&g_cfg.ragebot.weapon[i].static_point_scale, false, std::to_string(i) + crypt_str("Ragebot.static_point_scale"));
		setup_item(&g_cfg.ragebot.weapon[i].head_scale, 0.0f, std::to_string(i) + crypt_str("Ragebot.head_scale"));
		setup_item(&g_cfg.ragebot.weapon[i].body_scale, 0.0f, std::to_string(i) + crypt_str("Ragebot.body_scale"));
		setup_item(&g_cfg.ragebot.weapon[i].max_misses, false, std::to_string(i) + crypt_str("Ragebot.max_misses"));
		setup_item(&g_cfg.ragebot.weapon[i].max_misses_amount, 0, std::to_string(i) + crypt_str("Ragebot.max_misses_amount"));
		setup_item(&g_cfg.ragebot.weapon[i].prefer_safe_points, false, std::to_string(i) + crypt_str("Ragebot.prefer_safe_points"));
		setup_item(&g_cfg.ragebot.weapon[i].prefer_body_aim, false, std::to_string(i) + crypt_str("Ragebot.prefer_body_aim"));
	}

	setup_item(&g_cfg.antiaim.enable, false, crypt_str("Antiaim.enable"));
	setup_item(&g_cfg.antiaim.antiaim_type, 0, crypt_str("Antiaim.antiaim_type"));
	setup_item(&g_cfg.antiaim.hide_shots, false, crypt_str("Ragebot.hide_shots"));
	setup_item(&g_cfg.antiaim.hide_shots_key, key_bind(TOGGLE), crypt_str("Ragebot.hide_shots_key"));
	setup_item(&g_cfg.antiaim.desync, 0, crypt_str("Antiaim.desync"));
	setup_item(&g_cfg.antiaim.legit_lby_type, 0, crypt_str("Antiaim.legit_lby_type"));
	setup_item(&g_cfg.antiaim.lby_type, 0, crypt_str("Antiaim.lby_type"));
	setup_item(&g_cfg.antiaim.manual_back, key_bind(TOGGLE), crypt_str("Antiaim.manual_back"));
	setup_item(&g_cfg.antiaim.manual_left, key_bind(TOGGLE), crypt_str("Antiaim.manual_left"));
	setup_item(&g_cfg.antiaim.manual_right, key_bind(TOGGLE), crypt_str("Antiaim.manual_right"));
	setup_item(&g_cfg.antiaim.flip_desync, key_bind(TOGGLE), crypt_str("Antiaim.flip_desync"));
	setup_item(&g_cfg.antiaim.flip_indicator, false, crypt_str("Antiaim.flip_indicator"));
	setup_item(&g_cfg.antiaim.flip_indicator_color, Color(255, 255, 255), crypt_str("Antiaim.flip_indicator_color"));
	setup_item(&g_cfg.antiaim.fakelag, false, crypt_str("Antiaim.fake_lag"));
	setup_item(&g_cfg.antiaim.fakelag_type, 0, crypt_str("Antiaim.fake_lag_type"));
	setup_item(&g_cfg.antiaim.fakelag_enablers, 4, crypt_str("Antiaim.fake_lag_enablers"));
	setup_item(&g_cfg.antiaim.fakelag_amount, 1, crypt_str("Antiaim.fake_lag_limit"));
	setup_item(&g_cfg.antiaim.triggers_fakelag_amount, 1, crypt_str("Antiaim.triggers_fakelag_limit"));

	for (auto i = 0; i < 4; i++)
	{
		setup_item(&g_cfg.antiaim.type[i].pitch, 0, std::to_string(i) + crypt_str("Antiaim.pitch"));
		setup_item(&g_cfg.antiaim.type[i].base_angle, 0, std::to_string(i) + crypt_str("Antiaim.base_angle"));
		setup_item(&g_cfg.antiaim.type[i].yaw, 0, std::to_string(i) + crypt_str("Antiaim.yaw"));
		setup_item(&g_cfg.antiaim.type[i].range, 1, std::to_string(i) + crypt_str("Antiaim.range"));
		setup_item(&g_cfg.antiaim.type[i].speed, 1, std::to_string(i) + crypt_str("Antiaim.speed"));
		setup_item(&g_cfg.antiaim.type[i].desync, 0, std::to_string(i) + crypt_str("Antiaim.desync"));
		setup_item(&g_cfg.antiaim.type[i].desync_range, 60, std::to_string(i) + crypt_str("Antiaim.desync_range"));
		setup_item(&g_cfg.antiaim.type[i].inverted_desync_range, 60, std::to_string(i) + crypt_str("Antiaim.inverted_desync_range"));
		setup_item(&g_cfg.antiaim.type[i].body_lean, 0, std::to_string(i) + crypt_str("Antiaim.body_lean"));
		setup_item(&g_cfg.antiaim.type[i].inverted_body_lean, 0, std::to_string(i) + crypt_str("Antiaim.inverted_body_lean"));
	}

	setup_item(&g_cfg.radar.render_local, false, crypt_str("Player.render_local"));
	setup_item(&g_cfg.radar.render_enemy, false, crypt_str("Player.render_enemy"));
	setup_item(&g_cfg.radar.render_team, false, crypt_str("Player.render_team"));
	setup_item(&g_cfg.radar.render_planted_c4, false, crypt_str("Player.render_planted_c4"));
	setup_item(&g_cfg.radar.render_dropped_c4, false, crypt_str("Player.render_dropped_c4"));
	setup_item(&g_cfg.radar.render_health, false, crypt_str("Player.render_health"));

	setup_item(&g_cfg.player.enable, false, crypt_str("Player.enable"));
	setup_item(&g_cfg.player.arrows_color, Color(255, 255, 255), crypt_str("Player.arrows_color"));
	setup_item(&g_cfg.player.arrows, false, crypt_str("Player.arrows"));
	setup_item(&g_cfg.player.distance, 1, crypt_str("Player.arrows_distance"));
	setup_item(&g_cfg.player.size, 1, crypt_str("Player.arrows_size"));
	setup_item(&g_cfg.player.show_multi_points, false, crypt_str("Player.show_multi_points"));
	setup_item(&g_cfg.player.show_multi_points_color, Color(255, 255, 255), crypt_str("Player.show_multi_points_color"));
	setup_item(&g_cfg.player.lag_hitbox, false, crypt_str("Player.lag_hitbox"));
	setup_item(&g_cfg.player.lag_hitbox_color, Color(255, 255, 255), crypt_str("Player.lag_hitbox_color"));
	setup_item(&g_cfg.player.player_model_t, 0, crypt_str("Esp.player_model_t"));
	setup_item(&g_cfg.player.player_model_ct, 0, crypt_str("Esp.player_model_ct"));
	setup_item(&g_cfg.player.local_chams_type, 0, crypt_str("Player.local_chams_type"));
	setup_item(&g_cfg.player.fake_chams_enable, false, crypt_str("Player.fake_chams_enable"));
	setup_item(&g_cfg.player.visualize_lag, false, crypt_str("Player.vizualize_lag"));
	setup_item(&g_cfg.player.layered, false, crypt_str("Player.layered"));
	setup_item(&g_cfg.player.fake_chams_color, Color(255, 255, 255), crypt_str("Player.fake_chams_color"));
	setup_item(&g_cfg.player.fake_chams_type, 0, crypt_str("Player.fake_chams_type"));
	setup_item(&g_cfg.player.fake_double_material, false, crypt_str("Player.fake_double_material"));
	setup_item(&g_cfg.player.fake_double_material_color, Color(255, 255, 255), crypt_str("Player.fake_double_material_color"));
	setup_item(&g_cfg.player.fake_animated_material, false, crypt_str("Player.fake_animated_material"));
	setup_item(&g_cfg.player.fake_animated_material_color, Color(255, 255, 255), crypt_str("Player.fake_animated_material_color"));
	setup_item(&g_cfg.player.backtrack_chams, false, crypt_str("Player.backtrack_chams"));
	setup_item(&g_cfg.player.backtrack_chams_material, 0, crypt_str("Player.backtrack_chams_material"));
	setup_item(&g_cfg.player.backtrack_chams_color, Color(255, 255, 255), crypt_str("Player.backtrack_chams_color"));
	setup_item(&g_cfg.player.transparency_in_scope, false, crypt_str("Player.transparency_in_scope"));
	setup_item(&g_cfg.player.transparency_in_scope_amount, 1.0f, crypt_str("Player.transparency_in_scope_amount"));

	for (auto i = 0; i < 3; i++)
	{
		setup_item(&g_cfg.player.type[i].box, false, std::to_string(i) + crypt_str("Player.box"));
		setup_item(&g_cfg.player.type[i].box_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.box_color"));
		setup_item(&g_cfg.player.type[i].name, false, std::to_string(i) + crypt_str("Player.name"));
		setup_item(&g_cfg.player.type[i].name_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.name_color"));
		setup_item(&g_cfg.player.type[i].health, false, std::to_string(i) + crypt_str("Player.health"));
		setup_item(&g_cfg.player.type[i].custom_health_color, false, std::to_string(i) + crypt_str("Player.custom_health_color"));
		setup_item(&g_cfg.player.type[i].health_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.health_color"));
		setup_item(&g_cfg.player.type[i].weapon, 2, std::to_string(i) + crypt_str("Player.weapon"));
		setup_item(&g_cfg.player.type[i].weapon_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.weapon_bar_color"));
		setup_item(&g_cfg.player.type[i].skeleton, false, std::to_string(i) + crypt_str("Player.skeleton"));
		setup_item(&g_cfg.player.type[i].skeleton_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.skeleton_color"));
		setup_item(&g_cfg.player.type[i].ammo, false, std::to_string(i) + crypt_str("Player.ammo"));
		setup_item(&g_cfg.player.type[i].ammobar_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.ammobar_color"));
		setup_item(&g_cfg.player.type[i].snap_lines, false, std::to_string(i) + crypt_str("Player.snap_lines"));
		setup_item(&g_cfg.player.type[i].snap_lines_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.snap_lines_color"));
		setup_item(&g_cfg.player.type[i].footsteps, false, std::to_string(i) + crypt_str("Player.footsteps"));
		setup_item(&g_cfg.player.type[i].footsteps_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.footsteps_color"));
		setup_item(&g_cfg.player.type[i].thickness, 0, std::to_string(i) + crypt_str("Player.thickness"));
		setup_item(&g_cfg.player.type[i].radius, 0, std::to_string(i) + crypt_str("Player.radius"));
		setup_item(&g_cfg.player.type[i].glow, false, std::to_string(i) + crypt_str("Player.glow"));
		setup_item(&g_cfg.player.type[i].glow_type, 0, std::to_string(i) + crypt_str("Player.glow_type"));
		setup_item(&g_cfg.player.type[i].glow_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.glow_color"));
		setup_item(&g_cfg.player.type[i].chams, 2, std::to_string(i) + crypt_str("Player.chams"));
		setup_item(&g_cfg.player.type[i].chams_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.chams_color"));
		setup_item(&g_cfg.player.type[i].xqz_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.xqz_color"));
		setup_item(&g_cfg.player.type[i].chams_type, 0, std::to_string(i) + crypt_str("Player.chams_type"));
		setup_item(&g_cfg.player.type[i].double_material, false, std::to_string(i) + crypt_str("Player.double_material"));
		setup_item(&g_cfg.player.type[i].double_material_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.double_material_color"));
		setup_item(&g_cfg.player.type[i].animated_material, false, std::to_string(i) + crypt_str("Player.animated_material"));
		setup_item(&g_cfg.player.type[i].animated_material_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.animated_material_color"));
		setup_item(&g_cfg.player.type[i].ragdoll_chams, false, std::to_string(i) + crypt_str("Player.ragdoll_chams"));
		setup_item(&g_cfg.player.type[i].ragdoll_chams_material, 0, std::to_string(i) + crypt_str("Player.ragdoll_chams_material"));
		setup_item(&g_cfg.player.type[i].ragdoll_chams_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.ragdoll_chams_color"));
		setup_item(&g_cfg.player.type[i].flags, 8, std::to_string(i) + crypt_str("Player.esp_flags"));
	}

	setup_item(&g_cfg.esp.indicators, 8, crypt_str("Esp.rage_indicators"));
	setup_item(&g_cfg.esp.removals, 8, crypt_str("Esp.world_removals"));
	setup_item(&g_cfg.esp.fix_zoom_sensivity, false, crypt_str("Esp.fix_zoom_sensivity"));
	setup_item(&g_cfg.misc.thirdperson_toggle, key_bind(TOGGLE), crypt_str("Misc.thirdperson_toggle"));
	setup_item(&g_cfg.misc.thirdperson_when_spectating, false, crypt_str("Misc.thirdperson_when_spectating"));
	setup_item(&g_cfg.misc.thirdperson_distance, 100, crypt_str("Misc.thirdperson_distance"));
	setup_item(&g_cfg.esp.grenade_prediction, false, crypt_str("Esp.grenade_prediction"));
	setup_item(&g_cfg.esp.on_click , false, crypt_str("Esp.on_click"));
	setup_item(&g_cfg.esp.grenade_prediction_color, Color(255, 255, 255), crypt_str("Esp.grenade_prediction_color"));
	setup_item(&g_cfg.esp.grenade_prediction_tracer_color, Color(255, 255, 255), crypt_str("Esp.grenade_prediction_tracer_color"));
	setup_item(&g_cfg.esp.projectiles, false, crypt_str("Esp.projectiles"));
	setup_item(&g_cfg.esp.projectiles_color, Color(255, 255, 255), crypt_str("Esp.projectiles_color"));
	setup_item(&g_cfg.esp.molotov_timer, false, crypt_str("Esp.molotov_timer"));
	setup_item(&g_cfg.esp.molotov_timer_color, Color(255, 255, 255), crypt_str("Esp.molotov_timer_color"));
	setup_item(&g_cfg.esp.smoke_timer, false, crypt_str("Esp.smoke_timer"));
	setup_item(&g_cfg.esp.smoke_timer_color, Color(255, 255, 255), crypt_str("Esp.smoke_timer_color"));
	setup_item(&g_cfg.esp.bomb_timer, false, crypt_str("Esp.bomb_timer"));
	setup_item(&g_cfg.esp.bright, false, crypt_str("Esp.bright"));
	setup_item(&g_cfg.esp.nightmode, false, crypt_str("Esp.nightmode"));
	setup_item(&g_cfg.esp.world_color, Color(255, 255, 255), crypt_str("Esp.world_color"));
	setup_item(&g_cfg.esp.props_color, Color(255, 255, 255), crypt_str("Esp.props_color"));
	setup_item(&g_cfg.esp.skybox, 0, crypt_str("Esp.skybox"));
	setup_item(&g_cfg.esp.custom_skybox, crypt_str(""), crypt_str("Esp.custom_skybox"));
	setup_item(&g_cfg.esp.skybox_color, Color(255, 255, 255), crypt_str("Esp.skybox_color"));
	setup_item(&g_cfg.esp.client_bullet_impacts, false, crypt_str("Esp.client_bullet_impacts"));
	setup_item(&g_cfg.esp.client_bullet_impacts_color, Color(255, 255, 255), crypt_str("Esp.client_bullet_impacts_color"));
	setup_item(&g_cfg.esp.server_bullet_impacts, false, crypt_str("Esp.server_bullet_impacts"));
	setup_item(&g_cfg.esp.server_bullet_impacts_color, Color(255, 255, 255), crypt_str("Esp.server_bullet_impacts_color"));
	setup_item(&g_cfg.esp.bullet_tracer, false, crypt_str("Esp.bullet_tracer"));
	setup_item(&g_cfg.esp.bullet_tracer_color, Color(255, 255, 255), crypt_str("Esp.bullet_tracer_color"));
	setup_item(&g_cfg.esp.enemy_bullet_tracer, false, crypt_str("Esp.enemy_bullet_tracer"));
	setup_item(&g_cfg.esp.enemy_bullet_tracer_color, Color(255, 255, 255), crypt_str("Esp.enemy_bullet_tracer_color"));
	setup_item(&g_cfg.esp.preserve_killfeed, false, crypt_str("Esp.preserve_killfeed"));
	setup_item(&g_cfg.esp.hitmarker, 2, crypt_str("Esp.hit_marker"));
	setup_item(&g_cfg.esp.hitsound, 0, crypt_str("Esp.hitsound"));
	setup_item(&g_cfg.esp.killsound, false, crypt_str("Esp.killsound"));
	setup_item(&g_cfg.esp.damage_marker, false, crypt_str("Esp.damage_marker"));
	setup_item(&g_cfg.esp.kill_effect, false, crypt_str("Esp.kill_effect"));
	setup_item(&g_cfg.esp.kill_effect_duration, 3.0f, crypt_str("Esp.kill_effect_duration"));
	setup_item(&g_cfg.esp.fov, 0, crypt_str("Esp.fov"));
	setup_item(&g_cfg.esp.viewmodel_fov, 0, crypt_str("Esp.viewmodel_fov"));
	setup_item(&g_cfg.esp.viewmodel_x, 0, crypt_str("Esp.viewmodel_x"));
	setup_item(&g_cfg.esp.viewmodel_y, 0, crypt_str("Esp.viewmodel_y"));
	setup_item(&g_cfg.esp.viewmodel_z, 0, crypt_str("Esp.viewmodel_z"));
	setup_item(&g_cfg.esp.viewmodel_roll, 0, crypt_str("Esp.viewmodel_roll"));
	setup_item(&g_cfg.esp.arms_chams, false, crypt_str("Esp.arms_chams"));
	setup_item(&g_cfg.esp.arms_chams_type, 0, crypt_str("Esp.arms_chams_type"));
	setup_item(&g_cfg.esp.arms_chams_color, Color(255, 255, 255), crypt_str("Esp.arms_chams_color"));
	setup_item(&g_cfg.esp.arms_double_material, false, crypt_str("Esp.arms_double_material"));
	setup_item(&g_cfg.esp.arms_double_material_color, Color(255, 255, 255), crypt_str("Esp.arms_double_material_color"));
	setup_item(&g_cfg.esp.arms_animated_material, false, crypt_str("Esp.arms_animated_material"));
	setup_item(&g_cfg.esp.arms_animated_material_color, Color(255, 255, 255), crypt_str("Esp.arms_animated_material_color"));
	setup_item(&g_cfg.esp.weapon_chams, false, crypt_str("Esp.weapon_chams"));
	setup_item(&g_cfg.esp.weapon_chams_type, 0, crypt_str("Esp.weapon_chams_type"));
	setup_item(&g_cfg.esp.weapon_chams_color, Color(255, 255, 255), crypt_str("Esp.weapon_chams_color"));
	setup_item(&g_cfg.esp.weapon_double_material, false, crypt_str("Esp.weapon_double_material"));
	setup_item(&g_cfg.esp.weapon_double_material_color, Color(255, 255, 255), crypt_str("Esp.weapon_double_material_color"));
	setup_item(&g_cfg.esp.weapon_animated_material, false, crypt_str("Esp.weapon_animated_material"));
	setup_item(&g_cfg.esp.weapon_animated_material_color, Color(255, 255, 255), crypt_str("Esp.weapon_animated_material_color"));
	setup_item(&g_cfg.esp.taser_range, false, crypt_str("Esp.taser_range"));
	setup_item(&g_cfg.esp.show_spread, false, crypt_str("Esp.show_spread"));
	setup_item(&g_cfg.esp.show_spread_color, Color(255, 255, 255), crypt_str("Esp.show_spread_color"));
	setup_item(&g_cfg.esp.penetration_reticle, false, crypt_str("Esp.penetration_reticle"));
	setup_item(&g_cfg.esp.world_modulation, false, crypt_str("Esp.world_modulation"));
	setup_item(&g_cfg.esp.rain, false, crypt_str("Esp.rain"));
	setup_item(&g_cfg.esp.bloom, 0.0f, crypt_str("Esp.bloom"));
	setup_item(&g_cfg.esp.exposure, 0.0f, crypt_str("Esp.exposure"));
	setup_item(&g_cfg.esp.ambient, 0.0f, crypt_str("Esp.ambient"));
	setup_item(&g_cfg.esp.fog, false, crypt_str("Esp.fog"));
	setup_item(&g_cfg.esp.fog_distance, 0, crypt_str("Esp.fog_distance"));
	setup_item(&g_cfg.esp.fog_density, 0, crypt_str("Esp.fog_density"));
	setup_item(&g_cfg.esp.fog_color, Color(255, 255, 255), crypt_str("Esp.fog_color"));
	setup_item(&g_cfg.esp.weapon, 6, crypt_str("Esp.dropped_weapon"));
	setup_item(&g_cfg.esp.box_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapon_box_color"));
	setup_item(&g_cfg.esp.weapon_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapon_color"));
	setup_item(&g_cfg.esp.weapon_glow_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapon_glow_color"));
	setup_item(&g_cfg.esp.weapon_ammo_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapon_ammo_color"));
	setup_item(&g_cfg.esp.grenade_esp, 4, crypt_str("Esp.grenade_esp"));
	setup_item(&g_cfg.esp.grenade_glow_color, Color(255, 255, 255), crypt_str("Esp.grenade_glow_color"));
	setup_item(&g_cfg.esp.grenade_box_color, Color(255, 255, 255), crypt_str("Esp.grenade_box_color"));

	setup_item(&g_cfg.misc.spectators_list, false, crypt_str("Misc.spectators_list"));
	setup_item(&g_cfg.misc.ingame_radar, false, crypt_str("Misc.ingame_radar"));
	setup_item(&g_cfg.misc.ragdolls, false, crypt_str("Misc.ragdolls"));
	setup_item(&g_cfg.misc.bunnyhop, false, crypt_str("Misc.autohop"));
	setup_item(&g_cfg.misc.airstrafe, 0, crypt_str("Misc.airstrafe"));
	setup_item(&g_cfg.misc.crouch_in_air, false, crypt_str("Misc.crouch_in_air"));
	setup_item(&g_cfg.misc.automatic_peek, key_bind(HOLD), crypt_str("Misc.automatic_peek"));
	setup_item(&g_cfg.misc.edge_jump, key_bind(HOLD), crypt_str("Misc.edge_jump"));
	setup_item(&g_cfg.misc.noduck, false, crypt_str("Misc.noduck"));
	setup_item(&g_cfg.misc.fakeduck_key, key_bind(HOLD), crypt_str("Misc.fakeduck_key"));
	setup_item(&g_cfg.misc.fast_stop, false, crypt_str("Misc.fast_stop"));
	setup_item(&g_cfg.misc.slidewalk, false, crypt_str("Misc.slidewalk"));
	setup_item(&g_cfg.misc.slowwalk_key, key_bind(HOLD), crypt_str("Misc.slowwalk_key"));
	setup_item(&g_cfg.misc.chat, false, crypt_str("Misc.chat"));
	setup_item(&g_cfg.misc.log_output, 2, crypt_str("Misc.log_output"));
	setup_item(&g_cfg.misc.events_to_log, 3, crypt_str("Misc.events_to_log"));
	setup_item(&g_cfg.misc.show_default_log, false, crypt_str("Misc.show_default_log"));
	setup_item(&g_cfg.misc.log_color, Color(255, 255, 255), crypt_str("Misc.log_color"));
	setup_item(&g_cfg.misc.inventory_access, false, crypt_str("Misc.inventory_access"));
	setup_item(&g_cfg.misc.rank_reveal, false, crypt_str("Misc.rank_reveal"));
	setup_item(&g_cfg.misc.clantag_spammer, false, crypt_str("Misc.clantag_spammer"));
	setup_item(&g_cfg.misc.aspect_ratio, false, crypt_str("Misc.aspect_ratio"));
	setup_item(&g_cfg.misc.aspect_ratio_amount, 1.0f, crypt_str("Misc.aspect_ratio_amount"));
	setup_item(&g_cfg.misc.anti_screenshot, false, crypt_str("Misc.anti_screenshot"));
	setup_item(&g_cfg.misc.anti_untrusted, true, crypt_str("Misc.antiuntrusted"));
	setup_item(&g_cfg.misc.buybot_enable, false, crypt_str("Misc.buybot"));
	setup_item(&g_cfg.misc.buybot1, 0, crypt_str("Player.buybot1"));
	setup_item(&g_cfg.misc.buybot2, 0, crypt_str("Player.buybot2"));
	setup_item(&g_cfg.misc.buybot3, 4, crypt_str("Misc.buybot3"));

	setup_item(&g_cfg.skins.rare_animations, false, crypt_str("Skins.rare_animations"));

	for (auto i = 0; i < g_cfg.skins.skinChanger.size(); i++)
	{
		setup_item(&g_cfg.skins.skinChanger.at(i).definition_override_index, 0, std::to_string(i) + crypt_str("Skins.definition_override_index")); //-V807
		setup_item(&g_cfg.skins.skinChanger.at(i).definition_override_vector_index, 0, std::to_string(i) + crypt_str("Skins.definition_override_vector_index"));
		setup_item(&g_cfg.skins.skinChanger.at(i).entity_quality_vector_index, 0, std::to_string(i) + crypt_str("Skins.entity_quality_vector_index"));
		setup_item(&g_cfg.skins.skinChanger.at(i).itemId, 0, std::to_string(i) + crypt_str("Skins.itemId"));
		setup_item(&g_cfg.skins.skinChanger.at(i).itemIdIndex, 0, std::to_string(i) + crypt_str("Skins.itemIdIndex"));
		setup_item(&g_cfg.skins.skinChanger.at(i).paintKit, 0, std::to_string(i) + crypt_str("Skins.paintKit"));
		setup_item(&g_cfg.skins.skinChanger.at(i).paint_kit_vector_index, 0, std::to_string(i) + crypt_str("Skins.paint_kit_vector_index"));
		setup_item(&g_cfg.skins.skinChanger.at(i).quality, 0, std::to_string(i) + crypt_str("Skins.quality"));
		setup_item(&g_cfg.skins.skinChanger.at(i).seed, 0, std::to_string(i) + crypt_str("Skins.seed"));
		setup_item(&g_cfg.skins.skinChanger.at(i).stat_trak, 0, std::to_string(i) + crypt_str("Skins.stat_trak"));
		setup_item(&g_cfg.skins.skinChanger.at(i).wear, 0.0f, std::to_string(i) + crypt_str("Skins.wear"));
		setup_item(&g_cfg.skins.custom_name_tag[i], crypt_str(""), std::to_string(i) + crypt_str("Skins.custom_name_tag"));
	}

	setup_item(&g_cfg.menu.menu_theme, Color(126, 131, 219), crypt_str("Menu.menu_color"));
	setup_item(&g_cfg.menu.watermark, false, crypt_str("Menu.watermark"));

	setup_item(&g_cfg.scripts.scripts, crypt_str("Scripts.loaded"));
}

void C_ConfigManager::add_item(void * pointer, const char * name, const std::string& type) {
	items.push_back(new C_ConfigItem(std::string(name), pointer, type));
}

void C_ConfigManager::setup_item(int * pointer, int value, const std::string& name) 
{
	add_item(pointer, name.c_str(), crypt_str("int"));
	*pointer = value;
}

void C_ConfigManager::setup_item(bool * pointer, bool value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("bool"));
	*pointer = value;
}

void C_ConfigManager::setup_item(float * pointer, float value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("float"));
	*pointer = value;
}

void C_ConfigManager::setup_item(key_bind* pointer, key_bind value, const std::string& name) //-V813
{
	add_item(pointer, name.c_str(), crypt_str("KeyBind"));
	*pointer = value;
}

void C_ConfigManager::setup_item(Color* pointer, Color value, const std::string& name)
{
	colors[name][0] = (float)value.r() / 255.0f;
	colors[name][1] = (float)value.g() / 255.0f;
	colors[name][2] = (float)value.b() / 255.0f;
	colors[name][3] = (float)value.a() / 255.0f;

	add_item(pointer, name.c_str(), crypt_str("Color"));
	*pointer = value;
}

void C_ConfigManager::setup_item(std::vector< int > * pointer, int size, const std::string& name) 
{
	add_item(pointer, name.c_str(), crypt_str("vector<int>"));
	pointer->clear();

	for (int i = 0; i < size; i++)
		pointer->push_back(FALSE);
}

void C_ConfigManager::setup_item(std::vector< std::string >* pointer, const std::string& name)
{ 
	add_item(pointer, name.c_str(), crypt_str("vector<string>"));
}

void C_ConfigManager::setup_item(std::string * pointer, const std::string& value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("string"));
	*pointer = value; //-V820
}


namespace inventory
{

	Glove gloveFromJson(const json& j)
	{
		Glove glove;

		if (const auto wear = j.find("Wear"); wear != j.end() && wear->is_number_float())
			glove.wear = wear->get<float>();

		if (const auto seed = j.find("Seed"); seed != j.end() && seed->is_number_integer())
			glove.seed = seed->get<int>();

		return glove;
	}

	SouvenirPackage souvenirPackageFromJson(const json& j)
	{
		SouvenirPackage souvenirPackage;

		if (j.contains("Tournament Stage")) {
			if (const auto& tournamentStage = j["Tournament Stage"]; tournamentStage.is_number_unsigned())
				souvenirPackage.tournamentStage = tournamentStage;
		}

		if (j.contains("Tournament Team 1")) {
			if (const auto& tournamentTeam1 = j["Tournament Team 1"]; tournamentTeam1.is_number_unsigned())
				souvenirPackage.tournamentTeam1 = tournamentTeam1;
		}

		if (j.contains("Tournament Team 2")) {
			if (const auto& tournamentTeam2 = j["Tournament Team 2"]; tournamentTeam2.is_number_unsigned())
				souvenirPackage.tournamentTeam2 = tournamentTeam2;
		}

		if (j.contains("Tournament Player")) {
			if (const auto& tournamentPlayer = j["Tournament Player"]; tournamentPlayer.is_number_unsigned())
				souvenirPackage.proPlayer = tournamentPlayer;
		}

		return souvenirPackage;
	}

	Music musicFromJson(const json& j)
	{
		Music music;

		if (j.contains("StatTrak")) {
			if (const auto& statTrak = j["StatTrak"]; statTrak.is_number_integer() && statTrak > -1)
				music.statTrak = statTrak;
		}

		return music;
	}

	ServiceMedal serviceMedalFromJson(const json& j)
	{
		ServiceMedal serviceMedal;

		if (j.contains("Issue Date Timestamp")) {
			if (const auto& issueDateTimestamp = j["Issue Date Timestamp"]; issueDateTimestamp.is_number_unsigned())
				serviceMedal.issueDateTimestamp = issueDateTimestamp;
		}

		return serviceMedal;
	}

	Graffiti graffitiFromJson(const json& j)
	{
		Graffiti graffiti;

		if (j.contains("Uses Left")) {
			if (const auto& usesLeft = j["Uses Left"]; usesLeft.is_number_integer())
				graffiti.usesLeft = usesLeft;
		}

		return graffiti;
	}

	std::array<Skin::Sticker, 5> skinStickersFromJson(const json& j)
	{
		std::array<Skin::Sticker, 5> skinStickers;

		if (!j.contains("Stickers"))
			return skinStickers;

		const auto& stickers = j["Stickers"];
		if (!stickers.is_array())
			return skinStickers;

		for (const auto& sticker : stickers) {
			if (!sticker.is_object())
				continue;

			if (!sticker.contains("Sticker ID") || !sticker["Sticker ID"].is_number_integer())
				continue;

			if (!sticker.contains("Slot") || !sticker["Slot"].is_number_integer())
				continue;

			const int stickerID = sticker["Sticker ID"];
			if (stickerID == 0)
				continue;

			const std::size_t slot = sticker["Slot"];
			if (slot >= skinStickers.size())
				continue;

			skinStickers[slot].stickerID = stickerID;

			if (sticker.contains("Wear") && sticker["Wear"].is_number_float())
				skinStickers[slot].wear = sticker["Wear"];
		}

		return skinStickers;
	}

	Skin skinFromJson(const json& j)
	{
		Skin skin;

		if (j.contains("Tournament ID")) {
			if (const auto& tournamentID = j["Tournament ID"]; tournamentID.is_number_unsigned())
				skin.tournamentID = tournamentID;
		}

		if (j.contains("Wear")) {
			if (const auto& wear = j["Wear"]; wear.is_number_float())
				skin.wear = wear;
		}

		if (j.contains("Seed")) {
			if (const auto& seed = j["Seed"]; seed.is_number_integer())
				skin.seed = seed;
		}

		if (j.contains("StatTrak")) {
			if (const auto& statTrak = j["StatTrak"]; statTrak.is_number_integer())
				skin.statTrak = statTrak;
		}

		if (j.contains("Name Tag")) {
			if (const auto& nameTag = j["Name Tag"]; nameTag.is_string())
				skin.nameTag = nameTag;
		}

		if (j.contains("Tournament Stage")) {
			if (const auto& tournamentStage = j["Tournament Stage"]; tournamentStage.is_number_unsigned())
				skin.tournamentStage = tournamentStage;
		}

		if (j.contains("Tournament Team 1")) {
			if (const auto& tournamentTeam1 = j["Tournament Team 1"]; tournamentTeam1.is_number_unsigned())
				skin.tournamentTeam1 = tournamentTeam1;
		}

		if (j.contains("Tournament Team 2")) {
			if (const auto& tournamentTeam2 = j["Tournament Team 2"]; tournamentTeam2.is_number_unsigned())
				skin.tournamentTeam2 = tournamentTeam2;
		}

		if (j.contains("Tournament Player")) {
			if (const auto& tournamentPlayer = j["Tournament Player"]; tournamentPlayer.is_number_unsigned())
				skin.proPlayer = tournamentPlayer;
		}

		skin.stickers = inventory::skinStickersFromJson(j);
		return skin;
	}

}


[[nodiscard]] json toJson(const inventory::Skin& skin)
{
	json j;

	if (skin.tournamentID != 0)
		j["Tournament ID"] = skin.tournamentID;

	j["Wear"] = skin.wear;
	j["Seed"] = skin.seed;
	if (skin.statTrak > -1)
		j["StatTrak"] = skin.statTrak;

	if (!skin.nameTag.empty())
		j["Name Tag"] = skin.nameTag;

	auto& stickers = j["Stickers"];
	for (std::size_t i = 0; i < skin.stickers.size(); ++i) {
		const auto& sticker = skin.stickers[i];
		if (sticker.stickerID == 0)
			continue;

		json stickerConfig;
		stickerConfig["Sticker ID"] = sticker.stickerID;
		stickerConfig["Wear"] = sticker.wear;
		stickerConfig["Slot"] = i;
		stickers.push_back(std::move(stickerConfig));
	}

	if (skin.tournamentStage != TournamentStage{}) {
		j["Tournament Stage"] = skin.tournamentStage;
		j["Tournament Team 1"] = skin.tournamentTeam1;
		j["Tournament Team 2"] = skin.tournamentTeam2;
		j["Tournament Player"] = skin.proPlayer;
	}

	return j;
}

json InventoryChangertoJson() noexcept
{
	json j;

	const auto& backend = inventory_changer::backend::BackendSimulator::instance();
	const auto& loadout = backend.getLoadout();
	const auto& inventory = backend.getInventory();
	auto& items = j["Items"];
	for (auto itemIt = inventory.begin(); itemIt != inventory.end(); ++itemIt) {
		json itemConfig;

		if (const auto slotCT = loadout.getItemEquippedSlotCT(itemIt); slotCT.has_value()) {
			itemConfig["Equipped Slot"] = *slotCT;
			itemConfig["Equipped"].push_back("CT");
		}
		if (const auto slotTT = loadout.getItemEquippedSlotTT(itemIt); slotTT.has_value()) {
			itemConfig["Equipped Slot"] = *slotTT;
			itemConfig["Equipped"].push_back("TT");
		}
		if (const auto slotNoTeam = loadout.getItemEquippedSlotNoTeam(itemIt); slotNoTeam.has_value()) {
			itemConfig["Equipped Slot"] = *slotNoTeam;
			itemConfig["Equipped"].push_back("NOTEAM");
		}

		const auto& item = *itemIt;
		const auto& gameItem = item.gameItem();
		itemConfig["Weapon ID"] = gameItem.getWeaponID();
		itemConfig["Item Name"] = StaticData::getWeaponName(gameItem.getWeaponID());

		if (gameItem.isSticker()) {
			itemConfig["Sticker ID"] = StaticData::lookup().getStorage().getStickerKit(gameItem).id;
		}
		else if (gameItem.isGloves()) {
			const auto& staticData = StaticData::lookup().getStorage().getPaintKit(gameItem);
			itemConfig["Paint Kit"] = staticData.id;
			itemConfig["Paint Kit Name"] = staticData.name.forDisplay;

			if (const auto glove = item.get<inventory::Glove>()) {
				itemConfig["Wear"] = glove->wear;
				itemConfig["Seed"] = glove->seed;
			}
		}
		else if (gameItem.isSkin()) {
			const auto& staticData = StaticData::lookup().getStorage().getPaintKit(gameItem);
			itemConfig["Paint Kit"] = staticData.id;
			itemConfig["Paint Kit Name"] = staticData.name.forDisplay;

			if (const auto skin = item.get<inventory::Skin>())
				itemConfig.update(::toJson(*skin));

		}
		else if (gameItem.isMusic()) {
			itemConfig["Music ID"] = StaticData::lookup().getStorage().getMusicKit(gameItem).id;
			if (const auto music = item.get<inventory::Music>(); music && music->statTrak > -1)
				itemConfig["StatTrak"] = music->statTrak;
		}
		else if (gameItem.isPatch()) {
			itemConfig["Patch ID"] = StaticData::lookup().getStorage().getPatch(gameItem).id;
		}
		else if (gameItem.isGraffiti()) {
			itemConfig["Graffiti ID"] = StaticData::lookup().getStorage().getGraffitiKit(gameItem).id;
			if (const auto graffiti = item.get<inventory::Graffiti>(); graffiti && graffiti->usesLeft >= 0) {
				itemConfig["Uses Left"] = graffiti->usesLeft;
				itemConfig["Item Name"] = StaticData::getWeaponName(WeaponId::Graffiti);
			}
		}
		else if (gameItem.isAgent()) {
			if (const auto agent = item.get<inventory::Agent>()) {
				auto& stickers = itemConfig["Patches"];
				for (std::size_t i = 0; i < agent->patches.size(); ++i) {
					const auto& patch = agent->patches[i];
					if (patch.patchID == 0)
						continue;

					json patchConfig;
					patchConfig["Patch ID"] = patch.patchID;
					patchConfig["Slot"] = i;
					stickers.push_back(std::move(patchConfig));
				}
			}
		}
		else if (gameItem.isServiceMedal()) {
			if (const auto serviceMedal = item.get<inventory::ServiceMedal>(); serviceMedal && serviceMedal->issueDateTimestamp != 0)
				itemConfig["Issue Date Timestamp"] = serviceMedal->issueDateTimestamp;
		}
		else if (gameItem.isCase()) {
			if (StaticData::isSouvenirPackage(gameItem)) {
				if (const auto souvenirPackage = item.get<inventory::SouvenirPackage>(); souvenirPackage && souvenirPackage->tournamentStage != TournamentStage{}) {
					itemConfig["Tournament Stage"] = souvenirPackage->tournamentStage;
					itemConfig["Tournament Team 1"] = souvenirPackage->tournamentTeam1;
					itemConfig["Tournament Team 2"] = souvenirPackage->tournamentTeam2;
					itemConfig["Tournament Player"] = souvenirPackage->proPlayer;
				}
			}
		}

		items.push_back(std::move(itemConfig));
	}

	return j;
}

[[nodiscard]] auto loadAgentPatchesFromJson(const json& j) noexcept
{
	std::array<inventory::Agent::Patch, 5> agentPatches;

	if (!j.contains("Patches"))
		return agentPatches;

	const auto& patches = j["Patches"];
	if (!patches.is_array())
		return agentPatches;

	for (const auto& patch : patches) {
		if (!patch.is_object())
			continue;

		if (!patch.contains("Patch ID") || !patch["Patch ID"].is_number_integer())
			continue;

		if (!patch.contains("Slot") || !patch["Slot"].is_number_integer())
			continue;

		const int patchID = patch["Patch ID"];
		const std::size_t slot = patch["Slot"];

		if (patchID != 0 && slot < agentPatches.size())
			agentPatches[slot].patchID = patchID;
	}

	return agentPatches;
}

[[nodiscard]] inventory::Agent loadDynamicAgentDataFromJson(const json& j) noexcept
{
	inventory::Agent dynamicData;
	dynamicData.patches = loadAgentPatchesFromJson(j);
	return dynamicData;
}

[[nodiscard]] game_items::Lookup::OptionalItemReference gameItemFromJson(const game_items::Lookup& lookup, const json& j)
{
	if (const auto stickerID = j.find("Sticker ID"); stickerID != j.end() && stickerID->is_number_integer())
		return lookup.findSticker(stickerID->get<int>());
	if (const auto musicID = j.find("Music ID"); musicID != j.end() && musicID->is_number_integer())
		return lookup.findMusic(musicID->get<int>());
	if (const auto patchID = j.find("Patch ID"); patchID != j.end() && patchID->is_number_integer())
		return lookup.findPatch(patchID->get<int>());
	if (const auto graffitiID = j.find("Graffiti ID"); graffitiID != j.end() && graffitiID->is_number_integer())
		return lookup.findGraffiti(graffitiID->get<int>());

	const auto weaponID = j.find("Weapon ID");
	if (weaponID == j.end() || !weaponID->is_number_integer())
		return {};

	if (const auto paintKit = j.find("Paint Kit"); paintKit != j.end() && paintKit->is_number_integer())
		return lookup.findItem(weaponID->get<WeaponId>(), paintKit->get<int>());

	return lookup.findItem(weaponID->get<WeaponId>());
}

[[nodiscard]] inventory::StructWrapper itemFromJson(const game_items::Item& gameItem, const json& j)
{
	if (gameItem.isSkin())
		return inventory::skinFromJson(j);
	if (gameItem.isGloves())
		return inventory::gloveFromJson(j);
	if (gameItem.isMusic())
		return inventory::musicFromJson(j);
	if (gameItem.isAgent())
		return loadDynamicAgentDataFromJson(j);
	if (gameItem.isServiceMedal())
		return inventory::serviceMedalFromJson(j);
	if (gameItem.isCase() && StaticData::isSouvenirPackage(gameItem))
		return inventory::souvenirPackageFromJson(j);
	if (gameItem.isGraffiti())
		return inventory::graffitiFromJson(j);
	return {};
}

struct EquippedState {
	bool ct = false;
	bool tt = false;
	bool noTeam = false;
};

[[nodiscard]] EquippedState equippedFromJson(const json& j)
{
	EquippedState state;

	if (const auto equipped = j.find("Equipped"); equipped != j.end() && equipped->is_array()) {
		for (auto& team : *equipped) {
			if (!team.is_string())
				continue;

			const auto teamString = team.get<std::string>();
			if (teamString == "CT") {
				state.ct = true;
			}
			else if (teamString == "TT") {
				state.tt = true;
			}
			else if (teamString == "NOTEAM") {
				state.noTeam = true;
			}
		}
	}
	return state;
}

[[nodiscard]] std::uint8_t equippedSlotFromJson(const json& j)
{
	if (const auto equippedSlot = j.find("Equipped Slot"); equippedSlot != j.end() && equippedSlot->is_number_integer())
		return equippedSlot->get<std::uint8_t>();
	return static_cast<std::uint8_t>(-1);
}

void InventoryChangerfromJson(const json& j) noexcept
{
	if (!j.contains("Items"))
		return;

	const auto& items = j["Items"];
	if (!items.is_array())
		return;
	static int weird_fix = 0;
	auto& backend = inventory_changer::backend::BackendSimulator::instance();
	for (const auto& jsonItem : items) {

		std::optional<std::reference_wrapper<const game_items::Item>> itemOptional = gameItemFromJson(StaticData::lookup(), jsonItem);
		if (!itemOptional.has_value())
			continue;

		const game_items::Item& item = itemOptional->get();
		const auto itemAdded = backend.addItemAcknowledged(inventory::Item{ item, itemFromJson(item, jsonItem) });

		if (const auto equippedSlot = equippedSlotFromJson(jsonItem); equippedSlot != static_cast<std::uint8_t>(-1)) {
			const auto equippedState = equippedFromJson(jsonItem);
			if (equippedState.ct)
				backend.equipItemCT(itemAdded, equippedSlot);
			if (equippedState.tt)
				backend.equipItemTT(itemAdded, equippedSlot);
			if (equippedState.noTeam)
				backend.equipItemNoTeam(itemAdded, equippedSlot);
		}

	}
}



void InventoryChangerresetConfig() 
{
	auto& backend = inventory_changer::backend::BackendSimulator::instance();
	backend.clearInventory();
	backend.run(inventory_changer::BackendResponseHandler{ backend }, std::chrono::milliseconds{ 0 });
	callbackshit();
}

void C_ConfigManager::load(std::string config, bool load_script_items)
{
	static auto find_item = [](std::vector< C_ConfigItem* > items, std::string name) -> C_ConfigItem* 
	{
		for (int i = 0; i < (int)items.size(); i++) //-V202
			if (!items[i]->name.compare(name))
				return items[i];

		return nullptr;
	};

	std::string folder, file, invfile;

	auto get_dir = [&folder, &file, &config, &invfile]() ->void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\");
			file = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\") + config;
			invfile = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\Inventory\\") + config + "_inv";
		}

		CreateDirectory(folder.c_str(), NULL);
		CreateDirectory((folder + "Inventory\\").c_str(), NULL);
	};

	get_dir();
	std::string data;

	std::ifstream ifs;
	ifs.open(file + '\0');

	ifs >> data;
	ifs.close();

	if (data.empty())
		return;

	Base64 base64;

	std::string decoded_data;
	base64.decode(data, &decoded_data);

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << decoded_data;
	ofs.close();

	json allJson;
	
	std::ifstream ifs_final;
	ifs_final.open(file + '\0');

	ifs_final >> allJson;
	ifs_final.close();
	auto fix = allJson.dump();
	base64.encode(fix, &data);

	std::ofstream final_ofs;
	final_ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	final_ofs << data;
	final_ofs.close();

	for (auto it = allJson.begin(); it != allJson.end(); ++it)
	{
		json j = *it;

		std::string name = j[crypt_str("name")];
		std::string type = j[crypt_str("type")];

		auto script_item = std::count_if(name.begin(), name.end(),
			[](char& c)
			{
				return c == '.';
			}
		) >= 2;

		if (!load_script_items && !script_item)
		{
			auto item = find_item(items, name);

			if (item)
			{
				if (!type.compare(crypt_str("int")))
					*(int*)item->pointer = j[crypt_str("value")].get<int>(); //-V206
				else if (!type.compare(crypt_str("float")))
					*(float*)item->pointer = j[crypt_str("value")].get<float>();
				else if (!type.compare(crypt_str("bool")))
					*(bool*)item->pointer = j[crypt_str("value")].get<bool>();
				else if (!type.compare(crypt_str("KeyBind")))
				{
					std::vector<int> a;
					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						a.push_back(*it);

					*(key_bind*)item->pointer = key_bind((ButtonCode_t)a[0], (key_bind_mode)a[1]);
				}
				else if (!type.compare(crypt_str("Color")))
				{
					std::vector<int> a;
					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						a.push_back(*it);

					colors.erase(item->name);
					*(Color*)item->pointer = Color(a[0], a[1], a[2], a[3]);
				}
				else if (!type.compare(crypt_str("vector<int>")))
				{
					auto ptr = static_cast<std::vector <int>*> (item->pointer);
					ptr->clear();

					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						ptr->push_back(*it);
				}
				else if (!type.compare(crypt_str("vector<string>")))
				{
					auto ptr = static_cast<std::vector <std::string>*> (item->pointer);
					ptr->clear();

					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						ptr->push_back(*it);
				}
				else if (!type.compare(crypt_str("string")))
					*(std::string*)item->pointer = j[crypt_str("value")].get<std::string>();
			}
		}
	}

	//
	//new
	//
	InventoryChangerresetConfig();
	json jf;
	if (std::ifstream in{ invfile }; in.good()) {
		jf = json::parse(in, nullptr, false, true);
		if (jf.is_discarded())
			return;
	}
	else {
		return;
	}
	InventoryChangerfromJson(jf["Inventory Changer"]);
}

void C_ConfigManager::save(std::string config)
{
	std::string folder, file, invfile;

	auto get_dir = [&folder, &file, &config, &invfile]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\");
			file = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\") + config;
			invfile = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\Inventory\\") + config + "_inv";
		}
		CreateDirectory(folder.c_str(), NULL);
		CreateDirectory((folder + "Inventory\\").c_str(), NULL);
	};

	get_dir();
	json allJson;
	

	for (auto it : items)
	{
		json j;

		j[crypt_str("name")] = it->name;
		j[crypt_str("type")] = it->type;

		if (!it->type.compare(crypt_str("int")))
			j[crypt_str("value")] = (int)*(int*)it->pointer; //-V206
		else if (!it->type.compare(crypt_str("float")))
			j[crypt_str("value")] = (float)*(float*)it->pointer;
		else if (!it->type.compare(crypt_str("bool")))
			j[crypt_str("value")] = (bool)*(bool*)it->pointer;
		else if (!it->type.compare(crypt_str("KeyBind")))
		{
			auto k = *(key_bind*)(it->pointer);

			std::vector <int> a = { k.key, k.mode };
			json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("Color")))
		{
			auto c = *(Color*)(it->pointer);

			std::vector<int> a = { c.r(), c.g(), c.b(), c.a() };
			json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("vector<int>")))
		{
			auto& ptr = *(std::vector<int>*)(it->pointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("vector<string>")))
		{
			auto& ptr = *(std::vector<std::string>*)(it->pointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("string")))
			j[crypt_str("value")] = (std::string) * (std::string*)it->pointer;

		allJson.push_back(j);
	}

	
	std::string data;

	Base64 base64;
	auto fix = allJson.dump();
	base64.encode(fix, &data);

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << std::setw(4) << data << std::endl;
	ofs.close();

	//ffs
	json fj;
	std::ofstream invofs;
	invofs.open(invfile + '\0', std::ios::out | std::ios::trunc);
	fj["Inventory Changer"] = InventoryChangertoJson();
	invofs << std::setw(4) << fj.dump() << std::endl;
	invofs.close();
}

void C_ConfigManager::remove(std::string config)
{
	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\");
			file = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\") + config;
		}

		CreateDirectory(folder.c_str(), NULL);
	};

	get_dir();

	std::string path = file + '\0';
	std::remove(path.c_str());
}

void C_ConfigManager::config_files()
{
	std::string folder;

	auto get_dir = [&folder]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
			folder = std::string(path) + crypt_str("\\SHONAX-PROJECT\\Configs\\");

		CreateDirectory(folder.c_str(), NULL);
	};

	get_dir();
	files.clear();

	std::string path = folder + crypt_str("/*.one");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				files.push_back(fd.cFileName);
		} 
		while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}
}
