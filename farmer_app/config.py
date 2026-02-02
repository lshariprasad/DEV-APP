import os

class Config:
    # ===== BASIC APP CONFIG =====
    SECRET_KEY = os.environ.get("SECRET_KEY", "smart-farming-secret-key")

    # ===== DATABASE CONFIG =====
    BASE_DIR = os.path.abspath(os.path.dirname(__file__))
    DATABASE_PATH = os.path.join(BASE_DIR, "database.db")

    # ===== FLASK SETTINGS =====
    DEBUG = True

    # ===== FILE UPLOAD CONFIG =====
    UPLOAD_FOLDER = os.path.join(BASE_DIR, "uploads")
    ALLOWED_EXTENSIONS = {"png", "jpg", "jpeg"}

    # ===== OFFLINE / SYNC CONFIG =====
    SYNC_ENABLED = True
    SYNC_SERVER_URL = os.environ.get(
        "SYNC_SERVER_URL",
        "https://example.com/api/sync"
    )
