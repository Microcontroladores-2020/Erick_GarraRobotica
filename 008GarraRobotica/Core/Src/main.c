#include "stm32f401xe.h"
#include <stdint.h>

//C1 - > TRIGGER -> GPIO OUTPUT
//C0 -> ECHO -> GPIO INPUT
//B6 -> MOTOR CONTROL -> PWM OUTPUT

// função delay
void usdelay(uint32_t uSec);
//configuração e habilitação do GPIO utilizado
void init_gpio ();
// rotina de testes para o motor servo e calibração
void test_motor();
// configuração e inicialização do sinal PWM
void init_pwm();

//distancia calculada do ciclo atual
float distance = 0;
//distancia do ultimo ciclo
float dist_ctrl=0;
//coeficiente de correcao do da funcao delay já ajustado com valores reais no osciloscopio
const float coef = 2.8;


int main(void)
{
	volatile uint32_t tempo = 0;
	init_gpio();
	init_pwm();

	while(1){
		//PINO C1 gerando pulso de 10us
		GPIOC->ODR &= ~(0x1<<1);
		usdelay(3);
		GPIOC->ODR |= 0x1<<1;
		usdelay(10);
		GPIOC->ODR &= ~(0x1<<1);

		//espera receber echo (borda de subida echo)
		while(!(GPIOC->IDR & 0x1));

		tempo = 0;
		//leitura GPIO2 do echo com contagem
		while(GPIOC->IDR & 0x1){
			usdelay(2);
			tempo++;
		}

		// armazenando valor de distancia do ciclo anterior
		dist_ctrl = distance;
		//atualizando valor de distancia
	 	distance = (tempo+0.0f)*coef*0.0343/2;

	 	// controle para evitar valores absurdos recebidos pelo uC
	 	if(distance-dist_ctrl > 30) distance=dist_ctrl;

	 	// posicionamento da garra
	 	if(distance<3){
	 		TIM4->CCR1=9;
	 	}
	 	else if(distance>=3 && distance<6){
	 		TIM4->CCR1=8;
	 	}
	 	else if(distance>=6 && distance<9){
	 		TIM4->CCR1=7;
	 	}
	 	else if(distance>=9 && distance<12){
	 		TIM4->CCR1=6;
	 	}
	 	else if(distance>=12 && distance<15){
	 		TIM4->CCR1=5;
	 	}
	 	else if(distance>=15 && distance<18){
	 		TIM4->CCR1=4;
	 	}
	 	else{
	 		TIM4->CCR1=3;
	 	}
		usdelay(300000);
	}
}

void usdelay(uint32_t uSec)
{
	RCC->APB1ENR |= 0x1;	// habilitar clock em TIM2
	TIM2->PSC = 16;			// TIM2 freq = 16MHz/16 = 1MHz
	if(uSec < 2) uSec = 2;	// condicional para não haver valor negativo no registrador ARR na primeira iteração
	TIM2->ARR = uSec - 1; 	// ARR dinâmico
	TIM2->EGR = 1; 			// habilita reiniciar contagem
	TIM2->SR &= ~1; 		// reseta a flag de overflow do contador
	TIM2->CR1 |= 1; 		// habilita a contagem
	while((TIM2->SR&0x0001) != 1);	// delay
	TIM2->SR &= ~(0x0001);
}

void init_gpio ()
{
/* LED debug
	//GPIOA
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 1<<10;
*/
	//GPIOC
	RCC->AHB1ENR |= 0x1<<2;
	GPIOC->MODER |= 0x1<<2;	//C1 OUTPUT
	GPIOC->MODER &= ~(0x3);	// C0 INPUT

}
void init_pwm()
{
	//configuracoes iniciais (GPIO AF, TIM4 clk)
	RCC->AHB1ENR |= 0x1<<1;		//GPIOB habilitar
	RCC->APB1ENR |= (0x1<<2);	//clock TIM4
	GPIOB->MODER |= 0x1<<13;	//config PB6 como AF
	GPIOB->AFR[0] |= 0x1<<25;	//seleciona TIM3,4 e 5

	//TIM config
	TIM4->CCMR1 |= 0xD<<3;		//PWM mode 1 e habilita preload
	TIM4->CR1 |= 0x1<<7;		//habilita ARR preload buffer (load apos overflow)
	TIM4->CCER |= 0x1;			//habilita output

	//frequencia pwm = 50hz
	TIM4->CNT = 0;		//limpando contador
	TIM4->PSC = 3200-1;	//prescaler 3200->50hz
	TIM4->ARR = 100-1;	//reload register

	//duty cycle
	TIM4->CCR1 = 0;

	//habilitando do pwm
	TIM4->EGR |= 0x1;		//reinicializa a contagem apos overflow (UG)
	TIM4->CR1 |= 0x1;	//habilita contagem
}

// função teste para o motor servo
void test_motor()
{
	volatile uint8_t cont = 4;
	for(cont = 4; cont<9; cont++){
		TIM4->CCR1=cont;
		usdelay(600000);
	}
	for(cont = 9; cont>3; cont--){
		TIM4->CCR1=cont;
		usdelay(600000);
	}
}


