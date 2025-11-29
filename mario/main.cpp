#include <iostream>
#include <math.h>
#include <windows.h>
#include <cstdio>
#include <cstring>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

const int MAX_LEVEL = 3;

class TObject {
    float _x, _y;
    float _width, _height;
    float _vert_speed;
    bool _is_fly;
    char _c_type;
    float _horizon_speed;
public:
    TObject()
        : _x(0), _y(0), _width(0), _height(0),
          _vert_speed(0), _is_fly(false), _c_type(' '), _horizon_speed(0.2f) {}

    float x() const { return _x; }
    float y() const { return _y; }
    float width() const { return _width; }
    float height() const { return _height; }
    float vert_speed() const { return _vert_speed; }
    bool is_fly() const { return _is_fly; }
    char c_type() const { return _c_type; }
    float horizon_speed() const { return _horizon_speed; }

    bool intersects(const TObject& other) const {
        return ((_x + _width) > other._x) && (_x < (other._x + other._width)) &&
               ((_y + _height) > other._y) && (_y < (other._y + other._height));
    }

    friend class World;
};


class ConsoleMap {
    char map_[MAP_HEIGHT][MAP_WIDTH+1];

    bool is_pos_in_map(int x, int y){
        return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
    }
public:
    void clear_map() {
        for (int i = 0; i < MAP_WIDTH; i++)
            map_[0][i] = ' ';
        map_[0][MAP_WIDTH] = '\0';
        for (int j = 1; j < MAP_HEIGHT; j++)
            for (int i = 0; i <= MAP_WIDTH; i++)
                map_[j][i] = map_[0][i];
    }

    void put_object_on_map(const TObject& obj){
        int ix = (int)round(obj.x());
        int iy = (int)round(obj.y());
        int i_width = (int)round(obj.width());
        int i_height = (int)round(obj.height());
        for (int i = ix; i < (ix + i_width); i++)
            for (int j = iy; j < (iy + i_height); j++)
                if (is_pos_in_map(i, j))
                    map_[j][i] = obj.c_type();
    }

    void put_score_on_map(int score){
        char score_str[30];
        sprintf(score_str, "Score: %d", score);
        int len = (int)strlen(score_str);
        for (int i = 0; i < len; i++)
            map_[1][i] = score_str[i];
    }

