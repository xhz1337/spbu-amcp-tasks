#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_ship({60, 20}, 10, 7);
	ui_factory->create_ship({80, 25}, 20, 2);
	ui_factory->create_ship({120, 20}, 10, 7);
	ui_factory->create_ship({150, 25}, 40, 2);
	ui_factory->create_ship({210, 20}, 10, 7);
	
	ui_factory->create_full_box({25, 20}, 5, 3);
	ui_factory->create_box({35, 20}, 5, 3);
	ui_factory->create_full_box({45, 20}, 5, 3);
	
	ui_factory->create_full_box({70, 15}, 5, 3);
	ui_factory->create_box({75, 15}, 5, 3);
	
	ui_factory->create_box({85, 20}, 10, 3);
	ui_factory->create_full_box({100, 20}, 5, 3);
	
	ui_factory->create_full_box({130, 15}, 5, 3);
	ui_factory->create_box({140, 15}, 5, 3);
	ui_factory->create_full_box({150, 15}, 5, 3);
	
	ui_factory->create_box({200, 15}, 10, 3);
	ui_factory->create_full_box({220, 15}, 5, 3);
	
	ui_factory->create_money({25, 17}, 3, 2);
	ui_factory->create_money({50, 17}, 3, 2);
	ui_factory->create_money({85, 17}, 3, 2);
	ui_factory->create_money({130, 12}, 3, 2);
	ui_factory->create_money({160, 12}, 3, 2);
	ui_factory->create_money({210, 12}, 3, 2);
	
	ui_factory->create_enemy({30, 20}, 3, 2);
	ui_factory->create_enemy({75, 15}, 3, 2);
	ui_factory->create_enemy({105, 20}, 3, 2);
	ui_factory->create_enemy({140, 12}, 3, 2);
	ui_factory->create_enemy({165, 12}, 3, 2);
	ui_factory->create_enemy({215, 12}, 3, 2);
}
