# U4C5A2
Repositório para a atividade 1 da unidade 4 e capítulo 5: Temporizador de um disparo (One Shot).

__Aluno:__
Lucas Carneiro de Araújo Lima

## ATIVIDADE 
__Descrição:__
Este projeto implementa um sistema de controle de LEDs acionado por um botão, em que, ao ser pressionado, os três LEDs são ligados simultaneamente. A transição entre estados ocorre com um temporizador configurado para um atraso de 3 segundos, desligando gradativamente os LEDs até restar nenhum aceso. As mudanças de estado são gerenciadas por funções de _callback_ do temporizador, garantindo a execução ordenada das etapas. Além disso, o botão só pode ser acionado novamente após o desligamento completo do último LED, impedindo interferências durante a execução das rotinas de temporização.

<div align="center">
  <img src="https://github.com/user-attachments/assets/d23e8eb8-8fa6-45ef-a9d6-d5285357a5a8" alt="GIF demonstrativo" width="400"/>
</div>

__Para este trabalho, os seguintes componentes e ferramentas se fazem necessários:__
1) Microcontrolador Raspberry Pi Pico W.
2) Simulador de Sistemas Embarcados Wokwi.
3) Ambiente de trabalho VSCode.
4) 3 LEDs
5) 3 Resistores 330 Ω
6) 2 Botões Pull-Up
7) Ferramenta educacional BitDogLab.

## Instruções de Uso

### 1. Clone o repositório
Abra o terminal e execute o comando abaixo para clonar o repositório em sua máquina:
```bash
git clone https://github.com/LucasCarneiro3301/U4C4O12T.git
```

### 2. Configure o ambiente de desenvolvimento
Certifique-se de que o [SDK do Raspberry Pi Pico](https://github.com/raspberrypi/pico-sdk) esteja instalado e configurado corretamente no seu sistema.

### 3. Configure a extensão do simulador Wokwi
Certifique-se de que a extensão [Wokwi para VS Code](https://docs.wokwi.com/pt-BR/vscode/getting-started) esteja instalada e configurada corretamente em seu ambiente VS Code.

### 4. Conexão com a Rapberry Pico
1. Conecte o Raspberry Pi Pico ao seu computador via USB.
2. Inicie o modo de gravação pressionando o botão **BOOTSEL** e **RESTART**.
3. O Pico será montado como um dispositivo de armazenamento USB.
4. Execute através do comando **RUN** a fim de copiar o arquivo `U4C5A2.uf2` para o Pico.
5. O Pico reiniciará automaticamente e executará o programa.

### 4. Observações (IMPORTANTE !!!)
1. O projeto é compatível **tanto** com o simulador Wokwi **quanto** com a placa BitDogLab.
2. Manuseie a placa com cuidado.

## Recursos e Funcionalidades

### 1. Botões

| BOTÃO                            | DESCRIÇÃO                                     | 
|:----------------------------------:|:---------------------------------------------:|
| A                                  | Liga todos os 3 LEDs                   | 
| B                                  | Reinicia para o modo de gravação              | 

### 2. LEDs

Após pressionar o **Botão A**, todos os LEDs são acesos e, seguindo a sequência **azul → verde → vermelho**, são gradativamente desligados a cada 3000 ms (3 segundos). Na placa BitDogLab o semáforo é representado pelo LED RGB, seguindo a mesma sequência de cores.

<div align="center">
  <img src="https://github.com/user-attachments/assets/dc17d18b-5b38-4ad1-9805-47e0d5b5b13d" alt="GIF demonstrativo" width="300"/>
</div>

### 3. Temporização One-Shot

A função `add_alarm_in_ms()` configura um temporizador do tipo _one-shot_, que executa a função _callback_ após um atraso de _N_ segundos e depois se encerra. Nesse projeto, há 3 atrasos: Atraso de 3 segundos, que desativa o LED azul, atraso de 6 segundos, que desativa o LED verde e, por fim, um atraso de 9 segundos, que desativa o LED vermelho.

### 4. Interrupções

O programa implementa interrupção nos botões A e B. Dessa forma, não é necessário ler continuamente o estado de cada botão. A função do **Botão A** só é executada se o estado dos LEDs estiver definido como falso (desligado).

### 5. Deboucing

O programa implementa tratamento de boucing (via software). Dessa forma, evita leituras falsas de botões causadas por oscilações elétricas, garantindo que cada pressionamento seja registrado apenas uma vez,









