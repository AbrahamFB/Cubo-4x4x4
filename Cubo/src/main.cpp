#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
//#include <TimerOne.h>

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
int columnas[16] = {32, 33, 25, 26,
                    16, 4, 2, 15,
                    3, 18, 5, 17,
                    23, 22, 21, 19};

int tiempoD = 100; //lluvia agresiva

long lastMsg = 0;
char msg[50];
int value = 0;

void todoOn()
{
  for (int f = 0; f < 4; f++)
  {
    digitalWrite(niveles[f], 0);
  }
  for (int c = 0; c < 16; c++)
  {
    digitalWrite(columnas[c], 1);
  }
}

void ninguno()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columnas[i], 0);
  }
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(niveles[i], 1);
  }
}

void encenderColumna(int col)
{ //OK
  for (int i = 0; i < 16; i++)
  {

    digitalWrite(columnas[i], 1);
    if (i != col)
    {
      digitalWrite(niveles[i], 1);
    }
    else
    {
      digitalWrite(niveles[i], 0);
    }
  }
}

void elevacionNivelUp()
{ //OK
  for (int i = 0; i < 4; i++)
  {
    encenderColumna(i);
    delay(200);
  }
}

void elevacionNivelDown()
{ //OK
  for (int i = 3; i >= 0; i--)
  {
    encenderColumna(i);
    delay(200);
  }
}

void encenderFila(int fila)
{ //OK
  for (int i = 0; i < 4; i++)
  {
    if (i != fila)
    {
      digitalWrite(niveles[i], 0);
    }
  }
  digitalWrite(columnas[fila], 1);
}

void cubo2x2()
{ //OK
  digitalWrite(columnas[0], 0);
  digitalWrite(columnas[4], 0);

  for (int i = 5; i < 11; i++)
  {
    if (i == 5 || i == 6 || i == 9 || i == 10)
    {
      digitalWrite(columnas[i], 1);
      digitalWrite(columnas[4], 0);
    }
    digitalWrite(niveles[0], 1);
    digitalWrite(niveles[3], 1);
  }
}
void cubo4x4x4()
{ //OK
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(niveles[i], 1);
  }

  for (int j = 0; j < 16; j++)
  {
    digitalWrite(columnas[0], 1);
    digitalWrite(columnas[j], 1);

    digitalWrite(niveles[0], 0);
    delay(100);

    digitalWrite(niveles[0], 1);
    digitalWrite(columnas[j], 0);
  }

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      if ((j == 0 || j == 1 || j == 2 || j == 3) && i == 0)
      {

        digitalWrite(columnas[j], 1);

        digitalWrite(niveles[i], 0);
        delay(100);

        digitalWrite(niveles[i], 1);
        digitalWrite(columnas[j], 0);
      }

      if ((j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 7 || j == 8 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15) && i == 1)
      {
        digitalWrite(columnas[j], 1);

        digitalWrite(niveles[i], 0);
        delay(100);

        digitalWrite(niveles[i], 1);
        digitalWrite(columnas[j], 0);
      }

      if ((j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 7 || j == 8 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15) && i == 2)
      {
        digitalWrite(columnas[j], 1);

        digitalWrite(niveles[i], 0);
        delay(100);

        digitalWrite(niveles[i], 1);
        digitalWrite(columnas[j], 0);
      }

      if (i == 3)
      {
        digitalWrite(columnas[j], 1);

        digitalWrite(niveles[i], 0);
        delay(100);

        digitalWrite(niveles[i], 1);
        digitalWrite(columnas[j], 0);
      }
    }
  }
  delay(100);
}

