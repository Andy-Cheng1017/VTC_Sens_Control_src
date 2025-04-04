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

  gpio_init_type gpio_init_struct;
  tmr_output_config_type tmr_output_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr3_init 1 */

  /* add user code end tmr3_init 1 */

  /* configure the tmr3 CH2 pin */
  gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE5, GPIO_MUX_1);
  gpio_init_struct.gpio_pins = GPIO_PINS_5;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(GPIOB, &gpio_init_struct);

  /* configure counter settings */
  tmr_base_init(TMR3, 59999, 4);
  tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR3, FALSE);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR3, FALSE);
  tmr_primary_mode_select(TMR3, TMR_PRIMARY_SEL_OVERFLOW);

  /* configure overflow event */
  tmr_overflow_event_disable(TMR3, TRUE);

  /* configure channel 2 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
  tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, 0);
  tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_2, FALSE);

  tmr_output_channel_immediately_set(TMR3, TMR_SELECT_CHANNEL_2, FALSE);

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

/**
 * @brief  init tmr16 function.
 * @param  none
 * @retval none
 */
void wk_tmr16_init(void) {
  /* add user code begin tmr16_init 0 */

  /* add user code end tmr16_init 0 */

  /* add user code begin tmr16_init 1 */

  /* add user code end tmr16_init 1 */

  /* configure counter settings */
  tmr_base_init(TMR16, 65535, 1000);
  tmr_cnt_dir_set(TMR16, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR16, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR16, 0);
  tmr_period_buffer_enable(TMR16, FALSE);

  tmr_counter_enable(TMR16, TRUE);

  /* add user code begin tmr16_init 2 */

  /* add user code end tmr16_init 2 */
}

/**
 * @brief  init tmr17 function.
 * @param  none
 * @retval none
 */
void wk_tmr17_init(void) {
  /* add user code begin tmr17_init 0 */

  /* add user code end tmr17_init 0 */

  /* add user code begin tmr17_init 1 */

  /* add user code end tmr17_init 1 */

  /* configure counter settings */
  tmr_base_init(TMR17, 65535, 5);
  tmr_cnt_dir_set(TMR17, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR17, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR17, 0);
  tmr_period_buffer_enable(TMR17, FALSE);

  tmr_counter_enable(TMR17, TRUE);

  /* add user code begin tmr17_init 2 */

  /* add user code end tmr17_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
