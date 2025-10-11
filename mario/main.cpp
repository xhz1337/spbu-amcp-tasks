#include <iostream>
#include <math.h>
#include <windows.h>
#include <cstdio>
#include <cstring>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

typedef struct s_object {
    float x, y;
    float width, height;
    float vert_speed;
    bool is_fly;
    char c_type;
    float horizon_speed;
} TObject;

TObject *movings = NULL;
int movings_length;
int level = 1;
int score;
int max_level;

void clear_map(char map[MAP_HEIGHT][MAP_WIDTH+1]);
void create_level(TObject *mario,
    TObject *&bricks, int &bricks_length,
    int lvl
    );
void delete_moving(int i);
TObject *get_new_brick(TObject *&bricks, int &bricks_length);
TObject *get_new_moving();
void horizon_move_map(
    float dx, 
    TObject *mario, 
    TObject *bricks, int bricks_length
);
void horizon_move_object(TObject *obj, TObject *bricks, int bricks_length);
bool is_collision(TObject o1, TObject o2);
bool is_pos_in_map(int x, int y);
void init_object(
    TObject *obj,
    float x_pos, float y_pos,
    float o_width, float o_height,
    char in_type
);
void mario_collision(TObject *mario, TObject *&bricks, int &bricks_length);
void player_death(TObject *mario, TObject *&bricks, int &bricks_length);
void put_object_on_map(char map[MAP_HEIGHT][MAP_WIDTH+1], TObject obj);
void put_score_on_map(char map[MAP_HEIGHT][MAP_WIDTH+1]);
void set_cursor(int x, int y);
void set_object_pos(TObject *obj, float x_pos, float y_pos);
void show_map(char map[MAP_HEIGHT][MAP_WIDTH+1]);
void vert_move_object(
    TObject *obj, 
    TObject *mario,
    TObject *bricks, int bricks_length, 
    TObject *&bricks_ref, int &bricks_len_ref
    );

