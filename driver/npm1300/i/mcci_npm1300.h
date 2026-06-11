/*

Module:	mcci_npm1300.h

Function:
	Register definitions for the Nordic NPM1300 power managment chip.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#ifndef _mcci_npm1300_h_
#define _mcci_npm1300_h_	/* prevent multiple includes */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// @name C-style definitions for Nordic NPM1300 register addresses
/// @{

///	@name Event and interrupt registers
///    	@{
#define MCCI_PMIC_NPM1300_REG_TASKSWRESET                             0x0001     ///< Task Force a full reboot power-cycle
#define MCCI_PMIC_NPM1300_REG_EVENTSADCSET                            0x0002     ///< ADC Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSADCCLR                            0x0003     ///< ADC Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSADCSET                       0x0004     ///< ADC Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSADCCLR                       0x0005     ///< ADC Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSBCHARGERSET_0                     0x0006     ///< Battery Charger Temperature Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSBCHARGERCLR_0                     0x0007     ///< Battery Charger Temperature Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSBCHARGERSET_0                0x0008     ///< Battery Charger Temperature Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSBCHARGERCLR_0                0x0009     ///< Battery Charger Temperature Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSBCHARGERSET_1                     0x000A     ///< Battery Charger Status Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSBCHARGERCLR_1                     0x000B     ///< Battery Charger Status Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSBCHARGERSET_1                0x000C     ///< Battery Charger Status Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSBCHARGERCLR_1                0x000D     ///< Battery Charger Status Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSBCHARGERSET_2                     0x000E     ///< Battery Charger Battery Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSBCHARGERCLR_2                     0x000F     ///< Battery Charger Battery Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSBCHARGERSET_2                0x0010     ///< Battery Charger Battery Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSBCHARGERCLR_2                0x0011     ///< Battery Charger Battery Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSSHPHOLDSET                        0x0012     ///< ShipHold pin Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSSHPHOLDCLR                        0x0013     ///< ShipHold pin Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSSHPHOLDSET                   0x0014     ///< ShipHold pin Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSSHPHOLDCLR                   0x0015     ///< ShipHold pin Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSVBUSINSET_0                       0x0016     ///< VBUSIN Voltage Detection Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSVBUSINCLR_0                       0x0017     ///< VBUSIN Voltage Detection Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSVBUSINSET_0                  0x0018     ///< VBUSIN Voltage Detection Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSVBUSINCLR_0                  0x0019     ///< VBUSIN Voltage Detection Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSVBUSINSET_1                       0x001A     ///< VBUSIN Thermal and USB Events Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSVBUSINCLR_1                       0x001B     ///< VBUSIN Thermal and USB Events Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSVBUSINSET_1                  0x001C     ///< VBUSIN Thermal and USB Events Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSVBUSINCLR_1                  0x001D     ///< VBUSIN Thermal and USB Events Interrupt Enable Clear
#define MCCI_PMIC_NPM1300_REG_EVENTSGPIOSET                           0x0022     ///< GPIO Event Event Set
#define MCCI_PMIC_NPM1300_REG_EVENTSGPIOCLR                           0x0023     ///< GPIO Event Event Clear
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSGPIOSET                      0x0024     ///< GPIO Event Interrupt Enable Set
#define MCCI_PMIC_NPM1300_REG_INTENEVENTSGPIOCLR                      0x0025     ///< GPIO Event Interrupt Enable Clear
///	@}

///	@name System Regulator Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_TASKUPDATEILIMSW                        0x0200     ///< Select Input Current limit for VBUS
#define MCCI_PMIC_NPM1300_REG_VBUSINILIM_0                            0x0201     ///< Select Input Current limit for VBUS, Reset value from OTP
#define MCCI_PMIC_NPM1300_REG_VBUSINILIMSTARTUP                       0x0202     ///< Select input Current limit for VBUS at Startup
#define MCCI_PMIC_NPM1300_REG_VBUSSUSPEND                             0x0203     ///< Suspend mode enable
#define MCCI_PMIC_NPM1300_REG_USBCDETECTSTATUS                        0x0205     ///< VBUS CC comparator status flags
#define MCCI_PMIC_NPM1300_REG_VBUSINSTATUS                            0x0207     ///< VBUS status flags
///	@}

