from flask import Flask
from flask import request
from flask import jsonify
from flask import render_template
from twilio.rest import Client
import time
import json

account_sid = 'ACf2e898319fb8558b7148e7e0f8042024'
auth_token = 'dec5bedb928a15ac4b9f54a985cd8e8d'
client = Client(account_sid, auth_token)

def send(mes):
    message = client.messages.create(body=mes,from_='+18782134738', to='+19254284295')
    message.sid


app = Flask(__name__)

@app.route("/data/",methods=["GET","POST"])
def hello():
    all = request.args.get("var")
    all = all.split(',')
    all = [float(i) for i in all]

    sick = dict()
    sick['soil'] = all[0]
    sick['temp'] = all[1]
    sick['hum'] = all[2]
    sick['light'] = all[3]
    sick['time'] = time.time()
    if (sick['soil']>80):
        send("Too wet. Stop watering.")
    if (sick['temp']<7):
        send("Too cold. Bring me somewhere warm")

    with open('.//templates//data.json', 'w') as file:
        json.dump(sick, file)    
    return sick

@app.route("/")
def index():
    return render_template('index.html')
@app.route("/data.json")
def bin():
    with open('.//templates//data.json', 'r') as file:
        data = json.load(file)
    return data


if __name__ == '__main__':
    app.run(debug=True)



