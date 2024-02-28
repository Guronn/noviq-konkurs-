import os
import gpiozero
import time
from pyaudio import PyAudio, paInt16, paFloat32
from wave import Wave_Write
import numpy as np
import RPi.GPIO as GPIO

# Включение пина GPIO18 (для датчика света)
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Инициализация аудио интерфейса
audio = PyAudio()
stream = audio.open(format=paFloat32, channels=1, rate=44100, input_device_index=0)

# Определение функций для записи звука
def save_wavefile(filename):
    wf = wave.open(filename, 'w')  # Открываем файл для записи звука
    wf.setnchannels(1)  # Устанавливаем количество каналов (1 канал для монофонического звука)
    wf.setsampwidth(paFloat32)  # Устанавливаем ширину выборки (память в виде 16-битных целых)
    wf.setframerate(44100)  # Устанавливаем частоту дискретиза (частота звукового сигнала в Hz)
    wf.writeframes(data)  # Записываем звук (массив данных для записи в файл)
    wf.close()  # Закрываем файл

# Определение функций для обработки данных из датчика света
def read_light_sensor():
    GPIO.wait_for_edge(GPIO.gpio18, GPIO.FALLING)  # Ожидание