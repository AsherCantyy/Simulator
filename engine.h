/*
 * aclrmtr_lib.h
 *
 *   -Asher Canty
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "common.h"
#define ENGINE_REV_GEAR (-1)
#define ENGINE_TOP_GEAR 6
#define ENGINE_IDLE_RPM 900
#define ENGINE_THROTTLE_MAX 1000
#define ENGINE_RPM_MAX 9000
#define ENGINE_RPM_SLEW_PER_S 5

typedef struct engine
{
	/* input */
	bool clutchIn;
	uint16_t throttle_pM; //0-1000

	/* state */
	bool started;
	uint16_t rpm;
	int8_t gear;

	/* pull */
	uint16_t voltage_mV;
	uint16_t current_mA;

	/* simulated loads */
	int16_t engineLoad;
	int16_t engineBrking;

} engine_t;


status_t engine_Init(engine_t *pEngine);
status_t engine_Update(engine_t *pEngine, uint32_t dt_ms); // , uint32_t dt_ms
//
status_t engine_Start(engine_t *pEngine);
status_t engine_ShiftUp(engine_t *pEngine);
status_t engine_ShiftDwn(engine_t *pEngine);
void engine_Stop(engine_t *pEngine);
//
status_t engine_SetThrttl(engine_t *pEngine, uint16_t perMillie);
void engine_SetClutch(engine_t *pEngine, bool in);
//
static inline uint16_t engine_GetRpm(const engine_t *pEngine){return pEngine->rpm; }
static inline int8_t engine_GetGear(const engine_t *pEngine){return pEngine->gear; }
static inline bool engine_IsRunning(const engine_t *pEngine){return pEngine->started; }





#endif
