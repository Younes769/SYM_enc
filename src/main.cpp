#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

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

// Structure to hold step-by-step encryption info
struct EncryptionStep
{
    std::string original;
    std::string encrypted;
    std::string explanation;
};

void RunAnimationMode(void)
{
    const int screenWidth = 1100;
    const int screenHeight = 600;
    int run = 1;
    bool paused = false;

    Color col = GREEN;
    const char *message = "HELLO WORLD";
    int key = 3;
    const char *messagestat = "decrypted";

    // Animation variables
    Vector2 position = {500, 1};
    Vector2 mesposition = {220, 250};
    Vector2 txtposition = {225, 280};
    Vector2 velocity = {1, 1};
    Vector2 velocity2 = {2, 2};

    // Load textures
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

    char *currentMessage = strdup(message);

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        if (IsKeyPressed(KEY_P))
            paused = !paused;

        if (mesposition.x != 220 && mesposition.x >= 780)
        {
            messagestat = "encrypted";
            col = RED;
        }

        if (IsKeyPressed(KEY_R))
        {
            run = 1;
            paused = false;
            position = (Vector2){500, 1};
            mesposition = (Vector2){220, 250};
            txtposition = (Vector2){225, 280};
            free(currentMessage);
            currentMessage = strdup(message);
            col = GREEN;
            messagestat = "decrypted";
            velocity = (Vector2){1, 1};
            velocity2 = (Vector2){2, 2};
        }

        if (!paused && run == 1)
        {
            if (position.x >= 720)
            {
                position.x = 500;
                position.y = 0;
            }

            if (position.x != 500 || position.y != 0)
            {
                position.x -= velocity.x * 1.2f;
                position.y += velocity.y * 1.2f;
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
                char *temp = currentMessage;
                currentMessage = EncryptMessage(currentMessage, key);
                free(temp);
                mesposition.x += velocity2.x;
                velocity.x *= -1;
            }

            if (position.x >= 720)
            {
                position.x = 500;
                position.y = 0;
                char *temp = currentMessage;
                currentMessage = DecryptMessage(currentMessage, key);
                free(temp);
                run = 0;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(texture, position.x, position.y, WHITE);
        DrawTexture(pc1texture, 10, 180, WHITE);
        DrawTexture(pc2texture, 880, 180, WHITE);
        DrawTexture(mestexture, mesposition.x, mesposition.y, WHITE);
        DrawText(currentMessage, txtposition.x, txtposition.y, 12, BLACK);
        DrawText("message :", 350, 500, 20, BLACK);
        DrawText(currentMessage, 450, 500, 20, BLACK);
        DrawText("message status :", 350, 525, 20, BLACK);
        DrawText(messagestat, 520, 525, 20, col);

        if (paused)
        {
            DrawText("Paused (Press P to resume)", 10, 10, 20, RED);
        }
        else
        {
            DrawText("Press P to pause, R to restart", 10, 10, 20, DARKGRAY);
        }
        DrawText("Press ESC to return to menu", 10, 30, 20, DARKGRAY);
        EndDrawing();
    }

    free(currentMessage);
    UnloadTexture(texture);
    UnloadTexture(pc1texture);
    UnloadTexture(pc2texture);
    UnloadTexture(mestexture);
}

void RunStepByStepMode(void)
{
    const int screenWidth = 1100;
    const int screenHeight = 600;

    char inputText[256] = "";
    int textSize = 0;
    bool isEditing = true;
    const int encryptionKey = 3;
    std::vector<EncryptionStep> steps;
    Rectangle textBox = {screenWidth / 2 - 200, 100, 400, 40};
    Vector2 scrollPosition = {0, 0};
    float maxScroll = 0; // To track maximum scroll position

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        // Input handling
        if (isEditing)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (textSize < 255))
                {
                    inputText[textSize] = (char)key;
                    textSize++;
                    inputText[textSize] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (textSize > 0)
                {
                    textSize--;
                    inputText[textSize] = '\0';
                }
            }

            if (IsKeyPressed(KEY_ENTER) && textSize > 0)
            {
                isEditing = false;
                steps.clear();

                // Introduction step
                EncryptionStep intro;
                intro.original = inputText;
                intro.encrypted = inputText;
                intro.explanation = "Welcome to the Symmetric Encryption Tutorial!";
                steps.push_back(intro);

                // Explain the concept
                EncryptionStep concept;
                concept.original = inputText;
                concept.encrypted = inputText;
                concept.explanation = "Symmetric encryption uses the same key for encryption and decryption.";
                steps.push_back(concept);

                // Show the key and explain shift
                EncryptionStep keyStep;
                keyStep.original = inputText;
                keyStep.encrypted = inputText;
                keyStep.explanation = TextFormat("We'll use a shift cipher with key = %d (shifting each letter %d positions forward)",
                                                 encryptionKey, encryptionKey);
                steps.push_back(keyStep);

                // Process each character with detailed explanation
                std::string currentText = inputText;
                for (int i = 0; currentText[i] != '\0'; i++)
                {
                    if (isalpha(currentText[i]))
                    {
                        EncryptionStep step;
                        step.original = currentText;

                        char base = isupper(currentText[i]) ? 'A' : 'a';
                        int originalPos = currentText[i] - base;
                        char encrypted = base + (originalPos + encryptionKey) % 26;
                        currentText[i] = encrypted;

                        step.encrypted = currentText;
                        step.explanation = TextFormat("Letter '%c' (position %d in alphabet) -> shift by %d -> '%c' (position %d)",
                                                      step.original[i],
                                                      originalPos + 1,
                                                      encryptionKey,
                                                      encrypted,
                                                      ((originalPos + encryptionKey) % 26) + 1);
                        steps.push_back(step);
                    }
                }

                // Final explanation
                EncryptionStep final;
                final.original = inputText;
                final.encrypted = currentText;
                final.explanation = "Final Result: Each letter was shifted in the alphabet while maintaining case.";
                steps.push_back(final);

                // Security note
                EncryptionStep security;
                security.original = inputText;
                security.encrypted = currentText;
                security.explanation = "Note: This is a simple cipher for learning. Real encryption uses more complex methods!";
                steps.push_back(security);
            }
        }

        // Mouse wheel for scrolling - Modified for smoother scrolling
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            scrollPosition.y -= wheel * 40;
            if (scrollPosition.y < 0)
                scrollPosition.y = 0;
            if (scrollPosition.y > maxScroll)
                scrollPosition.y = maxScroll;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Interactive Encryption Learning", screenWidth / 2 - MeasureText("Interactive Encryption Learning", 30) / 2, 40, 30, BLACK);

        if (isEditing)
        {
            DrawRectangleRec(textBox, LIGHTGRAY);
            DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, BLACK);
            DrawText(inputText, textBox.x + 5, textBox.y + 10, 20, BLACK);
            DrawText("Type your message and press ENTER to see encryption in action!",
                     screenWidth / 2 - 250, 160, 20, DARKGRAY);
        }
        else
        {
            // Calculate total content height first
            float totalHeight = 0;
            for (size_t i = 0; i < steps.size(); i++)
            {
                totalHeight += 90; // Height of each step
            }
            maxScroll = totalHeight - (screenHeight - 200); // Update max scroll position
            if (maxScroll < 0)
                maxScroll = 0;

            // Draw scrollbar
            float scrollBarHeight = (screenHeight - 200) * ((screenHeight - 200) / totalHeight);
            float scrollBarY = 180 + (scrollPosition.y / maxScroll) * (screenHeight - 200 - scrollBarHeight);
            if (maxScroll > 0)
            {
                DrawRectangle(screenWidth - 20, 180, 10, screenHeight - 200, LIGHTGRAY);
                DrawRectangle(screenWidth - 20, scrollBarY, 10, scrollBarHeight, GRAY);
            }

            // Draw content
            float yPos = 180 - scrollPosition.y;
            for (const auto &step : steps)
            {
                // Only draw if in visible area (with some padding)
                if (yPos + 90 >= 160 && yPos <= screenHeight)
                {
                    // Draw explanation with a light background
                    DrawRectangle(30, yPos - 5, screenWidth - 70, 30, LIGHTGRAY);
                    DrawText(step.explanation.c_str(), 50, yPos, 20, BLACK);

                    // Draw the text transformation
                    if (step.original != step.encrypted)
                    {
                        DrawText(step.original.c_str(), 50, yPos + 35, 20, DARKGRAY);
                        DrawText("→", screenWidth / 2 - 20, yPos + 35, 20, BLACK);
                        DrawText(step.encrypted.c_str(), screenWidth / 2 + 20, yPos + 35, 20, RED);
                    }

                    DrawLine(30, yPos + 70, screenWidth - 30, yPos + 70, LIGHTGRAY);
                }
                yPos += 90;
            }

            // Draw scroll indicators if needed
            if (scrollPosition.y > 0)
            {
                DrawText("▲", screenWidth - 25, 160, 20, DARKGRAY);
            }
            if (scrollPosition.y < maxScroll)
            {
                DrawText("▼", screenWidth - 25, screenHeight - 20, 20, DARKGRAY);
            }

            DrawText("Press R to try with a new message", 10, screenHeight - 30, 20, DARKGRAY);
            if (IsKeyPressed(KEY_R))
            {
                isEditing = true;
                textSize = 0;
                inputText[0] = '\0';
                steps.clear();
                scrollPosition = {0, 0};
            }
        }

        DrawText("Press ESC to return to menu", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }
}

