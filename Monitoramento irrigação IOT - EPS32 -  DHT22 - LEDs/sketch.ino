#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define DHTPIN 32     // Pino onde o sensor está conectado (GPIO32)
#define DHTTYPE DHT22 // Tipo do sensor (DHT22)

#define ledR 13       // Pino do LED vermelho (GPIO13)
#define ledG 14       // Pino do LED verde (GPIO14)
#define ledN 12       // Pino do LED normal (GPIO12) - Novo LED
//#define vSolenoide 15 // Pino da válvula solenoide (comentado)

///########### configuração do wifi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6
int status = WL_IDLE_STATUS; // o status do rádio Wi-Fi

///########## configuração do MQTT
const char *mqtt_server = "test.mosquitto.org"; // Broker MQTT
char *my_topic_SUB = "FIT/SUB";                 // Tópico para inscrição
char *my_topic_PUB = "FIT/PUB";                 // Tópico para publicação

/////##### configuração do wifi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void conectawifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
    Serial.print("Conectando ao WiFi ");
    Serial.print(WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println(" Conectado!");

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

// Process incoming MQTT message and control the servo motor
void callback(char *topic, byte *payload, unsigned int length)
{
    String string;
    Serial.print("Chegou a mensagem [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        string += ((char)payload[i]);
    }
    Serial.print(string);
}

// Attempt to reconnect to the MQTT broker if the connection is lost
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Tentando conectar ao MQTT ...");
        if (client.connect("ESPClient"))
        {
            Serial.println("Conectado");
            client.subscribe(my_topic_SUB);
        }
        else
        {
            Serial.print("falhou, rc=");
            Serial.print(client.state());
            Serial.println(" Tente novamente em 5 segundos");
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledN, OUTPUT); // Configura o novo LED como saída
    //pinMode(vSolenoide, OUTPUT);
    dht.begin();
    conectawifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    float umidade = dht.readHumidity();
    float temperatura = dht.readTemperature(); // Lê a temperatura

    if (isnan(umidade) || isnan(temperatura))
    {
        Serial.println("Falha ao ler o sensor DHT!");
        return;
    }

    // Controle de umidade
    if (umidade < 50.0)
    {
        digitalWrite(ledR, HIGH);    // Liga o LED Vermelho
        digitalWrite(ledG, LOW);     // Desliga o LED Verde
        digitalWrite(ledN, LOW);     // Desliga o LED Normal
        //digitalWrite(vSolenoide, HIGH); // Ativa a válvula solenoide
        client.publish("umidade", "Umidade Baixa =( REGANDO..."); // Publica a umidade no tópico "umidade"
        delay(10000);                // Mantém a válvula solenoide ativa por 10 segundos
        //digitalWrite(vSolenoide, LOW); // Desativa a válvula solenoide
        digitalWrite(ledR, LOW);     // Desliga o LED Vermelho
        delay(2000);
    }
    else if (umidade >= 51.0)
    {
        digitalWrite(ledG, HIGH);    // Liga o LED Verde
        digitalWrite(ledR, LOW);     // Desliga o LED Vermelho
        digitalWrite(ledN, LOW);     // Desliga o LED Normal
        //digitalWrite(vSolenoide, LOW); // Mantém a válvula solenoide desativada
        client.publish("umidade", "Umidade Alta =)"); // Publica a umidade no tópico "umidade"
    }
    else
    {
        digitalWrite(ledG, LOW);     // Desliga o LED Verde
        digitalWrite(ledR, LOW);     // Desliga o LED Vermelho
        digitalWrite(ledN, LOW);     // Desliga o LED Normal
        //digitalWrite(vSolenoide, LOW); // Mantém a válvula solenoide desativada
        client.publish("umidade", "Normal"); // Publica a umidade no tópico "umidade"
    }

    // Controle de temperatura
    if (temperatura >= 18.0 && temperatura <= 28.0) // Exemplo de faixa de temperatura normal
    {
        digitalWrite(ledN, HIGH);    // Liga o LED Normal
        client.publish("temperatura", "Temperatura Normal =)"); // Publica a temperatura no tópico "temperatura"
    }
    else
    {
        digitalWrite(ledN, LOW);     // Desliga o LED Normal
        client.publish("temperatura", "Temperatura Fora da Faixa =("); // Publica a temperatura no tópico "temperatura"
    }

    delay(15000); // Aguarda 15 segundos antes de ler o sensor novamente
}