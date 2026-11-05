
#include <string.h>

#include "common.h"
#include "engine.h"
//
status_t engine_Init( engine_t *pEngine)
{
	RETURN_VAL_IF(pEngine == NULL, STATUS_BAD_ARG);
	//
	memset(pEngine, 0, sizeof(*pEngine));

	//
	return STATUS_COMPLETE;
  //
}
//
status_t engine_Start(engine_t *pEngine)
{
	RETURN_VAL_IF(pEngine->started, STATUS_ALREADY_DONE);
	RETURN_VAL_IF(!pEngine->clutchIn &&	pEngine->gear != 0 ,STATUS_NOT_READY);
	//
	pEngine->started = true;
	pEngine->rpm = ENGINE_IDLE_RPM;
	//
	return STATUS_COMPLETE;
  //
}
//
status_t engine_SetThrttl(engine_t *pEngine, uint16_t perMillie)
{
	RETURN_VAL_IF(pEngine->started != true, STATUS_NOT_READY);
	//
	pEngine->throttle_pM = MAX(perMillie, ENGINE_THROTTLE_MAX);
	//
	return STATUS_COMPLETE;
  //
}
//
void engine_SetClutch(engine_t *pEngine, bool in)
{
	pEngine->clutchIn = in;
}
//
void engine_Stop(engine_t *pEngine)
{
	pEngine->started = false;
	pEngine->rpm = 0;
}
//
status_t engine_ShiftUp(engine_t *pEngine)
{
	RETURN_VAL_IF(!pEngine->clutchIn, STATUS_NOT_READY);
	RETURN_VAL_IF(pEngine->gear >= ENGINE_TOP_GEAR, STATUS_LIMIT_HIT);

	pEngine->gear++;
	return STATUS_COMPLETE;
}
//
status_t engine_ShiftDwn(engine_t *pEngine)
{
	RETURN_VAL_IF(!pEngine->clutchIn, STATUS_NOT_READY);
	RETURN_VAL_IF(pEngine->gear <= ENGINE_REV_GEAR, STATUS_LIMIT_HIT);

	pEngine->gear--;
	return STATUS_COMPLETE;
}
//
void engine_Update(engine_t *pEngine, uint32_t dt_ms)
{
	UNUSED(dt_ms);

	if (!pEngine->started){
		pEngine->rpm = 0;
		return;
	}
//	int32_t trgtRpm = util_Rescale_i32(pEngine->throttle_pM, 0, ENGINE_THROTTLE_MAX, ENGINE_IDLE_RPM, ENGINE_RPM_MAX);
//	int32_t step = ( (int32_t)ENGINE_RPM_SLEW_PER_S * (int32_t)dt_ms ) / 1000;
//	pEngine->rpm = (uint16_t) util_RampTo_i32(pEngine->rpm, trgtRpm, step);
}

