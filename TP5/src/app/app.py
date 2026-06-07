from flask import Flask, render_template, jsonify, request
import threading
import time

app = Flask(__name__)

DEVICE_PATH = "/dev/gpio_driver"

current_signal = 1
samples = []
MAX_SAMPLES = 400
sample_counter = 0

def acquisition_loop():
    global samples
    global sample_counter

    while True:
        try:
            with open(DEVICE_PATH, "r") as driver_file:
                raw_data = driver_file.read().strip()

                if raw_data:
                    value = int(raw_data)
                else:
                    value = 0

        except Exception as e:
            print(f"[ERROR] No se pudo leer desde {DEVICE_PATH}: {e}")
            value = 0

        samples.append(value)
        sample_counter += 1

        if len(samples) > MAX_SAMPLES:
            samples.pop(0)

        time.sleep(0.05)


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/data")
def data():
    return jsonify({
        "signal": current_signal,
        "samples": samples,
        "sample_counter": sample_counter
    })

@app.route("/signal", methods=["POST"])
def change_signal():
    global current_signal
    global samples
    global sample_counter

    signal = request.json["signal"]

    current_signal = signal
    samples = []
    sample_counter = 0

    try:
        with open(DEVICE_PATH, "w") as driver_file:
            driver_file.write(str(signal))

        print(f"[OK] Se informo al driver el cambio al Sensor {signal}")

    except Exception as e:
        print(f"[ERROR] No se pudo escribir en {DEVICE_PATH}: {e}")

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
