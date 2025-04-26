################################################################################
# Imports

import paho.mqtt.client as mqtt
import random
import json
import time

################################################################################
# Dados simulados

payload = [{
    "uid": f"e643b48d-8dcd-4c4e-b5b5-611a5bb66fc8",
    "humidity": random.randint(0, 100),
    "temperature": 100,
    "unixtime": int(time.time()),
    "rainfall": random.randint(0, 100),
    "windSpeed": random.randint(0, 100),
    "pressure": random.randint(0, 100),
},
{
    "uid": f"f296aa48-dedb-4354-ac7d-a91f71de2f84",
    "humidity": random.randint(0, 100),
    "temperature": random.randint(0, 100),
    "unixtime": int(time.time()),
    "rainfall": random.randint(0, 100),
},
{
    "uid": f"67fa2d5d-6ef2-4cc1-b466-999166ec15d2",
    "humidity": random.randint(0, 100),
    "temperature": random.randint(0, 100),
    "unixtime": int(time.time()),
    "rainfall": random.randint(0, 100),
},
]

################################################################################
# Publisher

# Cria o cliente MQTT
pub = mqtt.Client()

# Conecta ao broker
pub.connect("test.mosquitto.org", 1883, 60)

# Converte os dados para JSON e publica no tópico
for p in payload:
    json_payload = json.dumps(p)
    pub.publish("fatec/api/sync/", json_payload)

# Desconecta do broker
pub.disconnect()