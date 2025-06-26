#include "include/raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define WINDOWHEIGHT 1000
#define WINDOWWIDTH 1000
#define WINDOWNAME "Flappy Dom"
#define GAP 200
int colCnt = 0;
typedef struct Dom
{
    float velocity;
    float gravity;
    float jumpStrength;
    Rectangle dom;
} Dom;

typedef struct Collumn
{
    Rectangle collum1;
    Rectangle collum2;
    int score;
} Collumn;

Dom InitDom(float velocity, float gravity, float jumpStrength, Rectangle dom)
{
    Dom initDom = {
        .velocity = velocity,
        .gravity = gravity,
        .jumpStrength = jumpStrength,
        .dom = dom};

    return initDom;
}

Collumn InitCollumn()
{
    Rectangle collum1 = {
        .height = GetRandomValue(10, WINDOWHEIGHT / 2),
        .width = 50,
        .x = WINDOWWIDTH,
        .y = 0,
    };

    Rectangle collum2 = {
        .height = WINDOWHEIGHT - (collum1.height + GAP),
        .width = 50,
        .x = WINDOWWIDTH,
        .y = (collum1.height + GAP),
    };

    Collumn initColum = {
        .collum1 = collum1,
        .collum2 = collum2,
        .score = ++colCnt
    };

    return initColum;
}

void updateJump(Dom *dom)
{
    dom->velocity = -dom->jumpStrength;
}

void updateDom(Dom *dom)
{
    dom->velocity += GetFrameTime() * dom->gravity;
    dom->dom.y += dom->velocity * GetFrameTime();
}

void updateCol(Collumn *collumn)
{
    collumn->collum1.x = collumn->collum2.x = collumn->collum1.x - GetFrameTime() * 100;
    if (collumn->collum1.x <= 0)
    {
        *collumn = InitCollumn();
    }
}

char* toString(int x) {
    char* res = (char*)calloc(10,sizeof(char));
    int n = x == 0 ? 1 : (int)log10(x) + 1;
    for(int i = 0;i < n;x/=10,i++) {
        int mod = x % 10;
        res[i] = (mod + '0');
    }
    for(int i =0,j = n-1;i <= j;++i,--j) {
        char temp = res[i];
        res[i] = res[j];
        res[j] = temp;
    };
    return res;
}

bool checkCollision(Dom *dom, Collumn *col)
{
    return (!CheckCollisionRecs(dom->dom, col->collum1) &&
            !CheckCollisionRecs(dom->dom, col->collum2) && dom->dom.y + dom->dom.height < WINDOWHEIGHT);
}

int main(void)
{

    InitWindow(WINDOWWIDTH, WINDOWHEIGHT, WINDOWNAME);
    SetTargetFPS(60);

    Collumn colArr[5];

    for (int i = 0; i < (sizeof(colArr) / sizeof(Collumn)); i++)
    {
        Collumn col = InitCollumn();

        colArr[i] = col;
    }

    for (int i = 1; i < (sizeof(colArr) / sizeof(Collumn)); i++)
    {
        colArr[i].collum1.x = colArr[i - 1].collum1.x + 200;
        colArr[i].collum2.x = colArr[i - 1].collum1.x + 200;
    }

    // init dom
    Rectangle domRec = {
        .height = 30,
        .width = 30,
        .x = 300,
        .y = 470};

    Dom dom = InitDom(0, 1000, 300, domRec);

    bool isCollision = false;
    int point = 1230;

    while (!WindowShouldClose())
    {
        for (int i = 0; i < (sizeof(colArr) / sizeof(Collumn)); i++)
        {
            if (!checkCollision(&dom, &colArr[i]))
            {
                isCollision = true;
                break;
            }

            if (dom.dom.x >= colArr[i].collum1.x) {
                point = colArr[i].score;
                printf("%d", point);
            }
        }

        if (!isCollision)
        {
            for (int i = 0; i < (sizeof(colArr) / sizeof(Collumn)); i++)
            {

                updateCol(&colArr[i]);
            }
            updateDom(&dom);
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            updateJump(&dom);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        if (isCollision)
        {
            DrawText("Game over", 50, 50, 30, RED);
        }

        DrawRectangleRec(dom.dom, GREEN);

        for (int i = 0; i < (sizeof(colArr) / sizeof(Collumn)); i++)
        {
            DrawRectangleRec(colArr[i].collum1, RED);
            DrawRectangleRec(colArr[i].collum2, YELLOW);
        }
        DrawText(toString(point),0,0,200,GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
