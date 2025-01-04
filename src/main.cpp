#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *EncryptMessage(const char *message, int key)
{
    char *encryptedMessage = (char *)malloc(strlen(message) + 1);
    if (!encryptedMessage)
    {
        return NULL; // Handle memory allocation failure
    }

    for (int i = 0; message[i] != '\0'; i++)
    {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            encryptedMessage[i] = 'A' + (message[i] - 'A' + key) % 26;
        }
        else if (message[i] >= 'a' && message[i] <= 'z')
        {
            encryptedMessage[i] = 'a' + (message[i] - 'a' + key) % 26;
        }
        else
        {
            encryptedMessage[i] = message[i];
        }
    }

    encryptedMessage[strlen(message)] = '\0';
    return encryptedMessage;
}

char *DecryptMessage(const char *message, int key)
{
    char *decryptedMessage = (char *)malloc(strlen(message) + 1);
    if (!decryptedMessage)
    {
        return NULL;
    }

    for (int i = 0; message[i] != '\0'; i++)
    {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            decryptedMessage[i] = 'A' + (message[i] - 'A' - key + 26) % 26;
        }
        else if (message[i] >= 'a' && message[i] <= 'z')
        {
            decryptedMessage[i] = 'a' + (message[i] - 'a' - key + 26) % 26;
        }
        else
        {
            decryptedMessage[i] = message[i];
        }
    }

    decryptedMessage[strlen(message)] = '\0';

    return decryptedMessage;
}

int main(void)
{
    const int screenWidth = 1100;
    const int screenHeight = 600;
    int run = 1;
    bool paused = false; // Pause state

    InitWindow(screenWidth, screenHeight, "Symmetric Encryption Animation");
    Color col = GREEN;
    SetTargetFPS(60);

    char *message = "HELLO WORLD";
    int key = 3;
    char *messagestat = "decrypted";

    // les variables te3 l animation
    Vector2 position = {500, 1};
    Vector2 mesposition = {220, 250};
    Vector2 txtposition = {225, 280};
    Vector2 velocity = {1, 1};
    Vector2 velocity2 = {2, 2};

    // ndiro load l images w nrj3ohom texture bch nmanipuliwhom facilmnt
    Image keys = LoadImage("img/key.png");
    ImageResize(&keys, 80, 80);
    Texture2D texture = LoadTextureFromImage(keys);
    UnloadImage(keys);

    Image pc1 = LoadImage("img/pc.png");
    ImageResize(&pc1, 200, 200);
    Texture2D pc1texture = LoadTextureFromImage(pc1);
    UnloadImage(pc1);

    Image pc2 = LoadImage("img/pc.png");
    ImageResize(&pc2, 200, 200);
    Texture2D pc2texture = LoadTextureFromImage(pc2);
    UnloadImage(pc2);

    Image mes = LoadImage("img/messag.png");
    ImageResize(&mes, 90, 90);
    Texture2D mestexture = LoadTextureFromImage(mes);
    UnloadImage(mes);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {   


        // Pause 3bz mra ya 7amid
        if (IsKeyPressed(KEY_P))
        {
            paused = !paused;
        }

        

        // Restart 3bz mra mktoba press mchi hold
        if (IsKeyPressed(KEY_R))
        {
            run = 1;
            paused = false;
            position = (Vector2){500, 1};
            mesposition = (Vector2){220, 250};
            txtposition = (Vector2){225, 280};
            message = "HELLO WORLD";
            col = GREEN;
            messagestat = "decrypted";
            velocity = (Vector2){1, 1};
            velocity2 = (Vector2){2, 2};
        }

        // bach nruniw l program w npusiwah
        if (!paused && run == 1)
        {
            if (position.x >= 720)
            {
                position.x = 500;
                position.y = 0;
            }

            if (position.x != 500 || position.y != 0)
            {
                position.x -= velocity.x * 1.2;
                position.y += velocity.y * 1.2;
            }

            if (position.x == 500 && position.y == 0)
            {
                mesposition.x += velocity2.x;
                txtposition.x += velocity2.x;

                if (mesposition.x >= 785 && txtposition.x >= 785)
                {
                    position.x = 501;        
                }
            }

            if (position.x <= 300)
            {
                position.x = 500;
                position.y = 0;
                message = EncryptMessage(message, key);
                mesposition.x += velocity2.x;
                velocity.x *= -1;
            }

            if (position.x >= 720)
            {
                position.x = 500;
                position.y = 0;
                message = DecryptMessage(message, key);
                run = 0;
            }
        }

        // nbdaw nrsmo
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(texture, position.x, position.y, WHITE);
        DrawTexture(pc1texture, 10, 180, WHITE);
        DrawTexture(pc2texture, 880, 180, WHITE);
        DrawTexture(mestexture, mesposition.x, mesposition.y, WHITE);
        DrawText(message, txtposition.x, txtposition.y, 12, BLACK);
        DrawText("message :", 350, 500, 20, BLACK);
        DrawText(message, 450, 500, 20, BLACK);


        if (paused)
        {
            DrawText("Paused (Press P to resume)", 10, 10, 20, RED);
        }
        else
        {
            DrawText("Press P to pause, R to restart", 10, 10, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // nghl9o l window
    CloseWindow();

    return 0;
}