///	@name Charger Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_TASKRELEASEERR                          0x0300     ///< Release Charger from Error
#define MCCI_PMIC_NPM1300_REG_TASKCLEARCHGERR                         0x0301     ///< Clear error registers
#define MCCI_PMIC_NPM1300_REG_TASKCLEARSAFETYTIMER                    0x0302     ///< Clear safety timers
#define MCCI_PMIC_NPM1300_REG_BCHGENABLESET                           0x0304     ///< Charger Enable Set
#define MCCI_PMIC_NPM1300_REG_BCHGENABLECLR                           0x0305     ///< Charger Enable Clear
#define MCCI_PMIC_NPM1300_REG_BCHGDISABLESET                          0x0306     ///< Charger Disable Recharge Set
#define MCCI_PMIC_NPM1300_REG_BCHGDISABLECLR                          0x0307     ///< Charger Disable Recharge Clear
#define MCCI_PMIC_NPM1300_REG_BCHGISETMSB                             0x0308     ///< Battery Charger Current Configuration
#define MCCI_PMIC_NPM1300_REG_BCHGISETLSB                             0x0309     ///< Battery Charger Current Configuration
#define MCCI_PMIC_NPM1300_REG_BCHGISETDISCHARGEMSB                    0x030A     ///< Battery Charger Discharge Configuration
#define MCCI_PMIC_NPM1300_REG_BCHGISETDISCHARGELSB                    0x030B     ///< Battery Charger Discharge Configuration
#define MCCI_PMIC_NPM1300_REG_BCHGVTERM                               0x030C     ///< Battery Charger Termination Voltage Normal temp
#define MCCI_PMIC_NPM1300_REG_BCHGVTERMR                              0x030D     ///< Battery Charger Termination Voltage Warm temp
#define MCCI_PMIC_NPM1300_REG_BCHGVTRICKLESEL                         0x030E     ///< Battery Charger Trickle Level Select
#define MCCI_PMIC_NPM1300_REG_BCHGITERMSEL                            0x030F     ///< Battery Charger ITERM Level Select
#define MCCI_PMIC_NPM1300_REG_NTCCOLD                                 0x0310     ///< NTC thermistor threshold for COLD temperature region
#define MCCI_PMIC_NPM1300_REG_NTCCOLDLSB                              0x0311     ///< NTC thermistor threshold for COLD temperature region
#define MCCI_PMIC_NPM1300_REG_NTCCOOL                                 0x0312     ///< NTC thermistor threshold for COOL temperature region
#define MCCI_PMIC_NPM1300_REG_NTCCOOLLSB                              0x0313     ///< NTC thermistor threshold for COOL temperature region
#define MCCI_PMIC_NPM1300_REG_NTCWARM                                 0x0314     ///< NTC thermistor threshold for WARM temperature region
#define MCCI_PMIC_NPM1300_REG_NTCWARMLSB                              0x0315     ///< NTC thermistor threshold for WARM temperature region
#define MCCI_PMIC_NPM1300_REG_NTCHOT                                  0x0316     ///< NTC thermistor threshold for HOT temperature region
#define MCCI_PMIC_NPM1300_REG_NTCHOTLSB                               0x0317     ///< NTC thermistor threshold for HOT temperature region
#define MCCI_PMIC_NPM1300_REG_DIETEMPSTOP                             0x0318     ///< DIE TEMP threshold for stop charging
#define MCCI_PMIC_NPM1300_REG_DIETEMPSTOPLSB                          0x0319     ///< DIE TEMP threshold for stop charging lsb
#define MCCI_PMIC_NPM1300_REG_DIETEMPRESUME                           0x031A     ///< DIE TEMP threshold for resuming charging
#define MCCI_PMIC_NPM1300_REG_DIETEMPRESUMELSB                        0x031B     ///< DIE TEMP threshold for resuming charging lsb
#define MCCI_PMIC_NPM1300_REG_BCHGILIMSTATUS                          0x032D     ///< BCHARGER Ilim Status
#define MCCI_PMIC_NPM1300_REG_NTCSTATUS                               0x0332     ///< NTC Comparator Status
#define MCCI_PMIC_NPM1300_REG_DIETEMPSTATUS                           0x0333     ///< DieTemp Comparator Status
#define MCCI_PMIC_NPM1300_REG_BCHGCHARGESTATUS                        0x0334     ///< Charging Status
#define MCCI_PMIC_NPM1300_REG_BCHGERRREASON                           0x0336     ///< Charger-FSM Error. Latched error reasons. Cleared with TASKS_CLEAR_CHG_ERR
#define MCCI_PMIC_NPM1300_REG_BCHGERRSENSOR                           0x0337     ///< Charger-FSM Error. Latched sensor values. Cleared with TASKS_CLEAR_CHG_ERR
#define MCCI_PMIC_NPM1300_REG_BCHGCONFIG                              0x033C     ///< Charger configuration
///	@}

