# Projeto microcontroladores VF2020

![DevBoard pinout](https://github.com/Microcontroladores-2020/Erick_GarraRobotica/blob/master/Imagens/STM32-Nucleo-F401RE-Pinout.png?raw=true)


## Motivação

A motivação do projeto é fazer um protótipo de garra robótica autônoma, que será bastante simplificado devido ao pouco tempo e disposição de recursos.
Além disso, uma proposta do projeto é tornar o código mais eficiente possível em termos de processamento dentro do que foi aprendido na disciplina até o momento. Com isso, as únicas bibliotecas necessárias para o projeto será a biblioteca da CMSIS "stm32f4xx.h" e as próprias start up files referentes ao microcontrolador que poderão ser baixados neste repositório.

## Descrição do conceito

O projeto será desenvolvido em um STM32F401RE embarcado em uma Nucleo development board e a proposta é criar uma garra robótica de apenas 1 eixo de liberadade. 
Para isso, será usado um servo motor como atuador do sistema, um sensor ultrassônico HC-SR04 e a próptia development board Nucleo STM32F401RE.
O sensor de ultrassom será ativado e lido pelo microcontrolador a cada ciclo do programa. Com ele, é possível ter uma noção da distância da garra robótica para um obstáculo ou objeto a ser manipulado.
A medida que o objeto se aproxima, a garra se fecha em formato de pinça.

## Funcionamento e descrição dos periféricos

Foram necessários 4 periféricos para o projeto final: TIM2, GPIOC e TIM4. Além disso, durante o desenvolvimento, foi usado USART2.

O clock interno utlizado nos reset values do microcontrolador é de 16 MHz e pode ser usado a até 84 Mhz. No nosso caso, o clock de 16 Mhz foi mantido. 

### TIM2

Foi usado para criar uma função de delay para ser aplicada ao código uma vez que a mesma não é uma função nativa da biblioteca do fabricante apesar de ser essencial para o fluxo do firmware.

#### Configurações iniciais:

Prescaler: 16-1
ARR: 0 (habilitado durante o código)
Counter mode: UP (Crescente)
Trigger event: UG bit
Load value: 0

### TIM4

Foi usado para gerar saída PWM para o controle do atuador. O mesmo está localizado no pino B6 da development board.

#### Configurações iniciais:

Output mode: PWM generation
Prescaler: 3200-1
ARR: 100-1
Counter mode: UP (Crescente)
Trigger event: UG bit
Load value: 0
CH polarity: HIGH

### GPIOB

Usado no modo alternate function ao habilitar AF2 do registrador AFRL. Isso por sua vez, permite que haja saída para o PWM configurado no periférico TIM4.

![AFR Multiplexer](https://github.com/Microcontroladores-2020/Erick_GarraRobotica/blob/master/Imagens/AF_multiplexador.png?raw=true)

### GPIOC

Este periférico controlou 3 pinos: ECHO, TRIGGER e userButton.

#### TRIGGER

Emite pulso de aproximadamente 10 us para o sensor ultrassom para requisitar as informações do mesmo.

Foi configurado como GPIO output e High Speed

#### ECHO

Recebe o sinal vindo do pino ECHO do ultrassom e amostra esse sinal recebido como forma de medir o tempo que o pulso fica em HIGH, que é usado para medir a distância.

Foi configurado como GPIO input

#### userButton

Permite que o usuário entre em uma rotina de testes para o servo motor ao clicar no user button da própria development board.

Foi configurado como GPIO input e interrupt trigger

### USART2 (não incluído no projeto final)
Obs: é conveniente usar comunicação serial UART para debugar e acompanhar os valores das variáveis do código durante o desenvolvimento. No caso do microcontrolador utilizado, usa-se o periférico USART2 para a comunicação com o host uma vez que ele tem conexão direta com a entrada USB do debugger.

#### Configurações iniciais:

Modo de comunicação: Assíncrona 
baud rate: 115200 bits/s
Tamanho da mensagem: 8 bits
Paridade: sem paridade
Stop bits: 1
Data direction: Full-duplex (transmitir e receber)

## Diagrama de Blocos



## Pin-out table



## Fluxograma do firmware



## Descrição de variáveis e funções



## Melhorias futuras

Um projeto inicial mais ambicioso, porém realizável a baixo custo seria tornar a garra mais precisa com mais resolução. Isso pode ser feito aosubstituir o motor servo por motor de passo. Para isso, ainda seria necessário incluir drivers de motor de passo. Outra boa adição ao sistema seria a inclusão de outros sensores de ultrassom em outras posições para melhorar a percepção do sistema e/ou até mesmo adicionar outros sensores como diodos foto sensíveis para curtas distâncias e CI ToF VL53L0X.
Além disso, poderia-se aplicar um controle mais rebuscado como fuzzy ou PID caso houvesse mais resolução nos motores.