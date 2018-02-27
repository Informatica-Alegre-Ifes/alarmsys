#include "SensorUltrasonico.h"

SensorUltrasonico::SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, int intervalo)
{
      	this->pinoEcho = pinoEcho;
      	this->pinoTrigger = pinoTrigger;
      	this->frequencia = frequencia;
      	this->intervalo = intervalo;
      	distanciaEcoada = deteccoes = 0;
      	objetoDetectado = false;
      	pinMode(pinoEcho, INPUT);
      	pinMode(pinoTrigger, OUTPUT);
}

bool
SensorUltrasonico::existeObjeto(void)
{
        return (objetoDetectado);
}

void
SensorUltrasonico::detectar(void)
{
        if (shouldRun())
        {
                setInterval(frequencia);
                run();

                Serial.print("Detecções dos pinos ");
                Serial.print(pinoEcho);
                Serial.print(" e ");
                Serial.print(pinoTrigger);
                Serial.print(": ");
                Serial.println(deteccoes);
                
                if (deteccoes == MINIMO_DETECCAO)
                {
                        setInterval(intervalo);
                        deteccoes = 0;
                        objetoDetectado = true;

                        Serial.print("OBJETO DETECTADO pelos pinos ");
                        Serial.print(pinoEcho);
                        Serial.print(" e ");
                        Serial.print(pinoTrigger);
                        Serial.println(". Inativo por 5 segndos.");
                }
                else
                        objetoDetectado = false;
        }
}

void
SensorUltrasonico::run()
{
        digitalWrite(pinoTrigger, LOW);
        delayMicroseconds(2);
        
        digitalWrite(pinoTrigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinoTrigger, LOW);
        
        distanciaEcoada = pulseIn(pinoEcho, HIGH);
        distanciaEcoada *= velocidadeSom / 2;
        
        if (distanciaEcoada < MAXIMA_DISTANCIA)
                deteccoes++;
        else
                deteccoes = 0;
        
        runned();
}
