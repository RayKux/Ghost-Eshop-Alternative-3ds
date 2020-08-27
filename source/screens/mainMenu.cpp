#include "config.hpp"
#include "credits.hpp"
#include "mainMenu.hpp"
#include "scriptHelper.hpp"
#include "scriptlist.hpp"
#include "settings.hpp"
#include "unistore.hpp"

extern std::unique_ptr<Config> config;
extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern int fadealpha;
extern bool fadein;
extern u32 TextColor;

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, config->useBars() ? 0 : 2, 0.7f, config->textColor(), "Ghost-Eshop", 400);
	Gui::DrawString(397-Gui::GetStringWidth(0.5f, V_STRING), (config->useBars() ? 239 : 237)-Gui::GetStringHeight(0.5f, V_STRING), 0.5f, config->textColor(), V_STRING);
	GFX::DrawSprite(sprites_universal_updater_idx, 0, 0);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	GFX::DrawBottom();
	GFX::DrawArrow(0, 218, 0, 1);

	GFX::DrawButton(mainButtons[0].x, mainButtons[0].y, "Ghost Eshop");
	GFX::DrawButton(mainButtons[1].x, mainButtons[1].y, Lang::get("SETTINGS"));
	GFX::DrawButton(mainButtons[2].x, mainButtons[2].y, Lang::get("CREDITS"));
	// Selector.
	Animation::Button(mainButtons[Selection].x, mainButtons[Selection].y, .060);

	// Draw UniStore Icon. ;P
	//GFX::DrawSprite(sprites_uniStore_idx, 10, 65);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if ((hDown & KEY_START) || (hDown & KEY_TOUCH && touching(touch, mainButtons[4]))) {
		fadeout = true;
		fadecolor = 0;
		exiting = true;
	}

	// Navigation.
	if (hDown & KEY_UP) {
		if (Selection > 0)	Selection --;
	} else if (hDown & KEY_DOWN) {
		if(Selection < 2)	Selection++;
	}

	if (hDown & KEY_A) {
		switch(Selection) {
			case 0:
				Gui::setScreen(std::make_unique<UniStore>(false, "NOT_USED"), config->screenFade(), true);
				break;
			case 1:
				Gui::setScreen(std::make_unique<Settings>(), config->screenFade(), true);
				break;
			case 2:
				Gui::setScreen(std::make_unique<Credits>(), config->screenFade(), true);
				break;
		}
	}

	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			Gui::setScreen(std::make_unique<UniStore>(false, "NOT_USED"), config->screenFade(), true);
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<Settings>(), config->screenFade(), true);
		} else if (touching(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>(), config->screenFade(), true);
		}
	}
}
