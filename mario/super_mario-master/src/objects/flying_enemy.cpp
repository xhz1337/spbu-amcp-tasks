#include "flying_enemy.hpp"

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.3;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	jump_timer++;
	if (jump_timer >= jump_interval) {
		vspeed = -0.5;
		jump_timer = 0;
	}
	
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
