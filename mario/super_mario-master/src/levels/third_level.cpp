#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* ThirdLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	ui_factory->create_ship({10, 25}, 35, 2);
	
	ui_factory->create_full_box({25, 15}, 5, 3);
	ui_factory->create_full_box({45, 15}, 5, 3);
	
	ui_factory->create_ship({55, 20}, 30, 7);
	
	ui_factory->create_box({55, 10}, 10, 3);
	ui_factory->create_full_box({65, 10}, 5, 3);
	ui_factory->create_box({70, 10}, 5, 3);
	ui_factory->create_full_box({75, 10}, 5, 3);
	ui_factory->create_box({80, 10}, 10, 3);
	
	ui_factory->create_ship({95, 25}, 25, 2);
	ui_factory->create_ship({120, 20}, 15, 7);
	ui_factory->create_ship({150, 25}, 35, 2);
	
	ui_factory->create_enemy({15, 5}, 3, 2);
	ui_factory->create_enemy({20, 5}, 3, 2);
	ui_factory->create_enemy({65, 15}, 3, 2);
	ui_factory->create_enemy({75, 5}, 3, 2);
	ui_factory->create_enemy({120, 5}, 3, 2);
	ui_factory->create_enemy({155, 5}, 3, 2);
	ui_factory->create_flying_enemy({125, 12}, 3, 2);
	ui_factory->create_jumping_enemy({100, 5}, 3, 2);
}