///	@name Buck Regulator Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_BUCKENASET_1                            0x0400     ///< BUCK1 Enable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKENACLR_1                            0x0401     ///< BUCK1 Disable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKENASET_2                            0x0402     ///< BUCK2 Enable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKENACLR_2                            0x0403     ///< BUCK2 Disable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKPWMSET_1                            0x0404     ///< BUCK1 PWM mode enable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKPWMCLR_1                            0x0405     ///< BUCK1 PWM mode disable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKPWMSET_2                            0x0406     ///< BUCK2 PWM mode enable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKPWMCLR_2                            0x0407     ///< BUCK2 PWM mode disable pulse
#define MCCI_PMIC_NPM1300_REG_BUCKNORMVOUT_1                          0x0408     ///< BUCK1 Output voltage Normal mode
#define MCCI_PMIC_NPM1300_REG_BUCKRETVOUT_1                           0x0409     ///< BUCK1 Output voltage Retention mode
#define MCCI_PMIC_NPM1300_REG_BUCKNORMVOUT_2                          0x040A     ///< BUCK2 Output voltage Normal mode
#define MCCI_PMIC_NPM1300_REG_BUCKRETVOUT_2                           0x040B     ///< BUCK2 Output voltage Retention mode
#define MCCI_PMIC_NPM1300_REG_BUCKENCTRL                              0x040C     ///< BUCK Enable GPIO Select
#define MCCI_PMIC_NPM1300_REG_BUCKVRETCTRL                            0x040D     ///< BUCK Retention Voltage select
#define MCCI_PMIC_NPM1300_REG_BUCKPWMCTRL                             0x040E     ///< BUCK Forced PWM mode GPIO select
#define MCCI_PMIC_NPM1300_REG_BUCKSWCTRLSEL                           0x040F     ///< BUCK Software Control select
#define MCCI_PMIC_NPM1300_REG_BUCKVOUTSTATUS_1                        0x0410     ///< BUCK1 VOUT Status register
#define MCCI_PMIC_NPM1300_REG_BUCKVOUTSTATUS_2                        0x0411     ///< BUCK2 VOUT Status register
#define MCCI_PMIC_NPM1300_REG_BUCKCTRL_0                              0x0415     ///< BUCK Auto PFM to PWM Control select
#define MCCI_PMIC_NPM1300_REG_BUCKSTATUS                              0x0434     ///< BUCK status register
///	@}

