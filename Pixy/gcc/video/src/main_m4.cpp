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

#include <exec.h>
#include <pixy_init.h>
#include <proggreyshades.h>

#if defined (LPC43_MULTICORE_M0APP) | defined (LPC43_MULTICORE_M0SUB)
#include "cr_start_m0.h"
#endif

//#define DONT_RESET_ON_RESTART

int main(void) {
	pixyInit();
#if 1
	exec_addProg(&g_progGreyshades);
	exec_loop();
#endif
	return 0;
}

