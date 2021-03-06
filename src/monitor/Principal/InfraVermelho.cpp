#include "InfraVermelho.h"

InfraVermelho::InfraVermelho(uint8_t pinoEntrada, uint16_t frequencia, uint16_t intervalo) : Sensor(pinoEntrada, frequencia, intervalo)
{
}

void
InfraVermelho::detectar(void)
{
	if (deveExecutar())
	{
		setIntervalo(getIntervalo());
		executar();
		detectar();
	}
}

void
InfraVermelho::executar(void)
{
	int valorSensoriado = digitalRead(getPinoEntrada());

	executado();
}
