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
	
	ui_factory->create_ship({15, 25}, 30, 2);
	ui_factory->create_ship({50, 20}, 15, 7);
	ui_factory->create_ship({75, 25}, 25, 2);
	ui_factory->create_ship({110, 20}, 15, 7);
	ui_factory->create_ship({140, 25}, 35, 2);
	ui_factory->create_ship({200, 20}, 20, 7);
	ui_factory->create_ship({240, 25}, 30, 2);
	
	ui_factory->create_full_box({20, 20}, 5, 3);
	ui_factory->create_box({30, 20}, 5, 3);
	ui_factory->create_full_box({40, 20}, 5, 3);
	
	ui_factory->create_box({55, 15}, 5, 3);
	ui_factory->create_full_box({65, 15}, 5, 3);
	
	ui_factory->create_full_box({80, 20}, 10, 3);
	ui_factory->create_box({95, 20}, 5, 3);
	
	ui_factory->create_box({115, 15}, 10, 3);
	ui_factory->create_full_box({130, 15}, 5, 3);
	
	ui_factory->create_full_box({155, 20}, 5, 3);
	ui_factory->create_box({165, 20}, 5, 3);
	ui_factory->create_full_box({175, 20}, 5, 3);
	
	ui_factory->create_box({210, 15}, 10, 3);
	ui_factory->create_full_box({225, 15}, 5, 3);
	
	ui_factory->create_box({245, 20}, 10, 3);
	ui_factory->create_full_box({260, 20}, 5, 3);
	
	ui_factory->create_money({20, 17}, 3, 2);
	ui_factory->create_money({35, 17}, 3, 2);
	ui_factory->create_money({50, 17}, 3, 2);
	ui_factory->create_money({70, 12}, 3, 2);
	ui_factory->create_money({90, 17}, 3, 2);
	ui_factory->create_money({125, 12}, 3, 2);
	ui_factory->create_money({160, 17}, 3, 2);
	ui_factory->create_money({190, 12}, 3, 2);
	ui_factory->create_money({230, 12}, 3, 2);
	ui_factory->create_money({255, 17}, 3, 2);
	
	ui_factory->create_enemy({25, 20}, 3, 2);
	ui_factory->create_enemy({45, 20}, 3, 2);
	ui_factory->create_enemy({65, 15}, 3, 2);
	ui_factory->create_enemy({100, 20}, 3, 2);
	ui_factory->create_enemy({135, 15}, 3, 2);
	ui_factory->create_enemy({170, 20}, 3, 2);
	ui_factory->create_enemy({215, 12}, 3, 2);
	ui_factory->create_enemy({250, 20}, 3, 2);
}