int main(){
    char map[MAP_HEIGHT][MAP_WIDTH+1];
    TObject mario;
    TObject *bricks = NULL;
    int bricks_length = 0;

    create_level(&mario, bricks, bricks_length, level);
    do {
        clear_map(map);
        if ((mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) mario.vert_speed = -0.8;
        if (GetKeyState('A') < 0) horizon_move_map(1, &mario, bricks, bricks_length);
        if (GetKeyState('D') < 0) horizon_move_map(-1, &mario, bricks, bricks_length);
        if (mario.y > MAP_HEIGHT) player_death(&mario, bricks, bricks_length);
        vert_move_object(&mario, &mario, bricks, bricks_length, bricks, bricks_length);
        mario_collision(&mario, bricks, bricks_length);
        for (int i = 0; i < bricks_length; i++)
            put_object_on_map(map, bricks[i]);
        for (int i = 0; i < movings_length; i++){
            vert_move_object(movings + i, &mario, bricks, bricks_length, bricks, bricks_length);
            horizon_move_object(movings + i, bricks, bricks_length);
            if (movings[i].y > MAP_HEIGHT) {
                delete_moving(i);
                i--;
                continue;
            }
            put_object_on_map(map, movings[i]);
        }
        put_object_on_map(map, mario);
        put_score_on_map(map);
        set_cursor(0, 0);
        show_map(map);
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);

    free(bricks);
    free(movings);
}

void clear_map(char map[MAP_HEIGHT][MAP_WIDTH+1]) {
    for (int i = 0; i < MAP_WIDTH; i++)
        map[0][i] = ' ';
    map[0][MAP_WIDTH] = '\0';
    for (int j = 1; j < MAP_HEIGHT; j++)
        for (int i = 0; i <= MAP_WIDTH; i++)
            map[j][i] = map[0][i];
}

bool is_collision(TObject o1, TObject o2){
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

bool is_pos_in_map(int x, int y){
    return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void set_object_pos(TObject *obj, float x_pos, float y_pos){
    obj->x = x_pos;
    obj->y = y_pos;
}

void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char in_type){
    set_object_pos(obj, x_pos, y_pos);
    obj->width = o_width;
    obj->height = o_height;
    obj->vert_speed = 0;
    obj->c_type = in_type;
    obj->horizon_speed = 0.2;
}

void delete_moving(int i){
    movings_length--;
    movings[i] = movings[movings_length];
    movings = (TObject*)realloc(movings, sizeof(*movings) * movings_length);
}

TObject *get_new_moving(){
    movings_length++;
    movings = (TObject*)realloc(movings, sizeof(*movings) * movings_length);
    return movings + movings_length - 1;
}

TObject *get_new_brick(TObject *&bricks, int &bricks_length){
    bricks_length++;
    bricks = (TObject*)realloc(bricks, sizeof(*bricks) * bricks_length);
    return bricks + bricks_length - 1;
}

void player_death(TObject *mario, TObject *&bricks, int &bricks_length) {
    system("color 4F");
    Sleep(500);
    create_level(mario, bricks, bricks_length, level);
}

void vert_move_object(
    TObject *obj, 
    TObject *mario,
    TObject *bricks, int bricks_length, 
    TObject *&bricks_ref, int &bricks_len_ref
    )
{
    obj->vert_speed += 0.05;
    obj->is_fly = true;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
    for (int i = 0; i < bricks_length; i++){
        if (is_collision(*obj, bricks[i])){
            if (obj->vert_speed > 0)
                obj->is_fly = false;
            if ((bricks[i].c_type == '?') && (obj->vert_speed < 0) && (obj == mario)){
                bricks[i].c_type = '-';
                init_object(get_new_moving(), bricks[i].x , bricks[i].y - 3 , 3, 2, '$');
                movings[movings_length - 1].vert_speed = -0.7;
            }
            obj->y -= obj->vert_speed;
            obj->vert_speed = 0;
            obj->is_fly = false;
            if (bricks[i].c_type == '+'){
                level++;
                if (level > max_level)
                    level = 1;
                system("color 2F");
                Sleep(500);
                create_level(mario, bricks_ref, bricks_len_ref, level);
            }
            break;
        }
    }
}

void horizon_move_object(TObject *obj, TObject *bricks, int bricks_length){
    obj->x += obj->horizon_speed;
    for (int i = 0; i < bricks_length; i++){
        if (is_collision(*obj, bricks[i])){
            obj->x -= obj->horizon_speed;
            obj->horizon_speed = -obj->horizon_speed;
            return;
        }
    }
    if (obj->c_type == 'o'){
        TObject tmp = *obj;
        vert_move_object(&tmp, NULL, bricks, bricks_length, bricks, bricks_length);
        if (tmp.is_fly == true){
            obj->x -= obj->horizon_speed;
            obj->horizon_speed = -obj->horizon_speed;
        }
    }
}

void mario_collision(TObject *mario, TObject *&bricks, int &bricks_length){
    for (int i = 0; i < movings_length; i++){
        if (movings[i].c_type == 'o'){
            if (is_collision(*mario, movings[i])){
                if (
                    mario->is_fly 
                    && (mario->vert_speed > 0) 
                    && (mario->y + mario->height < movings[i].y + movings[i].height * 0.5)
                ){
                    score += 50;
                    delete_moving(i);
                    i--;
                    continue;
                } else {
                    player_death(mario, bricks, bricks_length);
                }
            }
        }
        if (movings[i].c_type == '$'){
            if (is_collision(*mario, movings[i])){
                score += 100;
                delete_moving(i);
                i--;
                continue;
            }
        }
    }
}

void horizon_move_map(float dx, TObject *mario, TObject *bricks, int bricks_length){
    mario->x -= dx;
    for (int i = 0; i < bricks_length; i++){
        if (is_collision(*mario, bricks[i])) {
            mario->x += dx;
            return;
        }
    }
    mario->x += dx;
    for (int i = 0; i < bricks_length; i++)
        bricks[i].x += dx;
    for (int i = 0; i < movings_length; i++)
        movings[i].x += dx;
}

void put_object_on_map(char map[MAP_HEIGHT][MAP_WIDTH+1], TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int i_width = (int)round(obj.width);
    int i_height = (int)round(obj.height);
    for (int i = ix; i < (ix + i_width); i++)
        for (int j = iy; j < (iy + i_height); j++)
            if (is_pos_in_map(i, j))
                map[j][i] = obj.c_type;
}

void put_score_on_map(char map[MAP_HEIGHT][MAP_WIDTH+1]){
    char score_str[30];
    sprintf(score_str, "Score: %d", score);
    int len = (int)strlen(score_str);
    for (int i = 0; i < len; i++)
        map[1][i] = score_str[i];
}

void set_cursor(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void show_map(char map[MAP_HEIGHT][MAP_WIDTH+1]){
    map[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
    for (int i = 0; i < MAP_HEIGHT; i++)
        std::cout << map[i];
}

void create_level(TObject *mario,
    TObject *&bricks, int &bricks_length,
    int lvl
    )
{
    system("color 9F");
    bricks_length = 0;
    bricks = (TObject*)realloc(bricks, 0);
    movings_length = 0;
    movings = (TObject*)realloc(movings, 0);
    init_object(mario, 39, 10, 3, 3, '@');
    score = 0;
    if (lvl == 1){
        init_object(get_new_brick(bricks, bricks_length), 20, 20, 40, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 30, 10, 5, 3, '?');
        init_object(get_new_brick(bricks, bricks_length), 50, 10, 5, 3, '?');
        init_object(get_new_brick(bricks, bricks_length), 60, 15, 40, 10, '#');
        init_object(get_new_brick(bricks, bricks_length), 60, 5, 10, 3, '-');
        init_object(get_new_brick(bricks, bricks_length), 70, 5, 5, 3, '?');
        init_object(get_new_brick(bricks, bricks_length), 75, 5, 5, 3, '-');
        init_object(get_new_brick(bricks, bricks_length), 80, 5, 5, 3, '?');
        init_object(get_new_brick(bricks, bricks_length), 85, 5, 10, 3, '-');
        init_object(get_new_brick(bricks, bricks_length), 80, 20, 20, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 120, 15, 10, 10, '#');
        init_object(get_new_brick(bricks, bricks_length), 150, 20, 40, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 210, 15, 10, 10, '+');
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
    }
    if (lvl == 2){
        init_object(get_new_brick(bricks, bricks_length), 20, 20, 40, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 60, 15, 5, 10, '#');
        init_object(get_new_brick(bricks, bricks_length), 80, 20, 20, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 120, 15, 10, 10, '#');
        init_object(get_new_brick(bricks, bricks_length), 150, 20, 40, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 210, 15, 10, 10, '+');
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(), 65, 10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 160, 10, 3, 2, 'o');
    }
    if (lvl == 3){
        init_object(get_new_brick(bricks, bricks_length), 20, 20, 40, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 80, 20, 15, 5, '#');
        init_object(get_new_brick(bricks, bricks_length), 120, 15, 15, 10, '#');
        init_object(get_new_brick(bricks, bricks_length), 160, 10, 15, 15, '+');
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 50, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(), 90, 10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
    }
    max_level = 3;
}