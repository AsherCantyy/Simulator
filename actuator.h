/*
 * aclrmtr_lib.h
 *
 *   -Asher Canty
 */
//
#ifndef ACTUATOR_H_
#define ACTUATOR_H_
//
#include "common.h"
//
/* travel limits */
#define MAX_TRAVEL_MM (1000.0f)
#define MIN_TRAVEL_MM (100.0f)
#define MAX_VELOCITY_MM_S (20.0f)
#define MAX_ACCL_MM_S2 (5.0f)

#define ACT_UPDATE_PRD_MS (10.0f)
//
typedef struct actuator
{ 	/* needed so actuator instance can reach worm gear */
	wormGear_t wormGear;
	/* input from motionRig object */
	flt32_t trgtPos_mm;
	flt32_t trgtVelocity_mmSec;
	/* output command to gear objects */
	flt32_t cmdPos_mm;
	flt32_t cmdVelocity_mmSec;
	flt32_t cmdAccl_mmS2;
	/* feedback */
	flt32_t livePos_mm;
	flt32_t liveVelocity_mmSec;
	flt32_t liveAccl_mmS2;
	// error
	flt32_t errorPos_mm;
	/* states */
	bool enabled;//?
	bool faulted;//?
	bool homed;//?
	//
	status_t status;
  //
} actuator_t;
//
/* actuator object functions */
status_t actuator_Init(actuator_t *pAct);
//
status_t actuator_SetHomed(actuator_t *pAct, flt32_t homePos_mm);
//
status_t actuator_SetTrgt(actuator_t *pAct, flt32_t targetPosition_mm, flt32_t targetVelocity_mmSec);
//
status_t actuator_Update(actuator_t *pAct, flt32_t livePos_mm, flt32_t liveVelocity_mmSec);
//
bool actuator_AtTrgt(actuator_t *PAct, flt32_t tolerence_mm);
//
#endif