void patron1()
{ //OK

  for (int o = 0; o < 4; o++)
  {
    for (int j = 12; j < 16; j++)
    {
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);
    for (int j = 8; j < 12; j++)
    {
      digitalWrite(columnas[j + 4], 0);
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);

    for (int j = 4; j < 8; j++)
    {
      digitalWrite(columnas[j + 4], 0);
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);

    for (int j = 0; j < 4; j++)
    {

      digitalWrite(columnas[j + 4], 0);
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);

    for (int i = 0; i < 4; i++)
    {
      digitalWrite(columnas[i], 0);
    }

    // cambia de sentido /////////

    for (int j = 3; j < 16; j += 4)
    {
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);

    for (int j = 2; j < 15; j += 4)
    {

      digitalWrite(columnas[j + 1], 0);
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);

    for (int j = 1; j < 14; j += 4)
    {

      digitalWrite(columnas[j + 1], 0);
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);

    for (int j = 0; j < 13; j += 4)
    {
      digitalWrite(columnas[j + 1], 0);
      for (int i = 0; i < 4; i++)
      {
        if (i != j)
        {
          digitalWrite(niveles[i], 0);
        }
      }
      digitalWrite(columnas[j], 1);
    }
    delay(300);
    for (int i = 0; i < 13; i += 4)
    {
      digitalWrite(columnas[i], 0);
    }

    delay(300);
    elevacionNivelUp();
    delay(300);

    elevacionNivelDown();
    delay(300);
    for (int j = 0; j < 16; j++)
    {
      digitalWrite(columnas[j], 0);
    }
    delay(300);
  }
  todoOn();
}

void patron2()
{
  for (int l = 0; l < 4; l++)
  {
    for (int h = 0; h < 5; h++)
    {

      for (int u = 0; u < 4; u++)
      {
        digitalWrite(niveles[u], 0);
      }
      cubo2x2();
      delay(300);
      for (int u = 0; u < 4; u++)
      {
        digitalWrite(niveles[u], 1);
      }
      delay(300);
      for (int u = 0; u < 4; u++)
      {
        digitalWrite(niveles[u], 0);
      }

      delay(2);
    }
    cubo4x4x4();
    delay(2);
  }
  todoOn();
}

void porNiveles()
{
  for (int i = 0; i < 4; i++)
  {

    digitalWrite(niveles[i], 0);
    delay(500);

    digitalWrite(niveles[i], 0);
    digitalWrite(columnas[i], 1);
  }
}

void patron3()
{
  for (int l = 0; l < 4; l++)
  {
    for (int v = 0; v < 12; v++)
    {

      int numColumna1 = random(0, 4);
      int numColumna2 = random(4, 8);
      int numColumna3 = random(8, 12);
      int numColumna4 = random(12, 16);

      for (int i = 3; i >= 0; i--)
      {
        digitalWrite(columnas[numColumna1], 1);
        digitalWrite(columnas[numColumna2], 1);
        digitalWrite(columnas[numColumna3], 1);
        digitalWrite(columnas[numColumna4], 1);

        if (i == 0)
        {
          digitalWrite(niveles[0], 0);
          for (int b = 1; b < 4; b++)
          {
            digitalWrite(niveles[b], 1);
          }
        }
        if (i == 1)
        {
          digitalWrite(niveles[0], 1);
          digitalWrite(niveles[1], 0);
          digitalWrite(niveles[2], 1);
          digitalWrite(niveles[3], 1);
        }
        if (i == 2)
        {
          digitalWrite(niveles[0], 1);
          digitalWrite(niveles[1], 1);
          digitalWrite(niveles[2], 0);
          digitalWrite(niveles[3], 1);
        }
        if (i == 3)
        {
          digitalWrite(niveles[0], 1);
          digitalWrite(niveles[1], 1);
          digitalWrite(niveles[2], 1);
          digitalWrite(niveles[3], 0);
        }
        delay(tiempoD);
      }
      tiempoD -= 1;
      if (tiempoD <= 1)
      {
        tiempoD = 100;
      }
      //Serial.println(tiempoD);
      digitalWrite(columnas[numColumna1], 0);
      digitalWrite(columnas[numColumna2], 0);
      digitalWrite(columnas[numColumna3], 0);
      digitalWrite(columnas[numColumna4], 0);
    }
    delay(100);
    for (int v = 0; v < 12; v++)
    {

      int numColumna1 = random(0, 4);
      int numColumna2 = random(4, 8);
      int numColumna3 = random(8, 12);
      int numColumna4 = random(12, 16);

      for (int i = 0; i < 4; i++)
      {
        digitalWrite(columnas[numColumna1], 1);
        digitalWrite(columnas[numColumna2], 1);
        digitalWrite(columnas[numColumna3], 1);
        digitalWrite(columnas[numColumna4], 1);

        if (i == 0)
        {
          digitalWrite(niveles[0], 0);
          for (int a = 1; a < 4; a++)
          {
            digitalWrite(niveles[a], 1);
          }
        }
        if (i == 1)
        {
          digitalWrite(niveles[0], 1);
          digitalWrite(niveles[1], 0);
          digitalWrite(niveles[2], 1);
          digitalWrite(niveles[3], 1);
        }
        if (i == 2)
        {
          digitalWrite(niveles[0], 1);
          digitalWrite(niveles[1], 1);
          digitalWrite(niveles[2], 0);
          digitalWrite(niveles[3], 1);
        }
        if (i == 3)
        {
          for (int p = 0; p < 3; p++)
          {
            digitalWrite(niveles[p], 1);
          }

          digitalWrite(niveles[3], 0);
        }
        delay(tiempoD);
      }
      tiempoD -= 1;
      if (tiempoD <= 1)
      {
        tiempoD = 100;
      }
      //Serial.println(tiempoD);
      digitalWrite(columnas[numColumna1], 0);
      digitalWrite(columnas[numColumna2], 0);
      digitalWrite(columnas[numColumna3], 0);
      digitalWrite(columnas[numColumna4], 0);
    }
  }
  todoOn();
}

