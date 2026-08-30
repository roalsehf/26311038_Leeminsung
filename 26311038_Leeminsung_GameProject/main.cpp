#include <glc2d.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

// glc2d provides separate libraries for each architecture and configuration.
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
constexpr int kScreenWidth = 960;
constexpr int kScreenHeight = 540;
constexpr float kPlayerSpeed = 280.0F;
constexpr float kPlayerSize = 42.0F;
constexpr float kTargetWidth = 120.0F;
constexpr float kTargetHeight = 44.0F;

int g_titleFont = -1;
int g_bodyFont = -1;
int g_playerFont = -1;

float g_playerX = 100.0F;
float g_playerY = 300.0F;
float g_targetX = 700.0F;
float g_targetY = 320.0F;
int g_score = 0;
long long g_previousTime = 0;
bool g_wasTouchingTarget = false;

bool IsKeyDown(const KEYCODE* keys, int key)
{
    return keys != nullptr && keys[key] != EINPUT_NONE;
}

void ResetGame()
{
    g_playerX = 100.0F;
    g_playerY = 300.0F;
    g_targetX = 700.0F;
    g_targetY = 320.0F;
    g_score = 0;
    g_wasTouchingTarget = false;
}

void MoveTarget()
{
    // A deterministic position keeps this first-week prototype resource-free.
    g_targetX = 120.0F + static_cast<float>((g_score * 173) % 690);
    g_targetY = 190.0F + static_cast<float>((g_score * 97) % 260);
}

bool IsTouchingTarget()
{
    const float playerCenterX = g_playerX + kPlayerSize * 0.5F;
    const float playerCenterY = g_playerY + kPlayerSize * 0.5F;
    const float targetCenterX = g_targetX + kTargetWidth * 0.5F;
    const float targetCenterY = g_targetY + kTargetHeight * 0.5F;

    return std::abs(playerCenterX - targetCenterX) < (kPlayerSize + kTargetWidth) * 0.5F
        && std::abs(playerCenterY - targetCenterY) < (kPlayerSize + kTargetHeight) * 0.5F;
}

int FrameMove()
{
    const KEYCODE* keys = g2_GetKeyboard();
    const long long currentTime = g2_TimeGetTime();

    if (g_previousTime == 0)
    {
        g_previousTime = currentTime;
    }

    const float deltaTime = std::clamp(
        static_cast<float>(currentTime - g_previousTime) / 1000.0F,
        0.0F,
        0.05F);
    g_previousTime = currentTime;

    float moveX = 0.0F;
    float moveY = 0.0F;

    if (IsKeyDown(keys, VK_LEFT) || IsKeyDown(keys, 'A'))
    {
        moveX -= 1.0F;
    }
    if (IsKeyDown(keys, VK_RIGHT) || IsKeyDown(keys, 'D'))
    {
        moveX += 1.0F;
    }
    if (IsKeyDown(keys, VK_UP) || IsKeyDown(keys, 'W'))
    {
        moveY -= 1.0F;
    }
    if (IsKeyDown(keys, VK_DOWN) || IsKeyDown(keys, 'S'))
    {
        moveY += 1.0F;
    }

    if (moveX != 0.0F && moveY != 0.0F)
    {
        constexpr float kDiagonalScale = 0.70710678F;
        moveX *= kDiagonalScale;
        moveY *= kDiagonalScale;
    }

    g_playerX = std::clamp(
        g_playerX + moveX * kPlayerSpeed * deltaTime,
        20.0F,
        static_cast<float>(kScreenWidth) - kPlayerSize - 20.0F);
    g_playerY = std::clamp(
        g_playerY + moveY * kPlayerSpeed * deltaTime,
        160.0F,
        static_cast<float>(kScreenHeight) - kPlayerSize - 20.0F);

    const bool isTouchingTarget = IsTouchingTarget();
    if (isTouchingTarget && !g_wasTouchingTarget)
    {
        ++g_score;
        MoveTarget();
    }
    g_wasTouchingTarget = isTouchingTarget;

    if (IsKeyDown(keys, 'R'))
    {
        ResetGame();
    }

    if (IsKeyDown(keys, VK_ESCAPE))
    {
        PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
    }

    return 0;
}

int Render()
{
    g2_FontDrawText(
        g_titleFont,
        { 32, 24, kScreenWidth - 32, 80 },
        0xFFFFD166,
        "CATCH THE TARGET");

    g2_FontDrawText(
        g_bodyFont,
        { 34, 84, kScreenWidth - 34, 120 },
        0xFFD7E3FC,
        "Move P with Arrow Keys or WASD. R resets. ESC exits.");

    g2_FontDrawText(
        g_bodyFont,
        { 34, 124, 300, 158 },
        0xFF70E000,
        "SCORE: %d",
        g_score);

    const RECT targetArea = {
        static_cast<LONG>(g_targetX),
        static_cast<LONG>(g_targetY),
        static_cast<LONG>(g_targetX + kTargetWidth),
        static_cast<LONG>(g_targetY + kTargetHeight)
    };
    g2_FontDrawText(g_bodyFont, targetArea, 0xFFFF5D8F, "TARGET");

    const RECT playerArea = {
        static_cast<LONG>(g_playerX),
        static_cast<LONG>(g_playerY),
        static_cast<LONG>(g_playerX + kPlayerSize),
        static_cast<LONG>(g_playerY + kPlayerSize)
    };
    g2_FontDrawText(g_playerFont, playerArea, 0xFF48CAE4, "P");

    return 0;
}
} // namespace

int main()
{
    const int initResult = g2_InitSdk();
    if (initResult != 0)
    {
        std::fprintf(stderr, "glc2d SDK initialization failed: %d\n", initResult);
        return 1;
    }

    std::printf("glc2d SDK initialized.\n");
    g2_SetClearColor(0xFF10243E);
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);

    // true selects windowed mode in glc2d.
    const int createResult = g2_CreateWin(
        120,
        80,
        kScreenWidth,
        kScreenHeight,
        "Catch the Target - Week 1 Prototype",
        true);
    if (createResult != 0)
    {
        std::fprintf(stderr, "glc2d window creation failed: %d\n", createResult);
        g2_DestroyWin();
        return 1;
    }

    g_titleFont = g2_FontCreate("Arial", 38, 0);
    g_bodyFont = g2_FontCreate("Consolas", 21, 0);
    g_playerFont = g2_FontCreate("Arial", 38, 0);
    if (g_titleFont < 0 || g_bodyFont < 0 || g_playerFont < 0)
    {
        std::fprintf(stderr, "glc2d font creation failed.\n");
        g2_DestroyWin();
        return 1;
    }
    g_previousTime = g2_TimeGetTime();

    std::printf("Catch the Target started. Close the game window or press ESC to exit.\n");
    const int runResult = g2_Run();
    g2_DestroyWin();

    if (runResult != 0)
    {
        std::fprintf(stderr, "glc2d game loop failed: %d\n", runResult);
        return 1;
    }

    return 0;
}
