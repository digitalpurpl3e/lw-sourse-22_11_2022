#include "menu.h"
#include <ShlObj_core.h>
#include "../constchars.h"
#include "../cheats/misc/logs.h"


//#include "fuck/background_image.h"
#include "fuck/faprolight.h"
#include "fuck/hashes.h"
#include "fuck/logo_font.h"
#include "fuck/menu_font.h"



static inline ImVec2 operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2 operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2 operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }




void shadow(ImDrawList* drawlist, ImVec2 pos, ImVec2 size, ImVec4 color)
{
	while (true)
	{
		if (color.w <= 0.019f)
			break;

		drawlist->AddRect(pos, pos + size, ui::GetColorU32(color), 8);
		color.w -= color.w / 8;
		pos -= ImVec2(1.f, 1.f);
		size += ImVec2(2.f, 2.f);
	}
}

void nemesis::render_decorations()
{
	draw->AddRect(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 845, p.y + 560), ImColor(59, 59, 59, int(255 * alphamodulate)), 0, 15, 1.000000);
	draw->AddLine(ImVec2(p.x + 0, p.y + 30), ImVec2(p.x + 875, p.y + 30), ImColor(59, 59, 59, int(255 * alphamodulate)), 1.000000);
	//draw->AddImage(background, p, p + ImVec2{ 845.000000f, 560.000000f });
	draw->AddRectFilledMultiColor(ImVec2(p.x + 100, p.y + 30), ImVec2(p.x + 437, p.y + 31), ImColor(59, 59, 59, 0), ImColor(9, 169, 232, int(230 * alphamodulate)), ImColor(9, 169, 232, int(230 * alphamodulate)), ImColor(59, 59, 59, 0));
	draw->AddRectFilledMultiColor(ImVec2(p.x + 437, p.y + 30), ImVec2(p.x + 745, p.y + 31), ImColor(9, 169, 232, int(230 * alphamodulate)), ImColor(59, 59, 59, 0), ImColor(59, 59, 59, 0), ImColor(9, 169, 232, int(230 * alphamodulate)));
	draw->AddRectFilled(ImVec2(p.x + 7, p.y + 37), ImVec2(p.x + 85, p.y + 530), ImColor(12, 12, 12, int(170 * alphamodulate)), 0, 15);
	draw->AddRect(ImVec2(p.x + 7, p.y + 37), ImVec2(p.x + 85, p.y + 530), ImColor(59, 59, 59, int(170 * alphamodulate)), 0, 15, 1.000000);
	draw->AddRect(ImVec2(p.x + 8, p.y + 38), ImVec2(p.x + 84, p.y + 529), ImColor(2, 2, 2, int(170 * alphamodulate)), 0, 15, 1.000000);
	draw->AddRectFilled(ImVec2(p.x + 92, p.y + 37), ImVec2(p.x + 838, p.y + 530), ImColor(12, 12, 12, int(170 * alphamodulate)), 0, 15);
	draw->AddRect(ImVec2(p.x + 92, p.y + 37), ImVec2(p.x + 838, p.y + 530), ImColor(59, 59, 59, int(170 * alphamodulate)), 0, 15, 1.000000);
	draw->AddRect(ImVec2(p.x + 93, p.y + 38), ImVec2(p.x + 837, p.y + 529), ImColor(3, 1, 1, int(170 * alphamodulate)), 0, 15, 1.000000);

	draw->AddLine(ImVec2(p.x + 92, p.y + 37 + 26), ImVec2(p.x + 838, p.y + 37 + 26), ImColor(59, 59, 59, int(150 * alphamodulate)), 1.000000);
}







