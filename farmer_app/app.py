from flask import Flask, render_template, request, redirect, url_for
import sqlite3
import os

# ----- CONFIG -----
from config import Config

# ----- LOGIC / SERVICES -----
from utils.irrigation_logic import irrigation_decision
from models.disease_model import predict_disease
from services.sync_service import sync_to_server

# ================================
# APP INITIALIZATION
# ================================

app = Flask(__name__)
app.config.from_object(Config)

DB_PATH = app.config["DATABASE_PATH"]

# ================================
# DATABASE INITIALIZATION
# ================================
def init_db():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()

    cursor.execute(
        "CREATE TABLE IF NOT EXISTS farmer_data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "soil_moisture REAL NOT NULL, "
        "temperature REAL NOT NULL, "
        "irrigation_status TEXT NOT NULL, "
        "disease_status TEXT NOT NULL, "
        "synced INTEGER DEFAULT 0, "
        "created_at TEXT DEFAULT CURRENT_TIMESTAMP"
        ")"
    )

    conn.commit()
    conn.close()


# create db on startup
init_db()


# ================================
# ROUTES
# ================================

# HOME / LANDING PAGE
@app.route("/")
def index():
    return render_template("index.html")


# ANALYZE IRRIGATION
@app.route("/analyze", methods=["POST"])
def analyze():
    soil_moisture = float(request.form["soil_moisture"])
    temperature = float(request.form["temperature"])

    irrigation_status = irrigation_decision(soil_moisture, temperature)
    disease_status = "Not Checked"

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()

    cursor.execute("""
        INSERT INTO farmer_data
        (soil_moisture, temperature, irrigation_status, disease_status, synced)
        VALUES (?, ?, ?, ?, 0)
    """, (soil_moisture, temperature, irrigation_status, disease_status))

    conn.commit()
    conn.close()

    return render_template(
        "dashboard.html",
        soil_moisture=soil_moisture,
        temperature=temperature,
        irrigation=irrigation_status,
        disease=disease_status
    )


# DISEASE DETECTION
@app.route("/upload", methods=["GET", "POST"])
def upload():
    result = None

    if request.method == "POST":
        if "leaf" in request.files:
            image = request.files["leaf"]
            result = predict_disease(image)

    return render_template("upload.html", result=result)


# OFFLINE → ONLINE SYNC (OPTIONAL DEMO)
@app.route("/sync")
def sync():
    if not Config.SYNC_ENABLED:
        return "Sync disabled"

    response = sync_to_server(Config.SYNC_SERVER_URL)
    return response


# ================================
# APP START
# ================================
if __name__ == "__main__":
    app.run(debug=Config.DEBUG)