void patron4()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(niveles[0], 1);
    digitalWrite(niveles[3], 1);

    for (int d = 0; d < 4; d++)
    {
      digitalWrite(columnas[d], 1);
      delay(50);
    }

    digitalWrite(columnas[7], 1);
    digitalWrite(columnas[0], 0);
    delay(50);

    digitalWrite(columnas[6], 1);
    digitalWrite(columnas[1], 0);
    delay(50);

    digitalWrite(columnas[5], 1);
    digitalWrite(columnas[2], 0);
    delay(50);

    digitalWrite(columnas[4], 1);
    digitalWrite(columnas[3], 0);
    delay(50);

    //////////////////

    digitalWrite(columnas[8], 1);
    digitalWrite(columnas[7], 0);
    delay(50);

    digitalWrite(columnas[9], 1);
    digitalWrite(columnas[6], 0);
    delay(50);

    digitalWrite(columnas[10], 1);
    digitalWrite(columnas[5], 0);
    delay(50);

    digitalWrite(columnas[11], 1);
    digitalWrite(columnas[4], 0);
    delay(50);

    digitalWrite(columnas[15], 1);
    digitalWrite(columnas[8], 0);
    delay(50);

    digitalWrite(columnas[14], 1);
    digitalWrite(columnas[9], 0);
    delay(50);
    digitalWrite(columnas[13], 1);
    digitalWrite(columnas[10], 0);
    delay(50);
    digitalWrite(columnas[12], 1);
    digitalWrite(columnas[11], 0);
    delay(50);

    digitalWrite(niveles[0], 1);

    digitalWrite(columnas[8], 1);
    digitalWrite(columnas[15], 0);
    delay(50);

    digitalWrite(columnas[4], 1);
    digitalWrite(columnas[14], 0);
    delay(50);

    digitalWrite(columnas[0], 1);
    digitalWrite(columnas[13], 0);
    delay(50);

    //////

    digitalWrite(columnas[1], 1);
    digitalWrite(columnas[12], 0);
    delay(50);

    digitalWrite(columnas[2], 1);
    digitalWrite(columnas[8], 0);
    delay(50);

    digitalWrite(columnas[3], 1);
    digitalWrite(columnas[4], 0);
    delay(50);
    //////

    digitalWrite(columnas[7], 1);
    digitalWrite(columnas[0], 0);
    delay(50);

    digitalWrite(columnas[11], 1);
    digitalWrite(columnas[1], 0);
    delay(50);

    digitalWrite(columnas[15], 1);
    digitalWrite(columnas[2], 0);
    delay(50);

    /////////////////////

    delay(300);

    for (int i = 0; i < 16; i++)
    {
      digitalWrite(columnas[i], 0);
    }
  }
  todoOn();
}
void patron5()
{
  for (int i = 0; i < 4; i++)
  {
    for (int w = 0; w < 4; w++)
    {
      digitalWrite(niveles[w], 1);
    }
    for (int y = 0; y < 4; y++)
    {
      digitalWrite(niveles[y], 0);

      int esta = 0;
      int foco = 0;
      for (int f = 0; f < 2; f++)
      {
        if (esta == f)
        {
          foco = 0;
        }
        else
        {
          foco = 1;
        }
        digitalWrite(columnas[10], foco);
        digitalWrite(columnas[0], 1);
        delay(100);

        digitalWrite(columnas[3], 1);
        digitalWrite(columnas[0], foco);
        delay(100);

        digitalWrite(columnas[15], 1);
        digitalWrite(columnas[3], foco);
        delay(100);

        digitalWrite(columnas[12], 1);
        digitalWrite(columnas[15], foco);
        delay(100);

        digitalWrite(columnas[9], 1);
        digitalWrite(columnas[12], foco);
        delay(100);

        digitalWrite(columnas[5], 1);
        digitalWrite(columnas[9], foco);
        delay(100);

        digitalWrite(columnas[6], 1);
        digitalWrite(columnas[5], foco);
        delay(100);

        digitalWrite(columnas[10], 1);
        digitalWrite(columnas[6], foco);
        delay(100);
      }
    }
  }
  todoOn();
}

