#include <stdio.h>
#include "w1_bus.h"
#include "dht.h"

int main() {
  // Инициализация W1-буса и датчика влажности
  w1_bus_t *w;
  dht_t sensor;
  
  // Пробуем инициализировать W1-бус и датчик влажности
  w = w1_bus_init();
  if (w == NULL) {
    printf("W1-бус не инициализирован\n");
    return -1;
  }
  
  // Пробуем считать информацию с датчика влажности
  if (dht_read(w, &sensor)) {
    printf("Не удалось прочитать информацию с датчика влажности\n");
    return -1;
  }
  
  // Выводим полученную информацию на экран
  printf("Температура: %.2f°C\n", sensor.temperature);
  printf("Влажность: %.2f%%\n", sensor.humidity);
  
  // Завершение работы
  w1_bus_exit(w);
  return 0;
}