bool nemesis::beginchildex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* parent_window = g.CurrentWindow;

	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
	flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

	// Size
	const ImVec2 content_avail = ui::GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
	if (size.x <= 0.0f)
		size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
	if (size.y <= 0.0f)
		size.y = ImMax(content_avail.y + size.y, 4.0f);
	ui::SetNextWindowSize(size);

	// Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
	char title[256];
	if (name)
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%s_%08X", parent_window->Name, name, id);
	else
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%08X", parent_window->Name, id);

	const float backup_border_size = g.Style.ChildBorderSize;
	if (!border)
		g.Style.ChildBorderSize = 0.0f;
	bool ret = ui::BeginNemesis(title, NULL, flags);
	g.Style.ChildBorderSize = backup_border_size;

	ImGuiWindow* child_window = g.CurrentWindow;
	child_window->ChildId = id;
	child_window->AutoFitChildAxises = auto_fit_axises;

	// Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
	// While this is not really documented/defined, it seems that the expected thing to do.
	if (child_window->BeginCount == 1)
		parent_window->DC.CursorPos = child_window->Pos;

	// Process navigation-in immediately so NavInit can run on first frame
	if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayerActiveMask != 0 || child_window->DC.NavHasScroll))
	{
		ui::FocusWindow(child_window);
		ui::NavInitWindow(child_window, false);
		ui::SetActiveID(id + 1, child_window); // Steal ActiveId with another arbitrary id so that key-press won't activate child item
		g.ActiveIdSource = ImGuiInputSource_Nav;
	}
	parent_window->DrawList->AddRectFilled(ui::GetWindowPos(), ui::GetWindowPos() + size_arg, ImColor(12, 12, 12, int(alphamodulate * 170)), 0);
	parent_window->DrawList->AddRect(ui::GetWindowPos(), ui::GetWindowPos() + size_arg, ImColor(59, 59, 59, int(alphamodulate * 140)), 0);
	parent_window->DrawList->AddRect(ui::GetWindowPos() + ImVec2(1, 1), ui::GetWindowPos() + size_arg - ImVec2(1, 1), ImColor(2, 2, 2, int(alphamodulate * 170)), 0);
	return ret;
}


bool nemesis::beginchild(const char* str_id, const ImVec2& size_arg, bool border = false, ImGuiWindowFlags extra_flags = NULL)
{

	ImGuiWindow* window = ui::GetCurrentWindow();
	return beginchildex(str_id, window->GetID(str_id), size_arg, border, extra_flags);
}

static float CalcMaxPopupHeightFromItemCount(int items_count)
{
	ImGuiContext& g = *GImGui;
	if (items_count <= 0)
		return FLT_MAX;
	return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
}

bool nemesis::tab(const char* label, bool selected)
{
	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ui::CalcItemSize({ 76,78 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ui::ItemSize(size, style.FramePadding.y);
	if (!ui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ui::SetMouseCursor(7);

	float t = selected ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.50f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = selected ? (t_anim) : (1.0f - t_anim);
	}

	ImVec4 col = ImLerp(ImVec4{ 229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate }, ImVec4{ 9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate }, t);


	window->DrawList->AddLine(ImVec2(bb.Min.x + 10, bb.Min.y + 81), ImVec2(bb.Max.x - 10, bb.Min.y + 81), ImColor(59, 59, 59, int(alphamodulate * 255)));

	if (!selected)
		ui::PushStyleColor(ImGuiCol_Text, col);
	else
		ui::PushStyleColor(ImGuiCol_Text, col);
	ui::PushFont(fff);
	ui::RenderText(ImVec2(bb.Min.x + 0 + (76 / 2 - label_size.x / 2) - 8, bb.Min.y + style.FramePadding.y + 35 + 5), label);
	ui::PopFont();
	ui::PopStyleColor();

	return pressed;
}

bool nemesis::subtab(const char* label, bool selected, ImVec2 size_arg = ImVec2(0, 0))
{
	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ui::ItemSize(size, style.FramePadding.y);
	if (!ui::ItemAdd(bb, id))
		return false;

	float t = selected ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.50f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = selected ? (t_anim) : (1.0f - t_anim);
	}

	bool hovered, held;
	bool pressed = ui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ui::SetMouseCursor(7);

	ImVec4 col = ImLerp(ImVec4{ 140 / 255.f, 140 / 255.f, 140 / 255.f, alphamodulate }, ImVec4{ 9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate }, t);
	ImVec4 col2 = ImLerp(ImVec4{ 140 / 255.f, 140 / 255.f, 140 / 255.f, 0 / 255.f }, ImVec4{ 9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate }, t);

	ui::PushStyleColor(ImGuiCol_Text, col);
	ui::RenderText(ImVec2(bb.Min.x + (size_arg.x / 2 - label_size.x / 2), bb.Min.y + (size_arg.y / 2 - label_size.y / 2)), label);
	ui::PopStyleColor();

	window->DrawList->AddLine(bb.Min + ImVec2(40, size_arg.y), bb.Max - ImVec2(40, 0), ui::GetColorU32(col2));

	return pressed;
}















bool nemesis::checkbox(const char* label, bool* v)
{

	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);
	const float square_sz = ui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos + ImVec2(10, 5), pos + ImVec2(square_sz + (style.ItemInnerSpacing.x + label_size.x + 0), 0 + label_size.y + style.FramePadding.y * 2) + ImVec2(10, 5));
	ui::ItemSize(total_bb, style.FramePadding.y);
	ui::ItemAdd(total_bb, id);

	bool hovered, held;
	bool pressed = ui::ButtonBehavior(total_bb, id, &hovered, &held);

	if (hovered || held)
		ui::SetMouseCursor(7);

	if (pressed)
		*v = !(*v);

	window->DrawList->AddRectFilled(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 10), ImColor(37, 37, 37, int(alphamodulate * 253)), 0, 15);
	window->DrawList->AddRect(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 10), ImColor(27, 27, 27, int(alphamodulate * 253)), 0, 15);

	if (*v)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(total_bb.Min.x + 1, total_bb.Min.y + 1), ImVec2(total_bb.Min.x + 9, total_bb.Min.y + 9), ImColor(9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate), ImColor(9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate), ImColor(0, 54, 116, int(alphamodulate * 253)), ImColor(0, 54, 116, int(alphamodulate * 253)));
	}

	ui::PushStyleColor(ImGuiCol_Text, ImVec4(214 / 255.f, 214 / 255.f, 214 / 255.f, alphamodulate));
	ui::RenderText(ImVec2(total_bb.Min.x + style.ItemInnerSpacing.x + 10, total_bb.Min.y + style.FramePadding.y + -4), label);
	ui::PopStyleColor();
	return pressed;
}




