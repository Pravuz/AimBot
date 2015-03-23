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

#ifndef _PROGGREYSHADES_H
#define _PROGGREYSHADES_H
#define __PIXY

#include <list>
#include "lpc43xx_uart.h"
#include "exec.h"

extern Program g_progGreyshades;

#define AIM_X    (320/2)
#define AIM_Y    (198/2)

// Regions in a 320x198 frame divided into 3 regions.
#define REGS_X				320
#define REGS_Y				66
#define REG_A_OFFSET_Y		2
#define REG_B_OFFSET_Y		REGS_Y + REG_A_OFFSET_Y
#define REG_C_OFFSET_Y		REGS_Y + REG_B_OFFSET_Y

//making room at the end of the 72K SRAM bank for storage.
#define LAST_REGION_SIZE 		REGS_X*REGS_Y
#define LAST_REGION_MEMORY 		((uint8_t *)SRAM1_LOC + SRAM1_SIZE - LAST_REGION_SIZE)

struct sPoint16
{
    sPoint16()
    {
        m_x = m_y = 0;
    }

    sPoint16(int16_t x, int16_t y)
    {
        m_x = x;
        m_y = y;
    }

    int16_t m_x;
    int16_t m_y;
};

struct uPoint16
{
    uPoint16()
    {
        m_x = m_y = 0;
    }

    uPoint16(uint16_t x, uint16_t y)
    {
        m_x = x;
        m_y = y;
    }

    uint16_t m_x;
    uint16_t m_y;
};


struct DetectedObject {
	bool sameObject(const uPoint16 &p) {
		if (topLeft.m_x - 2 <= p.m_x && p.m_x <= bottomRight.m_x + 2
				&& bottomRight.m_y /* - 2 */<= p.m_y
				&& p.m_y <= topLeft.m_y + 2) { //will never be below bottomRight.m_y
			if (topLeft.m_x > p.m_x)
				topLeft.m_x = p.m_x;
			else if (bottomRight.m_x < p.m_x)
				bottomRight.m_x = p.m_x;
			if (topLeft.m_y < p.m_y)
				topLeft.m_y = p.m_y;
			else if (bottomRight.m_y > p.m_y)
				bottomRight.m_y = p.m_y; // never needed due to how a frame is iterated.
			objPixels++;
			return true;
		}
		return false;
	}
	DetectedObject(uPoint16 p) {
		objPixels = 1;
		topLeft = bottomRight = p;
	}
	uint16_t objPixels;
	uPoint16 topLeft, bottomRight;
};

enum GreyRegion {
	REG_A1, REG_A2, REG_B1, REG_B2, REG_C1, REG_C2, FINISHED
};

int greySetup();
int greyLoop();
void greyLoadParams();
void initUart();
uint32_t serialPrintVector(sPoint16 &p);
uint32_t serialRecieve();

class GreyShades {
public:
	uint16_t nOfP;
	uint8_t deltaP;
	GreyShades(uint8_t *lastRegionMem);
	~GreyShades();
	void setParams(const uint8_t deltaP, const uint16_t nOfP);
	void handleImage();
	void reset();

private:
	uint8_t *m_lastRegion;
	std::list<DetectedObject> m_DetectedObjects;
	std::list<sPoint16> m_vectorsToCenter;

	void convertRawToGrey(const bool compare);
	void objCalcs();
	void separateObjects();

};

extern GreyShades *g_gShades;
#endif