int main(void)
{
    const int screenWidth = 1100;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Symmetric Encryption Visualization");
    SetTargetFPS(60);

    enum GameScreen
    {
        MENU = 0,
        ANIMATION,
        STEP_BY_STEP
    } currentScreen = MENU;

    Rectangle animationButton = {screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 60};
    Rectangle stepByStepButton = {screenWidth / 2 - 150, screenHeight / 2 + 30, 300, 60};
    Rectangle exitButton = {screenWidth / 2 - 150, screenHeight / 2 + 110, 300, 60};

    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
        case MENU:
        {
            Vector2 mousePoint = GetMousePosition();

            // Check button clicks
            if (CheckCollisionPointRec(mousePoint, animationButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = ANIMATION;

            if (CheckCollisionPointRec(mousePoint, stepByStepButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = STEP_BY_STEP;

            if (CheckCollisionPointRec(mousePoint, exitButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                break;

            BeginDrawing();
            ClearBackground(WHITE);

            DrawText("Symmetric Encryption", screenWidth / 2 - MeasureText("Symmetric Encryption", 40) / 2, 100, 40, BLACK);
            DrawText("Learning Tool", screenWidth / 2 - MeasureText("Learning Tool", 30) / 2, 150, 30, DARKGRAY);

            // Draw buttons
            DrawRectangleRec(animationButton, CheckCollisionPointRec(mousePoint, animationButton) ? LIGHTGRAY : GRAY);
            DrawRectangleRec(stepByStepButton, CheckCollisionPointRec(mousePoint, stepByStepButton) ? LIGHTGRAY : GRAY);
            DrawRectangleRec(exitButton, CheckCollisionPointRec(mousePoint, exitButton) ? LIGHTGRAY : GRAY);

            DrawText("Watch Animation", animationButton.x + 60, animationButton.y + 20, 20, BLACK);
            DrawText("Step-by-Step Learning", stepByStepButton.x + 50, stepByStepButton.y + 20, 20, BLACK);
            DrawText("Exit", exitButton.x + 130, exitButton.y + 20, 20, BLACK);
            EndDrawing();
        }
        break;

        case ANIMATION:
            RunAnimationMode();
            currentScreen = MENU;
            break;

        case STEP_BY_STEP:
            RunStepByStepMode();
            currentScreen = MENU;
            break;
        }

        if (WindowShouldClose())
            break;
    }

    CloseWindow();
    return 0;
}
