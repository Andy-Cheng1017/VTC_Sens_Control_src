/* add user code begin Header */
/**
 **************************************************************************
 * @file     wk_tmr.c
 * @brief    work bench config program
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "wk_tmr.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
 * @brief  init tmr3 function.
 * @param  none
 * @retval none
 */
void wk_tmr3_init(void) {
  /* add user code begin tmr3_init 0 */

  /* add user code end tmr3_init 0 */

  /* add user code begin tmr3_init 1 */

  /* add user code end tmr3_init 1 */

  /* configure counter settings */
  tmr_base_init(TMR3, 65535, 200);
  tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR3, FALSE);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR3, FALSE);
  tmr_primary_mode_select(TMR3, TMR_PRIMARY_SEL_OVERFLOW);

  tmr_counter_enable(TMR3, TRUE);

  /* add user code begin tmr3_init 2 */

  /* add user code end tmr3_init 2 */
}

/**
 * @brief  init tmr15 function.
 * @param  none
 * @retval none
 */
void wk_tmr15_init(void) {
  /* add user code begin tmr15_init 0 */

  /* add user code end tmr15_init 0 */

  /* add user code begin tmr15_init 1 */

  /* add user code end tmr15_init 1 */

  /* configure counter settings */
  tmr_base_init(TMR15, 65535, 200);
  tmr_cnt_dir_set(TMR15, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR15, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR15, 0x0);
  tmr_period_buffer_enable(TMR15, FALSE);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR15, FALSE);
  tmr_primary_mode_select(TMR15, TMR_PRIMARY_SEL_OVERFLOW);

  tmr_counter_enable(TMR15, TRUE);

  /* add user code begin tmr15_init 2 */

  /* add user code end tmr15_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
