#include <thread>
#include <stdio.h>
#include <cstdint>
#include <atomic>  // 添加对原子操作的支持

#include "ModelicaArduino.h"
#include "ModelicaUtilities.h"
#include "ModelicaUtilityFunctions.h"

#include "Arduino.h"
#include "SoftArduino.h"

#ifdef _WIN32
#include <conio.h>  //
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif


#ifdef _WIN32
// Windows-specific implementations (if needed)
#else
bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}
#endif
/** Constructor function of the external object */
void * ModelicaArduino_open(void *callbacks) {

	setModelicaUtilityFunctions(reinterpret_cast<ModelicaUtilityFunctions_t *>(callbacks));

	return INSTANCE;
}

/** Destructor function of the external object */
void ModelicaArduino_close(void *externalObject) {
	//ModelicaMessage("ModelicaArduino_close()\n");
}

void ModelicaArduino_update(void *instance__,
							double time,
							double analogReference,
							double *potential,
							int *portMode,
							int *pulseWidth,
							int *pulsePeriod) {

	if (INSTANCE->error) {
		ModelicaFormatError("Error in loop(): %s", INSTANCE->error);
		return;
	}

	if (INSTANCE->analogReferenceMode == EXTERNAL && analogReference == 0) {
		ModelicaFormatError("Reference voltage must not be 0.");
		return;
	}

	// update the time
	INSTANCE->time = static_cast<unsigned long>(time * 1e6);

	const double V_ref = INSTANCE->analogReferenceMode == EXTERNAL ? analogReference : 5.;

	for (int i = 0; i < NUM_DIGITAL_PINS; i++) {
		INSTANCE->potential[i] = potential[i] / V_ref;
	}

	INSTANCE->update();

	for (int i = 0; i < NUM_DIGITAL_PINS; i++) {
		portMode[i] = INSTANCE->portMode[i];
		pulseWidth[i] = INSTANCE->pulseWidth[i];
		pulsePeriod[i] = INSTANCE->pulsePeriod[i];
	}

	// interrupts
	if (INSTANCE->interruptsEnabled) {
		for (int i = 0; i < 2; i++) {
			if (INSTANCE->interrupts[i]) {
				const int p = INSTANCE->potential[interruptToDigitalPin(i)] > 0.5 ? HIGH : LOW;
				INSTANCE->interrupts[i]->update(p);
			}
		}
	}

}
