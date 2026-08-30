#include <glc2d.h>

#include <cstdio>

#if defined(_DEBUG)
    #if defined(_M_X64)
        #pragma comment(lib, "glc2d_x64_debug.lib")
    #elif defined(_M_IX86)
        #pragma comment(lib, "glc2d_win32_debug.lib")
    #endif
#else
    #if defined(_M_X64)
        #pragma comment(lib, "glc2d_x64_release.lib")
    #elif defined(_M_IX86)
        #pragma comment(lib, "glc2d_win32_release.lib")
    #endif
#endif

namespace
{
constexpr int kScreenWidth = 1024;
constexpr int kScreenHeight = 640;
constexpr int kMenuCount = 3;

enum class GameState
{
    MainMenu,
    HowToPlay,
    BattlePreview
};

GameState g_gameState = GameState::MainMenu;
int g_selectedMenu = 0;
int g_titleFont = -1;
int g_headingFont = -1;
int g_menuFont = -1;
int g_bodyFont = -1;

bool IsKeyPressed(const KEYCODE* keys, int key)
{
    return keys != nullptr && keys[key] == EINPUT_DOWN;
}

void RequestExit()
{
    PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
}

void SelectMenuItem()
{
    switch (g_selectedMenu)
    {
    case 0:
        g_gameState = GameState::BattlePreview;
        break;

    case 1:
        g_gameState = GameState::HowToPlay;
        break;

    case 2:
        RequestExit();
        break;

    default:
        break;
    }
}

void UpdateMainMenu(const KEYCODE* keys)
{
    if (IsKeyPressed(keys, VK_UP) || IsKeyPressed(keys, 'W'))
    {
        --g_selectedMenu;
        if (g_selectedMenu < 0)
        {
            g_selectedMenu = kMenuCount - 1;
        }
    }

    if (IsKeyPressed(keys, VK_DOWN) || IsKeyPressed(keys, 'S'))
    {
        ++g_selectedMenu;
        if (g_selectedMenu >= kMenuCount)
        {
            g_selectedMenu = 0;
        }
    }

    if (IsKeyPressed(keys, VK_RETURN))
    {
        SelectMenuItem();
    }

    if (IsKeyPressed(keys, VK_ESCAPE))
    {
        RequestExit();
    }
}

int FrameMove()
{
    const KEYCODE* keys = g2_GetKeyboard();

    if (g_gameState == GameState::MainMenu)
    {
        UpdateMainMenu(keys);
    }
    else if (IsKeyPressed(keys, VK_RETURN) || IsKeyPressed(keys, VK_ESCAPE))
    {
        g_gameState = GameState::MainMenu;
    }

    return 0;
}

void DrawMainMenu()
{
    g2_FontDrawText(
        g_titleFont,
        { 285, 45, 760, 105 },
        0xFFD9B3FF,
        "DUNGEON DECK");

    g2_FontDrawText(
        g_bodyFont,
        { 350, 112, 760, 150 },
        0xFFB8C5D6,
        "TURN BASED CARD RPG");

    const char* menuItems[kMenuCount] =
    {
        "GAME START",
        "HOW TO PLAY",
        "EXIT"
    };

    for (int index = 0; index < kMenuCount; ++index)
    {
        const int top = 220 + index * 72;
        const DWORD color = index == g_selectedMenu
            ? 0xFFFFD166
            : 0xFFE6EDF3;

        g2_FontDrawText(
            g_menuFont,
            { 405, top, 720, top + 48 },
            color,
            "%s",
            menuItems[index]);
    }

    g2_FontDrawText(
        g_bodyFont,
        { 310, 510, 800, 548 },
        0xFF8FB8DE,
        "W, S or Arrow Keys: Move");

    g2_FontDrawText(
        g_bodyFont,
        { 375, 552, 760, 590 },
        0xFF8FB8DE,
        "Enter: Select   Esc: Exit");
}

void DrawHowToPlay()
{
    g2_FontDrawText(
        g_headingFont,
        { 380, 40, 760, 90 },
        0xFFD9B3FF,
        "HOW TO PLAY");

    g2_FontDrawText(
        g_bodyFont,
        { 115, 120, 920, 155 },
        0xFFE6EDF3,
        "Draw five cards at the beginning of each player turn.");
    g2_FontDrawText(
        g_bodyFont,
        { 115, 168, 920, 203 },
        0xFFE6EDF3,
        "Use Energy to play Attack and Skill cards.");
    g2_FontDrawText(
        g_bodyFont,
        { 115, 216, 920, 251 },
        0xFFE6EDF3,
        "Strike deals damage. Guard adds Block. Focus draws a card.");
    g2_FontDrawText(
        g_bodyFont,
        { 115, 264, 920, 299 },
        0xFFE6EDF3,
        "End the turn to let the enemy perform its displayed action.");
    g2_FontDrawText(
        g_bodyFont,
        { 115, 312, 920, 347 },
        0xFFE6EDF3,
        "Reach Stage 3 and defeat the Dungeon Warden to clear the game.");

    g2_FontDrawText(
        g_bodyFont,
        { 115, 400, 920, 435 },
        0xFF70E000,
        "Starting HP: 50   Energy: 3   Hand: 5 cards");

    g2_FontDrawText(
        g_bodyFont,
        { 310, 550, 820, 590 },
        0xFF8FB8DE,
        "Enter or Esc: Return to Main Menu");
}

void DrawBattlePreview()
{
    g2_FontDrawText(
        g_headingFont,
        { 390, 32, 760, 82 },
        0xFFFFD166,
        "BATTLE START");

    g2_FontDrawText(
        g_headingFont,
        { 95, 120, 450, 165 },
        0xFFFF7B7B,
        "TRAINING GOBLIN");
    g2_FontDrawText(
        g_bodyFont,
        { 100, 178, 430, 213 },
        0xFFE6EDF3,
        "HP: 32 / 32");
    g2_FontDrawText(
        g_bodyFont,
        { 100, 220, 430, 255 },
        0xFFE6EDF3,
        "Next Action: Attack 7");

    g2_FontDrawText(
        g_headingFont,
        { 650, 120, 900, 165 },
        0xFF48CAE4,
        "PLAYER");
    g2_FontDrawText(
        g_bodyFont,
        { 650, 178, 950, 213 },
        0xFFE6EDF3,
        "HP: 50 / 50");
    g2_FontDrawText(
        g_bodyFont,
        { 650, 220, 950, 255 },
        0xFFE6EDF3,
        "Energy: 3 / 3");

    g2_FontDrawText(
        g_bodyFont,
        { 285, 330, 850, 365 },
        0xFFD9B3FF,
        "Week 1 Battle Screen Prototype");
    g2_FontDrawText(
        g_bodyFont,
        { 235, 380, 900, 415 },
        0xFFB8C5D6,
        "Card and turn systems will be connected in later logs.");

    g2_FontDrawText(
        g_bodyFont,
        { 310, 550, 820, 590 },
        0xFF8FB8DE,
        "Enter or Esc: Return to Main Menu");
}

int Render()
{
    switch (g_gameState)
    {
    case GameState::MainMenu:
        DrawMainMenu();
        break;

    case GameState::HowToPlay:
        DrawHowToPlay();
        break;

    case GameState::BattlePreview:
        DrawBattlePreview();
        break;
    }

    return 0;
}
}

