# DEV-APP — Embedded, Mobile & Smart Farming Projects

A collection of application-development and embedded-system projects by Hari Prasad L S.

## Project index

| Project | Location | Technology / focus |
|---|---|---|
| Smart Farming Application | `farmer_app/` | Flutter mobile client, Python Flask prototype, FastAPI backend, SQLite and optional Firebase integration |
| Go Kart multi-sensor monitoring | `Go Kart Projects/` | Arduino Mega 2560 and sensor modules, with individual sketches for DHT11, display, ADXL335, MLX90614, GPS and MQ-series sensors |

## Repository layout

```text
DEV-APP/
├── farmer_app/
│   ├── app.py                 # Flask application entry point
│   ├── config.py              # Flask application configuration
│   ├── backend/               # FastAPI service and routers
│   ├── mobile_app/            # Flutter mobile application
│   ├── database.db            # Existing SQLite database file
│   └── README.md              # Smart Farming project guide
├── Go Kart Projects/
│   ├── README.md
│   └── individual Arduino project folders and sketches
└── README.md
```

## Smart Farming Application

The project contains both a Flask application (`farmer_app/app.py`) and a FastAPI service (`farmer_app/backend/main.py`), plus a Flutter client under `farmer_app/mobile_app/`.

Start with the [Smart Farming project guide](farmer_app/README.md) for setup notes, service entry points and current prototype limitations.

## Go Kart multi-sensor monitoring

The [Go Kart project guide](Go%20Kart%20Projects/README.md) describes the Arduino Mega 2560 sensor-monitoring setup. The folder contains separate sketches for individual sensor modules. Review the relevant sketch and wiring notes before assembling hardware.

## General development tools

- Git and GitHub
- Flutter SDK and Dart for the mobile client
- Python 3 for the Flask and FastAPI code
- Arduino IDE for the embedded sketches
- MATLAB/Arduino libraries and platform dependencies as specified by each project

## Current repository notes

- Some generated Python cache files and an SQLite database are already tracked in the repository. Review the database contents before publishing or sharing it; it may contain local application data. The new ignore rules prevent future untracked runtime files from being added, but do not remove files already tracked by Git.
- The disease-prediction API currently returns a fixed demonstration response; do not interpret it as a validated machine-learning diagnosis.
- The irrigation GET route returns sample values. Use the POST analysis route for the rule-based calculation.
- The repository contains prototype and coursework material. Hardware and application behavior should be tested on the target devices before being described as production-ready.

## Author

Hari Prasad L S — [GitHub profile](https://github.com/lshariprasad)
