# Smart Farming Application

A prototype smart-farming project combining a Flutter mobile client with Python application services. The repository currently contains a Flask application, a FastAPI backend, local SQLite storage, and optional Firebase Admin integration.

## Repository components

| Path | Purpose |
|---|---|
| `app.py` | Flask web application entry point |
| `config.py` | Flask configuration and local SQLite path |
| `backend/main.py` | FastAPI application entry point |
| `backend/routers/` | Irrigation, disease and chat API routes |
| `backend/services/` | Backend service logic |
| `backend/requirements.txt` | Python backend dependencies |
| `mobile_app/` | Flutter mobile application |
| `database.db` | SQLite database file currently present in the repository |

## Prerequisites

- Python 3.10 or newer is recommended; use a version compatible with the installed packages.
- Flutter SDK and Dart for the mobile client.
- Android Studio or an Android device for running the Flutter app.
- Arduino IDE is not required for this application.

## FastAPI backend

From the project directory:

```bash
cd backend
python -m venv .venv
```

Activate the virtual environment, then install dependencies:

**Windows PowerShell**
```powershell
.venv\Scripts\Activate.ps1
pip install -r requirements.txt
python main.py
```

**macOS / Linux**
```bash
source .venv/bin/activate
pip install -r requirements.txt
python main.py
```

The FastAPI application starts on port 8000. Interactive API documentation is available at `http://127.0.0.1:8000/docs` while the server is running locally.

### Routes currently defined in the FastAPI source

| Method | Path | Current behavior |
|---|---|---|
| GET | `/` | Returns an API running message |
| GET | `/irrigation/` | Returns fixed demonstration values |
| POST | `/irrigation/analyze` | Calculates irrigation status from supplied soil moisture and temperature |
| POST | `/disease/predict` | Returns a fixed demonstration disease response |
| POST | `/chat/` | Passes a message to the local farming-advice service |

The disease endpoint currently returns a hard-coded example response (including a confidence string); it does not run a trained model in the inspected route. Treat it as a prototype placeholder, not an agricultural diagnosis. The irrigation GET endpoint also uses mock values; use the POST route to exercise the calculation service.

## Flask application

The separate Flask entry point is `app.py` at the `farmer_app/` root. It uses `config.py`, local SQLite storage and modules under the Flask app's own `utils/`, `models/` and `services/` folders.

Run it from the `farmer_app/` directory after installing its Flask dependencies (a dedicated requirements file for this Flask application is not currently documented):

```bash
python app.py
```

The current configuration has development settings. Do not deploy this Flask app publicly without setting a strong secret key, disabling debug mode, reviewing upload handling and securing the sync endpoint.

## Flutter mobile client

From the project directory:

```bash
cd mobile_app
flutter pub get
flutter run
```

Connect an Android emulator or a supported physical device. The Flutter package manifest includes dependencies for Riverpod, Hive, Firebase, maps, image picking and HTTP requests. Some dependencies and assets may require additional platform configuration; follow Flutter and package setup instructions.

The mobile README mentions Hive code generation. Run the generator only if the project source contains Hive adapters that require generation:

```bash
dart run build_runner build --delete-conflicting-outputs
```

## Firebase configuration

The FastAPI-side `backend/firebase_config.py` looks for a service-account JSON file using the `FIREBASE_CREDENTIALS` environment variable; if unset, it checks for `serviceAccountKey.json` in the working directory. Do not commit service-account JSON files or expose their contents. Firebase features are disabled when the file is absent.

## Security and data handling

- Never commit real Firebase service-account credentials, API keys, passwords or production secrets.
- The existing repository includes `database.db`. Review it for personal or sensitive records before sharing the repository; ignore rules do not remove already tracked files.
- Python bytecode and cache directories are generated artifacts and should not be committed.
- The Flask configuration currently contains a development secret fallback and has debug mode enabled. Set a secure environment-provided secret and disable debug before any deployment.
- The disease prediction route returns mock output. Do not use it to make crop-treatment decisions.
- The sync route and local API services need authentication, validation and deployment security review before public exposure.

## Current status

This is a development and demonstration repository. The documentation describes source-visible behavior and does not claim that all modules have been tested on real farms or deployed in production.

## Author

Hari Prasad L S — [GitHub profile](https://github.com/lshariprasad)
