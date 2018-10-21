/*

Programa para testar duas tarefas no FreeRTOS

*/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h> 
#include <math.h>

#define ADC_PIN			0

uint16_t adc_read(uint8_t ch);
void adc_init();
uint8_t readButton(void);

//Variaveis auxiliares do ADC
uint16_t val, temp, ph_val;
//Variavel utilizada na maquina de estados
uint8_t state = 0;

#define true 1

void temperatura();
void mostura();


xSemaphoreHandle s_1, s_2;

/*
Função principal - coloca o kernel em execução e cria as tarefas
*/
int main(void) {

	DDRB = 0b00111111;
	DDRD = 0b00000000;
	
	state = 0;
	adc_init();
	
	s_1 = xSemaphoreCreateCounting(1, 1);
	s_2 = xSemaphoreCreateCounting(1, 0);
	
	xTaskCreate( temperatura, (signed char*)"temperatura", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	xTaskCreate( mostura, (signed char*)"mostura", configMINIMAL_STACK_SIZE, NULL, 7, NULL );

	vTaskStartScheduler();
}


/*
Implementação das tarefas
*/
void temperatura()
{
	
	while (true) {
		xSemaphoreTake(s_1, portMAX_DELAY);
		
		val = adc_read(ADC_PIN);
		temp= round(val*0.48876);
		//vTaskDelay(200);

		xSemaphoreGive(s_2);
	}

}

void mostura()
{
	
	while (true) {
		xSemaphoreTake(s_2, portMAX_DELAY);
		switch(state){
            case 0:
                if(readButton()==1)
                    PORTB ^= (1 << PB1);
                else{
                    PORTB ^= (0 << PB1);
                    state = 1;
                }
            break;
            case 1:
				PORTB ^= (0 << PB1);
				PORTB ^= (1 << PB5);
                if(temp<70)
                    PORTB ^= (1 << PB0);
                else{
					PORTB ^= (0 << PB0);
                    state = 2;
				}
            break;
            case 2:
				PORTB ^= (1 << PB2);
				PORTB ^= (1 << PB3);
				_delay_ms(100);
				PORTB ^= (0 << PB2);
				PORTB ^= (0 << PB3);
                state = 3;
            break;
            case 3:
                if(temp<=100)
                    PORTB ^= (1 << PB0);
                else if(temp>100)
                    state = 4;
            break;
            case 4:
                if(temp>40)
                    PORTB ^= (1 << PB0);
                else{
                    PORTB ^= (1 << PB4);
                    _delay_ms(100);
                    PORTB ^= (0 << PB0);
                    state = 5;
                }
            break;
            case 5:
                PORTB ^= (0 << PB0);
                PORTB ^= (0 << PB4);
                PORTB ^= (0 << PB5);
            break;
		}
		xSemaphoreGive(s_1);	
	}
}

void adc_init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
    ch &= 0b00000111;
    ADMUX = (ADMUX & 0xF8)|ch;
 
    ADCSRA |= (1<<ADSC);
 
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
}

uint8_t readButton(void){
 if((PIND & (1<<PD0)) == 0)
	return 1;
 else
	return 0;
}

