# SucChess - Chess Game in C++ using Qt

## ♟️ About the Project

`SucChess` is a **chess game** developed in **C++** with a graphical user interface built using **Qt**. It provides an immersive and complete chess-playing experience with various useful features and a user-friendly design.

## 🚀 Features

- ✅ **Full Chess Rules Implementation** (basic moves, castling, promotions, checks, checkmates, en passant, threefold repetition rule, etc.)
- 🎮 **Player vs Player Gameplay** (local play, no online functionality)
- ⏳ **Timer / No Timer Option**
- ⏸️ **Pause Game Feature**
- 📜 **Move History & Rewind** (visually revert past game states for analysis)
- 💾 **Save & Load Game Configuration** 
  - Supports **FEN** & **PGN** formats
  - Configurations saved as `.fen` and `.pgn` files for later analysis or game continuation
- 🤝 **Draw Proposal System** (one player proposes, the other accepts or declines)
- 🛠️ **Testing with Google Tests**
- 📋 **Board Configuration Copy-Paste Support to ease testing**
  ```cpp
  CharMatrix m = { {
      {'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'},
      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
      {'-', '-', '-', '-', '-', '-', '-', '-'},
      {'-', '-', '-', '-', '-', '-', '-', '-'},
      {'-', '-', '-', '-', '-', '-', '-', '-'},
      {'-', '-', '-', '-', '-', '-', '-', '-'},
      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
      {'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'}
  }};
  Game g(m, EColor::White, EState::Playing);
  ```
- 🏆 **Captured Pieces Tracker**
- ❌ **Friendly Error Handling** (messages explain invalid moves)
- 🗄️ **Efficient Memory Usage** (board stored using a bitmap)
- 🎨 **Design Patterns Used:**
  - **Observer**
  - **Factory**
  - **Singleton**
- 📊 **UML Diagram Created** (VisualParadigm)

<p align="center">
  <img width="560" src="https://github.com/user-attachments/assets/d49910d8-5dbf-468e-84cd-6d5b0b708ee8" alt="MainChess">
</p>

- 📖 **Doxygen Documentation Available**

## 🛠️ Installation
The game comes with an **installer**, making it easy for users to download and start playing right away.

### Option 1: Download Installer
1. Download the installer from [GitHub Releases](#) *(replace with actual link)*.
2. Run the installer and follow the setup instructions.
3. Launch the game and enjoy!

### Option 2: Run from Source
If you want to run the code manually, you will need:
- **Visual Studio** (at least **2019**)
- **Qt version 6.5.1** installed and configured
- **NuGet package for Google Tests**

#### Setting up Google Tests with NuGet
1. Open **Visual Studio** and go to **Tools** > **NuGet Package Manager** > **Manage NuGet Packages for Solution**.
2. Search for **GoogleTestAdapter** and install it.
3. Ensure the test project is correctly linked to the Google Test library.
4. Build and run tests to verify everything is working correctly.

## 📸 Preview

<p align="center">
  <img width="560" src="https://github.com/user-attachments/assets/33f790ed-d27c-44f3-b9c8-3678a0faf024" alt="MainChess">
</p>

## 👨‍💻 Authors

- Stoica David-Ioan • [github](https://github.com/stoica-david) • [stoicadavidioan@gmail.com](mailto:stoicadavidioan@gmail.com)
- Popovici Cosmin Florian • [github](https://github.com/Cosminflv)

---

🎯 *Enjoy playing chess and analyzing your games with this feature-rich application!*