void callback(char *topix, byte *payload, unsigned int length)
{
  //Serial.println("Mensaje recibido bajo el tópico-> ");
  //Serial.println(topix);
  //Serial.println("\n");

  for (int i = 0; i < length; i++)
  {
    //Serial.println((char)payload[i]);
  }

  if ((char)payload[0] == '0')
  {
    //digitalWrite(BUILTIN_LED, LOW);
    //Serial.println("\n Led Apagado");
    ninguno();
    // for (int i = 0; i < 16; i++)
    // {
    //   digitalWrite(columnas[i], 0);
    // }
    // //turning on layers
    // for (int i = 0; i < 4; i++)
    // {
    //   digitalWrite(niveles[i], 1);
    // }
  }
  else
  {
    if ((char)payload[0] == '1')
    {
      //digitalWrite(BUILTIN_LED, HIGH);
      patron1();
      //  Serial.println("\n Patrón 1");
    }
    if ((char)payload[0] == '2')
    {
      patron2();
      //digitalWrite(BUILTIN_LED, HIGH);
      // Serial.println("\n Patrón 2");
    }
    if ((char)payload[0] == '3')
    {
      patron3();
      //digitalWrite(BUILTIN_LED, HIGH);
      //  Serial.println("\n Patrón 3");
    }
    if ((char)payload[0] == '4')
    {
      patron4();
      // digitalWrite(BUILTIN_LED, HIGH);
      //  Serial.println("\n Patrón 4");
    }
    if ((char)payload[0] == '5')
    {
      patron5();
      //digitalWrite(BUILTIN_LED, HIGH);
      //  Serial.println("\n Patrón 5");
    }
  }

  //  Serial.println();
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
      // Serial.println("Conexión a MQTT exitosa!!");
      client.publish("afb", "primer mensaje");
      client.subscribe("afb1");
    }
    else
    {
      // Serial.println("Falló la conexión ");
      //Serial.println(client.state());
      //Serial.println(" Se intentará de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup_wifi()
{
  // put your setup code here, to run once:
  //Serial.begin(115200);
  delay(10);

  //Serial.println("");
  // Serial.println("");

  //Serial.println("Conectado a -> ");
  // Serial.println(ssid);

  //Me conecto a la red WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    // Serial.println(".");
    delay(250);
  }

  //Serial.println("");
  //Serial.println("Conexión Exitosa!");

  //Serial.println("Mi ip es -> ");
  //Serial.println(WiFi.localIP());
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

  //pinMode(BUILTIN_LED, OUTPUT);
  //Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  ninguno();
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
    //Serial.println("Mensaje enviado -> " + String(value));
  }
}
