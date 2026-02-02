# Smart Farming Mobile App - Setup Guide

## 1. Prerequisites

- Flutter SDK installed and in PATH.
- Android Emulator or Physical Device connected.

## 2. Setup Steps

Open a terminal in the `mobile_app` folder:

```bash
# Get dependencies
flutter pub get

# Generate Hive Adapters (Vital for Offline Data)
dart run build_runner build --delete-conflicting-outputs
```

## 3. Running the App

```bash
flutter run
```

## 4. Troubleshooting

- **Firebase Error**: If you haven't set up `google-services.json`, the app might warn on startup. Keep the dummy initialization in `main.dart` for now.
- **Assets Error**: If `disease_model.tflite` is missing, ensure you ran the setup or the file exists in `assets/models/`.