///	@name System Monitor Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_TASKVBATMEASURE                         0x0500     ///< Task Take VBAT measurement
#define MCCI_PMIC_NPM1300_REG_TASKNTCMEASURE                          0x0501     ///< Task Take NTC measurement
#define MCCI_PMIC_NPM1300_REG_TASKTEMPMEASURE                         0x0502     ///< Task Take Die Temperature measurement
#define MCCI_PMIC_NPM1300_REG_TASKVSYSMEASURE                         0x0503     ///< Task Take VSYS measurement
#define MCCI_PMIC_NPM1300_REG_TASKIBATMEASURE                         0x0506     ///< Task Take IBATmeasurement
#define MCCI_PMIC_NPM1300_REG_TASKVBUSMEASURE_7                       0x0507     ///< Task Take VBUS 7V range measurement
#define MCCI_PMIC_NPM1300_REG_TASKDELAYEDVBATMEASURE                  0x0508     ///< Task Take delayed VBAT measurement
#define MCCI_PMIC_NPM1300_REG_ADCCONFIG                               0x0509     ///< ADC Configuration
#define MCCI_PMIC_NPM1300_REG_ADCNTCRSEL                              0x050A     ///< Select Battery NTC register
#define MCCI_PMIC_NPM1300_REG_ADCAUTOTIMCONF                          0x050B     ///< Auto measurement intervals
#define MCCI_PMIC_NPM1300_REG_TASKAUTOTIMUPDATE                       0x050C     ///< update toggle for NTC and Die temp AutoTime register bits
#define MCCI_PMIC_NPM1300_REG_ADCDELTIMCONF                           0x050D     ///< Vbat Delay timer control
#define MCCI_PMIC_NPM1300_REG_ADCIBATMEASURESTATUS                    0x0510     ///< Battery current measurement status
#define MCCI_PMIC_NPM1300_REG_ADCVBATRESULTMSB                        0x0511     ///< ADC VBAT measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCNTCRESULTMSB                         0x0512     ///< ADC NTC measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCTEMPRESULTMSB                        0x0513     ///< ADC DIE TEMP measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCVSYSRESULTMSB                        0x0514     ///< ADC VSYS measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCGPRESULTLSBS_0                       0x0515     ///< ADC result LSB's (Vbat, Ntc, Temp and Vsys)
#define MCCI_PMIC_NPM1300_REG_ADCVBATRESULTMSB_0                      0x0516     ///< ADC VBAT0 Burst measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCVBATRESULTMSB_1                      0x0517     ///< ADC VBAT1 Burst measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCVBATRESULTMSB_2                      0x0518     ///< ADC VBAT2 Burst measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCVBATRESULTMSB_3                      0x0519     ///< ADC VBAT3 Burst or VBUS measurement result MSB
#define MCCI_PMIC_NPM1300_REG_ADCGPRESULTLSBS_1                       0x051A     ///< ADC result LSB's (Vbat_burst0, 1, 2 and 3)
#define MCCI_PMIC_NPM1300_REG_ADCIBATMEASEN                           0x0524     ///< Enable auto IBAT measurement
///	@}

