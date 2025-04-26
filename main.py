################################################################################
# Imports

import paho.mqtt.client as mqtt
import json
from pymongo import MongoClient
from dotenv import load_dotenv
import os

################################################################################
# Main

def on_connect(con, userdata, flags, rc):
    """ Função chamada quando o cliente se conecta ao broker. """
    con.subscribe("fatec/api/sync/")

def on_message(con, userdata, msg):
    """ Função para processar mensagens recebidas. """
    mensagem = msg.payload.decode("utf-8")
    mensagem = json.loads(mensagem)

    measure_table = db["measures"]
    measure_table.insert_one(mensagem)

    print(mensagem)

################################################################################

# ENV
load_dotenv()
URL = os.getenv("MONGO_URL")
DB_NAME = os.getenv("MONGO_DB_NAME")

# MongoDB
try:
    client = MongoClient(URL)
    db = client[DB_NAME]
    print("Conectado ao MongoDB com sucesso!")
except Exception as e:
    print(f"Erro ao conectar ao MongoDB: {e}")

# MQTT
con = mqtt.Client()
con.on_connect = on_connect
con.on_message = on_message

con.connect("test.mosquitto.org", 1883, 60)
con.loop_forever()