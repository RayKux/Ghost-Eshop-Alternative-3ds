#include "mainMenu.hpp"
#include "startup.hpp"
#include "unistore.hpp"
#include <unistd.h>

extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern int fadealpha;
extern bool fadein;
extern std::unique_ptr<Config> config;

Startup::Startup(int mode, std::string file) {
	this->mode = mode; this->file = file;
}

void Startup::Draw(void) const {
	GFX::DrawTop();
	GFX::DrawSprite(sprites_dev_by_idx, 0, 25);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	GFX::DrawBottom();
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void Startup::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->delay > 0) {
		this->delay -= 2;
		if (this->delay <= 0) {
			if (this->mode == 0) {
				config->firstStartup(false);
				Gui::setScreen(std::make_unique<MainMenu>(), true, true);
			} else if (this->mode == 1) {
				config->firstStartup(false);
				if (access(this->file.c_str(), F_OK) == 0) {
					Gui::setScreen(std::make_unique<UniStore>(true, this->file), true, true);
				} else {
					Gui::setScreen(std::make_unique<MainMenu>(), true, true);
				}
			}
		}
	}
}