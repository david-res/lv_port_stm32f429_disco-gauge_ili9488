/**
 * @file indev.c
 * 
 */

/*********************
 *      INCLUDES
 *********************/
#include "hal_stm_lvgl/tft/tft.h"
#include "lvgl/src/lv_hal/lv_hal.h"

#include "stm32f4xx.h"
#include "../stm32f429i_discovery.h"
#include "ft6x06.h"
#include "stdio.h"
//#include "stm32469i_discovery_ts.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static bool touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t *data);
static bool touchpad_get_xy(int16_t *x, int16_t *y);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize your input devices here
 */


void touchpad_init(void)
{
	ft6x06_Init(TS_I2C_ADDRESS);
	ft6x06_TS_Start(TS_I2C_ADDRESS);

  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touchpad_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Read an input device
 * @param indev_id id of the input device to read
 * @param x put the x coordinate here
 * @param y put the y coordinate here
 * @return true: the device is pressed, false: released
 */


static bool touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t *data)
{
	static int16_t last_x = 0;
	static int16_t last_y = 0;

	bool detected;
	int16_t x;
	int16_t y;
	detected = touchpad_get_xy(&x, &y);
	if(detected) {
		data->point.x = x;
		data->point.y = y;
		last_x = data->point.x;
		last_y = data->point.y;
		//printf("FIXED = X value %d Y value %d \n", x,y);

		data->state = LV_INDEV_STATE_PR;
	} else {
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_REL;
	}


	return false;
}




static bool touchpad_get_xy(int16_t *x, int16_t *y)
{
	static int32_t _x = 0, _y = 0;
	int16_t xDiff, yDiff;
	uint16_t x_raw, y_raw;

	bool detected;
	detected = ft6x06_TS_DetectTouch(TS_I2C_ADDRESS);


	if(!detected) return false;
	ft6x06_TS_GetXY(TS_I2C_ADDRESS, &x_raw, &y_raw);


	xDiff = x_raw > _x? (x_raw - _x): (_x - x_raw);
	yDiff = y_raw > _y? (y_raw - _y): (_y - y_raw);

	if (xDiff + yDiff > 5) {
		_x = x_raw;
		_y = y_raw;
	}

	//Update the X and Y position
	*x = _x;
	*y = _y;

	return true;
}

