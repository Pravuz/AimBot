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

#include "proggreyshades.h"
#include "camera.h"
#include "pixyvals.h"
#include "lpc43xx_scu.h"

Program g_progGreyshades = { "grey", "perform shades of grey analysis",
		greySetup, greyLoop };

static GreyShades g_greyShades((uint8_t *) LAST_REGION_MEMORY);
extern GreyShades g_greyShades;
bool running;

#include "Aimbot_Serial.h"

GreyRegion currentRegion;
sPoint16 m_medianVector; //vector can have a negative direction, so using a signed version of the point struct.

AimBot_Serial m_serial;

GreyShades::GreyShades(uint8_t *lastRegionMem) {
	m_lastRegion = lastRegionMem;
}

GreyShades::~GreyShades() {
}

void GreyShades::setParams(const uint8_t deltaP, const uint16_t nOfP) {
	if (deltaP < 1 || deltaP > 255)
		this->deltaP = 15; //invalid, using default.
	else
		this->deltaP = deltaP;

	if (nOfP > 10500 || nOfP < 1)
		this->nOfP = 10500; //invalid, using default.
	else
		this->nOfP = nOfP;
}

void GreyShades::handleImage() {
	uint8_t *frame = (uint8_t *) SRAM1_LOC; //location where the image sensor stores our pixels.
	int response = -1;

	switch (currentRegion) {
	case REG_A1:
		response = cam_getFrame(frame, SRAM1_SIZE, CAM_GRAB_M1R2, 0,
		REG_A_OFFSET_Y, REGS_X, REGS_Y); //grab a region from the camerasensor.
		if (response == 0) //if response is not 0, something wrong happened.
			convertRawToGrey(false); //not comparing with previous image, since this is a new region.
		else
			break; //repeat this iteration, try again.
		currentRegion = REG_A2; // Finished with this region
		break;
	case REG_A2:
		response = cam_getFrame(frame, SRAM1_SIZE, CAM_GRAB_M1R2, 0,
		REG_A_OFFSET_Y, REGS_X, REGS_Y);
		if (response == 0)
			convertRawToGrey(true); //we can now compare the previous region with the current.
		else
			break;
		separateObjects(); //separate the objects in this region, save for later.
		currentRegion = REG_B1;
		break;
	case REG_B1:
		response = cam_getFrame(frame, SRAM1_SIZE, CAM_GRAB_M1R2, 0,
		REG_B_OFFSET_Y, REGS_X, REGS_Y);
		if (response == 0)
			convertRawToGrey(false);
		else
			break;
		currentRegion = REG_B2;
		break;
	case REG_B2:
		response = cam_getFrame(frame, SRAM1_SIZE, CAM_GRAB_M1R2, 0,
		REG_B_OFFSET_Y, REGS_X, REGS_Y);
		if (response == 0)
			convertRawToGrey(true);
		else
			break;
		separateObjects();
		currentRegion = REG_C1;
		break;
	case REG_C1:
		response = cam_getFrame(frame, SRAM1_SIZE, CAM_GRAB_M1R2, 0,
		REG_C_OFFSET_Y, REGS_X, REGS_Y);
		if (response == 0)
			convertRawToGrey(false);
		else
			break;
		currentRegion = REG_C2;
		break;
	case REG_C2:
		response = cam_getFrame(frame, SRAM1_SIZE, CAM_GRAB_M1R2, 0,
		REG_C_OFFSET_Y, REGS_X, REGS_Y);
		if (response == 0)
			convertRawToGrey(true);
		else
			break;
		separateObjects();
		currentRegion = FINISHED;
		break;
	case FINISHED:
		objCalcs(); //completed grabbing and analyzing an entire image from the sensor. Ready for calculations.
		currentRegion = REG_A1; // Restart.
		break;
	}
}

