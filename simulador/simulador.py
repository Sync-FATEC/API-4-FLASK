################################################################################
# Importações

import paho.mqtt.client as mqtt
import json
################################################################################
# Main

def on_connect(con, userdata, flags, rc):
    """ Função chamada quando o cliente se conecta ao broker. """
    con.subscribe("fatec/api/sync/")
################################################################################

def on_message(con, userdata, msg):
    """ Função para processar mensagens recebidas. """
    mensagem = msg.payload.decode("utf-8")
    mensagem= json.loads(mensagem)

    print(mensagem)

################################################################################

con = mqtt.Client()
con.on_connect = on_connect
con.on_message = on_message

################################################################################
con.connect("test.mosquitto.org", 1883, 60)
con.loop_forever()