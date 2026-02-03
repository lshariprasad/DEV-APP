# Smart Farming Application 🌾

A comprehensive solution for farmers to manage irrigation, monitor crop health, and detect diseases using AI-powered insights. Designed specifically for low-connectivity rural areas.

## 🚀 Overview : 

This application addresses the critical needs of farmers by providing:

- **Smart Irrigation**: Precision watering recommendations based on sensor data.
- **Disease Detection**: AI-driven analysis of crop leaves via mobile camera.
- **Krishi Assistant**: A rule-based chatbot for immediate farming advice.
- **Offline-First Design**: Critical features work without an active internet connection using local caching.

## 🏗️ Architecture :

- **Frontend**: Flutter (Material 3) - Cross-platform mobile app.
- **Backend**: FastAPI (Python) - High-performance RESTful API.
- **Local Database**: Hive - Fast NoSQL storage for offline caching.
- **ML Logic**: Prototype logic for leaf disease analysis (easily swappable with TensorFlow Lite).

## 🛠️ Setup & Run Instructions


### 1. Backend (FastAPI)

The backend provides the intelligence for the application.

1. Navigate to the `backend` folder.
2. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Start the server:
   ```bash
   python main.py
   ```
   _The API will be available at `http://localhost:8000`._

### 2. Frontend (Flutter)

The mobile app connects to the computer's localhost via a special IP.

1. Navigate to the `mobile_app` folder.
2. Install dependencies:
   ```bash
   flutter pub get
   ```
3. Run on Android Emulator:
   ```bash
   flutter run
   ```
   _Note: The app is pre-configured to connect to `10.0.2.2:8000`, which is the standard bridge to your computer's localhost from an Android emulator._

## 📱 Key Screens

1. **Login Screen**: Simple email/password entry with a "Continue as Guest" option for accessibility.
2. **Dashboard**: Vibrant, high-contrast cards showing weather, soil moisture, and quick access to tools.
3. **Disease Scan**: Interactive camera/gallery interface for leaf analysis with detailed results and solutions.
4. **Krishi Assistant**: WhatsApp-style chat interface with real-time replies and offline fallbacks.

## 🖼️ Pictures :

<img width="165" height="597" alt="image" src="https://github.com/user-attachments/assets/1da46e66-3086-4532-9573-dd9a9f47c817" />

<img width="165" height="597" alt="image" src="https://github.com/user-attachments/assets/bf7c59a4-cc92-4ba9-827f-41474b504c55" />

<img width="165" height="597" alt="image" src="https://github.com/user-attachments/assets/ebddfdb9-1a3b-4211-b2a0-298f38c885ba" />

<img width="165" height="597" alt="image" src="https://github.com/user-attachments/assets/7338ba23-e193-4324-a46e-e208184b3ec1" />

<img width="165" height="597" alt="image" src="https://github.com/user-attachments/assets/0c30082c-037e-4e68-9689-133889e2dc76" />

<img width="165" height="597" alt="image" src="https://github.com/user-attachments/assets/d2490d8d-84d0-42b4-a248-fb1f2265f8b6" />

## 🔗 API Endpoints :

- `GET /`: Health check.
- `GET /irrigation/`: Get real-time irrigation recommendations.
- `POST /disease/predict`: Submit an image for disease analysis.
- `POST /chat/`: Send a message to the farming assistant.

## 💡 Technical Features :

- **Clean Code**: Follows modular architecture for easy maintenance.
- **Responsive UI**: Adapts to different screen sizes and orientations.
- **Graceful Error Handling**: Informative messages for connection issues.
- **Modern Aesthetics**: Uses Google Fonts (Outfit) and Material 3 design principles for a premium feel.

---

_Developed for College Submission & Demo purposes._