///	@name GPIO Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_GPIOMODE_0                              0x0600     ///< GPIO Mode Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOMODE_1                              0x0601     ///< GPIO Mode Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOMODE_2                              0x0602     ///< GPIO Mode Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOMODE_3                              0x0603     ///< GPIO Mode Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOMODE_4                              0x0604     ///< GPIO Mode Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODRIVE_0                             0x0605     ///< GPIO Drive strength Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODRIVE_1                             0x0606     ///< GPIO Drive strength Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODRIVE_2                             0x0607     ///< GPIO Drive strength Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODRIVE_3                             0x0608     ///< GPIO Drive strength Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODRIVE_4                             0x0609     ///< GPIO Drive strength Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPUEN_0                              0x060A     ///< GPIO Pull-up Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPUEN_1                              0x060B     ///< GPIO Pull-up Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPUEN_2                              0x060C     ///< GPIO Pull-up Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPUEN_3                              0x060D     ///< GPIO Pull-up Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPUEN_4                              0x060E     ///< GPIO Pull-up Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPDEN_0                              0x060F     ///< GPIO Pull-down Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPDEN_1                              0x0610     ///< GPIO Pull-down Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPDEN_2                              0x0611     ///< GPIO Pull-down Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPDEN_3                              0x0612     ///< GPIO Pull-down Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOPDEN_4                              0x0613     ///< GPIO Pull-down Enable Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOOPENDRAIN_0                         0x0614     ///< GPIO Open Drain Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOOPENDRAIN_1                         0x0615     ///< GPIO Open Drain Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOOPENDRAIN_2                         0x0616     ///< GPIO Open Drain Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOOPENDRAIN_3                         0x0617     ///< GPIO Open Drain Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOOPENDRAIN_4                         0x0618     ///< GPIO Open Drain Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODEBOUNCE_0                          0x0619     ///< GPIO Debounce Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODEBOUNCE_1                          0x061A     ///< GPIO Debounce Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODEBOUNCE_2                          0x061B     ///< GPIO Debounce Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODEBOUNCE_3                          0x061C     ///< GPIO Debounce Configuration
#define MCCI_PMIC_NPM1300_REG_GPIODEBOUNCE_4                          0x061D     ///< GPIO Debounce Configuration
#define MCCI_PMIC_NPM1300_REG_GPIOSTATUS                              0x061E     ///< GPIO Status from GPIO Pads
///	@}

///	@name Timer Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_TIMERSET                                0x0700     ///< Start Timer
#define MCCI_PMIC_NPM1300_REG_TIMERCLR                                0x0701     ///< Stop Timer
#define MCCI_PMIC_NPM1300_REG_TIMERTARGETSTROBE                       0x0703     ///< Strobe for timer Target
#define MCCI_PMIC_NPM1300_REG_WATCHDOGKICK                            0x0704     ///< Watchdog kick
#define MCCI_PMIC_NPM1300_REG_TIMERCONFIG                             0x0705     ///< Timer mode selection
#define MCCI_PMIC_NPM1300_REG_TIMERSTATUS                             0x0706     ///< Timers Status
#define MCCI_PMIC_NPM1300_REG_TIMERHIBYTE                             0x0708     ///< Timer Most Significant Byte
#define MCCI_PMIC_NPM1300_REG_TIMERMIDBYTE                            0x0709     ///< Timer Middle Byte
#define MCCI_PMIC_NPM1300_REG_TIMERLOWBYTE                            0x070A     ///< Timer Least Significant Byte
///	@}

///	@name Load Switch/LDO Registers
///	Control loads and low-dropout regulators ("LDO").
///	@{
#define MCCI_PMIC_NPM1300_REG_TASKLDSWSET_1                           0x0800     ///< Enable LDSW1
#define MCCI_PMIC_NPM1300_REG_TASKLDSWCLR_1                           0x0801     ///< Disable LDSW1
#define MCCI_PMIC_NPM1300_REG_TASKLDSWSET_2                           0x0802     ///< Enable LDSW2
#define MCCI_PMIC_NPM1300_REG_TASKLDSWCLR_2                           0x0803     ///< Disable LDSW2
#define MCCI_PMIC_NPM1300_REG_LDSWSTATUS                              0x0804     ///< Load Switch Status
#define MCCI_PMIC_NPM1300_REG_LDSWGPISEL_1                            0x0805     ///< Load Switch1 GPIO Control Select
#define MCCI_PMIC_NPM1300_REG_LDSWGPISEL_2                            0x0806     ///< Load Switch2 GPIO Control Select
#define MCCI_PMIC_NPM1300_REG_LDSWCONFIG                              0x0807     ///< Load Switch Configuration
#define MCCI_PMIC_NPM1300_REG_LDSWLDOSEL_1                            0x0808     ///< Load Switch1 / LDO Select
#define MCCI_PMIC_NPM1300_REG_LDSWLDOSEL_2                            0x0809     ///< Load Switch2 / LDO Select
#define MCCI_PMIC_NPM1300_REG_LDSWVOUTSEL_1                           0x080C     ///< LDO1 programmable output voltage
#define MCCI_PMIC_NPM1300_REG_LDSWVOUTSEL_2                           0x080D     ///< LDO2 programmable output voltage
///	@}