bool nemesis::button(const char* label, const ImVec2& size_arg)
{
	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos + ImVec2(11, 3);
	ImVec2 size = ui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ui::ItemSize(size, style.FramePadding.y);
	if (!ui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ui::SetMouseCursor(7);

	if (!hovered)
		window->DrawList->AddRectFilledMultiColor(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)));
	else
		window->DrawList->AddRectFilledMultiColor(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)));

	ui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	ui::RenderText(ImVec2(bb.Min.x + style.ItemInnerSpacing.x + 0, bb.Min.y + style.FramePadding.y + 0), label);
	ui::PopStyleColor();

	return pressed;
}



static float CalcMaxPopupHeightFromItemCounttt(int items_count)
{
	ImGuiContext& g = *GImGui;
	if (items_count <= 0)
		return FLT_MAX;
	return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
}

bool nemesis::begincombo(const char* label, const char* preview_value, ImGuiComboFlags flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiCond backup_next_window_size_constraint = g.NextWindowData.SizeConstraintCond;
	g.NextWindowData.SizeConstraintCond = 0;
	//bool has_window_size_constraint = (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint) != 0;
	//g.NextWindowData.Flags &= ~ImGuiNextWindowDataFlags_HasSizeConstraint;

	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : ui::GetFrameHeight();
	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);
	const float expected_w = 240;
	const float w = (flags & ImGuiComboFlags_NoPreview) ? 240 : 240;

	const ImRect frame_bb(window->DC.CursorPos + ImVec2(11, 0), window->DC.CursorPos + ImVec2(w + 0, label_size.y + style.FramePadding.y * 2.0f + 0) + ImVec2(15, 18));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	ui::ItemSize(total_bb, style.FramePadding.y);
	if (!ui::ItemAdd(total_bb, id, &frame_bb))
		return false;

	bool hovered, held;
	bool pressed = ui::ButtonBehavior(frame_bb, id, &hovered, &held);
	bool popup_open = ui::IsPopupOpen(id);

	if (hovered || held)
		ui::SetMouseCursor(7);

	const float value_x2 = ImMax(frame_bb.Min.x, frame_bb.Max.x - arrow_size);

	if (!hovered)
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 18), ImVec2(frame_bb.Max.x - 15, frame_bb.Max.y + 0), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)));
	else
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 18), ImVec2(frame_bb.Max.x - 15, frame_bb.Max.y + 0), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)));

	ui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	if (preview_value != NULL && !(flags & ImGuiComboFlags_NoPreview))
		ui::RenderText(frame_bb.Min + style.FramePadding + ImVec2(0, 18), preview_value);
	ui::PopStyleColor();

	ui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	if (label_size.x > 0)
		ui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y + 0), label);
	ui::PopStyleColor();

	if ((pressed || g.NavActivateId == id) && !popup_open)
	{
		if (window->DC.NavLayerCurrent == 0)
			window->NavLastIds[0] = id;
		ui::OpenPopupEx(id);
		popup_open = true;
	}

	if (!popup_open)
		return false;

	if ((flags & ImGuiComboFlags_HeightMask_) == 0)
		flags |= ImGuiComboFlags_HeightRegular;
	IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiComboFlags_HeightMask_));
	int popup_max_height_in_items = -1;
	if (flags & ImGuiComboFlags_HeightRegular)     popup_max_height_in_items = 8;
	else if (flags & ImGuiComboFlags_HeightSmall)  popup_max_height_in_items = 4;
	else if (flags & ImGuiComboFlags_HeightLarge)  popup_max_height_in_items = 20;
	ui::SetNextWindowSizeConstraints(ImVec2(w - 11, 0.0f), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCounttt(popup_max_height_in_items)));

	char name[16];
	ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size);

	if (ImGuiWindow* popup_window = ui::FindWindowByName(name))
		if (popup_window->WasActive)
		{
			ImVec2 size_expected = ui::CalcWindowExpectedSize(popup_window);
			if (flags & ImGuiComboFlags_PopupAlignLeft)
				popup_window->AutoPosLastDirection = ImGuiDir_Left;
			ImRect r_outer = ui::GetWindowAllowedExtentRect(popup_window);
			ImVec2 pos = ui::FindBestWindowPosForPopupEx(frame_bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, frame_bb, ImGuiPopupPositionPolicy_ComboBox);
			ui::SetNextWindowPos(pos);
		}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

	ui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(style.FramePadding.x, style.WindowPadding.y));
	bool ret = ui::BeginNemesis(name, NULL, window_flags);
	ui::PopStyleVar();

	if (!ret)
	{
		ui::EndPopupNemesis();
		return false;
	}
	return true;
}


