#ifdef __ISPIXY

#define ID_SYNC 				0xa5
#define ID_PARAM				0x2d
#define ID_STARTSTOP			0x3c
#define ID_VECTOR				0x4b
#define BUF_SIZE				6

/*******************************************************
 * BUFFER TABLE
 * n =	VECTOR			PARAM				CMD
 * -----------------------------------------------------
 * 0 = 	ID_SYNC			ID_SYNC				ID_SYNC
 * 1 = 	ID_VECTOR		ID_PARAM	 		ID_STARTSTOP
 * 2 = 	MSB(X)			PARAM(DeltaP)		0
 * 3 = 	LSB(X)			PARAM(MSB(nOfP))	0
 * 4 = 	MSB(Y)			PARAM(LSB(nOfP))	0
 * 5 = 	LSB(Y)			0					0
 * *****************************************************/
#endif
#ifdef __ISARDUINO
#define ID_SYNC 				0xa5
#define ID_PARAM				0x2d
#define ID_STARTSTOP			0x3c
#define ID_VECTOR				0x4b
#define BUF_SIZE				6
#endif
