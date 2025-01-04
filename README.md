# Symmetric Encryption Visualization Tool 🔐

An interactive educational tool that demonstrates how symmetric encryption works through animations and step-by-step visualization. This project helps users understand the basic concepts of encryption in a visual and engaging way.

## 🌟 Features

### 1. Interactive Animation Mode

- Visual representation of encryption/decryption process
- Animated key movement between sender and receiver
- Real-time message transformation
- Pause/Resume functionality (Press P)
- Restart capability (Press R)
- Message status indicator

### 2. Step-by-Step Learning Mode

- Interactive text input for custom messages
- Detailed explanation of each encryption step
- Position tracking in the alphabet
- Visual transformation of each character
- Scrollable interface for longer messages
- Educational notes about real-world encryption

## 🛠️ Prerequisites

Before running this project, make sure you have:

1. C++ Compiler (MinGW-w64 recommended for Windows)
2. Raylib Library (version 5.0 or higher)
3. Basic understanding of command line operations

## 📥 Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/Younes769/SYM_enc.git
   cd SYM_enc
   ```

2. **Install Raylib**

   - Download Raylib from [official website](https://www.raylib.com/)
   - For Windows:
     - Extract to `C:/raylib`
     - Ensure the path structure is `C:/raylib/raylib-5.5_win64_mingw-w64`

3. **Set Up Development Environment**
   - Add MinGW-w64 to your system PATH
   - Ensure raylib's include and lib directories are properly set up

## 🚀 Building and Running

1. **Using Make**

   ```bash
   mingw32-make
   ```

2. **Run the Application**
   ```bash
   ./main
   ```

## 🎮 How to Use

### Main Menu

- Choose between two visualization modes:
  - "Watch Animation" for the animated demonstration
  - "Step-by-Step Learning" for interactive learning

### Animation Mode

- Watch how messages are encrypted and decrypted
- Controls:
  - `P` - Pause/Resume animation
  - `R` - Restart animation
  - `ESC` - Return to menu

### Step-by-Step Mode

- Type your own message
- Press Enter to see the encryption process
- Learn how each character is transformed
- Controls:
  - Mouse wheel to scroll through steps
  - `R` - Try a new message
  - `ESC` - Return to menu

## 🔍 Technical Details

### Encryption Method

- Uses a simple shift cipher (Caesar cipher)
- Default shift key: 3 positions
- Maintains case sensitivity
- Handles both uppercase and lowercase letters
- Non-alphabetic characters remain unchanged

### Implementation

- Written in C++ using Raylib for graphics
- Modular design with separate functions for:
  - Encryption/Decryption logic
  - Animation rendering
  - Interactive learning mode
  - Menu system

## 🤝 Contributing

Feel free to contribute to this project:

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## ⚠️ Note

This is an educational tool using a simple cipher for demonstration. Real-world encryption uses much more complex and secure methods.

## 📝 License

This project is open source and available under the MIT License.

## 👥 Authors

- [@Younes769](https://github.com/Younes769)
- [@belkezaimw](https://github.com/belkezaimw) - Collaborator

## 🙏 Acknowledgments

- Raylib library for providing the graphics framework
- The open-source community for inspiration and support
