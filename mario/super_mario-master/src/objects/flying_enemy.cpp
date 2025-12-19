#include <cmath>

#include "flying_enemy.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	original_y = top_left.y;
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
	distance_since_turn = 0.0f;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	const Rect mario_rect = mario->get_rect();
	const Rect self_rect = get_rect();
	const bool mario_from_top =
		mario->get_speed().v > 0 &&
		mario_rect.get_bottom() <= self_rect.get_top() + TOP_HIT_TOLERANCE;

	if (mario_from_top) {
		is_dead = true;
		Collisionable::kill();
		vspeed = 0.0f;
		hspeed = 0.0f;
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	if (is_dead) {
		if (vspeed > 0) {
			top_left.y -= vspeed;
		}
		vspeed = 0.0f;
		return;
	}

	top_left.y = original_y;
	vspeed = 0.0f;
}

void FlyingEnemy::move_horizontally() noexcept {
	if (is_dead) {
		return;
	}
	top_left.x += hspeed;
	distance_since_turn += std::abs(hspeed);
	if (distance_since_turn >= PATROL_DISTANCE) {
		distance_since_turn = 0.0f;
		hspeed = -hspeed;
	}
}

void FlyingEnemy::move_vertically() noexcept {
	if (is_dead) {
		Movable::move_vertically();
		return;
	}

	// Override Movable gravity; flying enemies stay at their original altitude
	top_left.y += vspeed;
}
