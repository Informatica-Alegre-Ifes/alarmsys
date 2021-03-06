#include "Sensor.h"

Sensor::Sensor(uint8_t pinoEntrada, uint16_t frequencia, uint16_t intervalo)
{
      	this->pinoEntrada = pinoEntrada;
      	this->frequencia = frequencia;
      	this->intervalo = intervalo;
      	pinMode(this->pinoEntrada, INPUT);
}

uint8_t
Sensor::getPinoEntrada()
{
        return (pinoEntrada);
}

uint16_t
Sensor::getFrequencia()
{
        return (frequencia);
}

uint16_t
Sensor::getIntervalo()
{
        return (intervalo);
}

bool
Sensor::existeObjeto(void)
{
        return (objetoDetectado);
}