///	@name POF (Power-Fail Comparator) Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_POFCONFIG                               0x0900     ///< Power Failure Detection block configuration
///	@}

///	@name LED Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_LEDDRVMODESEL_0                         0x0A00     ///< Select for LED_0 mode
#define MCCI_PMIC_NPM1300_REG_LEDDRVMODESEL_1                         0x0A01     ///< Select for LED_1 mode
#define MCCI_PMIC_NPM1300_REG_LEDDRVMODESEL_2                         0x0A02     ///< Select for LED_2 mode
#define MCCI_PMIC_NPM1300_REG_LEDDRVSET_0                             0x0A03     ///< Set LED_0 to be On
#define MCCI_PMIC_NPM1300_REG_LEDDRVCLR_0                             0x0A04     ///< Clear LED_0 to be Off
#define MCCI_PMIC_NPM1300_REG_LEDDRVSET_1                             0x0A05     ///< Set LED_1 to be On
#define MCCI_PMIC_NPM1300_REG_LEDDRVCLR_1                             0x0A06     ///< Clear LED_1 to be Off
#define MCCI_PMIC_NPM1300_REG_LEDDRVSET_2                             0x0A07     ///< Set LED_2 to be On
#define MCCI_PMIC_NPM1300_REG_LEDDRVCLR_2                             0x0A08     ///< Clear LED_2 to be Off
///	@}

///	@name Ship and Hibernate Registers
///	Allow system power to be disconnected for shipping the product, or for a long duration
///	very low-power sleep.
///	@{
#define MCCI_PMIC_NPM1300_REG_TASKENTERHIBERNATE                      0x0B00     ///< Task Enter Hibernate
#define MCCI_PMIC_NPM1300_REG_TASKSHPHLDCFGSTROBE                     0x0B01     ///< Task Ship Hold config
#define MCCI_PMIC_NPM1300_REG_TASKENTERSHIPMODE                       0x0B02     ///< Task enter ShipMode
#define MCCI_PMIC_NPM1300_REG_TASKRESETCFG                            0x0B03     ///< Request reset config
#define MCCI_PMIC_NPM1300_REG_SHPHLDCONFIG                            0x0B04     ///< Ship Hold button press timer config
#define MCCI_PMIC_NPM1300_REG_SHPHLDSTATUS                            0x0B05     ///< Status of the SHPHLD pin
#define MCCI_PMIC_NPM1300_REG_LPRESETCONFIG                           0x0B06     ///< Long press reset config register
///	@}

///	@name Reset and Error Registers
///	@{
#define MCCI_PMIC_NPM1300_REG_TASKCLRERRLOG                           0x0E00     ///< Task to clear the Errlog registers
#define MCCI_PMIC_NPM1300_REG_SCRATCH_0                               0x0E01     ///< Scratch register 0
#define MCCI_PMIC_NPM1300_REG_SCRATCH_1                               0x0E02     ///< Scratch register 1
#define MCCI_PMIC_NPM1300_REG_RSTCAUSE                                0x0E03     ///< Error log for internal reset causes. Cleared withTASK_CLR_ERRLOG
#define MCCI_PMIC_NPM1300_REG_CHARGERERRREASON                        0x0E04     ///< Error log for slowDomain. Cleared with TASK_CLR_ERRLOG
#define MCCI_PMIC_NPM1300_REG_CHARGERERRSENSOR                        0x0E05     ///< Bcharger Fsm sensor error. Cleared with TASK_CLR_ERRLOG
///	@}
/// @}

#ifdef __cplusplus
}
#endif

#endif /* _mcci_npm1300_h_ */
