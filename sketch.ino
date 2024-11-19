#include <WiFi.h>
#include <HTTPClient.h>

// Configurações da rede Wi-Fi
#define WIFI_SSID "Wokwi-GUEST"         
#define WIFI_PASSWORD ""               

// Configurações do ThingSpeak
#define THINGSPEAK_API_KEY "P0U4CRF44LFSEUVD" 
#define THINGSPEAK_URL "http://api.thingspeak.com/update"

#define PINO_SENSOR_CORRENTE 34         
#define PINO_SENSOR_PRESENCA 15         
#define PINO_RELE 2                    

#define LED_VERDE 16                   
#define LED_AMARELO 17                 
#define LED_VERMELHO 18                

float consumoTotal = 0.0;
float corrente = 0.0;
bool ocupacao = false;
unsigned long tempoAnterior = 0;
const unsigned long intervalo = 1000;

void setup() {
  Serial.begin(115200);

  pinMode(PINO_SENSOR_PRESENCA, INPUT);
  pinMode(PINO_RELE, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Aguardando conexão Wi-Fi...");
  }
  Serial.println("Wi-Fi conectado!");
}

void enviarDadosThingSpeak(float consumo, float corrente, bool ocupacao) {
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;
    String url = String(THINGSPEAK_URL) + "?api_key=" + THINGSPEAK_API_KEY +
                 "&field1=" + String(consumo) + 
                 "&field2=" + String(corrente) + 
                 "&field3=" + String(ocupacao);
    http.begin(url);
    
    int httpResponseCode = http.GET(); 
    if (httpResponseCode > 0) {
      Serial.print("Dados enviados ao ThingSpeak com sucesso: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Erro ao enviar os dados: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Wi-Fi desconectado. Não foi possível enviar os dados.");
  }
}

void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;

    int leituraCorrente = analogRead(PINO_SENSOR_CORRENTE);
    corrente = (leituraCorrente * (2 / 4095.0)) * 100;  
    consumoTotal += corrente;
    ocupacao = digitalRead(PINO_SENSOR_PRESENCA);

    if (ocupacao) {
      digitalWrite(PINO_RELE, HIGH);
      Serial.println("Sala ocupada. Dispositivo ativado.");
    } else {
      digitalWrite(PINO_RELE, LOW);
      Serial.println("Sala desocupada. Dispositivo desativado.");
    }

    if (corrente <= 110) {
      digitalWrite(LED_VERDE, HIGH);   
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERMELHO, LOW);
    } else if (corrente > 110 && corrente <= 199) {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARELO, HIGH); 
      digitalWrite(LED_VERMELHO, LOW);
    } else if (corrente > 199) {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERMELHO, HIGH); 
    }

    Serial.print("Consumo atual: ");
    Serial.print(corrente);
    Serial.println("v");

    Serial.print("Consumo total acumulado: ");
    Serial.print(consumoTotal);
    Serial.println("v");

    enviarDadosThingSpeak(consumoTotal, corrente, ocupacao);
  }
}
