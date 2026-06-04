from flask import Flask, render_template, jsonify, request
import threading
import time
import math
import random

app = Flask(__name__)

current_signal = 1
samples = []
t = 0

MAX_SAMPLES = 60

def acquisition_loop():
    global t, samples

    while True:

        if current_signal == 1:
            value = random.randint(0, 100)

        else:
            value = 50 + 50 * math.sin(t)

        samples.append(value)

        if len(samples) > MAX_SAMPLES:
            samples.pop(0)

        t += 0.2

        time.sleep(1)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/data")
def data():
    return jsonify({
        "signal": current_signal,
        "samples": samples
    })


@app.route("/signal", methods=["POST"])
def change_signal():

    global current_signal
    global samples

    signal = request.json["signal"]

    current_signal = signal
    samples = []

    return jsonify({"status": "ok"})


if __name__ == "__main__":

    acquisition_thread = threading.Thread(
        target=acquisition_loop,
        daemon=True
    )

    acquisition_thread.start()

    app.run(
        host="0.0.0.0",
        port=5000,
        debug=False
    )
