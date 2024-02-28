import os
import time
from datetime import datetime as dt
from gpiozero import Button

# Определение функций для обработки данных из датчика времени
def read_time_sensor():
    # Проверка нажатия кнопки (индикатор начала измерения)
    button = Button(18)  # Включение пина GPIO18 (для датчика времени)
    if not button.is_pressed:  # Если кнопка не нажата, продолжать опрос датчика
        while True:
            if button.is_pressed:  # Если кнопка нажата, завершать опрос датчика и прочитать значение
                break
        time.sleep(1)  # Задержка для завершения опроса датчика
        return datetime.now().strftime('%d/%m/%Y %H:%M:%S')
    else:  # Если кнопка нажата, завершать опрос датчика и прочитать значение
        return datetime.now().strftime('%d/%m/%Y %H:%M:%S')

# Определение функций для записи и чтения данных из датчика времени
def save_time_data():
    # Проверка нажатия кнопки (индикатор записи данных)
    button = Button(18)  # Включение пина GPIO18 (для датчика времени)
    if not button.is_pressed:  # Если кнопка не нажата, продолжать опрос датчика
        while True:
            if button.is_pressed:  # Если кнопка нажата, завершать опрос датчика и прочитать значение
                break
        time