#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char *ssid = "Totalplay-749E";
const char *password = "749E074Ataqg9m92";

const char *mqtt_server = "driver.cloudmqtt.com";
const int mqtt_port = 18651;
const char *mqtt_user = "clxxwiek";
const char *mqtt_pass = "PtsiiKX9xhVm";

WiFiClient espClient;
PubSubClient client(espClient);

//LEDS
int niveles[4] = {13, 12, 14, 27};
int columnas[16] = {26, 25, 33, 32, 23, 22, 1, 3, 21, 19, 18, 5, 17, 16, 4, 15};

long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char *topix, byte *payload, unsigned int length)
{
  Serial.print("Mensaje recibido bajo el tópico-> ");
  Serial.print(topix);
  Serial.print("\n");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  if ((char)payload[0] == '0')
  {
    digitalWrite(BUILTIN_LED, LOW);
    Serial.println("\n Led Apagado");

    for (int i = 0; i < 16; i++)
    {
      digitalWrite(columnas[i], 0);
    }
    //turning on layers
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(niveles[i], 1);
    }
  }
  else
  {
    if ((char)payload[0] == '1')
    {
      digitalWrite(BUILTIN_LED, HIGH);
      patron1();
      Serial.println("\n Patrón 1");
    }
    if ((char)payload[0] == '2')
    {
      patron2();
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("\n Patrón 2");
    }
    if ((char)payload[0] == '3')
    {
      patron3();
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("\n Patrón 3");
    }
    if ((char)payload[0] == '4')
    {
      patron4();
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("\n Patrón 4");
    }
    if ((char)payload[0] == '5')
    {
      patron5();
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("\n Patrón 5");
    }
  }

  Serial.println();
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Intentando Conexión MQTT");

    String clientId = "iot_1_";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conexión a MQTT exitosa!!");
      client.publish("afb", "primer mensaje");
      client.subscribe("afb1");
    }
    else
    {
      Serial.println("Falló la conexión ");
      Serial.print(client.state());
      Serial.print(" Se intentará de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup_wifi()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  Serial.println("");
  Serial.println("");

  Serial.println("Conectado a -> ");
  Serial.println(ssid);

  //Me conecto a la red WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(250);
  }

  Serial.println("");
  Serial.println("Conexión Exitosa!");

  Serial.println("Mi ip es -> ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  //Se configuran los leds por columnas(16) y niveles(4)
  for (int i = 0; i < 16; i++)
  {
    pinMode(columnas[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++)
  {
    pinMode(niveles[i], OUTPUT);
  }

  randomSeed(analogRead(10));

  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  if (client.connected() == false)
  {
    reconnect();
  }

  client.loop(); //mantener nuestro dispositivo en escucha de posibles mensajes (obligatoria)

  if (millis() - lastMsg > 2000)
  {
    lastMsg = millis();
    value++;
    String mes = "Tiempo: " + String(value) + "s"; // El mensaje a publicar será el contenido de la variable
    mes.toCharArray(msg, 50);
    client.publish("afb1", msg);
    Serial.println("Mensaje enviado -> " + String(value));
  }
}

void patron1()
{
}
void patron2()
{
}
void patron3()
{
}
void patron4()
{
}
void patron5()
{
}
void ninguno()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columnas[i], 0);
  }
  //turning on layers
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(niveles[i], 1);
  }
}