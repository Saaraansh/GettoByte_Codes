/*
 * gpio_driver.c
 *
 *  Created on: Dec 18, 2022
 *      Author: saar
 */

#include <gpio_driver.h>

/**
 * @brief  Configures the mode of a pin : input, output, alt or analog mode
 * @param  *GPIOx : GPIO Port Base address
 * @param  pin_no : GPIO pin number
 * @param  mode   : mode to be configured
 * @retval None
*/
static void hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t mode)
{
	GPIOx->MODER |= (mode << (2 * pin_no)); //Each bit takes 2 bits in the MODER Register
}
/**
 * @brief  Configures the output type of a pin
 * @param  *GPIOx : GPIO Port Base address
 * @param  pin_no : GPIO pin number
 * @param  op_type   : output type to be configured with
 * @retval None
*/
static void hal_gpio_configure_pin_otype(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t op_type)
{
	GPIOx->OTYPER |= (op_type << (2 * pin_no));
}

/**
	* @brief  Configures the speed of a pin
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number
	* @param  speed   : value of the speed
	* @retval None
	*/
static void hal_gpio_configure_pin_speed(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t speed)
{
	GPIOx->OSPEEDR |= (speed << (2 * pin_no));
}

/**
 * @brief  Activates the internall pull up or pull down resistors
 * @param  *GPIOx : GPIO Port Base address
 * @param  pin_no : GPIO pin number
 * @param  pupd   : specifies which resistor to activate
 * @retval None
*/
void hal_gpio_configure_pin_pupd(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t pupd)
{
	 GPIOx->PUPDR |= (pupd << (2 * pin_no));
}

/**
 * @brief  Initializes the gpio pin
 * @param  *GPIOx : GPIO Port Base address
 * @param  *gpio_pin_conf :Pointer to the pin conf structure sent by application
 * @retval None
*/
void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf)
{
	hal_gpio_configure_pin_mode(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->mode);
	hal_gpio_configure_pin_speed(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->speed);
	hal_gpio_configure_pin_otype(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->op_type);
	hal_gpio_configure_pin_pupd(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->pupd);
}

/***
 * @brief Set Alternate Functionality for the Given Pin
 * @param *GPIO	  		  : GPIO Port Base Address
 * 		   pin_no		  : GPIO Pin Number
 * 		   alt_fun_value  : Alternate Function Value to be Configured with
 * @return None
 */
void hal_gpio_set_alt_fun(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint16_t alt_fun_value)
{
	if (pin_no <= 7)
		GPIOx->AFR[0] |= (alt_fun_value << (pin_no * 4));
	else
		GPIOx->AFR[1] |= (alt_fun_value << ((pin_no % 8) * 4));
}

/***
 * @brief Read a Value from a Given Pin
 * @param *GPIO	  : GPIO Port Base Address
 * 		   pin_no : GPIO Pin Number
 * @return uint8_t: Value Read
 */
uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	uint8_t value;
	value = ((GPIOx->IDR >> pin_no) & 0x00000001);
	//Read the IDR then right shift by the value of pin number to get the input status value of the pin to LSB
	return value;
}

/***
 * @brief Write a Value to a Given Pin Number
 * @param *GPIO	  : GPIO Port Base Address
 * 		   pin_no : GPIO Pin Number
 * 		   value  : Value to be written
 * @return None
 */
void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value)
{
	if (value)
		GPIOx->ODR |= (1 << pin_no);
	else
		GPIOx->ODR &= ~(1 << pin_no);

}

/**
 * @brief  Configure the interrupt for a given pin number
 * @param  pin_no 	  : GPIO pin number
 * @param  edge_sel   :  Triggering edge slection value of type "int_edge_sel_t"
 * @retval None
*/
void hal_gpio_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel)
{
	if (edge_sel == INT_RISING_EDG)
		EXTI->RTSR |= (1 << pin_no);
	else if (edge_sel == INT_FALLING_EDGE)
		EXTI->FTSR |= (1 << pin_no);
	else if (edge_sel == INT_RISING_FALLING_EDGE)
	{
		EXTI->FTSR |= (1 << pin_no);
		EXTI->RTSR |= (1 << pin_no);
	}
}

/**
 * @brief  Enable the interrupt for a give pin number and irq number
 * @param  pin_no 	: GPIO pin number
 * @param  irq_no   :  irq_number to be enabled in NVIC
 * @retval None
*/
void hal_gpio_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no)
{
	EXTI->IMR |= (1 << pin_no);
	NVIC_EnableIRQ(irq_no);
}

/**
 * @brief  Clear the sticky interrupt pending bit if set
 * @param  pin_no : GPIO pin number
 * @retval None
*/
void hal_gpio_clear_interrupt(uint16_t pin)
{
	if(EXTI->PR & (1 << pin))
		EXTI->PR |= (1 << pin);
}