void GreyShades::convertRawToGrey(const bool compare) {
	uint16_t x, y, width, nOfPCount;
	uint8_t temp;
	uint8_t *pixels;

	nOfPCount = 0;
	bool nOfPAboveTresh = false;
	width = g_rawFrame.m_width;
	pixels = g_rawFrame.m_pixels; //pointer to our memory location containing our pixels.

	for (y = 0; y < g_rawFrame.m_height; y++, pixels += width) {
		for (x = 0; x < width; x++) {
			temp = pixels[x] | 0x01; //minimum value for each pixels is 1. the value 0 will indicate a detected motion.
			if (nOfPCount >= nOfP)
				nOfPAboveTresh = true;

			// Is the value for the previous pixel minus this pixel above pixelchange treshold 'deltaP'?
			if (compare && (abs(m_lastRegion[(width * y) + x]) - temp) > deltaP
					&& !nOfPAboveTresh) {
				nOfPCount++;
				temp = 0x00; // this pixel now indicates motion.
			}

			//saves this pixel in last frame.
			m_lastRegion[(width * y) + x] = temp;
		}
	}

#if 0 //no longer interpolating
	uint32_t temp;
	uint16_t x, y, r, g, b, width, nOfPCount;
	uint8_t *pixels;
	nOfPCount = 0;
	bool nOfPAboveTresh = false;
	width = g_rawFrame.m_width;
	pixels = g_rawFrame.m_pixels;

	//skip first line
	pixels += width;

	// Skipping top, left and rightmost rows/columns
	for (y = 1; y < g_rawFrame.m_height - 1; y++, pixels += width) {
		for (x = 1; x < width - 1; x++) {
			// Interpolating Bayer.
			if (y & 1) { //odd row
				if (x & 1) { //odd column
					r = pixels[x];
					g = (pixels[x - 1] + pixels[x + 1] + pixels[x + width]
							+ pixels[x - width]) >> 2;
					b = (pixels[x - width - 1] + pixels[x - width + 1]
							+ pixels[x + width - 1] + pixels[x + width + 1])
					>> 2;
				} else { //even column
					r = (pixels[x - 1] + pixels[x + 1]) >> 1;
					g = pixels[x];
					b = (pixels[x - width] + pixels[x + width]) >> 1;
				}
			} else { //even row
				if (x & 1) { //odd column
					r = (pixels[x - width] + pixels[x + width]) >> 1;
					g = pixels[x];
					b = (pixels[x - 1] + pixels[x + 1]) >> 1;
				} else { //even column
					r = (pixels[x - width - 1] + pixels[x - width + 1]
							+ pixels[x + width - 1] + pixels[x + width + 1])
					>> 2;
					g = (pixels[x - 1] + pixels[x + 1] + pixels[x + width]
							+ pixels[x - width]) >> 2;
					b = pixels[x];
				}
			}

			//converting to greyscale
			temp = ((r + g + b) * 341 >> 10) | 0x01;// (r+g+b)/3 => (r+g+b)*341>>10..
			// | 0x01 sets minimum value for each pixel to 1
			// a pixel value of 0 will be used for indicating motion in this pixel

			// Is maximum amount of pixelchanges reached?
			if (nOfPCount >= nOfP)
			nOfPAboveTresh = true;

			// Is the value for the previous pixel minus this pixel above pixelchange treshold 'deltaP'?
			if (compare
					&& (abs(m_lastRegion[((width - 2) * (y - 2)) + x - 1]) - temp)
					> deltaP && !nOfPAboveTresh) {
				nOfPCount++;
				temp = 0x00; // this pixel now indicates motion.
			}

			//saves this pixel in last frame.
			m_lastRegion[((width - 2) * (y - 2)) + x - 1] = (uint8_t) temp;
		}
	}
#endif
}

