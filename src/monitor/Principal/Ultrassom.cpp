#include "Ultrassom.h"

Ultrassom::Ultrassom(uint8_t pinoEntrada, uint16_t frequencia, uint16_t intervalo, uint8_t pinoSaida, uint16_t distancia, uint16_t limiteDeteccoes) : Sensor(pinoEntrada, frequencia, intervalo)
{
        this->pinoSaida = pinoSaida;
        this->distancia = distancia;
        this->limiteDeteccoes = limiteDeteccoes;
        distanciaEcoada = 0;
        deteccoes = 0;
      	pinMode(this->pinoSaida, OUTPUT);
}

void
Ultrassom::detectar(void)
{
        if (deveExecutar())
        {
                setIntervalo(getFrequencia());
                executar();
                 // ESTE BLOCO DE CÓDIGO É USADO APENAS PARA TESTE DE SENSIBILIDADE
                // DOS SENSORES, E DEVERÁ SER REMOVIDO APÓS A CONCLUSÃO DO PROJETO.
                Serial.print("Pinos ");
                Serial.print(getPinoEntrada());
                Serial.print(" e ");
                Serial.print(pinoSaida);
                Serial.print(": ");
                Serial.println(deteccoes);
                
                if (deteccoes == limiteDeteccoes)
                {
                        setIntervalo(getIntervalo());
                        deteccoes = 0;
                        objetoDetectado = true;

                        // ESTE BLOCO DE CÓDIGO É USADO APENAS PARA TESTE DE SENSIBILIDADE
                        // DOS SENSORES, E DEVERÁ SER REMOVIDO APÓS A CONCLUSÃO DO PROJETO.
                        Serial.print("OBJETO DETECTADO! Pinos ");
                        Serial.print(getPinoEntrada());
                        Serial.print(" e ");
                        Serial.print(pinoSaida);
                        Serial.println(". Inativo por 15 segundos.");                        
                }
                else
                        objetoDetectado = false;
        }
}

void
Ultrassom::executar(void)
{
        digitalWrite(pinoSaida, LOW);
        delayMicroseconds(2);
        
        digitalWrite(pinoSaida, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinoSaida, LOW);
        
        distanciaEcoada = pulseIn(getPinoEntrada(), HIGH);
        distanciaEcoada *= velocidadeSom / 2;
        
        if (distanciaEcoada < distancia)
                deteccoes++;
        else
                deteccoes = 0;
        
        executado();
}
