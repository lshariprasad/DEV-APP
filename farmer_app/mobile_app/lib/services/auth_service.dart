import 'package:flutter/material.dart';

class AuthService {
  // Simple mock login for prototype
  static Future<bool> login(String email, String password) async {
    await Future.delayed(const Duration(seconds: 1)); // Simulate network delay
    if (email.isNotEmpty && password.length >= 6) {
      return true;
    }
    return false;
  }
}
