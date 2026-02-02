import 'package:hive_flutter/hive_flutter.dart';
import '../models/weather_data.dart';

class OfflineService {
  static const String _telemetryBox = 'telemetry_cache';
  static const String _settingsBox = 'settings';

  // --- Telemetry (Sync Queue) ---

  Future<void> cacheTelemetryData(Map<String, dynamic> data) async {
    final box = await Hive.openBox(_telemetryBox);
    await box.add(data);
    print("Offline: Telemetry cached. Count: ${box.length}");
  }

  Future<List<Map<dynamic, dynamic>>> getPendingTelemetry() async {
    final box = await Hive.openBox(_telemetryBox);
    return box.values.cast<Map<dynamic, dynamic>>().toList();
  }

  Future<void> clearPendingTelemetry() async {
    final box = await Hive.openBox(_telemetryBox);
    await box.clear();
  }

  // --- User Preferences / Cached State ---

  Future<void> saveLastWeather(WeatherData weather) async {
    final box = await Hive.openBox(_settingsBox);
    await box.put('last_weather', weather); // Requires TypeAdapter
  }

  Future<WeatherData?> getLastWeather() async {
    final box = await Hive.openBox(_settingsBox);
    return box.get('last_weather') as WeatherData?;
  }
}
