#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
				static constexpr float PATROL_DISTANCE = 15.0f;
				static constexpr float TOP_HIT_TOLERANCE = 1.0f;
				float distance_since_turn = 0.0f;
				float original_y;
				bool is_dead = false;
			
		public:
			FlyingEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
				void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
	};
}
