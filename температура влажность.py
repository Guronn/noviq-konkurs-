from flask import Flask, render_template
import os
from w1thermsensor import W1ThermSensor

app = Flask(__name__)

if __name__ == '__main__':
    sensor = W1ThermSensor()
    if sensor.search_for_w1_sensor():
        print("Температура: {:0.2f}°C".format(sensor.get_temperature()))
        print("Влажность: {:0.2f}%".format(sensor.get_humidity()))
    else:
        print("Не удалось найти датчик влажности")