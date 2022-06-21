from flask import Flask, request, jsonify
from flask_restful import Resource, Api
import paho.mqtt.client as mqtt
import time
import threading

app = Flask(__name__)
api = Api(app)

events = []
 
class GetAllEvents(Resource):
    def get(self):
        return events

class GetSomeEvents(Resource):
    def get(self, cnt):
        return events[0:cnt]
#    def get(self, count):
#        return jsonify(events[0:count])
#
#    def get(self, start, end):
#        return jsonify(events[start:end])


def on_message(client, userdata, message):
    try:
        events.insert(0, eval(str(message.payload.decode('utf-8'))))
        print(events)
    except:
        print("malformed json received");

def on_log(client, userdata, level, buf):
    print('log: ',buf)

if __name__ == '__main__':
    api.add_resource(GetAllEvents, '/events')
    api.add_resource(GetSomeEvents, '/events/<int:cnt>')
#    api.add_resource(GetEvents, '/last/<int:to>')
#    api.add_resource(GetEvents, '/range/<int:from>:<int:to>')

    client = mqtt.Client('hub')
    client.connect('127.0.0.1')

    client.subscribe('HTL')
    client.on_message = on_message
    client.on_log = on_log

    threading.Thread(target=lambda: app.run(debug=True, use_reloader=False)).start()
    client.loop_forever() # loop starten in Endlosschleife (blockiert)
    print('EXIT')
