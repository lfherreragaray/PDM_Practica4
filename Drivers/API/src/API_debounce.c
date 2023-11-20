/*
 * API_debounce.c
 *
 *  Created on: Nov 19, 2023
 *      Author: ubuntu
 */


#include "API_debounce.h"


const uint8_t espera =40;
typedef enum{
	Button_Up,
	Button_Falling,
	Button_Down,
	Button_Rising,
} debounceState_t;
debounceState_t Estado;//=Button_Up;
delay_t delay;
bool_t Pulsador=false;



void debounceFSM_Init(){
	 Estado=Button_Up;
	 delayInit(&delay,espera);

}

void debounceFSM_Update(){
switch (Estado)
{
case Button_Up: if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
						{
							Estado=Button_Falling;
						}
break;
case Button_Falling: 			  delayRead(&delay);
					    if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
						{

						Estado=Button_Up;
						}
						else
						{

						    buttonPressed();
						    Estado=Button_Down;
						}
					  break;
case Button_Down: 				if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
						{

						Estado=Button_Rising;
						}
break;

case Button_Rising:
						delayRead(&delay);
						if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
						{


						Estado=Button_Down;
						}
						else
						{
						    buttonReleased();
						    Estado=Button_Up;
						}
break;
default: Estado= Button_Up;

    }
}
 void buttonPressed()
     {
     Pulsador=true;
     }

 void buttonReleased()
      {

      }


bool_t readKey()
    {
    if (Pulsador)
	{
	Pulsador=false;
	return true;
	}
    return false;
    }
