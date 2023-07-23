#pragma once
#include <iostream>
#include <string>

#include "IGame.h"
#include "GameExceptions.h"
#include "BoardExceptions.h"

#include <windows.h>
#define color_gray "\x1b[90m"
#define color_white "\x1b[37m"
#define color_black "\x1b[30m"
#define color_blue "\033[34m"
#define color_cyan "\033[36m"
#define color_yellow "\033[33m"
#define color_red "\033[31m"

void PrintBoard(const IGamePtr& game);
bool VerifyInput(const std::string& input);
bool VerifyPieceName(const std::string& input);
std::string DeleteSpaces(std::string input);
void Play(const IGamePtr& game);

void PrintMinus();
void PrintVerticalLine();
void PrintHorizohtalLine();
void PrintSpace();
void Enter();
void SetBackground();