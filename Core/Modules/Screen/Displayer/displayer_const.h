/*
 * displayer_const.h
 *
 *  Created on: Jan 30, 2021
 *      Author: emrei
 */

#ifndef MODULES_SCREEN_DISPLAYER_DISPLAYER_CONST_H_
#define MODULES_SCREEN_DISPLAYER_DISPLAYER_CONST_H_

/**
  * @brief  Displayer Size
  */
#define  DISPLAYER_WIDTH    ((uint16_t)480)          /* LCD PIXEL WIDTH            */
#define  DISPLAYER_HEIGHT   ((uint16_t)272)          /* LCD PIXEL HEIGHT           */

/**
  * @brief  Displayer Timing
  */

#define  DISPLAYER_HSYNC            ((uint16_t)41)   /* Horizontal synchronization */
#define  DISPLAYER_HBP              ((uint16_t)13)   /* Horizontal back porch      */
#define  DISPLAYER_HFP              ((uint16_t)32)   /* Horizontal front porch     */
#define  DISPLAYER_VSYNC            ((uint16_t)10)   /* Vertical synchronization   */
#define  DISPLAYER_VBP              ((uint16_t)2)    /* Vertical back porch        */
#define  DISPLAYER_VFP              ((uint16_t)2)    /* Vertical front porch       */

#endif /* MODULES_SCREEN_DISPLAYER_DISPLAYER_CONST_H_ */