static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

// Getter for the old Combo() API: "item1\0item2\0item3\0"
static bool Items_SingleStringGetter(void* data, int idx, const char** out_text)
{
	// FIXME-OPT: we could pre-compute the indices to fasten this. But only 1 active combo means the waste is limited.
	const char* items_separated_by_zeros = (const char*)data;
	int items_count = 0;
	const char* p = items_separated_by_zeros;
	while (*p)
	{
		if (idx == items_count)
			break;
		p += strlen(p) + 1;
		items_count++;
	}
	if (!*p)
		return false;
	if (out_text)
		*out_text = p;
	return true;
}

// Old API, prefer using BeginCombo() nowadays if you can.
bool nemesis::combo(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int popup_max_height_in_items)
{
	ImGuiContext& g = *GImGui;

	// Call the getter to obtain the preview string which is a parameter to BeginCombo()
	const char* preview_value = NULL;
	if (*current_item >= 0 && *current_item < items_count)
		items_getter(data, *current_item, &preview_value);

	// The old Combo() API exposed "popup_max_height_in_items". The new more general BeginCombo() API doesn't have/need it, but we emulate it here.
	if (popup_max_height_in_items != -1 && !g.NextWindowData.SizeConstraintCond)
		ui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCounttt(popup_max_height_in_items)));

	if (!begincombo(label, preview_value, ImGuiComboFlags_None))
		return false;

	// FIXME-OPT: Use clipper (but we need to disable it on the appearing frame to make sure our call to SetItemDefaultFocus() is processed)
	bool value_changed = false;
	for (int i = 0; i < items_count; i++)
	{
		ui::PushID((void*)(intptr_t)i);
		const bool item_selected = (i == *current_item);
		const char* item_text;
		if (!items_getter(data, i, &item_text))
			item_text = "*Unknown item*";
		if (ui::SelectableOT(item_text, item_selected))
		{
			value_changed = true;
			*current_item = i;
		}
		if (item_selected)
			ui::SetItemDefaultFocus();
		ui::PopID();
	}

	ui::EndComboNemesis();
	return value_changed;
}

