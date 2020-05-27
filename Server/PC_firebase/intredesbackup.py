import serial
import firebase_admin
import time
import datetime
import ast
from firebase_admin import db
from firebase_admin import credentials
#from firebase import firebase

def State():
    print("Aqui")

# iniciando configuração do Firebase
# Deve ser feito o download do arquivo .json do realtime database do firebase e renomeie para adminsdk.json
cred = credentials.Certificate(
    "adminsdk.json")

default_app = firebase_admin.initialize_app(cred,
                                            {'databaseURL': 'YOUR_DATABASEURL/'
                                             })

# Iniciando conexao serial
arduino = serial.Serial('COM5', 9600)

# firebase_admin.db.reference('stand/State/').listen(State())
# acrescenta /Linha  na raíz
#root.child('Stand').on('child_changed', snapshot())

timeAnterior = time.time()
while(True):
    #time.sleep(0.200) #adiciona-se um timer para sincronizar a conexão
    
    root = db.reference('/stand')
    
    print('entrou')
    # recebe dados do arduino como bytes/string
    data_str = arduino.readline()[:]
    data = data_str.split()  # transforma a string data_str pra lista
    first = True
    if(first):
        first = False
    if (data[0].decode('utf-8') == "entrei" ):
        root.child('flow').set({"flow": data[1].decode('utf-8')})
        root.child('SetPoint').set({"SetPoint": data[2].decode('utf-8')})
        root.child('rotation').set({"rotation": data[3].decode('utf-8')})
        root.child('opening').set({"opening": data[4].decode('utf-8')})