int main()
{
    const int initResult = g2_InitSdk();
    if (initResult != 0)
    {
        std::fprintf(stderr, "glc2d SDK initialization failed: %d\n", initResult);
        return 1;
    }

    g2_SetClearColor(0xFF101827);
    g2_SetStateShow(0);
    g2_SetCursorShow(0);
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);

    const int createResult = g2_CreateWin(
        100,
        70,
        kScreenWidth,
        kScreenHeight,
        "DUNGEON DECK - glc2d Card RPG",
        true);

    if (createResult != 0)
    {
        std::fprintf(stderr, "glc2d window creation failed: %d\n", createResult);
        g2_DestroyWin();
        return 1;
    }

    g_titleFont = g2_FontCreate("Arial", 40, 0);
    g_headingFont = g2_FontCreate("Arial", 30, 0);
    g_menuFont = g2_FontCreate("Arial", 27, 0);
    g_bodyFont = g2_FontCreate("Consolas", 20, 0);

    if (g_titleFont < 0 || g_headingFont < 0 || g_menuFont < 0 || g_bodyFont < 0)
    {
        std::fprintf(stderr, "glc2d font creation failed.\n");
        g2_DestroyWin();
        return 1;
    }

    std::printf("DUNGEON DECK started. Close the game window or press Esc to exit.\n");
    const int runResult = g2_Run();
    g2_DestroyWin();

    if (runResult != 0)
    {
        std::fprintf(stderr, "glc2d game loop failed: %d\n", runResult);
        return 1;
    }

    return 0;
}
