#include <iostream>
#include <math.h>

#define mapWidth 80
#define mapHeith 25


typedef struct SObject {
    float x, y;
    float width, heigh;
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
}


void putObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width); 
    int iHeigh = (int)round(obj.heigh);

    for (int i = ix; i < (ix + iWidth); i++){
        for (int j = iy; j < (iy + iHeigh); j++){
            map[j][i] = '@';
        }
    }
    map[iy][ix] = '@';
} 


int main(){
    initObject(&mario, 39, 10, 3, 3);
    clearMap();
    putObjectOnMap(mario);
    showMap();
    return 0;
}