#include <iostream>
#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25


typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool isFly;
    char cType; 
} TObject;


char map[mapHeight][mapWidth+1];
TObject mario;
TObject *brick = NULL;
int brickLength;


void clearMap() {
    for (int i = 0; i < mapWidth; i++){
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++){
        for (int i = 0; i <= mapWidth; i++){
            map[j][i] = map[0][i];
        }
    }
}


void showMap()
{
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int i = 0; i < mapHeight   ; i++){
        std::cout << map[i];
    }
}


void setObjectPos(TObject *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}


void initObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeigh, char inType){
    setObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeigh;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
}   


bool isCollision(TObject o1, TObject o2){
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}


void vertMoveObject(TObject *obj){
    (*obj).vertSpeed += 0.05;
    (*obj).isFly = true;
    setObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
    for (int i = 0; i < brickLength; i++){
        if (isCollision(*obj, brick[i])){
            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;
            (*obj).isFly = false;
            break;
        }
    }
}


bool isPosInMap(int x, int y){
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}



void putObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width); 
    int iHeigh = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++){
        for (int j = iy; j < (iy + iHeigh); j++){
            if (isPosInMap(i, j)){
                map[j][i] = obj.cType;
            }
        }
    }
} 


void setCur(int x, int y){
    COORD coord; 
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord );
}


void horizonMoveMap(float dx){
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++){
        if (isCollision(mario, brick[i])) {
            mario.x += dx;
            return;
        }
    }
    for (int i = 0; i < brickLength; i++){
        brick[i].x += dx;
    }
}


void createLevel(){
    initObject(&mario, 39, 10, 3, 3, '@');
    brickLength = 5; 
    brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
    initObject(brick, 20, 20, 40, 5, '#');
    initObject(brick+1, 60, 15, 5, 10, '#');
    initObject(brick+2, 80, 20, 20, 5, '#');
    initObject(brick+3, 120, 15, 10, 10, '#');
    initObject(brick+4, 150, 20, 40, 5, '#');

}

int main(){
    createLevel();
    do {
        clearMap();

        if ((mario.isFly == false) && (GetKeyState(VK_SPACE) < 0)) mario.vertSpeed = -0.7;
        if (GetKeyState('A') < 0) horizonMoveMap(1);
        if (GetKeyState('D') < 0) horizonMoveMap(-1); 

        if (mario.y > mapHeight) createLevel(); 

        vertMoveObject(&mario);
        for (int i = 0; i < brickLength; i++){
            putObjectOnMap(brick[i]);
        }
        putObjectOnMap(mario);
        setCur(0, 0);
        showMap();  
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);  
}