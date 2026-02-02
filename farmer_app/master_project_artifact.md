# Master Project Artifact: Smart Farming "Hackathon Winner" Suite

## 1. Project Overview

**Title**: Smart Farming Application for Irrigation Management and Crop Health Monitoring

**Problem Statement**:
Farmers face difficulties in deciding the right time for irrigation, identifying crop health issues, and detecting early-stage crop diseases, especially in rural areas with limited connectivity.

**Objective**:
To design and develop a smart farming application that helps farmers determine irrigation needs, monitor crop health, and predict crop diseases, functioning in both online and offline modes.

**Proposed Solution**:
A hybrid online–offline application that uses soil moisture and temperature data for irrigation recommendations and image-based disease detection, with local storage and server synchronization.

## 2. Technical Architecture

### A. Mobile App (Flutter)

- **Framework**: Flutter (Dart)
- **State Management**: Riverpod (for robust, scalable state)
- **Offline Storage**: Hive (NoSQL, faster than SQLite for cache)
- **Auth**: Firebase Auth (Phone OTP & Google Sign-In)
- **Maps**: Mapbox GL / Google Maps Flutter
- **ML Engine**: `tflite_flutter` for on-device inference.

### B. Backend (FastAPI + Firebase)

- **Framework**: FastAPI (Python 3.14 compatible)
- **Database**:
  - **Primary**: Firebase Firestore (NoSQL, real-time syncing)
  - **Analytics/Heavy Data**: BigQuery (future scope) or local SQLite for prototyping.
- **ML Services**:
  - **Training Pipeline**: Python script to convert `.h5` (Keras) -> `.tflite`.
  - **Edge Fallback**: API endpoint for deeper analysis if edge inference fails.

## 3. Directory Structure

```
root/
├── .vscode/               # Editor config
├── backend/               # FastAPI + ML Training
│   ├── main.py
│   ├── firebase_config.py # Firebase Admin SDK setup
│   ├── routers/           # API Endpoints
│   │   ├── advisory.py    # Chatbot/LLM logic
│   │   └── telemetry.py   # Sync endpoints
│   ├── ml/
│   │   ├── train_model.py # Script to update models
│   │   └── converter.py   # TF -> TFLite converter
│   └── requirements.txt
├── mobile_app/            # Flutter Project
│   ├── assets/
│   │   ├── models/        # .tflite files
│   │   └── images/
│   ├── lib/
│   │   ├── features/
│   │   │   ├── dashboard/ # Glassmorphic UI
│   │   │   ├── camera/    # Image Picker + TFLite logic
│   │   │   └── map/       # Disease Heatmap
│   │   ├── services/      # Firebase, LocalStorage
│   │   └── l10n/          # Arb files (15+ languages)
│   └── pubspec.yaml
└── README.md
```

## 4. Feature Strategy

### Phase 1: Smart Irrigation & Crop Health

- **Irrigation Logic**: Analyze soil moisture and climate data to provide real-time recommendations.
- **Disease Prediction**: Implement image processing for early detection of crop diseases.

### Phase 2: Offline Capabilities & Sync

- **Local Storage**: Use local database to store logs and predictions when offline.
- **Synchronization**: Automatically sync local data with the server once internet connectivity is restored.

### Phase 3: User-Friendly Interface

- **Mobile & Web**: Ensure the UI is responsive and accessible across both mobile and web platforms.
- **Accessibility**: Design for ease of use by farmers in rural regions.

## 5. API Endpoints (FastAPI)

| Method | Endpoint                     | Description                         |
| :----- | :--------------------------- | :---------------------------------- |
| POST   | `/api/v1/irrigation/analyze` | Submit soil data for recommendation |
| POST   | `/api/v1/disease/predict`    | Upload image for disease detection  |
| POST   | `/api/v1/sync`               | Synchronize offline stored data     |
| GET    | `/api/v1/health`             | Check system status                 |

## 6. Testing Strategy

- **Flutter**: Data-driven widget tests for all localization. Integration tests for the offline-sync flow.
- **Backend**: Pytest for all endpoints. 90%+ coverage target.
