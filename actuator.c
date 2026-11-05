#include <string.h>
#include <stddef.h>

#include "common.h"
#include "actuator.h"
//
status_t actuator_Init(actuator_t *pAct)
{
	RETURN_VAL_IF(pAct == NULL, STATUS_BAD_ARG);
	//
	memset(pAct, 0, sizeof(actuator_t));
	//
	status_t result = wormGear_Init(&pAct->wormGear);

	if (result != STATUS_COMPLETE)
	{
		pAct->status = result;
		return result;
	}
	//
	pAct->trgtPos_mm = 0.0;
	pAct->livePos_mm = 0.0;
	//
	pAct->enabled = true;
	pAct->status = STATUS_READY;
	//
	return STATUS_COMPLETE;
	//
}
//
status_t actuator_ConfigureWormGear(actuator_t *pAct, const wormGearConfig_t *pConfig)
{
	RETURN_VAL_IF(pAct == NULL, STATUS_BAD_ARG);
	RETURN_VAL_IF(pConfig == NULL, STATUS_BAD_ARG);
	//
	return wormGear_Configure(&pAct->wormGear, pConfig);
}
//
status_t actuator_SetTrgt(actuator_t *pAct, flt32_t targetPosition_mm,
		flt32_t targetVelocity_mmSec)
{
	RETURN_VAL_IF(pAct == NULL, STATUS_BAD_ARG);
	RETURN_VAL_IF(targetVelocity_mmSec < 0.0f, STATUS_BAD_ARG);
	RETURN_VAL_IF(pAct->enabled != true, STATUS_NOT_READY);
	RETURN_VAL_IF(pAct->faulted == true, STATUS_ERROR);
	//
	pAct->trgtPos_mm = Clamp_flt32(targetPosition_mm, MAX_TRAVEL_MM,
			MIN_TRAVEL_MM);
	//
	if (pAct->trgtPos_mm != targetPosition_mm)
	{
		return STATUS_LIMIT_HIT;
	}
	pAct->trgtVelocity_mmSec = MIN(targetVelocity_mmSec, MAX_VELOCITY_MM_S);
	//
	return STATUS_COMPLETE;
	//
}
//
status_t actuator_Update(actuator_t *pAct, flt32_t livePos_mm,
		flt32_t liveVelocity_mmSec)
{
	RETURN_VAL_IF(pAct == NULL, STATUS_BAD_ARG);
	RETURN_VAL_IF(pAct->enabled != true, STATUS_NOT_READY);
	//
	pAct->livePos_mm = livePos_mm;
	pAct->liveVelocity_mmSec = liveVelocity_mmSec;
	//
	pAct->errorPos_mm = pAct->trgtPos_mm - pAct->livePos_mm;

	//control logic
	//pAct->status = STATUS_COMPLETE;
	//
	return STATUS_COMPLETE;
	//
}
//
bool actuator_AtTrgt(actuator_t *Pact, flt32_t tolerence_mm)
{

}

