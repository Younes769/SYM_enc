#include "raylib.h"
#include <string.h>
#include <stdlib.h>

// Caesar cipher encryption
char EncryptChar(char c, int shift) {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + shift) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + shift) % 26;
    }
    return c; // Non-alphabetic characters remain unchanged
}

int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 600;

    // Initialize Raylib
    InitWindow(screenWidth, screenHeight, "Select Menu with Encryption");
    SetTargetFPS(60);

    Color bgColor = DARKGRAY;
    Color buttonColor = LIGHTGRAY;
    Color buttonHoverColor = GRAY;
    Color textColor = WHITE;

    // Define button rectangles
    Rectangle button1 = { screenWidth / 2 - 150, 200, 300, 50 };
    Rectangle button2 = { screenWidth / 2 - 150, 300, 300, 50 };

    int selectedOption = -1; // -1: None, 0: Option 1, 1: Option 2

    // Encryption variables
    char inputText[256] = "";
    char encryptedText[256] = "";
    int currentIndex = 0;
    int shiftValue = 3; // Example shift for Caesar cipher
    bool encryptionComplete = false;

    while (!WindowShouldClose()) {
        // Check mouse clicks on buttons
        Vector2 mousePoint = GetMousePosition();

        if (selectedOption == -1) {
            // Main menu
            if (CheckCollisionPointRec(mousePoint, button1)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedOption = 0; // Option 1 selected
                }
            }
            if (CheckCollisionPointRec(mousePoint, button2)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedOption = 1; // Option 2 selected
                }
            }
        } else if (selectedOption == 0) {
            // Option 1: Encryption Animation
            if (!encryptionComplete && IsKeyPressed(KEY_ENTER)) {
                if (currentIndex < strlen(inputText)) {
                    char currentChar = inputText[currentIndex];
                    char encryptedChar = EncryptChar(currentChar, shiftValue);
                    encryptedText[currentIndex] = encryptedChar;
                    currentIndex++;
                    encryptedText[currentIndex] = '\0'; // Null-terminate
                } else {
                    encryptionComplete = true;
                }
            }

            // Typing text input
            if (!encryptionComplete && currentIndex == 0) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (strlen(inputText) < sizeof(inputText) - 1)) {
                        size_t len = strlen(inputText);
                        inputText[len] = (char)key;
                        inputText[len + 1] = '\0';
                    }
                    key = GetCharPressed();
                }
            }

            // Clear text input with backspace
            if (IsKeyPressed(KEY_BACKSPACE) && currentIndex == 0) {
                size_t len = strlen(inputText);
                if (len > 0) inputText[len - 1] = '\0';
            }
        }

        // Draw UI
        BeginDrawing();
        ClearBackground(bgColor);

        if (selectedOption == -1) {
            // Draw main menu
            DrawText("Select an Option", screenWidth / 2 - MeasureText("Select an Option", 30) / 2, 100, 30, textColor);

            // Encryption Button
            DrawRectangleRec(button1, CheckCollisionPointRec(mousePoint, button1) ? buttonHoverColor : buttonColor);
            DrawText("Option 1: Encryption", screenWidth / 2 - MeasureText("Option 1: Encryption", 20) / 2, 215, 20, textColor);

            // Placeholder Button for Option 2
            DrawRectangleRec(button2, CheckCollisionPointRec(mousePoint, button2) ? buttonHoverColor : buttonColor);
            DrawText("Option 2: Coming Soon", screenWidth / 2 - MeasureText("Option 2: Coming Soon", 20) / 2, 315, 20, textColor);
        } else if (selectedOption == 0) {
            // Option 1: Encryption UI
            DrawText("Encryption Animation", screenWidth / 2 - MeasureText("Encryption Animation", 30) / 2, 20, 30, textColor);

            // Input text section
            DrawRectangle(50, 100, screenWidth - 100, 50, Fade(textColor, 0.2f));
            DrawText("Enter text to encrypt:", 60, 110, 20, textColor);
            DrawText(inputText, 300, 110, 20, textColor);

            // Encrypted text section
            DrawRectangle(50, 200, screenWidth - 100, 50, Fade(textColor, 0.2f));
            DrawText("Encrypted Text:", 60, 210, 20, textColor);
            DrawText(encryptedText, 300, 210, 20, RED);

            // Status messages
            if (encryptionComplete) {
                DrawText("Encryption Complete! Press ESC to exit.", screenWidth / 2 - MeasureText("Encryption Complete! Press ESC to exit.", 20) / 2, 300, 20, textColor);
            } else if (strlen(inputText) > 0) {
                DrawText("Press Enter to encrypt the next letter.", screenWidth / 2 - MeasureText("Press Enter to encrypt the next letter.", 20) / 2, 300, 20, textColor);
            } else {
                DrawText("Type text and press Enter to start encryption.", screenWidth / 2 - MeasureText("Type text and press Enter to start encryption.", 20) / 2, 300, 20, textColor);
            }

            // Footer
            DrawText("Press BACKSPACE to clear text.", 50, screenHeight - 50, 20, GRAY);
        }

        EndDrawing();
    }

    // Close Raylib
    CloseWindow();

    return 0;
}
