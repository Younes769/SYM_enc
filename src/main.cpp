#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *EncryptMessage(const char *message, int key) {

    char *encryptedMessage = (char *)malloc(strlen(message) + 1); 
    if (!encryptedMessage) {
        return NULL; // Handle memory allocation failure
    }

  
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            encryptedMessage[i] = 'A' + (message[i] - 'A' + key) % 26;
        } else if (message[i] >= 'a' && message[i] <= 'z') {
            encryptedMessage[i] = 'a' + (message[i] - 'a' + key) % 26;
        } else {
            encryptedMessage[i] = message[i]; 
        }
    }

    encryptedMessage[strlen(message)] = '\0';
    return encryptedMessage;
}


char *DecryptMessage(const char *message, int key) {
    
    char *decryptedMessage = (char *)malloc(strlen(message) + 1); 
    if (!decryptedMessage) {
        return NULL; 
    }

  
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            decryptedMessage[i] = 'A' + (message[i] - 'A' - key + 26) % 26; 
        } else if (message[i] >= 'a' && message[i] <= 'z') {
            decryptedMessage[i] = 'a' + (message[i] - 'a' - key + 26) % 26; 
        } else {
            decryptedMessage[i] = message[i]; 
        }
    }

    // Null-terminate the decrypted string
    decryptedMessage[strlen(message)] = '\0';

    return decryptedMessage;
}

int main(void) {
    const int screenWidth = 1100;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Symmetric Encryption Animation");

    SetTargetFPS(60);

    char *message = "HELLO world!";
    int key = 3;  
 
    Vector2 position = {600, 0};  // Starting position
    Vector2 mesposition = {220, 250};  // Starting position
    Vector2 velocity = {1, 1};      // Speed in pixels per frame

    Image keys = LoadImage("img/key.png"); //n7oto l image f var
    ImageResize(&keys, 80, 80); 
    Texture2D texture = LoadTextureFromImage(keys);          
    UnloadImage(keys);  

    Image pc1 = LoadImage("img/pc.png"); //n7oto l image f var
    ImageResize(&pc1, 200, 200); 
    Texture2D pc1texture = LoadTextureFromImage(pc1);          
    UnloadImage(pc1);

    Image pc2 = LoadImage("img/pc.png"); //n7oto l image f var
    ImageResize(&pc2, 200, 200); 
    Texture2D pc2texture = LoadTextureFromImage(pc2);          
    UnloadImage(pc2);

    Image mes = LoadImage("img/messag.png"); //n7oto l image f var
    ImageResize(&mes, 90, 90); 
    Texture2D mestexture = LoadTextureFromImage(mes);          
    UnloadImage(mes);

    SetTargetFPS(60);     
    

    while (!WindowShouldClose())    
    {
        position.x -= velocity.x;
        position.y += velocity.y;
        if (position.x <= 350) {
            position.x = 600;
            position.y = 0;
            message =  EncryptMessage(message , key);

            velocity.x *= -1;
            
        } 


        if (position.x >= 800) {
            position.x = 600;
            position.y = 0;
            message =  DecryptMessage(message , key);
            velocity.x *= -1;
        }



        BeginDrawing();

            ClearBackground(WHITE);
            
            DrawTexture(texture, position.x, position.y, WHITE);
            DrawTexture(pc1texture, 10, 180, WHITE);
            DrawTexture(pc2texture, 880, 180, WHITE);
            DrawTexture(mestexture, mesposition.x, mesposition.y, WHITE);
            DrawText(message, 230, 270, 12, BLACK);
        EndDrawing();
        
    }


    UnloadTexture(texture);       

    CloseWindow();                
    

    
    return 0;
}