void GreyShades::separateObjects() {
	bool noMatchFound = true;
	uPoint16 point; //curent pixel point.
	//skipping 2 top columns because of sameObject(point)
	for (int y = 0; y <= REGS_Y - 2; y++)
		// skipping 2 leftmost and 2 rightmost columns because of sameObject(point)
		for (int x = 2; x <= REGS_X - 2; x++) {
			if (m_lastRegion[(REGS_X * y) + x] != 0x00)
				continue; //skip this iteration, this pixel doesn't have a change.

			noMatchFound = true;
			point.m_x = x;
			point.m_y = y;
			if (currentRegion == REG_A2)
				point.m_y += REG_A_OFFSET_Y;
			if (currentRegion == REG_B2)
				point.m_y += REG_B_OFFSET_Y;
			if (currentRegion == REG_C2)
				point.m_y += REG_C_OFFSET_Y;

			// loops trough existing objects, checking if this pixel may belong to one of the detected objects.
			if (!m_DetectedObjects.empty()) {
				for (std::list<DetectedObject>::iterator i =
						m_DetectedObjects.begin();
						noMatchFound && i != m_DetectedObjects.end(); i++) {
					if (i->sameObject(point))
						noMatchFound = false; //this pixel now belongs to an existing object.
				}
			}
			if (noMatchFound)
				m_DetectedObjects.push_back(DetectedObject(point)); //this pixels belongs in a new object.
		}
}

void GreyShades::objCalcs() {
	// find largest object and calc midpoint and vector to crosshair.
	// If there is absolutely no movement detected, theres no need to do any further calculations.
	if (m_DetectedObjects.empty())
		return;
	DetectedObject m_largestObj = m_DetectedObjects.front();
	m_DetectedObjects.pop_front();
	if (!m_DetectedObjects.empty())
		for (std::list<DetectedObject>::iterator i = m_DetectedObjects.begin();
				i != m_DetectedObjects.end(); i++)
			if (m_largestObj.objPixels < i->objPixels)
				m_largestObj = *i;

	// memory leakage deluxe if we don't clear this after each image is produced.
	// this is also the most reasonable (if not the only) place where we can safely clear the list.
	m_DetectedObjects.clear();

	sPoint16 m_vector;

	m_vector.m_x = AIM_X
			- (((m_largestObj.bottomRight.m_x - m_largestObj.topLeft.m_x) >> 1)
					+ m_largestObj.topLeft.m_x);
	m_vector.m_y = AIM_Y
			- (((m_largestObj.topLeft.m_y - m_largestObj.bottomRight.m_y) >> 1)
					+ m_largestObj.bottomRight.m_y);

	m_vectorsToCenter.push_back(m_vector);

	if (m_vectorsToCenter.size() >= 5) {
		std::list<int> medianOfVTC_x, medianOfVTC_y;
		for (std::list<sPoint16>::iterator i = m_vectorsToCenter.begin();
				i != m_vectorsToCenter.end(); i++) {
			medianOfVTC_x.push_back(i->m_x);
			medianOfVTC_y.push_back(i->m_y);
		}

		medianOfVTC_x.sort();
		medianOfVTC_y.sort();

		//getting median X vector
		medianOfVTC_x.pop_front();
		medianOfVTC_x.pop_front();
		m_medianVector.m_x = medianOfVTC_x.front();

		//getting median Y vector
		medianOfVTC_y.pop_front();
		medianOfVTC_y.pop_front();
		m_medianVector.m_y = medianOfVTC_y.front();

		// We now have a vector ready for arduino
		m_serial.sendVector(m_medianVector);
	}

	while (m_vectorsToCenter.size() > 5)
		m_vectorsToCenter.pop_front(); // will likely only happend once pr objCalcs
}

void GreyShades::reset() {
	currentRegion = REG_A1;
	m_vectorsToCenter.clear();
	m_DetectedObjects.clear();
}

int greySetup() {
	//init serial.
	m_serial.setupSerial();

//initial currentRegion
	currentRegion = REG_A1;
// setup camera mode
	cam_setMode(CAM_MODE0); //don't want to run mode 1 for some reason, what does modes entail?

// load parameters
	greyLoadParams();

//init vector
	m_medianVector.m_x = 0;
	m_medianVector.m_y = 0;

	running = true;

	return 0;
}

int greyLoop() {
	//check for new instructions
	m_serial.updateSerial();

//handle images in parts.
	if (running)
		g_greyShades.handleImage();

	return 0;
}

void greyLoadParams() {
	//default params.
	g_greyShades.setParams(15, 10500);
}
