import firebase_admin
from firebase_admin import credentials, firestore
import os

# Initialize Firebase Admin
# Expects a service account JSON file path in environment variable or local file
cred_path = os.getenv("FIREBASE_CREDENTIALS", "serviceAccountKey.json")

if os.path.exists(cred_path):
    cred = credentials.Certificate(cred_path)
    firebase_admin.initialize_app(cred)
    db = firestore.client()
    print("Firebase Admin Initialized")
else:
    print(f"Warning: Firebase credentials not found at {cred_path}. Firestore features will be disabled.")
    db = None

def get_firestore_db():
    return db
