import os
import time
from Adafruit_ADS1x15.ads1105 import ADS1105

# Инициализация датчика ADXL345
adc = ADS1105()  # Включение датчика ADXL345

# Определение функций для обработки данных об уровне воды времени
def read_water_level():
    # Проверка нажатия кнопки (индикатор начала измерения)
    button = Button(18)  # Включение пина GPIO18 (для датчика уровня воды времени)
    if not button.is_pressed:  # Если кнопка не нажата, продолжать опрос датчика
        while True:
            if button.is_pressed:  # Если кнопка нажата, завершать опрос датчика и прочитать значение
                break
        time.sleep(1)  # Задержка для завершения опроса датчика
        return datetime.now().strftime('%d/%m/%Y %H:%M:%S')