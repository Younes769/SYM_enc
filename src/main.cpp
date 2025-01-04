#include <raylib.h>
#include <string.h>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Character Animation with Raylib");

    char m[256] = ""; // Input message buffer
    char m1[256]; // Array to store the transformed (encrypted) string
    char m2[256]; // Array to store the decrypted string
    int frameCounter = 0; // Counter to control animation speed
    int letterIndex = 0; // Current letter to display

    char displayedText[256] = ""; // Stores progressively displayed characters
    char decryptedText[256] = ""; // Stores progressively revealed decrypted characters

    bool inputActive = true; // State for text input
    bool decryptionActive = false; // State for decryption input

    SetTargetFPS(60); // Set the game to run at 60 frames per second

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update
        if (inputActive) {
            int key = GetCharPressed();

            // Check if the key is valid and append it to the input string
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (strlen(m) < 255)) {
                    size_t len = strlen(m);
                    m[len] = (char)key;
                    m[len + 1] = '\0';
                }
                key = GetCharPressed();
            }

            // Remove the last character if backspace is pressed
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(m) > 0) {
                m[strlen(m) - 1] = '\0';
            }

            // Process the input and exit input mode on Enter key
            if (IsKeyPressed(KEY_ENTER) && strlen(m) > 0) {
                for (int i = 0; i < strlen(m); i++) {
                    if (m[i] != ' ') { // Skip spaces
                        m1[i] = m[i] + 3; // Add 3 to each character
                    } else {
                        m1[i] = ' '; // Preserve spaces
                    }
                }
                m1[strlen(m)] = '\0'; // Null-terminate the string
                inputActive = false; // Stop input mode
                decryptionActive = true; // Start decryption mode
            }
        } else if (decryptionActive) {
            frameCounter++;
            if (frameCounter >= 30 && letterIndex < strlen(m1)) { // Change letter every 30 frames (~0.5 seconds)
                frameCounter = 0;
                displayedText[letterIndex] = m1[letterIndex]; // Add the next encrypted character
                displayedText[letterIndex + 1] = '\0';

                m2[letterIndex] = m1[letterIndex] - 3; // Decrypt the character
                decryptedText[letterIndex] = m2[letterIndex];
                decryptedText[letterIndex + 1] = '\0';

                letterIndex++;
            }
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (inputActive) {
            DrawText("Enter a message: ", 50, 50, 20, GRAY);
            DrawText(m, 50, 100, 20, BLUE);
            DrawText("Press ENTER to encrypt", 50, 150, 20, DARKGRAY);
        } else if (decryptionActive) {
            DrawText("Original:", 50, 50, 20, GRAY);
            DrawText(m, 200, 50, 20, BLUE);
            DrawText("Encrypted:", 50, 100, 20, GRAY);
            DrawText(displayedText, 200, 100, 20, RED); // Draw progressively revealed encrypted text
            DrawText("Decrypted:", 50, 150, 20, GRAY);
            DrawText(decryptedText, 200, 150, 20, YELLOW); // Draw progressively revealed decrypted text
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
