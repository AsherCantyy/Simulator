#include <math.h>
#include <string.h>

#include "common.h"
#include "motion_rig.h"
//
// used to
static flt32_t motionRig_radTOdeg (RigPoint_t point, flt32_t pitch_rad, flt32_t roll_rad, flt32_t heave_mm)
{
	return heave_mm + point.x_mm * sinf(pitch_rad) + point.y_mm * sinf(roll_rad);
}
//
status_t motionRig_Init(motionRig_t *pRig)
{
	RETURN_VAL_IF(pRig == NULL,STATUS_BAD_ARG);
	RETURN_VAL_IF(pRig->enabled == true, STATUS_ALREADY_DONE);
	//
	memset(pRig, 0, sizeof(motionRig_t));
	//
	pRig->enabled = true;
	pRig->status = STATUS_READY;
	//
	return STATUS_COMPLETE;
  //
}
//
status_t motionRig_SetTrgt(motionRig_t *pRig, flt32_t pitch_deg, flt32_t roll_deg, flt32_t heave_mm)
{
	RETURN_VAL_IF(pRig == NULL, STATUS_BAD_ARG);
	RETURN_VAL_IF(pRig->enabled == false, STATUS_NOT_READY);
	//
	pRig->trgtPitch_deg = pitch_deg;
	pRig->trgtRoll_deg = roll_deg;
	pRig->trgtHeave_mm = heave_mm;
	//
	return STATUS_COMPLETE;
  //
}
//
status_t motionRig_Update(motionRig_t *pRig)
{
	RETURN_VAL_IF(pRig == NULL, STATUS_BAD_ARG);
	RETURN_VAL_IF(pRig->enabled == false, STATUS_NOT_READY);
	//
	flt32_t trgtPitch_rad = DEG_TO_RAD(pRig->trgtPitch_deg);
	flt32_t trgtRoll_rad = DEG_TO_RAD(pRig->trgtRoll_deg);
	//
	pRig->trgtFrntLt_mm = motionRig_radTOdeg(pRig->loc_FrntLt_mm, trgtPitch_rad, trgtRoll_rad, pRig->trgtHeave_mm);
	pRig->trgtFrntRt_mm = motionRig_radTOdeg(pRig->loc_FrntRt_mm, trgtPitch_rad, trgtRoll_rad, pRig->trgtHeave_mm);

	pRig->trgtBackLt_mm = motionRig_radTOdeg(pRig->loc_BackLt_mm, trgtPitch_rad, trgtRoll_rad, pRig->trgtHeave_mm);
	pRig->trgtBackRt_mm = motionRig_radTOdeg(pRig->loc_BackRt_mm, trgtPitch_rad, trgtRoll_rad, pRig->trgtHeave_mm);

	pRig->trgtCenter_mm = pRig->trgtHeave_mm;
	//
	return STATUS_COMPLETE;
  //
}
//
