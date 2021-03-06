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

#include "../Components/Textfield.h"

#include "../../Character/Look/CharLook.h"
#include "../../Template/BoolPair.h"

namespace jrc
{
	class UIClassCreation : public UIElement
	{
	public:
		static constexpr Type TYPE = CLASSCREATION;
		static constexpr bool FOCUSED = false;
		static constexpr bool TOGGLED = false;

		UIClassCreation(uint16_t job);

		void draw(float) const override;
		void update() override;

		Cursor::State send_cursor(bool, Point<int16_t>) override;

		void send_naming_result(bool success);

	protected:
		Button::State button_pressed(uint16_t button_id) override;

	private:
		void back();
		void randomize_look();
		const std::string& get_equipname(Equipslot::Id slot) const;

		enum Classes
		{
			CYGNUS,
			EXPLORERS,
			ARAN
		};

		enum Buttons
		{
			BT_BACK,
			BT_CHARC_OK,
			BT_CHARC_CANCEL,
			BT_CHARC_FACEL,
			BT_CHARC_FACER,
			BT_CHARC_HAIRL,
			BT_CHARC_HAIRR,
			BT_CHARC_SKINL,
			BT_CHARC_SKINR,
			BT_CHARC_TOPL,
			BT_CHARC_TOPR,
			BT_CHARC_BOTL,
			BT_CHARC_BOTR,
			BT_CHARC_SHOESL,
			BT_CHARC_SHOESR,
			BT_CHARC_WEPL,
			BT_CHARC_WEPR,
			BT_CHARC_GENDER_M,
			BT_CHARC_GEMDER_F,
			BT_CHARC_HAIRC0,
			BT_CHARC_HAIRC1,
			BT_CHARC_HAIRC2,
			BT_CHARC_HAIRC3,
			BT_CHARC_HAIRC4,
			BT_CHARC_HAIRC5,
			BT_CHARC_HAIRC6,
			BT_CHARC_HAIRC7
		};

		enum GenderButtons
		{
			GENDER_BACKGROUND,
			GENDER_HEAD,
			GENDER_TOP,
			GENDER_MID,
			GENDER_BOTTOM
		};

		std::vector<Sprite> sprites_lookboard;
		std::vector<Sprite> sprites_gender_select;
		std::vector<Sprite> sprites_keytype;
		Texture sky;
		Texture cloud;
		float cloudfx;
		Texture nameboard;
		Textfield namechar;
		CharLook newchar;
		Randomizer randomizer;

		BoolPair<std::vector<uint8_t>> skins;
		BoolPair<std::vector<uint8_t>> haircolors;
		BoolPair<std::vector<int32_t>> faces;
		BoolPair<std::vector<int32_t>> hairs;
		BoolPair<std::vector<int32_t>> tops;
		BoolPair<std::vector<int32_t>> bots;
		BoolPair<std::vector<int32_t>> shoes;
		BoolPair<std::vector<int32_t>> weapons;

		bool gender;
		bool charSet;
		bool named;
		bool female;
		size_t skin;
		size_t haircolor;
		size_t face;
		size_t hair;
		size_t top;
		size_t bot;
		size_t shoe;
		size_t weapon;
		Text facename;
		Text hairname;
		Text haircname;
		Text bodyname;
		Text topname;
		Text botname;
		Text shoename;
		Text wepname;
		Text gendername;
		Text version;
		uint16_t cjob;
	};
}