// Combo box helper allowing to pass an array of strings.
bool nemesis::combo(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
{
	const bool value_changed = combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
	return value_changed;
}

// Combo box helper allowing to pass all items in a single string literal holding multiple zero-terminated items "item1\0item2\0"
bool nemesis::combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
{
	int items_count = 0;
	const char* p = items_separated_by_zeros;       // FIXME-OPT: Avoid computing this, or at least only when combo is open
	while (*p)
	{
		p += strlen(p) + 1;
		items_count++;
	}
	bool value_changed = combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
	return value_changed;
}




void nemesis::render_tabs()
{
	
}










static const char* PatchFormatStringFloatToInt(const char* fmt)
{
	if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0)
		return "%d";

	const char* fmt_start = ImParseFormatFindStart(fmt);
	const char* fmt_end = ImParseFormatFindEnd(fmt_start);
	if (fmt_end > fmt_start&& fmt_end[-1] == 'f')
	{
		if (fmt_start == fmt && fmt_end[0] == 0)
			return "%d";
		ImGuiContext& g = *GImGui;
		ImFormatString(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), "%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end);
		return g.TempBuffer;
	}
	return fmt;
}


struct ImGuiDataTypeInfo
{
	size_t      Size;
	const char* PrintFmt;   // Unused
	const char* ScanFmt;
};

static const ImGuiDataTypeInfo GDataTypeInfo[] =
{
	{ sizeof(int),          "%d",   "%d"    },
	{ sizeof(unsigned int), "%u",   "%u"    },
#ifdef _MSC_VER
	{ sizeof(ImS64),        "%I64d","%I64d" },
	{ sizeof(ImU64),        "%I64u","%I64u" },
#else
	{ sizeof(ImS64),        "%lld", "%lld"  },
	{ sizeof(ImU64),        "%llu", "%llu"  },
#endif
	{ sizeof(float),        "%f",   "%f"    },  // float are promoted to double in va_arg
	{ sizeof(double),       "%f",   "%lf"   },
};

static inline int DataTypeFormatString(char* buf, int buf_size, ImGuiDataType data_type, const void* data_ptr, const char* format)
{
	if (data_type == ImGuiDataType_S32 || data_type == ImGuiDataType_U32)   // Signedness doesn't matter when pushing the argument
		return ImFormatString(buf, buf_size, format, *(const ImU32*)data_ptr);
	if (data_type == ImGuiDataType_S64 || data_type == ImGuiDataType_U64)   // Signedness doesn't matter when pushing the argument
		return ImFormatString(buf, buf_size, format, *(const ImU64*)data_ptr);
	if (data_type == ImGuiDataType_Float)
		return ImFormatString(buf, buf_size, format, *(const float*)data_ptr);
	if (data_type == ImGuiDataType_Double)
		return ImFormatString(buf, buf_size, format, *(const double*)data_ptr);
	IM_ASSERT(0);
	return 0;
}



