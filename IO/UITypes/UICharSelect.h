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
#pragma once
#include "../UIElement.h"

#include "../Components/Charset.h"
#include "../Components/Nametag.h"

#include "../../Character/Look/CharLook.h"
#include "../../Graphics/Sprite.h"
#include "../../Graphics/OutlinedText.h"
#include "../../Net/Login.h"

namespace jrc
{
	// The character selection screen.
	class UICharSelect : public UIElement
	{
	public:
		static constexpr Type TYPE = CHARSELECT;
		static constexpr bool FOCUSED = false;
		static constexpr bool TOGGLED = false;

		UICharSelect(std::vector<CharEntry> characters, uint8_t count, uint8_t slots, int8_t pic);

		void draw(float alpha) const override;
		void update() override;
		Button::State button_pressed(uint16_t id) override;

		void add_character(CharEntry&& character);
		void remove_char(int32_t cid);

		const CharEntry& get_character(int32_t cid);

	private:
		void send_selection();
		void send_deletion();
		void update_selection();
		void update_counts();
		std::string get_label_string(size_t label) const;
		Point<int16_t> get_label_pos(size_t label) const;
		Point<int16_t> get_char_pos(size_t id) const;
		std::string get_slot_text() const;

		enum Buttons
		{
			BT_CREATECHAR,
			BT_DELETECHAR,
			BT_SELECTCHAR,
			BT_CHANGEPIC,
			BT_RESETPIC,
			BT_CHANGELOC,
			BT_PAGELEFT,
			BT_PAGERIGHT,
			BT_BACK,
			BT_CHAR0
		};

		static constexpr uint8_t PAGESIZE = 8;

		Text version;
		nl::node pages;
		nl::node charselect;
		Point<int16_t> pages_pos;
		uint8_t pages_start;
		uint8_t num_width;
		uint8_t pages_y;
		Charset levelset;
		nl::node nametag;

		std::vector<CharEntry> characters;
		std::vector<CharLook> charlooks;
		std::vector<Nametag> nametags;
		int8_t require_pic;

		uint8_t charcount_absolute;
		uint8_t charcount_relative;
		uint8_t slots_absolute;
		uint8_t slots_relative;
		uint8_t selected_absolute;
		uint8_t selected_relative;
		uint8_t page;
		uint8_t total_pages;

		OutlinedText namelabel;
		OutlinedText charSlot;

		static const size_t NUM_LABELS = 5;

		enum InfoLabel
		{
			JOB, STR, DEX, INT, LUK
		};

		OutlinedText infolabels[NUM_LABELS];
	};
}