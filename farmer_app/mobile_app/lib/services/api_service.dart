import 'dart:convert';
import 'dart:io';
import 'package:http/http.dart' as http;
import 'package:hive/hive.dart';

class ApiService {
  static const String baseUrl =
      "http://10.0.2.2:8000"; // Emulator local address

  static Future<Map<String, dynamic>> predictDisease(File imageFile) async {
    try {
      final request =
          http.MultipartRequest('POST', Uri.parse("$baseUrl/disease/predict"));
      request.files
          .add(await http.MultipartFile.fromPath('file', imageFile.path));

      final streamsResponse = await request.send();
      final response = await http.Response.fromStream(streamsResponse);

      if (response.statusCode == 200) {
        final data = json.decode(response.body);
        // Cache result
        final box = await Hive.openBox('api_cache');
        await box.put('last_disease_result', data);
        return data;
      } else {
        throw Exception("Server Error");
      }
    } catch (e) {
      // Return cached data if available
      final box = await Hive.openBox('api_cache');
      final cached = box.get('last_disease_result');
      if (cached != null) {
        return Map<String, dynamic>.from(cached)..['isOffline'] = true;
      }
      throw Exception("Connection failed and no cached data available.");
    }
  }

  static Future<String> chatWithAssistant(String message) async {
    try {
      final response = await http.post(
        Uri.parse("$baseUrl/chat/"),
        headers: {"Content-Type": "application/json"},
        body: json.encode({"message": message}),
      );

      if (response.statusCode == 200) {
        final data = json.decode(response.body);
        return data['reply'];
      } else {
        throw Exception("Server Error");
      }
    } catch (e) {
      // Offline fallback
      if (message.toLowerCase().contains("water")) {
        return "Offline: It's best to water early or late to save moisture.";
      }
      return "Offline: I'm having trouble connecting to the server. Please check your internet.";
    }
  }

  static Future<Map<String, dynamic>> getIrrigationRecommendation() async {
    try {
      final response = await http.get(Uri.parse("$baseUrl/irrigation/"));
      if (response.statusCode == 200) {
        return json.decode(response.body);
      }
      throw Exception("Server error");
    } catch (e) {
      return {
        "status": "Offline: Check soil manually",
        "soil_moisture": 0.0,
        "temperature": 0.0
      };
    }
  }
}
