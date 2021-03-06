//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "Keyboard.h"

#include "glfw3.h"

#include <iostream>

namespace jrc
{
	constexpr int32_t Keytable[90] =
	{
		// Number keys, up to key 0
		0, GLFW_KEY_GRAVE_ACCENT, GLFW_KEY_0, GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4, GLFW_KEY_5, GLFW_KEY_6, GLFW_KEY_7, GLFW_KEY_8, GLFW_KEY_9, GLFW_KEY_MINUS, GLFW_KEY_EQUAL,	// 14
		// First letter row, up to key 28
		0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', GLFW_KEY_LEFT_BRACKET, GLFW_KEY_RIGHT_BRACKET, GLFW_KEY_BACKSLASH,															// 39
		// Second row, up to 41
		GLFW_KEY_LEFT_CONTROL, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', GLFW_KEY_SEMICOLON, GLFW_KEY_APOSTROPHE, 0,																		// 42
		// Third row, up to 58
		GLFW_KEY_LEFT_SHIFT, 0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', GLFW_KEY_COMMA, GLFW_KEY_PERIOD, GLFW_KEY_SLASH, 0, 0, GLFW_KEY_LEFT_ALT, GLFW_KEY_SPACE, 0,								// 59
		// Up to 70
		GLFW_KEY_F1, GLFW_KEY_F2, GLFW_KEY_F3, GLFW_KEY_F4, GLFW_KEY_F5, GLFW_KEY_F6, GLFW_KEY_F7, GLFW_KEY_F8, GLFW_KEY_F9, GLFW_KEY_F10, GLFW_KEY_F11, GLFW_KEY_F12,						// 71
		GLFW_KEY_HOME, 0, GLFW_KEY_PAGE_UP, 0, 0, 0, 0, 0, GLFW_KEY_END, 0, GLFW_KEY_PAGE_DOWN, GLFW_KEY_INSERT, GLFW_KEY_DELETE, 0, 0, 0, 0, 0, 0											// 90
	};

	constexpr int32_t Shifttable[126] =
	{
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,//  10
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,//  20
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,//  30
		  0,  0, 49, 39, 51, 52, 53, 55,  0, 57,//  40
		 48, 56, 61,  0,  0,  0,  0,  0,  0,  0,//  50
		  0,  0,  0,  0,  0,  0,  0, 59,  0, 44,//  60
		  0, 46, 47, 50, 97, 98, 99,100,101,102,//  70
		103,104,105,106,107,108,109,110,111,112,//  80
		113,114,115,116,117,118,119,120,121,122,//  90
		  0,  0,  0, 54, 45,  0,  0,  0,  0,  0,// 100
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 110
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 120
		  0,  0, 91, 92, 93, 96					// 126
	};

	constexpr int32_t Specialtable[96] =
	{
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 10
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 20
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 30
		  0,  0,  0,  0,  0,  0,  0,  0, 34,  0,// 40
		  0,  0,  0, 60, 95, 62, 63, 41, 33, 64,// 50
		 35, 36, 37, 94, 38, 42, 40,  0, 58,  0,// 60
		 43,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 70
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 80
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,// 90
		123,124,125,  0,  0,126					// 96
	};

	Keyboard::Keyboard()
	{
		keymap[GLFW_KEY_LEFT] = { KeyType::ACTION, KeyAction::LEFT };
		keymap[GLFW_KEY_RIGHT] = { KeyType::ACTION, KeyAction::RIGHT };
		keymap[GLFW_KEY_UP] = { KeyType::ACTION, KeyAction::UP };
		keymap[GLFW_KEY_DOWN] = { KeyType::ACTION, KeyAction::DOWN };
		keymap[GLFW_KEY_ESCAPE] = { KeyType::ACTION, KeyAction::ESCAPE };
		keymap[GLFW_KEY_ENTER] = { KeyType::ACTION, KeyAction::RETURN };
		keymap[GLFW_KEY_KP_ENTER] = { KeyType::ACTION, KeyAction::RETURN };
		keymap[GLFW_KEY_TAB] = { KeyType::ACTION, KeyAction::TAB };

		textactions[GLFW_KEY_BACKSPACE] = KeyAction::BACK;
		textactions[GLFW_KEY_ENTER] = KeyAction::RETURN;
		textactions[GLFW_KEY_KP_ENTER] = KeyAction::RETURN;
		textactions[GLFW_KEY_SPACE] = KeyAction::SPACE;
		textactions[GLFW_KEY_TAB] = KeyAction::TAB;
		textactions[GLFW_KEY_ESCAPE] = KeyAction::ESCAPE;
		textactions[GLFW_KEY_HOME] = KeyAction::HOME;
		textactions[GLFW_KEY_END] = KeyAction::END;
		textactions[GLFW_KEY_DELETE] = KeyAction::DELETE;
	}

	int32_t Keyboard::leftshiftcode() const
	{
		return GLFW_KEY_LEFT_SHIFT;
	}

	int32_t Keyboard::rightshiftcode() const
	{
		return GLFW_KEY_RIGHT_SHIFT;
	}

	int32_t Keyboard::capslockcode() const
	{
		return GLFW_KEY_CAPS_LOCK;
	}

	int32_t Keyboard::leftctrlcode() const
	{
		return GLFW_KEY_LEFT_CONTROL;
	}

	int32_t Keyboard::rightctrlcode() const
	{
		return GLFW_KEY_LEFT_CONTROL;
	}

	KeyAction::Id Keyboard::get_ctrl_action(int32_t keycode) const
	{
		switch (keycode)
		{
		case GLFW_KEY_C:
			return KeyAction::COPY;
		case GLFW_KEY_V:
			return KeyAction::PASTE;
			/*case GLFW_KEY_A:
				return KeyAction::SELECTALL;*/
		default:
			return KeyAction::NOACTION;
		}
	}

	void Keyboard::assign(uint8_t key, uint8_t tid, int32_t action)
	{
		if (KeyType::Id type = KeyType::typebyid(tid))
		{
			Mapping mapping{ type, action };
			keymap[Keytable[key]] = mapping;
			maplekeys[key] = mapping;
		}
	}

	Keyboard::Mapping Keyboard::get_text_mapping(int32_t keycode, bool shift) const
	{
		if (textactions.count(keycode))
		{
			return{ KeyType::ACTION, textactions.at(keycode) };
		}
		else if (keycode == 39 || (keycode >= 44 && keycode <= 57) || keycode == 59 || keycode == 61 || (keycode >= 91 && keycode <= 93) || keycode == 96)
		{
			if (!shift)
				return{ KeyType::TEXT, keycode };
			else
				return{ KeyType::TEXT, Specialtable[keycode - 1] };
		}
		else if (keycode >= 33 && keycode <= 126)
		{
			if (shift)
				return{ KeyType::TEXT, keycode };
			else
				return{ KeyType::TEXT, Shifttable[keycode - 1] };
		}
		else
		{
			switch (keycode)
			{
			case GLFW_KEY_LEFT:
			case GLFW_KEY_RIGHT:
			case GLFW_KEY_UP:
			case GLFW_KEY_DOWN:
				return keymap.at(keycode);
			default:
				return{ KeyType::NONE, 0 };
			}
		}
	}

	Keyboard::Mapping Keyboard::get_mapping(int32_t keycode) const
	{
		auto iter = keymap.find(keycode);
		if (iter == keymap.end())
			return{};

		return iter->second;
	}
}