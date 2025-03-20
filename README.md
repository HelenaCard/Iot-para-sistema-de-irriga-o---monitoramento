# IOT para sistema de irrigação e monitoramneto de temperatura e umidade.

## Projeto base para monitoramento de temperatura e umidade em um sistema simples de irrigação. 

O projeto foi relizado na plataforma [Wokwi](https://wokwi.com/) para simulação e produção do código de comando para o sistema de irrigação. Para testar o funcionamento do sistema utilizamos também o [Cliente Test](https://testclient-cloud.mqtt.cool/).

## Interface da Plataforma Wokwi
![Captura de tela 2025-03-20 153232](https://github.com/user-attachments/assets/5389c9c6-a6ce-46a9-83b4-714e8308be86)

## Documentação da platafroma WOKWI 

![Captura de tela 2025-03-20 153408](https://github.com/user-attachments/assets/67143979-9522-4394-8b89-56871e6207a4)

[Documentação disponível aqui](https://docs.wokwi.com/pt-BR/)

### Problema 

A irrigação manual em plantações exige monitoramento constante e intervenção humana, resultando em ineficiência e potencial desperdício de água. A necessidade de eliminar a dependência de sistemas manuais e otimizar o processo de irrigação torna-se crucial para garantir o uso eficiente dos recursos hídricos e aumentar a produtividade agrícola.

### Solução: 

Desenvolver um sistema de irrigação automatizado baseado em IoT, utilizando um ESP32 e um sensor DHT22. O sistema monitora a temperatura e a umidade do local, acionando automaticamente a irrigação quando necessário. Além disso, fornece feedback visual através de LEDs, indicando o status da umidade e da temperatura em tempo real. Os dados coletados são enviados para um broker MQTT, garantindo o monitoramento remoto das condições da plantação de qualquer local com acesso à internet. Os LEDs acendem ou apagam conforme a umidade e temperatura aumentam ou diminuem, fornecendo um retorno claro do estado da plantação.

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
