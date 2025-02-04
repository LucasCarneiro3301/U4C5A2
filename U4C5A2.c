/*
    Aluno: Lucas Carneiro de Araújo Lima
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "pico/time.h"
#include "pico/bootrom.h"

//Pinagem dos componentes
#define BTNA 5
#define BTNB 6

const uint blue = 11;  // VERDE na BitDogLab
const uint green = 12; // AZUL na BitDogLab
const uint red = 13; // VERMELHO na BitDogLab

bool rgb_state = false; // Estado dos 3 LEDs
bool btn_state = false; // Estado do botão A
bool reset = false; // true caso pressionado o botão B

static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

static void setup(); // Prototipação da função que define os LEDs RGB como saídas e os botões como entradas
static int64_t turn_off_led(alarm_id_t id, void *user_data); // Prototipação da rotina de temporização one-shot que desativa um LED 
static void gpio_irq_handler(uint gpio, uint32_t events); // Prototipação da função de interrupção
static void RGB_config(unsigned short int state); // Prototipação da função que configura o estado dos 3 LEDs

int main() {
    stdio_init_all(); // Inicialização dos recursos de entrada e saída padrão
    
    setup(); // Inicialização e configuração dos LEDs

    gpio_set_irq_enabled_with_callback(BTNA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); //Callback de interrupção do Botão A
    gpio_set_irq_enabled_with_callback(BTNB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); //Callback de interrupção do Botão B

    while (true) {
        if (rgb_state && btn_state) { // Só é executada se rgb_state (LEDs ligados) e btn_state (botão pressionado) estiverem true
            RGB_config(0x111); // Liga os 3 LEDs
            add_alarm_in_ms(3e3, turn_off_led, (void*)&blue, false); //Desliga o LED azul
            add_alarm_in_ms(6e3, turn_off_led, (void*)&green, false); //Desliga o LED verde
            add_alarm_in_ms(9e3, turn_off_led, (void*)&red, false); //Desliga o LED vermelho
            btn_state = false;
        } 

        if(reset) {
            printf("Saindo para o modo de gravação...\n\n");
            reset_usb_boot(0,0); // Sai para o modo de gravação
        }
        sleep_ms(10);
    }
    return 0;
}

// Inicializa e configura os LEDs RGB como saída. Inicializa e configura os botões como entradas.
void setup() {
    gpio_init(red);
    gpio_set_dir(red, GPIO_OUT); 

    gpio_init(green);
    gpio_set_dir(green, GPIO_OUT); 

    gpio_init(blue);
    gpio_set_dir(blue, GPIO_OUT);

    gpio_init(BTNA);
    gpio_set_dir(BTNA, GPIO_IN);
    gpio_pull_up(BTNA);  

    gpio_init(BTNB);
    gpio_set_dir(BTNB, GPIO_IN);
    gpio_pull_up(BTNB);  
}

// Configura o estado de cada um dos 3 LEDs
void RGB_config(unsigned short int state) {
    gpio_put(red,state & 0x100);
    gpio_put(green,state & 0x010);
    gpio_put(blue,state & 0x001);
}

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // Obtém o tempo atual em microssegundos

    if (current_time - last_time > 2e5) { // 200 ms de debouncing
        last_time = current_time; 

        if(gpio == BTNA && !rgb_state) {rgb_state = true; btn_state = true;} // Só é selecionado se o botão selecionado for o A e rgb_state for false (LEDs completamente desligados)
        else if(gpio == BTNB) reset = true;
    }
}

// Rotina de temporização one-shot. A cada 3 seg um LED é desligado
int64_t turn_off_led(alarm_id_t id, void *user_data) {
    gpio_put(*(uint*)user_data, false);
    if(*(uint*)user_data == red) rgb_state = false; // Se for a vez do LED vermelho, então todos os LEDs foram, enfim, desligados
    return 0;
}
