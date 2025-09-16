#include <iostream>
#include <math.h>
#include <Windows.h>

#define mapWidth 80
#define mapHeith 25


typedef struct SObject {
    float x, y;
    float width, heigh;
    float vertSpeed;
} TObject;


char map[mapHeith][mapWidth+1];
TObject mario;


void clearMap() {
    for (int i = 0; i < mapWidth; i++){
        map[0][i] = '.';
    }
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeith; j++){
        for (int i = 0; i <= mapWidth; i++){
            map[j][i] = map[0][i];
        }
    }
}


void showMap()
{
    map[mapHeith - 1][mapWidth - 1] = '\0';
    for (int i = 0; i < mapHeith; i++){
        std::cout << map[i];
    }
}


void setObjectPos(TObject *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}


void initObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeigh){
    setObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).heigh = oHeigh;
    (*obj).vertSpeed = 0;
}


void vertMoveObject(TObject *obj){
    (*obj).vertSpeed += 0.05;
    setObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
}


void putObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width); 
    int iHeigh = (int)round(obj.heigh);

    for (int i = ix; i < (ix + iWidth); i++){
        for (int j = iy; j < (iy + iHeigh); j++){
            if (isPosInMap(i, j)){
                map[j][i] = '@';
            }
        }
    }
    map[iy][ix] = '@';
} 


bool isPosInMap(int x, int y){
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeith));
}

void setCur(int x, int y){
    COORD coord; 
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord );
}

int main(){
    initObject(&mario, 39, 10, 3, 3);
    do {
        clearMap();
        vertMoveObject(&mario);
        putObjectOnMap(mario);
        setCur(0, 0);
        showMap();
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);  
    system("pause");
}