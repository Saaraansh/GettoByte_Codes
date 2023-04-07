/*
 * gpio_driver.h
 *
 *  Created on: Dec 18, 2022
 *      Author: saar
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

// MCU Specific Header File for STM32f411CEU6 for Black Pill
#include <stm32f411xe.h>
#include <stdint.h>

/***************************************************************************************************
  							Macros Used For GPIO PIN Initialization
***************************************************************************************************/
// GPIO MODE Setting Values
#define GPIO_PIN_INPUT_MODE				((uint32_t) 0x00)
#define GPIO_PIN_OUTPUT_MODE			((uint32_t) 0x01)
#define GPIO_PIN_ALTERNATE_MODE			((uint32_t) 0x02)
#define GPIO_PIN_ANALOG_MODE			((uint32_t) 0x03)

//GPIO OP Type Selection Values
#define GPIO_PIN_OP_TYPE_PUSHPULL			((uint32_t) 0x00)
#define GPIO_PIN_OP_TYPE_OPENDRAIN			((uint32_t) 0x01)

//GPIO SPEED Type Selection Values
#define GPIO_PIN_SPEED_LOW				((uint32_t) 0x00)
#define GPIO_PIN_SPEED_MEDIUM			((uint32_t) 0x01)
#define GPIO_PIN_SPEED_FAST				((uint32_t) 0x02)
#define GPIO_PIN_SPEED_HIGH				((uint32_t) 0x03)

//GPIO PULL-UP/PULL-DOWN Selection Values
#define GPIO_PIN_NO_PULLUPPUSHDOWN		((uint32_t) 0x00)
#define GPIO_PIN_PULLUP					((uint32_t) 0x01)
#define GPIO_PIN_PUSHDOWN				((uint32_t) 0x02)
#define GPIO_PIN_RESERVED				((uint32_t) 0x03)

//GPIO PORT Address
#define GPIO_PORT_A			GPIOA
#define GPIO_PORT_B			GPIOB
#define GPIO_PORT_C			GPIOC
#define GPIO_PORT_D			GPIOD
#define GPIO_PORT_E			GPIOE
#define GPIO_PORT_H			GPIOH

//Macros to Enable Clock for Different GPIO Ports in RCC Register
#define _HAL_RCC_GPIOA_CLK_ENABLE_RCC()				(RCC->AHB1ENR |= (1 << 0))
#define _HAL_RCC_GPIOB_CLK_ENABLE_RCC()				(RCC->AHB1ENR |= (1 << 1))
#define _HAL_RCC_GPIOC_CLK_ENABLE_RCC()				(RCC->AHB1ENR |= (1 << 2))
#define _HAL_RCC_GPIOD_CLK_ENABLE_RCC()				(RCC->AHB1ENR |= (1 << 3))
#define _HAL_RCC_GPIOE_CLK_ENABLE_RCC()				(RCC->AHB1ENR |= (1 << 4))
#define _HAL_RCC_GPIOH_CLK_ENABLE_RCC()				(RCC->AHB1ENR |= (1 << 7))

/********************************************************************************************************************
 	 	 	 	 	 	 	 	 	 Data Structure for GPIO Pin Initialization
********************************************************************************************************************/

/***
 * @brief GPIO Pin Configuration Structure
 * This Structure will be filled and passed to driver by the application and will initialize the GPIO Pin
 */
typedef struct
{
	uint32_t pin;			//Specifies the GPIO Pin to be configured
	uint32_t mode; 			//Specifies the operation mode for the specific pin
	uint32_t op_type;		//Specifies the output type for the specific pin
	uint32_t pupd;			//Specifies the Pull-Up or Push-Down for the specific pin
	uint32_t speed; 		//Specifies the speed r the specific pin
	uint32_t alternate;		//Specifies the alternate function value if the mode is set for alt function mode
}gpio_pin_conf_t;


/****
 * @brief I2C pinspack enumeration
 */
typedef enum
{
	INT_RISING_EDG,
	INT_FALLING_EDGE,
	INT_RISING_FALLING_EDGE
}int_edge_sel_t;

/********************************************************************************************************************
 	 	 	 	 	 	 	 	 	 	 	 	 Driver Exposed APIs
********************************************************************************************************************/
/***
 * @brief Initializes the GPIO Pin
 * @param *GPIO			 : GPIO Port Base Address
 * 		   *gpio_pin_conf: Pointer to the pin config structure sent by application
 * @return None
 */
void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf);

/***
 * @brief Read a Value from a Given Pin
 * @param *GPIO	  : GPIO Port Base Address
 * 		   pin_no : GPIO Pin Number
 * @return uint8_t: Value Read
 */
uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no);

/***
 * @brief Write a Value to a Given Pin Number
 * @param *GPIO	  : GPIO Port Base Address
 * 		   pin_no : GPIO Pin Number
 * 		   value  : Value to be written
 * @return None
 */
void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value);

/***
 * @brief Set Alternate Functionality for the Given Pin
 * @param *GPIO	  		  : GPIO Port Base Address
 * 		   pin_no		  : GPIO Pin Number
 * 		   alt_fun_value  : Alternate Function Value to be Configured with
 * @return None
 */
void hal_gpio_set_alt_fun(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint16_t alt_fun_value);

/**
 * @brief  Configure the interrupt for a given pin number
 * @param  pin_no 	  : GPIO pin number
 * @param  edge_sel   :  Triggering edge slection value of type "int_edge_sel_t"
 * @retval None
*/
void hal_gpio_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel);

/**
 * @brief  Enable the interrupt for a give pin number and irq number
 * @param  pin_no 	: GPIO pin number
 * @param  irq_no   :  irq_number to be enabled in NVIC
 * @retval None
*/
void hal_gpio_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no);

/**
 * @brief  Clear the sticky interrupt pending bit if set
 * @param  pin_no : GPIO pin number
 * @retval None
*/
void hal_gpio_clear_interrupt(uint16_t pin);

#endif /* GPIO_DRIVER_H_ */
