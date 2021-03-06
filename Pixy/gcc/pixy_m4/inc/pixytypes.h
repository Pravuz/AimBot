//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
#ifndef PIXYTYPES_H
#define PIXYTYPES_H

#include <stdint.h>

#define RENDER_FLAG_FLUSH            0x01
#define RENDER_FLAG_BLEND_BG         0x02

#define PRM_FLAG_INTERNAL            0x01
#define PRM_FLAG_ADVANCED            0x02
#define PRM_FLAG_HEX_FORMAT          0x10
#define PRM_FLAG_SIGNED              0x80
#ifndef NULL
#define NULL ((void*) 0)
#endif

typedef uint32_t Qval;

struct Point16
{
    Point16()
    {
        m_x = m_y = 0;
    }

    Point16(uint16_t x, uint16_t y)
    {
        m_x = x;
        m_y = y;
    }

    uint16_t m_x;
    uint16_t m_y;
};

struct Frame8
{
    Frame8()
    {
        m_pixels = (uint8_t *)NULL;
        m_width = m_height = 0;
    }

    Frame8(uint8_t *pixels, uint16_t width, uint16_t height)
    {
        m_pixels = pixels;
        m_width = width;
        m_height = height;
    }

    uint8_t *m_pixels;
    int16_t m_width;
    int16_t m_height;
};

struct RectA
{
    RectA()
    {
        m_xOffset = m_yOffset = m_width = m_height = 0;
    }

    RectA(uint16_t xOffset, uint16_t yOffset, uint16_t width, uint16_t height)
    {
        m_xOffset = xOffset;
        m_yOffset = yOffset;
        m_width = width;
        m_height = height;
    }

    uint16_t m_xOffset;
    uint16_t m_yOffset;
    uint16_t m_width;
    uint16_t m_height;
};

struct RectB
{
    RectB()
    {
        m_left = m_right = m_top = m_bottom = 0;
    }

    RectB(uint16_t left, uint16_t right, uint16_t top, uint16_t bottom)
    {
        m_left = left;
        m_right = right;
        m_top = top;
        m_bottom = bottom;
    }

    uint16_t m_left;
    uint16_t m_right;
    uint16_t m_top;
    uint16_t m_bottom;
};

struct BlobA
{
    BlobA()
    {
        m_model = m_left = m_right = m_top = m_bottom = 0;
    }

    BlobA(uint16_t model, uint16_t left, uint16_t right, uint16_t top, uint16_t bottom)
    {
        m_model = model;
        m_left = left;
        m_right = right;
        m_top = top;
        m_bottom = bottom;
    }

    uint16_t m_model;
    uint16_t m_left;
    uint16_t m_right;
    uint16_t m_top;
    uint16_t m_bottom;
};

struct BlobB
{
    BlobB()
    {
        m_model = m_left = m_right = m_top = m_bottom = m_angle = 0;
    }

    BlobB(uint16_t model, uint16_t left, uint16_t right, uint16_t top, uint16_t bottom, int16_t angle)
    {
        m_model = model;
        m_left = left;
        m_right = right;
        m_top = top;
        m_bottom = bottom;
		m_angle = angle;
    }

    uint16_t m_model;
    uint16_t m_left;
    uint16_t m_right;
    uint16_t m_top;
    uint16_t m_bottom;
	int16_t m_angle;
};


struct HuePixel
{
    HuePixel()
    {
        m_u = m_v = 0;
    }

    HuePixel(int8_t u, int8_t v)
    {
        m_u = u;
        m_v = v;
    }

    int8_t m_u;
    int8_t m_v;
};

struct Fpoint
{
    Fpoint()
    {
        m_x = m_y = 0.0;
    }

    Fpoint(float x, float y)
    {
        m_x = x;
        m_y = y;
    }

    float m_x;
    float m_y;
};

struct Line
{
    Line()
    {
        m_slope = m_yi = 0.0;
    }
    Line(float slope, float yi)
    {
        m_slope = slope;
        m_yi = yi;
    }

    float m_slope;
    float m_yi;
};

#endif // PIXYTYPES_H