bool nemesis::SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
{
	ImGuiWindow* window = ui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = 240;

	const ImVec2 label_size = ui::CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(12, 18), window->DC.CursorPos + ImVec2(w + 0, label_size.y + 7 + (style.FramePadding.y * 2)));
	const ImRect total_bb(frame_bb.Min + ImVec2(12, -18), frame_bb.Max + ImVec2(0, 1) + ImVec2(0.0f, 0.0f));

	ui::ItemSize(total_bb, style.FramePadding.y);
	if (!ui::ItemAdd(total_bb, id, &frame_bb))
		return false;

	if (format == NULL)
		format = GDataTypeInfo[data_type].PrintFmt;
	else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
		format = PatchFormatStringFloatToInt(format);
	bool start_text_input = false;
	const bool tab_focus_requested = ui::FocusableItemRegister(window, id);
	const bool hovered = ui::ItemHoverable(frame_bb, id);
	if (tab_focus_requested || (hovered && g.IO.MouseClicked[0]) || g.NavActivateId == id || (g.NavInputId == id && g.ScalarAsInputTextId != id))
	{
		ui::SetActiveID(id, window);
		ui::SetFocusID(id, window);
		ui::FocusWindow(window);
		g.ActiveIdAllowNavDirFlags = (1 << ImGuiDir_Up) | (1 << ImGuiDir_Down);
		if (tab_focus_requested || g.IO.KeyCtrl || g.NavInputId == id)
		{
			start_text_input = true;
			g.ScalarAsInputTextId = 0;
		}
	}
	//if (start_text_input || (g.ActiveId == id && g.ScalarAsInputTextId == id))
	//{
	//	window->DC.CursorPos = frame_bb.Min;
	//	ui::FocusableItemUnregister(window);
	//	return ui::InputScalarAsWidgetReplacement(frame_bb, id, label, data_type, v, format);
	//}
	//draw nemesis things
	if (!hovered)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 0), ImVec2(frame_bb.Max.x + 0, frame_bb.Max.y + 0), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)));
	}
	else
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 0), ImVec2(frame_bb.Max.x + 0, frame_bb.Max.y + 0), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)));
	}

	ImRect grab_bb;
	const bool value_changed = ui::SliderBehaviorNemesis(frame_bb, id, data_type, p_data, p_min, p_max, format, 1.0f, flags, &grab_bb);

	grab_bb.Min = frame_bb.Min;
	grab_bb.Min += ImVec2(0, 0);
	grab_bb.Max += ImVec2(0, 2);

	if (!hovered)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(grab_bb.Min.x + 0, grab_bb.Min.y + 0), ImVec2(grab_bb.Max.x + 0, grab_bb.Max.y + 0), ImColor(9, 169, 232, int(230 * alphamodulate)), ImColor(9, 169, 232, int(230 * alphamodulate)), ImColor(2, 134, 186, int(230 * alphamodulate)), ImColor(2, 134, 186, int(230 * alphamodulate)));
	}
	else
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(grab_bb.Min.x + 0, grab_bb.Min.y + 0), ImVec2(grab_bb.Max.x + 0, grab_bb.Max.y + 0), ImColor(2, 134, 186, int(230 * alphamodulate)), ImColor(2, 134, 186, int(230 * alphamodulate)), ImColor(0, 108, 150, int(230 * alphamodulate)), ImColor(0, 108, 150, int(230 * alphamodulate)));
	}

	char value_buf[64];
	const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

	ui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	ui::RenderText(ImVec2(frame_bb.Max.x - ui::CalcTextSize(value_buf).x, frame_bb.Min.y + style.FramePadding.y + -19), value_buf);
	ui::PopStyleColor();

	if (hovered)
		ui::SetMouseCursor(7);

	ui::PushStyleColor(ImGuiCol_Text, ImVec4(198 / 255.f, 198 / 255.f, 198 / 255.f, alphamodulate));
	ui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y + -19), label);
	ui::PopStyleColor();
	return value_changed;
}

bool nemesis::slider_float(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
}

bool nemesis::slider_int(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
}