    void set_cursor(int x, int y){
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void show_map(){
        map_[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
        for (int i = 0; i < MAP_HEIGHT; i++)
            std::cout << map_[i];
    }
};

class World {
    int level_;
    int score_;
    TObject mario_;
    TObject *bricks_;
    int bricks_length_;
    TObject *movings_;
    int movings_length_;

    void set_object_pos(TObject *obj, float x_pos, float y_pos){
        obj->_x = x_pos;
        obj->_y = y_pos;
    }

    void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char in_type){
        set_object_pos(obj, x_pos, y_pos);
        obj->_width = o_width;
        obj->_height = o_height;
        obj->_vert_speed = 0;
        obj->_c_type = in_type;
        obj->_horizon_speed = 0.2f;
    }

    void delete_moving(int i){
        movings_length_--;
        movings_[i] = movings_[movings_length_];
        movings_ = (TObject*)realloc(movings_, sizeof(*movings_) * movings_length_);
    }

    TObject *get_new_brick(){
        bricks_length_++;
        bricks_ = (TObject*)realloc(bricks_, sizeof(*bricks_) * bricks_length_);
        return bricks_ + bricks_length_ - 1;
    }

    TObject *get_new_moving(){
        movings_length_++;
        movings_ = (TObject*)realloc(movings_, sizeof(*movings_) * movings_length_);
        return movings_ + movings_length_ - 1;
    }

    void player_death(){
        system("color 4F");
        Sleep(500);
        create_level(level_);
    }

    void vert_move_object(TObject *obj, TObject *mario_ptr){
        obj->_vert_speed += 0.05f;
        obj->_is_fly = true;
        set_object_pos(obj, obj->_x, obj->_y + obj->_vert_speed);
        for (int i = 0; i < bricks_length_; i++){
            if (obj->intersects(bricks_[i])){
                if (obj->_vert_speed > 0)
                    obj->_is_fly = false;
                if ((bricks_[i].c_type() == '?') && (obj->_vert_speed < 0) && (obj == mario_ptr)){
                    bricks_[i]._c_type = '-';
                    init_object(get_new_moving(), bricks_[i].x() , bricks_[i].y() - 3 , 3, 2, '$');
                    movings_[movings_length_ - 1]._vert_speed = -0.7f;
                }
                obj->_y -= obj->_vert_speed;
                obj->_vert_speed = 0;
                obj->_is_fly = false;
                if (bricks_[i].c_type() == '+'){
                    level_++;
                    if (level_ > MAX_LEVEL)
                        level_ = 1;
                    system("color 2F");
                    Sleep(500);
                    create_level(level_);
                }
                break;
            }
        }
    }

    void horizon_move_object(TObject *obj){
        obj->_x += obj->_horizon_speed;
        for (int i = 0; i < bricks_length_; i++){
            if (obj->intersects(bricks_[i])){
                obj->_x -= obj->_horizon_speed;
                obj->_horizon_speed = -obj->_horizon_speed;
                return;
            }
        }
        if (obj->c_type() == 'o'){
            TObject tmp = *obj;
            vert_move_object(&tmp, NULL);
            if (tmp.is_fly() == true){
                obj->_x -= obj->_horizon_speed;
                obj->_horizon_speed = -obj->_horizon_speed;
            }
        }
    }

    void mario_collision(){
        for (int i = 0; i < movings_length_; i++){
            if (movings_[i].c_type() == 'o'){
                if (mario_.intersects(movings_[i])){
                    if (
                        mario_.is_fly() 
                        && (mario_.vert_speed() > 0) 
                        && (mario_.y() + mario_.height() < movings_[i].y() + movings_[i].height() * 0.5f)
                    ){
                        score_ += 50;
                        delete_moving(i);
                        i--;
                        continue;
                    } else {
                        player_death();
                    }
                }
            }
            if (movings_[i].c_type() == '$'){
                if (mario_.intersects(movings_[i])){
                    score_ += 100;
                    delete_moving(i);
                    i--;
                    continue;
                }
            }
        }
    }

    void horizon_move_map(float dx){
        mario_._x -= dx;
        for (int i = 0; i < bricks_length_; i++){
            if (mario_.intersects(bricks_[i])) {
                mario_._x += dx;
                return;
            }
        }
        mario_._x += dx;
        for (int i = 0; i < bricks_length_; i++)
            bricks_[i]._x += dx;
        for (int i = 0; i < movings_length_; i++)
            movings_[i]._x += dx;
    }

public:
    World(){
        level_ = 1;
        score_ = 0;
        bricks_ = NULL;
        bricks_length_ = 0;
        movings_ = NULL;
        movings_length_ = 0;
    }

    ~World(){
        free(bricks_);
        free(movings_);
    }

    void create_level(int lvl){
        system("color 9F");
        bricks_length_ = 0;
        bricks_ = (TObject*)realloc(bricks_, 0);
        movings_length_ = 0;
        movings_ = (TObject*)realloc(movings_, 0);
        init_object(&mario_, 39, 10, 3, 3, '@');
        score_ = 0;
        if (lvl == 1){
            init_object(get_new_brick(), 20, 20, 40, 5, '#');
            init_object(get_new_brick(), 30, 10, 5, 3, '?');
            init_object(get_new_brick(), 50, 10, 5, 3, '?');
            init_object(get_new_brick(), 60, 15, 40, 10, '#');
            init_object(get_new_brick(), 60, 5, 10, 3, '-');
            init_object(get_new_brick(), 70, 5, 5, 3, '?');
            init_object(get_new_brick(), 75, 5, 5, 3, '-');
            init_object(get_new_brick(), 80, 5, 5, 3, '?');
            init_object(get_new_brick(), 85, 5, 10, 3, '-');
            init_object(get_new_brick(), 80, 20, 20, 5, '#');
            init_object(get_new_brick(), 120, 15, 10, 10, '#');
            init_object(get_new_brick(), 150, 20, 40, 5, '#');
            init_object(get_new_brick(), 210, 15, 10, 10, '+');
            init_object(get_new_moving(), 25, 10, 3, 2, 'o');
            init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        }
        if (lvl == 2){
            init_object(get_new_brick(), 20, 20, 40, 5, '#');
            init_object(get_new_brick(), 60, 15, 5, 10, '#');
            init_object(get_new_brick(), 80, 20, 20, 5, '#');
            init_object(get_new_brick(), 120, 15, 10, 10, '#');
            init_object(get_new_brick(), 150, 20, 40, 5, '#');
            init_object(get_new_brick(), 210, 15, 10, 10, '+');
            init_object(get_new_moving(), 25, 10, 3, 2, 'o');
            init_object(get_new_moving(), 80, 10, 3, 2, 'o');
            init_object(get_new_moving(), 65, 10, 3, 2, 'o');
            init_object(get_new_moving(), 120, 10, 3, 2, 'o');
            init_object(get_new_moving(), 160, 10, 3, 2, 'o');
        }
        if (lvl == 3){
            init_object(get_new_brick(), 20, 20, 40, 5, '#');
            init_object(get_new_brick(), 80, 20, 15, 5, '#');
            init_object(get_new_brick(), 120, 15, 15, 10, '#');
            init_object(get_new_brick(), 160, 10, 15, 15, '+');
            init_object(get_new_moving(), 25, 10, 3, 2, 'o');
            init_object(get_new_moving(), 50, 10, 3, 2, 'o');
            init_object(get_new_moving(), 80, 10, 3, 2, 'o');
            init_object(get_new_moving(), 90, 10, 3, 2, 'o');
            init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        }
    }

    void handle_controls(bool jump, bool left, bool right){
        if ((mario_._is_fly == false) && jump) mario_._vert_speed = -0.8f;
        if (left)  horizon_move_map(1);
        if (right) horizon_move_map(-1);
    }

    void update(){
        if (mario_._y > MAP_HEIGHT) player_death();
        vert_move_object(&mario_, &mario_);
        mario_collision();
        for (int i = 0; i < movings_length_; i++){
            vert_move_object(movings_ + i, &mario_);
            horizon_move_object(movings_ + i);
            if (movings_[i].y() > MAP_HEIGHT) {
                delete_moving(i);
                i--;
            }
        }
    }

    void draw(ConsoleMap& map){
        for (int i = 0; i < bricks_length_; i++)
            map.put_object_on_map(bricks_[i]);
        for (int i = 0; i < movings_length_; i++)
            map.put_object_on_map(movings_[i]);
        map.put_object_on_map(mario_);
        map.put_score_on_map(score_);
    }
};

int main(){
    ConsoleMap map;
    World world;

    world.create_level(1);
    do {
        map.clear_map();
        bool jump = (GetKeyState(VK_SPACE) < 0);
        bool left = (GetKeyState('A') < 0);
        bool right = (GetKeyState('D') < 0);

        world.handle_controls(jump, left, right);
        world.update();
        map.set_cursor(0, 0);
        world.draw(map);
        map.show_map();
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
}
