/** ###################################################################
**     Filename  : Events.c
**     Project   : ProcessorExpert
**     Processor : MCF51CN128CLK
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2011-03-17, 12:29, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Platform.h"
#include "RTOS.h"
#include "App.h"
#if PL_HAS_CALENDAR_DEMO
  #include "Calendar.h"
#endif
#if PL_HAS_TETRIS_DEMO
  #include "Tetris.h"
#endif
#if PL_HAS_I2C_COMM
  #include "I2C.h"
#endif
#if PL_HAS_BOOTLOADER || PL_IS_BOOTLOADER
  #include "Bootloader.h"
#endif
#include "AnalogDigital.h"
#if PL_HAS_SD_DEMO
  #include "TMOUT1.h"
  #include "SDCard.h"
#endif

/*
** ===================================================================
**     Event       :  EVNT1_AppHandleEvent (module Events)
**
**     Component   :  EVNT1 [SimpleEvents]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - Event (event number) to be processed.
**     Returns     : Nothing
** ===================================================================
*/
void EVNT1_AppHandleEvent(uint8_t event)
{
  RTOS_HandleEvent(event);
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * pxTask          - Pointer to task handle
**       * pcTaskName      - Pointer to 
**     Returns     : Nothing
** ===================================================================
*/
#if PL_USE_RTOS
void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  /* Write your code here ... */
  (void)pxTask; (void)pcTaskName;
  for(;;) {}
}
#endif

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationTickHook(void)
{
#if PL_HAS_SD_DEMO
  TMOUT1_AddTick();
#endif
#if PL_USE_RTOS
  TRG1_AddTick();
#endif
#if PL_HAS_TETRIS_DEMO
  TETRIS_AddTime(10); /* additional 10ms */
#endif  
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationIdleHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationIdleHook(void)
{
  Cpu_SetWaitMode();
}

/*
** ===================================================================
**     Event       :  UI1_OnEvent (module Events)
**
**     Component   :  UI1 [UserInterface]
**     Description :
**         Event called for various element events
**     Parameters  :
**         NAME            - DESCRIPTION
**       * screen          - Pointer to screen
**       * window          - Pointer to window
**       * element         - Pointer to element
**         event           - kind of event
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_UI
void UI1_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event)
{
  APP_OnEvent(screen, window, element, event);
}
#endif /*PL_HAS_UI*/

/*
** ===================================================================
**     Event       :  I2C1_OnReceiveData (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the reception of the
**         data successfully. This event is not available for the SLAVE
**         mode and if both RecvChar and RecvBlock are disabled. This
**         event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C1_OnReceiveData(void)
{
#if PL_HAS_I2C_COMM
  I2C_OnRxChar();
#endif
}

/*
** ===================================================================
**     Event       :  I2C1_OnTransmitData (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the transmission of
**         the data successfully. This event is not available for the
**         SLAVE mode and if both SendChar and SendBlock are disabled.
**         This event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C1_OnTransmitData(void)
{
#if PL_HAS_I2C_COMM
  I2C_OnTxChar();
#endif
}

/*
** ===================================================================
**     Event       :  I2C1_OnRxChar (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         Called when a correct character is received. This event is
**         not available for the MASTER mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C1_OnRxChar(void)
{
#if PL_HAS_I2C_COMM
  I2C_OnRxChar();
#endif
}

/*
** ===================================================================
**     Event       :  I2C1_OnTxChar (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         Called when a correct character is sent (placed to the
**         transmitter). This event is not available for the MASTER
**         mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C1_OnTxChar(void)
{
#if PL_HAS_I2C_COMM
  I2C_OnTxChar();
#endif
}

/*
** ===================================================================
**     Event       :  KEY1_OnKeyPressed (module Events)
**
**     Component   :  KEY1 [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyPressed(uint8_t keys)
{
#if PL_BOARD_TWR_CN128 && PL_TWR_LCD_REV_0
  /* navigation switch on the TWR-LCD1: some we get from here */
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_PRESSED);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON5_PRESSED);
  } else if (keys&4) {
    EVNT1_SetEvent(EVNT1_BUTTON3_PRESSED);
  }
#elif PL_HAS_HW_NAV_SWITCH /* we get events from the navigation switch */
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_PRESSED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_PRESSED);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_BUTTON3_PRESSED);
  } else if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_BUTTON4_PRESSED);
  } else if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_BUTTON5_PRESSED);
  }
#elif PL_BOARD_TWR_CN128  || PL_BOARD_TWR_52259 /* we get events from the two TWR-CN128 onboard switches */ 
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_PRESSED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_PRESSED);
  }
#else
  (void)keys; /* ignore compiler warning */
#endif
}

/*
** ===================================================================
**     Event       :  KEY1_OnKeyReleased (module Events)
**
**     Component   :  KEY1 [Key]
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyReleased(uint8_t keys)
{
#if PL_BOARD_TWR_CN128 && PL_TWR_LCD_REV_0
  /* navigation switch on the TWR-LCD1: some we get from here */
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED);
  } else if (keys&4) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED);
  }
#elif PL_HAS_HW_NAV_SWITCH /* we get events from the navigation switch */
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED);
  } else if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_BUTTON4_RELEASED);
  } else if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED);
  }
#elif PL_BOARD_TWR_CN128 || PL_BOARD_TWR_52259 /* we get events from the two onboard switches */ 
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED);
  }
