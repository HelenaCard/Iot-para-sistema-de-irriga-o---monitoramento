# IOT para sistema de irrigação e monitoramneto de temperatura e umidade.

## Projeto base para monitoramento de temperatura e umidade em um sistema simples de irrigação. 

O projeto foi relizado na plataforma [Wokwi](https://wokwi.com/) para simulação e produção do código de comando para o sistema de irrigação. Para testar o funcionamento do sistema utilizamos também o [Cliente Test](https://testclient-cloud.mqtt.cool/).

### Problema:
Para não utilizar mais sistemas manuais, em que, o indivíduo tem que cuidar quando há necessidade de uma área de plantação ser irrigada, criei um projeto base que permite essa área ser irrigada a partir de dispositivos que controlam a temperatura e umidade. O código monitora a umidade e a temperatura usando um sensor DHT22 conectado a um ESP32. Com base nos valores lidos e controlando LEDs para indicar o estado da umidade e da temperatura e publicando os dados em um broker MQTT para monitoramento remoto. Problema: Iot em sistemas de irrigação para diminuir o uso de ações manuais. 

### Solução: Automatizar por meio de dispositivo IoT (EPS32) quando a horta será irrigada. Assim, os leds tendem a acender ou apagar conforme a umidade e temperatura aumentam ou diminuem.

### Funcionamento Geral Conexão Wi-Fi: 
O ESP32 se conecta a uma rede Wi-Fi para se comunicar com o broker MQTT.

Leitura do Sensor DHT22: monitora a umidade e a temperatura do ambiente. 

### Controle dos LEDs: 
LED Vermelho: acende se a umidade estiver baixa (< 50%).

LED Verde: acende se a umidade estiver alta (>= 51%).

LED Normal: acende se a temperatura estiver na faixa normal (18°C a 28°C).


### Publicação MQTT:
Envia os dados de umidade e temperatura para os tópicos MQTT:

umidade: estado da umidade (baixa, alta ou normal).

temperatura: estado da temperatura (normal ou fora da faixa).

### Temporização:
O código aguarda 15 segundos entre cada leitura do sensor.

### Fluxo do Código
Setup:
Inicializa os pinos dos LEDs, o sensor DHT22, a conexão Wi-Fi e o cliente MQTT.

### Loop:
Verifica a conexão MQTT.

Lê a umidade e a temperatura.

Controla os LEDs com base nos valores lidos.

Publica os dados no broker MQTT.

Aguarda 15 segundos antes de repetir o processo.

### Componentes
Sensor DHT22: mede umidade e temperatura.

LEDs:

Vermelho: umidade baixa.

Verde: umidade alta.

Normal: temperatura ideal.

MQTT: envia dados para um broker (ex: test.mosquitto.org).

## Saída Esperada

### Monitor Serial:

Exibe o status da conexão Wi-Fi, leituras do sensor e mensagens MQTT.

LEDs:
Indicam visualmente o estado da umidade e da temperatura.

Broker MQTT:

Recebe os dados publicados para monitoramento remoto.

### Miniprojeto Wokwi

### Desenho do Projeto:

![image](https://github.com/user-attachments/assets/e41beba6-8152-4a26-8d7e-748b53979991)

### Código do Projeto:


[Link para simulação do projeto na plataforma WOKWI](https://wokwi.com/projects/424436528949370881)
