/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_CPU_IS_KINETIS                (1)

#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_HEAP_SCHEME                       3 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (16*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"

/* performance counter: */
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (0)
#define configGET_RUNTIMER_COUNTER_VALUE_FROM_ISR   AppGetRuntimeCounterValueFromISR
#define configCONFIGURE_TIMER_FOR_RUNTIME_STATS     AppConfigureTimerForRuntimeStats


/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define SYSVIEW_APP_NAME                            "tinyK22 LedRing"
#define SYSVIEW_DEVICE_NAME                         "NXP K22FN512"

/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START

/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "tinyK22 LedRing"
#define McuShell_MULTI_CMD_ENABLED                    (0)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (96)

#endif /* INCLUDEMCULIBCONFIG_H_ */
