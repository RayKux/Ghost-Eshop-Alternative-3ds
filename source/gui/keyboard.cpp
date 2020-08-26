#include "config.hpp"
#include "gfx.hpp"
#include "keyboard.hpp"
#include "screenCommon.hpp"

extern std::unique_ptr<Config> config;

std::string Input::setkbdString(uint maxLength, std::string Text) {
	C3D_FrameEnd(0);
	SwkbdState state;
	swkbdInit(&state, SWKBD_TYPE_NORMAL, 2, maxLength);
	char temp[maxLength] = {0};
	swkbdSetHintText(&state, Text.c_str());
	swkbdSetValidation(&state, SWKBD_NOTBLANK_NOTEMPTY, SWKBD_FILTER_PROFANITY, 0);
	SwkbdButton ret = swkbdInputText(&state, temp, sizeof(temp));
	temp[maxLength-1] = '\0';

	if (ret == SWKBD_BUTTON_CONFIRM) {
		return temp;
	}

	return "";
}

int Input::setInt(int maxValue, std::string Text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	GFX::DrawTop();
	Gui::DrawStringCentered(0, config->useBars() ? 0 : 2, 0.7f, config->textColor(), Text, 400);
	C3D_FrameEnd(0);
	SwkbdState state;
	swkbdInit(&state, SWKBD_TYPE_NUMPAD, 2, 3);
	swkbdSetFeatures(&state, SWKBD_FIXED_WIDTH);
	swkbdSetValidation(&state, SWKBD_NOTBLANK_NOTEMPTY, 0, 0);
	char input[4]   = {0};
	SwkbdButton ret = swkbdInputText(&state, input, sizeof(input));
	input[3]        = '\0';

	if (ret == SWKBD_BUTTON_CONFIRM) {
		return (int)std::min(std::stoi(input), maxValue);
	} else {
		return -1;
	}

	return -1;
}

std::uint8_t Input::setu8(std::string Text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	GFX::DrawTop();
	Gui::DrawStringCentered(0, config->useBars() ? 0 : 2, 0.7f, config->textColor(), Text, 400);
	C3D_FrameEnd(0);
	SwkbdState state;
	swkbdInit(&state, SWKBD_TYPE_NUMPAD, 2, 3);
	swkbdSetFeatures(&state, SWKBD_FIXED_WIDTH);
	swkbdSetValidation(&state, SWKBD_NOTBLANK_NOTEMPTY, 0, 0);
	char input[4]   = {0};
	SwkbdButton ret = swkbdInputText(&state, input, sizeof(input));
	input[3]        = '\0';

	if (ret == SWKBD_BUTTON_CONFIRM) {
		return (u8)std::min(std::stoi(input), 255);
	} else {
		return -1;
	}

	return -1;
}