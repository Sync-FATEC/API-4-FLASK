################################################################################
# Imports

import paho.mqtt.client as mqtt
import random
import json
import time

################################################################################
# Dados simulados

payload = {
    "uid": f"BCD{random.randint(0, 10)}{random.randint(0, 10)}{random.randint(0, 10)}",
    "umi": random.randint(0, 100),
    "temp": random.randint(0, 100),
    "unixtime": int(time.time()),
    "chuva": random.randint(0, 100),
}

################################################################################
# Publisher

# Cria o cliente MQTT
pub = mqtt.Client()

# Conecta ao broker
pub.connect("test.mosquitto.org", 1883, 60)

# Converte os dados para JSON e publica no tópico
json_payload = json.dumps(payload)
pub.publish("fatec/api/sync/", json_payload)

# Desconecta do broker
pub.disconnect()