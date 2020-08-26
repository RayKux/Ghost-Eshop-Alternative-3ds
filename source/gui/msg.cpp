#include "common.hpp"
#include "msg.hpp"

extern std::unique_ptr<Config> config;
extern bool isScriptSelected;

extern u32 barColor, bgTopColor, bgBottomColor, TextColor;

// I do not think we need that at all.
void Msg::DisplayStartMSG() {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 25, config->barColor());
	Gui::Draw_Rect(0, 25, 400, 190, config->topBG());
	Gui::Draw_Rect(0, 215, 400, 25, config->barColor());
	Gui::DrawStringCentered(0, 2, 0.7f, config->textColor(), Lang::get("STARTING_GHOST_ESHOP"));
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 25, config->barColor());
	Gui::Draw_Rect(0, 25, 320, 190, config->topBG());
	Gui::Draw_Rect(0, 215, 320, 25, config->barColor());
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	C3D_FrameEnd(0);
}

void Msg::DisplayMsg(std::string text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6f, text))/2, 0.6f, isScriptSelected ? TextColor : config->textColor(), text, 395, 70);
	GFX::DrawBottom();
	C3D_FrameEnd(0);
}

void Msg::DisplayWarnMsg(std::string Text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 1, 0.6f, isScriptSelected ? TextColor : config->textColor(), Text, 400);
	GFX::DrawBottom();
	C3D_FrameEnd(0);
	for (int i = 0; i < 60*3; i++) {
		gspWaitForVBlank();
	}
}


const std::vector<Structs::ButtonPos> promptBtn = {
	{10, 100, 140, 35}, // Yes.
	{170, 100, 140, 35} // No.
};

extern touchPosition touch;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

// Display a Message, which needs to be confirmed with A/B.
bool Msg::promptMsg(std::string promptMsg) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6f, promptMsg))/2, 0.6f, isScriptSelected ? TextColor : config->textColor(), promptMsg, 395, 70);
	Gui::DrawStringCentered(0, 217, 0.72f, isScriptSelected ? TextColor : config->textColor(), Lang::get("CONFIRM_OR_CANCEL"), 400);

	GFX::DrawBottom();
	Gui::Draw_Rect(10, 100, 140, 35, isScriptSelected ? barColor : config->barColor());
	Gui::Draw_Rect(170, 100, 140, 35, isScriptSelected ? barColor : config->barColor());
	Gui::DrawString((320-Gui::GetStringWidth(0.6f, Lang::get("YES")))/2-150+70, 110, 0.6f, isScriptSelected ? TextColor : config->textColor(), Lang::get("YES"), 140);
	Gui::DrawString((320-Gui::GetStringWidth(0.6f, Lang::get("NO")))/2+150-70, 110, 0.6f, isScriptSelected ? TextColor : config->textColor(), Lang::get("NO"), 140);

	C3D_FrameEnd(0);
	while(1) {
		gspWaitForVBlank();
		hidScanInput();
		hidTouchRead(&touch);
		if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH && touching(touch, promptBtn[0]))) {
			return true;
		} else if ((hidKeysDown() & KEY_B) || (hidKeysDown() & KEY_TOUCH && touching(touch, promptBtn[1]))) {
			return false;
		}
	}
}