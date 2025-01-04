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
    InitWindow(screenWidth, screenHeight, "Symmetric Encryption Animation");
    Color col = GREEN;
    SetTargetFPS(60);

    // Input box variables
    char inputText[256] = "";  // Store input text
    int letterCount = 0;       // Count letters in input
    Rectangle textBox = { 350, 100, 300, 30 };  // Input text box
    bool mouseOnText = false;  // Check if mouse is on text box
    bool isInputActive = false;  // Check if we're typing
    int framesCounter = 0;     // Frames counter for cursor blink

    const char *message = "Click to enter message";  // Default message
    int key = 3;
    const char *messagestat = "decrypted";
    Vector2 position = {500, 1}; // win ybda l key
    Vector2 mesposition = {220, 250};
    Vector2 txtposition = {225, 280};
    Vector2 velocity = {1, 1};
    Vector2 velocity2 = {2, 2};

    Image keys = LoadImage("img/key.png"); // n7oto l image f var
    ImageResize(&keys, 80, 80);
    Texture2D texture = LoadTextureFromImage(keys);
    UnloadImage(keys);

    Image pc1 = LoadImage("img/pc.png"); // n7oto l image f var
    ImageResize(&pc1, 200, 200);
    Texture2D pc1texture = LoadTextureFromImage(pc1);
    UnloadImage(pc1);

    Image pc2 = LoadImage("img/pc.png"); // n7oto l image f var
    ImageResize(&pc2, 200, 200);
    Texture2D pc2texture = LoadTextureFromImage(pc2);
    UnloadImage(pc2);

    Image mes = LoadImage("img/messag.png"); // n7oto l image f var
    ImageResize(&mes, 90, 90);
    Texture2D mestexture = LoadTextureFromImage(mes);
    UnloadImage(mes);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update input box
        mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);
        
        if (mouseOnText && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isInputActive = true;
            letterCount = strlen(inputText);
        } else if (!mouseOnText && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isInputActive = false;
        }

        if (isInputActive) {
            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed
            while (key > 0) {
                // Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < 255)) {
                    inputText[letterCount] = (char)key;
                    inputText[letterCount + 1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();  // Check next character in the queue
            }

            // Delete characters
            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                inputText[letterCount] = '\0';
            }

            // Submit text
            if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
                message = inputText;
                isInputActive = false;
                run = 1;  // Restart animation
                // Reset positions to starting points
                position = (Vector2){ 500, 1 };
                mesposition = (Vector2){ 220, 250 };
                txtposition = (Vector2){ 225, 280 };
                velocity.x = abs(velocity.x);  // Ensure velocity is positive
                messagestat = "decrypted";
                col = GREEN;
            }
        }

        // Animation logic
        if (run == 1)
        {
            if (position.x >= 720)
            {
                position.x = 500;
                position.y = 1;
            }

            // Key moves down to first computer
            if (position.x == 500 && position.y < 180)
            {
                position.y += velocity.y * 1.2;
                
                if (position.y >= 180)  // Reached first PC
                {
                    message = EncryptMessage(message, key);
                    messagestat = "encrypted";
                    col = RED;
                    position.x = 501;  // Trigger next phase
                }
            }
            
            // Message moves to second computer while key returns up
            if (position.x == 501)
            {
                mesposition.x += velocity2.x;
                txtposition.x += velocity2.x;
                position.y -= velocity.y * 1.2;
                
                if (position.y <= 1)
                {
                    position.y = 1;
                }
                
                if (mesposition.x >= 785)
                {
                    position.x = 720;  // Move key to second PC
                }
            }

            // Key moves down to second computer
            if (position.x == 720)
            {
                position.y += velocity.y * 1.2;
                
                if (position.y >= 180)  // Reached second PC
                {
                    message = DecryptMessage(message, key);
                    messagestat = "decrypted";
                    col = GREEN;
                    run = 0;
                    position = (Vector2){ 500, 1 };
                }
            }
        }
        

        BeginDrawing();

        ClearBackground(WHITE);
        DrawTexture(texture, position.x, position.y, WHITE);
        DrawTexture(pc1texture, 10, 180, WHITE);
        DrawTexture(pc2texture, 880, 180, WHITE);
        DrawTexture(mestexture, mesposition.x, mesposition.y, WHITE);
        DrawText(message, txtposition.x, txtposition.y, 12, BLACK);
        DrawText("message :", 350, 500, 20, BLACK);
        DrawText(message, 450, 500, 20, BLACK);
        DrawText("messag status :", 350, 525, 20, BLACK);
        DrawText(messagestat, 520, 525, 20, col);

        // Draw input box
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, mouseOnText ? RED : DARKGRAY);
        DrawText(inputText, textBox.x + 5, textBox.y + 4, 20, BLACK);

        // Draw cursor blink
        if (isInputActive) {
            framesCounter++;
            if (((framesCounter/30)%2) == 0) {
                DrawText("_", textBox.x + 8 + MeasureText(inputText, 20), textBox.y + 4, 20, BLACK);
            }
        }

        // Draw instruction
        DrawText("Type your message and press ENTER", 350, 70, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}