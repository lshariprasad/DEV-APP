import 'package:hive/hive.dart';

part 'weather_data.g.dart';

@HiveType(typeId: 0)
class WeatherData extends HiveObject {
  @HiveField(0)
  final double temperature;

  @HiveField(1)
  final double moisture;

  @HiveField(2)
  final String condition;

  @HiveField(3)
  final DateTime timestamp;

  WeatherData({
    required this.temperature,
    required this.moisture,
    required this.condition,
    required this.timestamp,
  });
}
