import 'dart:io';
import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:image_picker/image_picker.dart';
import '../services/api_service.dart';

class DiseaseScanScreen extends StatefulWidget {
  const DiseaseScanScreen({super.key});

  @override
  State<DiseaseScanScreen> createState() => _DiseaseScanScreenState();
}

class _DiseaseScanScreenState extends State<DiseaseScanScreen> {
  File? _image;
  bool _isAnalyzing = false;
  Map<String, dynamic>? _result;
  final _picker = ImagePicker();

  Future<void> _pickImage(ImageSource source) async {
    final pickedFile = await _picker.pickImage(source: source);
    if (pickedFile != null) {
      setState(() {
        _image = File(pickedFile.path);
        _result = null;
      });
    }
  }

  Future<void> _analyzeCrop() async {
    if (_image == null) return;

    setState(() {
      _isAnalyzing = true;
      _result = null;
    });

    try {
      final result = await ApiService.predictDisease(_image!);
      setState(() {
        _result = result;
      });
    } catch (e) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text(e.toString())),
      );
    } finally {
      setState(() {
        _isAnalyzing = false;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Scaffold(
      appBar: AppBar(
        title: Text("Disease Scan",
            style: GoogleFonts.outfit(fontWeight: FontWeight.bold)),
        backgroundColor: Colors.transparent,
        elevation: 0,
      ),
      body: SingleChildScrollView(
        padding: const EdgeInsets.all(20),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            // Image Preview
            Container(
              height: 300,
              decoration: BoxDecoration(
                color: theme.colorScheme.surfaceVariant,
                borderRadius: BorderRadius.circular(24),
                border: Border.all(color: theme.colorScheme.outlineVariant),
              ),
              child: _image != null
                  ? ClipRRect(
                      borderRadius: BorderRadius.circular(24),
                      child: Image.file(_image!, fit: BoxFit.cover),
                    )
                  : Center(
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Icon(Icons.image_search_rounded,
                              size: 64,
                              color:
                                  theme.colorScheme.primary.withOpacity(0.5)),
                          const SizedBox(height: 12),
                          Text("No leaf image selected",
                              style: GoogleFonts.outfit(
                                  color: theme.colorScheme.onSurfaceVariant)),
                        ],
                      ),
                    ),
            ),
            const SizedBox(height: 24),

            // Camera & Gallery Buttons
            Row(
              children: [
                Expanded(
                  child: ElevatedButton.icon(
                    onPressed: () => _pickImage(ImageSource.camera),
                    icon: const Icon(Icons.camera_alt_rounded),
                    label: const Text("Camera"),
                    style: ElevatedButton.styleFrom(
                      padding: const EdgeInsets.symmetric(vertical: 12),
                      shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(16)),
                    ),
                  ),
                ),
                const SizedBox(width: 16),
                Expanded(
                  child: ElevatedButton.icon(
                    onPressed: () => _pickImage(ImageSource.gallery),
                    icon: const Icon(Icons.photo_library_rounded),
                    label: const Text("Gallery"),
                    style: ElevatedButton.styleFrom(
                      padding: const EdgeInsets.symmetric(vertical: 12),
                      shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(16)),
                    ),
                  ),
                ),
              ],
            ),
            const SizedBox(height: 24),

            // Analyze Button
            ElevatedButton(
              onPressed: (_image == null || _isAnalyzing) ? null : _analyzeCrop,
              style: ElevatedButton.styleFrom(
                backgroundColor: theme.colorScheme.primary,
                foregroundColor: theme.colorScheme.onPrimary,
                padding: const EdgeInsets.symmetric(vertical: 16),
                shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(16)),
              ),
              child: _isAnalyzing
                  ? const CircularProgressIndicator(color: Colors.white)
                  : Text("Analyze Crop Health",
                      style: GoogleFonts.outfit(
                          fontSize: 18, fontWeight: FontWeight.bold)),
            ),

            if (_result != null) ...[
              const SizedBox(height: 32),
              _buildResultCard(theme),
            ],
          ],
        ),
      ),
    );
  }

  Widget _buildResultCard(ThemeData theme) {
    final isOffline = _result?['isOffline'] ?? false;
    return Container(
      padding: const EdgeInsets.all(20),
      decoration: BoxDecoration(
        color: theme.colorScheme.primaryContainer,
        borderRadius: BorderRadius.circular(24),
        border: Border.all(color: theme.colorScheme.primary.withOpacity(0.2)),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Text(
                "Analysis Result",
                style: GoogleFonts.outfit(
                    fontSize: 20,
                    fontWeight: FontWeight.bold,
                    color: theme.colorScheme.onPrimaryContainer),
              ),
              if (isOffline)
                const Chip(
                    label: Text("Cached Data"),
                    backgroundColor: Colors.orangeAccent),
            ],
          ),
          const SizedBox(height: 16),
          _resultRow("Disease:", _result!['disease'], theme),
          _resultRow("Confidence:", _result!['confidence'], theme),
          const Divider(height: 32),
          Text(
            "Solution:",
            style: GoogleFonts.outfit(
                fontWeight: FontWeight.bold,
                color: theme.colorScheme.onPrimaryContainer),
          ),
          const SizedBox(height: 4),
          Text(
            _result!['solution'],
            style: GoogleFonts.outfit(
                fontSize: 16, color: theme.colorScheme.onPrimaryContainer),
          ),
        ],
      ),
    );
  }

  Widget _resultRow(String label, String value, ThemeData theme) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 4),
      child: Row(
        children: [
          Text("$label ",
              style: GoogleFonts.outfit(
                  fontWeight: FontWeight.w500,
                  color: theme.colorScheme.onPrimaryContainer)),
          Text(value,
              style: GoogleFonts.outfit(
                  fontWeight: FontWeight.bold,
                  color: theme.colorScheme.primary)),
        ],
      ),
    );
  }
}
