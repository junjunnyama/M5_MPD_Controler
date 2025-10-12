# ifndef __EFONT_COLORS_H__ //二重でincludeされることを防ぐ
# define __EFONT_COLORS_H__

namespace efont_colors  // Color definitions for backwards compatibility with old sketches
  {
    #ifdef ILI9341_BLACK
    #undef ILI9341_BLACK
    #undef ILI9341_NAVY
    #undef ILI9341_DARKGREEN
    #undef ILI9341_DARKCYAN
    #undef ILI9341_MAROON
    #undef ILI9341_PURPLE
    #undef ILI9341_OLIVE
    #undef ILI9341_LIGHTGREY
    #undef ILI9341_DARKGREY
    #undef ILI9341_BLUE
    #undef ILI9341_GREEN
    #undef ILI9341_CYAN
    #undef ILI9341_RED
    #undef ILI9341_MAGENTA
    #undef ILI9341_YELLOW
    #undef ILI9341_WHITE
    #undef ILI9341_ORANGE
    #undef ILI9341_GREENYELLOW
    #undef ILI9341_PINK
    #endif

    #ifdef BLACK
    #undef BLACK
    #undef NAVY
    #undef DARKGREEN
    #undef DARKCYAN
    #undef MAROON
    #undef PURPLE
    #undef OLIVE
    #undef LIGHTGREY
    #undef DARKGREY
    #undef BLUE
    #undef GREEN
    #undef CYAN
    #undef RED
    #undef MAGENTA
    #undef YELLOW
    #undef WHITE
    #undef ORANGE
    #undef GREENYELLOW
    #undef PINK
    #endif

    static constexpr long ILI9341_BLACK       = 0x000000;      /*   0,   0,   0 */
    static constexpr long ILI9341_NAVY        = 0x000080;      /*   0,   0, 128 */
    static constexpr long ILI9341_DARKGREEN   = 0x008000;      /*   0, 128,   0 */
    static constexpr long ILI9341_DARKCYAN    = 0x008080;      /*   0, 128, 128 */
    static constexpr long ILI9341_MAROON      = 0x800000;      /* 128,   0,   0 */
    static constexpr long ILI9341_PURPLE      = 0x800080;      /* 128,   0, 128 */
    static constexpr long ILI9341_OLIVE       = 0x808000;      /* 128, 128,   0 */
    static constexpr long ILI9341_LIGHTGREY   = 0xD3D3D3;      /* 211, 211, 211 */
    static constexpr long ILI9341_DARKGREY    = 0x808080;      /* 128, 128, 128 */
    static constexpr long ILI9341_BLUE        = 0x0000FF;      /*   0,   0, 255 */
    static constexpr long ILI9341_GREEN       = 0x00FF00;      /*   0, 255,   0 */
    static constexpr long ILI9341_CYAN        = 0x00FFFF;      /*   0, 255, 255 */
    static constexpr long ILI9341_RED         = 0xFF0000;      /* 255,   0,   0 */
    static constexpr long ILI9341_MAGENTA     = 0xFF00FF;      /* 255,   0, 255 */
    static constexpr long ILI9341_YELLOW      = 0xFFFF00;      /* 255, 255,   0 */
    static constexpr long ILI9341_WHITE       = 0xFFFFFF;      /* 255, 255, 255 */
    static constexpr long ILI9341_ORANGE      = 0xFFB400;      /* 255, 180,   0 */
    static constexpr long ILI9341_GREENYELLOW = 0xB4FF00;      /* 180, 255,   0 */
    static constexpr long ILI9341_PINK        = 0xFFC0CB;      /* 255, 192, 203 */
    static constexpr long ILI9341_BROWN       = 0x964B00;      /* 150,  75,   0 */
    static constexpr long ILI9341_GOLD        = 0xFFD700;      /* 255, 215,   0 */
    static constexpr long ILI9341_SILVER      = 0xC0C0C0;      /* 192, 192, 192 */
    static constexpr long ILI9341_SKYBLUE     = 0x87CEEB;      /* 135, 206, 235 */
    static constexpr long ILI9341_VIOLET      = 0xB42EE2;      /* 180,  46, 226 */

    static constexpr long BLACK       = 0x000000;      /*   0,   0,   0 */
    static constexpr long NAVY        = 0x000080;      /*   0,   0, 128 */
    static constexpr long DARKGREEN   = 0x008000;      /*   0, 128,   0 */
    static constexpr long DARKCYAN    = 0x008080;      /*   0, 128, 128 */
    static constexpr long MAROON      = 0x800000;      /* 128,   0,   0 */
    static constexpr long PURPLE      = 0x800080;      /* 128,   0, 128 */
    static constexpr long OLIVE       = 0x808000;      /* 128, 128,   0 */
    static constexpr long LIGHTGREY   = 0xD3D3D3;      /* 211, 211, 211 */
    static constexpr long DARKGREY    = 0x808080;      /* 128, 128, 128 */
    static constexpr long BLUE        = 0x0000FF;      /*   0,   0, 255 */
    static constexpr long GREEN       = 0x00FF00;      /*   0, 255,   0 */
    static constexpr long CYAN        = 0x00FFFF;      /*   0, 255, 255 */
    static constexpr long RED         = 0xFF0000;      /* 255,   0,   0 */
    static constexpr long MAGENTA     = 0xFF00FF;      /* 255,   0, 255 */
    static constexpr long YELLOW      = 0xFFFF00;      /* 255, 255,   0 */
    static constexpr long WHITE       = 0xFFFFFF;      /* 255, 255, 255 */
    static constexpr long ORANGE      = 0xFFB400;      /* 255, 180,   0 */
    static constexpr long GREENYELLOW = 0xB4FF00;      /* 180, 255,   0 */
    static constexpr long PINK        = 0xFFC0CB;      /* 255, 192, 203 */
    static constexpr long BROWN       = 0x964B00;      /* 150,  75,   0 */
    static constexpr long GOLD        = 0xFFD700;      /* 255, 215,   0 */
    static constexpr long SILVER      = 0xC0C0C0;      /* 192, 192, 192 */
    static constexpr long SKYBLUE     = 0x87CEEB;      /* 135, 206, 235 */
    static constexpr long VIOLET      = 0xB42EE2;      /* 180,  46, 226 */
  }

# endif //__EFONT_COLORS_H__
