/*
 * eeprom_addresses.c
 *
 *  Created on: 24.01.2020
 *      Author: Yannick
 */

#include "eeprom_addresses.h"

/*
Add all used addresses to the VirtAddVarTab[] array. This is important for the eeprom emulation to correctly transfer between pages.
This ensures that addresses that were once used are not copied again in a page transfer if they are not in this array.
*/
uint16_t VirtAddVarTab[NB_OF_VAR] =
	{
		ADR_HW_VERSION, ADR_SW_VERSION,
		ADR_CURRENT_CONFIG,

		ADR_FFBWHEEL_CONFIG,ADR_FFBWHEEL_POWER,ADR_FFBWHEEL_BUTTONCONF,ADR_FFBWHEEL_ANALOGCONF,ADR_FFBWHEEL_DEGREES,
		ADR_TMC1_MOTCONF,ADR_TMC1_PPR,ADR_TMC1_ENCA,ADR_TMC1_OFFSETFLUX,ADR_TMC1_TORQUE_P,ADR_TMC1_TORQUE_I,ADR_TMC1_FLUX_P,ADR_TMC1_FLUX_I,
		ADR_FFB_EFFECTS1,
		ADR_SHIFTER_BTN_CONF,
		ADR_LOCAL_BTN_CONF,
		ADR_SPI_BTN_CONF,
		ADR_PWM_MODE


	};
