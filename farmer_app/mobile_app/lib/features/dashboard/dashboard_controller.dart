import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../../models/weather_data.dart';
import '../../services/offline_service.dart';

// Service Provider
final offlineServiceProvider = Provider((ref) => OfflineService());

// State Provider
final weatherProvider = StateNotifierProvider<WeatherNotifier, AsyncValue<WeatherData>>((ref) {
  return WeatherNotifier(ref.read(offlineServiceProvider));
});

class WeatherNotifier extends StateNotifier<AsyncValue<WeatherData>> {
  final OfflineService _offlineService;

  WeatherNotifier(this._offlineService) : super(const AsyncValue.loading()) {
    loadWeatherData();
  }

  Future<void> loadWeatherData() async {
    try {
      // 1. Try to fetch from API (Simulated failure for now)
      // await api.fetchWeather()...
      throw Exception("Offline Mode test");
      
    } catch (e) {
      // 2. Fallback to offline cache
      final cached = await _offlineService.getLastWeather();
      if (cached != null) {
        state = AsyncValue.data(cached);
      } else {
        // Default data if first run
        state = AsyncValue.data(WeatherData(
          temperature: 28.5, 
          moisture: 42.0, 
          condition: "Sunny", 
          timestamp: DateTime.now()
        ));
      }
    }
  }

  Future<void> refresh() async {
    state = const AsyncValue.loading();
    await loadWeatherData();
  }
}
