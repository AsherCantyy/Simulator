/*
 * motion rig object header
 * details whats inside of the object and prototypes its functions
 */
//
#ifndef MOTION_RIG_H_
#define MOTION_RIG_H_
//

#include "common.h"
#include "actuator.h"
//
typedef struct rigPoint
{ /*struct used for defining each actuators point in xy cords relative to the center pivot */
	//
	flt32_t x_mm;
	flt32_t y_mm;
  //
}RigPoint_t;
//
typedef struct motionRig
{	/* motionRig OWNS actuator_t instances: */
	 actuator_t actuatorFrntLt;
	 actuator_t actuatorFrntRt;
	 actuator_t actuatorBackLt;
	 actuator_t actuatorBackRt;
	 actuator_t actuatorCenter;

	/* inputs */
	flt32_t trgtPitch_deg;
	flt32_t trgtRoll_deg;
	flt32_t trgtHeave_mm;

	/* actuator arm connections relative to center pivot */
	RigPoint_t  loc_FrntLt_mm;
	RigPoint_t  loc_FrntRt_mm;
	RigPoint_t  loc_BackLt_mm;
	RigPoint_t  loc_BackRt_mm;

	/* output to actuator objects in mm */
	flt32_t trgtFrntLt_mm;
	flt32_t trgtFrntRt_mm;
	flt32_t trgtBackLt_mm;
	flt32_t trgtBackRt_mm;

	flt32_t trgtCenter_mm;
	/* states */
	bool enabled;
	status_t status;
  //
} motionRig_t;
///* objects function prototypes */
//
static flt32_t motionRig_radTOdeg(RigPoint_t point, flt32_t pitch_rad,flt32_t roll_rad, flt32_t heave_mm);
//
static flt32_t motionRig_Calc(motionRig_t *pRig, flt32_t current);
//
status_t motionRig_Init(motionRig_t *pRig);
//
status_t motionRig_SetTrgt(motionRig_t *pRig, flt32_t pitch_deg,flt32_t roll_deg, flt32_t heave_mm); // , uint32_t dt_ms
//
status_t motionRig_Update(motionRig_t *pRig);
//
#endif