#else
  (void)keys; /* ignore compiler warning */
#endif
}

/*
** ===================================================================
**     Event       :  KEY1_OnKeyReleasedLong (module Events)
**
**     Component   :  KEY1 [Key]
**     Description :
**         Event generated after a key has been released (long key
**         press).
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyReleasedLong(uint8_t keys)
{
#if PL_BOARD_TWR_CN128 && PL_TWR_LCD_REV_0
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED_LONG);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED_LONG);
  } else if (keys&4) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED_LONG);
  }
#elif PL_HAS_HW_NAV_SWITCH /* we get events from the navigation switch */
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED_LONG);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED_LONG);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED_LONG);
  } else if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_BUTTON4_RELEASED_LONG);
  } else if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED_LONG);
  }
#elif PL_BOARD_TWR_CN128 || PL_BOARD_TWR_52259 /* we get events from the two on-board switches */ 
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED_LONG);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED_LONG);
  }
#else
  (void)keys;
#endif
}

/*
** ===================================================================
**     Event       :  SD1_OnIdle (module Events)
**
**     Component   :  SD1 [SD_Card]
**     Description :
**         Event called in case we are waiting on the device. Useful to
**         make a task switch for an RTOS.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_SD_DEMO
#endif

/*
** ===================================================================
**     Event       :  FAT1_OnIdle (module Events)
**
**     Component   :  FAT1 [FAT_FileSystem]
**     Description :
**         Event called while driver is waiting. Useful to call the OS
**         scheduler.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_SD_DEMO
#endif

/*
** ===================================================================
**     Event       :  FAT1_OnSchedule (module Events)
**
**     Component   :  FAT1 [FAT_FileSystem]
**     Description :
**         Event called to give an RTOS scheduler a chance.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_SD_DEMO
#endif

/*
** ===================================================================
**     Event       :  SD1_OnError (module Events)
**
**     Component   :  SD1 [SD_Card]
**     Description :
**         Event called in case of an low level error communicating
**         with the device
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_SD_DEMO
void SD1_OnError(void)
{
  SDC_Err();
}
#endif

/*
** ===================================================================
**     Event       :  ACCEL1_OnADGet (module Events)
**
**     Component   :  ACCEL1 [MMA7260Q]
**     Description :
**         Called to get mutual access to the A/D converter
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_HW_ACCELEROMETER
void ACCEL1_OnADGet(void)
{
  AD_GetDevice();
}
#endif
/*
** ===================================================================
**     Event       :  ACCEL1_OnADGive (module Events)
**
**     Component   :  ACCEL1 [MMA7260Q]
**     Description :
**         Called to give back mutual access to the A/D converter
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_HW_ACCELEROMETER
void ACCEL1_OnADGive(void)
{
  AD_GiveDevice();
}
#endif

/*
** ===================================================================
**     Event       :  UICalendar1_OnCalendarGetAppointments (module Events)
**
**     Component   :  UICalendar1 [UICalendar]
**     Description :
**         Event called in order to get a list of appointment. Note
**         that the list needs to remain in memory until the next call.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * startHint       - Pointer to the start date/time
**                           the event is interested in. As the event is
**                           requesting only appointments for a certain
**                           day, you may limit the amount of data
**                           passed.
**       * appointmentList - Pointer to linked
**                           list of appointments. The callee has to
**                           return here the pointer to the first
**                           element of the list.
**     Returns     : Nothing
** ===================================================================
*/
#if PL_HAS_CALENDAR_DEMO
void UICalendar1_OnCalendarGetAppointments(UICalendar1_CalendarDateTime *startHint, UICalendar1_CalendarAppointment **appointmentList)
{
  CAL_OnCalendarGetAppointments(startHint, appointmentList);
}
#endif

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Write your code here ... */
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  Sensor1_OnADGet (module Events)
**
**     Component   :  Sensor1 [TouchScreenSensor]
**     Description :
**         Event called to get mutual exclusive access to the A/D port
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Sensor1_OnADGet(void)
{
  AD_GetDevice();
}

/*
** ===================================================================
**     Event       :  Sensor1_OnADGive (module Events)
**
**     Component   :  Sensor1 [TouchScreenSensor]
**     Description :
**         Event called to return the mutual exclusive access to the
**         A/D port
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Sensor1_OnADGive(void)
{
  AD_GiveDevice();
}

/*
** ===================================================================
**     Description :
**         Event generated at the time a long key press has been
**         detected.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyPressedLong(uint8_t keys)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Description :
**         Used in tickless idle mode only, but required in this mode.
**         Hook for the application to enter low power mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/
void vOnPreSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used */
#if 0
  /* example for Kinetis (enable SetOperationMode() in CPU component): */
  // Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); /* Processor Expert way to get into WAIT mode */
  /* or to wait for interrupt: */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#elif 1
  /* example for S08/S12/ColdFire V1 (enable SetWaitMode() in CPU): */
  Cpu_SetWaitMode();
#elif 0
  /* example for ColdFire V2: */
   __asm("stop #0x2000"); */
#else
  #error "you *must* enter low power mode (wait for interrupt) here!"
#endif
  /* Write your code here ... */
}

/*
** ===================================================================
**     Description :
**         Event called after the CPU woke up after low power mode.
**         This event is optional.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/
void vOnPostSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used (yet?) */
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