void nemesis::render_content()
{
	ui::SetCursorPos({ (float)92, (float)38 });
	ui::BeginChildNemesis("workzone", ImVec2(838 - 92, 530 - 37), false, ImGuiWindowFlags_NoResize);

	if (selectedtab == 1)
	{
		ui::BeginGroup();
		if (subtab("SUBTAB 1", 0 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 0;
		ui::SameLine();
		if (subtab("SUBTAB 2", 1 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 1;
		ui::SameLine();
		if (subtab("SUBTAB 3", 2 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 2;
		ui::SameLine();
		if (subtab("SUBTAB 4", 3 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 3;
		ui::EndGroup();
	
		ui::SetCursorPos({ 15,35 });
		ui::BeginChildNemesis("workzone", ImVec2(838 - 92 - 30, 530 - 72), false, ImGuiWindowFlags_NoResize);
		{
			beginchild("##subtabs3", { 362,445 });
			{
				ui::Spacing();
				ui::Spacing();
				static bool checkboxbool2;
				checkbox("Checkbox", &checkboxbool2);
				static bool checkboxbool;
				checkbox("Checkbox Inact.", &checkboxbool);
				static int sliderint;
				slider_int("Slider", &sliderint, 0, 100, NULL, NULL);
				static int comboint;

				combo("Menu changing", &g_ctx.menu_type, "Skeet\0\Evolve\0\Onetap v3\0\Nemesis\0\Neverlose\0\0", 2);
				button("Button", { 100,20 });
			}
			ui::EndChildNemesis();
		}
		ui::EndChildNemesis();
	}

	ui::EndChildNemesis();
}


void nemesis::render()
{
	if (hooks::menu_open && alphamodulate <= 1.f)
		alphamodulate += 0.05f;
	else if (!hooks::menu_open && alphamodulate >= 0.f)
	{
		alphamodulate -= 0.05f;
	}





	auto& style = ui::GetStyle();



	style.WindowPadding = ImVec2(0.000000f, 0.000000f);
	style.FramePadding = ImVec2(4.000000f, 3.000000f);
	style.ItemSpacing = ImVec2(8.000000f, 4.000000f);
	style.ItemInnerSpacing = ImVec2(4.000000f, 4.000000f);
	style.IndentSpacing = 21.000000f;
	style.ScrollbarSize = 15.000000f;
	style.GrabMinSize = 1.000000f;
	style.WindowBorderSize = 0.000000f;
	style.ChildBorderSize = 1.000000f;
	style.PopupBorderSize = 0.000000f;
	style.FrameBorderSize = 1.000000f;
	style.WindowRounding = 0.000000f;
	style.ChildRounding = 0.000000f;
	style.FrameRounding = 0.000000f;
	style.PopupRounding = 0.000000f;
	style.ScrollbarRounding = 4.000000f;
	style.GrabRounding = 0.000000f;
	style.WindowTitleAlign = ImVec2(0.000000f, 0.500000f);
	style.ButtonTextAlign = ImVec2(0.500000f, 0.500000f);
	style.SelectableTextAlign = ImVec2(0.500000f, 0.500000f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.900000f, 0.900000f, 0.900000f, 1.000000f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.600000f, 0.600000f, 0.600000f, 1.000000f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.058824f, 0.058824f, 0.058824f, 1.000000f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(57 / 255.f, 57 / 255.f, 57 / 255.f, 1);
	style.Colors[ImGuiCol_Border] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.430000f, 0.430000f, 0.430000f, 0.390000f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.470000f, 0.470000f, 0.690000f, 0.400000f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.420000f, 0.410000f, 0.640000f, 0.690000f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.270000f, 0.270000f, 0.540000f, 0.830000f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.320000f, 0.320000f, 0.630000f, 0.870000f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.200000f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.400000f, 0.400000f, 0.550000f, 0.800000f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200000f, 0.250000f, 0.300000f, 0.000000f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.300000f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.400000f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.600000f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.900000f, 0.900000f, 0.900000f, 0.500000f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.300000f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.410000f, 0.390000f, 0.800000f, 0.600000f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.350000f, 0.400000f, 0.610000f, 0.620000f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.400000f, 0.480000f, 0.710000f, 0.790000f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.460000f, 0.540000f, 0.800000f, 1.000000f);
	style.Colors[ImGuiCol_Header] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(50 / 255.f, 50 / 255.f, 50 / 255.f, 1);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.600000f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.600000f, 0.600000f, 0.700000f, 1.000000f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.700000f, 0.700000f, 0.900000f, 1.000000f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.160000f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.600000f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.900000f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.000000f, 0.000000f, 1.000000f, 0.350000f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000f, 1.000000f, 0.000000f, 0.900000f);


	auto flags = ImGuiWindowFlags_NoTitleBar | NULL | NULL | NULL | ImGuiWindowFlags_NoResize | NULL | NULL | NULL | NULL;

	ui::SetNextWindowSize({ 845.000000f,560.000000f });


	ui::PushStyleVar(ImGuiStyleVar_Alpha, alphamodulate);
	ui::BeginNemesis("Edited", nullptr, flags);
	{
		p = ui::GetWindowPos();
		draw = ui::GetWindowDrawList();

		render_decorations();
		render_tabs();
		render_content();

		draw->AddText({ p.x + 7, p.y + 8 }, ImColor(9, 169, 232, int(230 * alphamodulate)), "shonax project");
	}
	ui::EndNemesis();
	ui::PopStyleVar(1);

	shadow(ui::GetOverlayDrawList(), p, { 845.000000f,560.000000f }, ImVec4(9 / 255.F, 169 / 255.F, 232 / 255.F, 0.25f * alphamodulate));
}
