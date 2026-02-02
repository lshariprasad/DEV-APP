import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'dashboard_controller.dart';
import '../../screens/login_screen.dart';
import '../../screens/disease_scan_screen.dart';
import '../../screens/krishi_assistant_screen.dart';
import '../../services/api_service.dart';

class SmartFarmingDashboard extends ConsumerStatefulWidget {
  const SmartFarmingDashboard({super.key});

  @override
  ConsumerState<SmartFarmingDashboard> createState() =>
      _SmartFarmingDashboardState();
}

class _SmartFarmingDashboardState extends ConsumerState<SmartFarmingDashboard> {
  Map<String, dynamic>? _irrigationStatus;

  @override
  void initState() {
    super.initState();
    _loadIrrigationData();
  }

  Future<void> _loadIrrigationData() async {
    try {
      final recommendation = await ApiService.getIrrigationRecommendation();
      if (mounted) {
        setState(() {
          _irrigationStatus = recommendation;
        });
      }
    } catch (e) {
      // Silently fail or show cached
    }
  }

  @override
  Widget build(BuildContext context) {
    final weatherAsync = ref.watch(weatherProvider);
    final theme = Theme.of(context);

    return Scaffold(
      backgroundColor: theme.colorScheme.surface,
      body: SafeArea(
        child: CustomScrollView(
          physics: const BouncingScrollPhysics(),
          slivers: [
            // Welcome Header
            SliverToBoxAdapter(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(20, 24, 20, 20),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            Text(
                              "Welcome, Farmer 👨‍🌾",
                              style: GoogleFonts.outfit(
                                fontSize: 28,
                                fontWeight: FontWeight.bold,
                                color: theme.colorScheme.onSurface,
                              ),
                            ),
                            const SizedBox(height: 4),
                            Text(
                              "Let's check your farm's health today",
                              style: GoogleFonts.outfit(
                                fontSize: 16,
                                color: theme.colorScheme.onSurfaceVariant,
                              ),
                            ),
                          ],
                        ),
                        IconButton(
                          icon: Icon(Icons.logout_rounded,
                              color: theme.colorScheme.error),
                          onPressed: () {
                            Navigator.pushReplacement(
                              context,
                              MaterialPageRoute(
                                  builder: (context) => const LoginScreen()),
                            );
                          },
                        ),
                        const SizedBox(width: 8),
                        CircleAvatar(
                          radius: 20,
                          backgroundColor: theme.colorScheme.primaryContainer,
                          child: Icon(Icons.person,
                              size: 20,
                              color: theme.colorScheme.onPrimaryContainer),
                        ),
                      ],
                    ),
                    const SizedBox(height: 24),

                    // Weather & Soil Status Card
                    weatherAsync.when(
                      data: (weather) =>
                          _buildWeatherStatusCard(context, weather),
                      loading: () =>
                          const Center(child: CircularProgressIndicator()),
                      error: (e, _) => _buildWeatherStatusCard(
                          context, null), // Show fallback
                    ),
                  ],
                ),
              ),
            ),

            // Feature Grid Section Header
            SliverToBoxAdapter(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(20, 8, 20, 12),
                child: Row(
                  children: [
                    Text(
                      "Smart Tools",
                      style: GoogleFonts.outfit(
                        fontSize: 22,
                        fontWeight: FontWeight.bold,
                        color: theme.colorScheme.onSurface,
                      ),
                    ),
                    const Spacer(),
                    TextButton(
                        onPressed: () {},
                        child: Text("View All",
                            style: GoogleFonts.outfit(
                                color: theme.colorScheme.primary))),
                  ],
                ),
              ),
            ),

            // Feature Cards Grid
            SliverPadding(
              padding: const EdgeInsets.symmetric(horizontal: 20),
              sliver: SliverGrid(
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                  crossAxisCount: 2,
                  mainAxisSpacing: 20,
                  crossAxisSpacing: 20,
                  childAspectRatio: 0.9,
                ),
                delegate: SliverChildListDelegate([
                  _FeatureCard(
                    title: "Smart Irrigation",
                    subtitle: _irrigationStatus != null
                        ? _irrigationStatus!['status']
                        : "Check soil levels",
                    icon: Icons.water_drop_rounded,
                    color: const Color(0xFF2196F3),
                    onTap: () async {
                      await _loadIrrigationData();
                      if (mounted) {
                        showModalBottomSheet(
                          context: context,
                          shape: const RoundedRectangleBorder(
                            borderRadius:
                                BorderRadius.vertical(top: Radius.circular(25)),
                          ),
                          builder: (context) => Container(
                            padding: const EdgeInsets.all(24),
                            child: Column(
                              mainAxisSize: MainAxisSize.min,
                              children: [
                                Text("Irrigation Report",
                                    style: GoogleFonts.outfit(
                                        fontSize: 20,
                                        fontWeight: FontWeight.bold)),
                                const SizedBox(height: 20),
                                ListTile(
                                  leading: const Icon(Icons.info_outline,
                                      color: Colors.blue),
                                  title: const Text("Status"),
                                  trailing: Text(
                                      _irrigationStatus?['status'] ??
                                          "Checking...",
                                      style: const TextStyle(
                                          fontWeight: FontWeight.bold)),
                                ),
                                ListTile(
                                  leading: const Icon(Icons.opacity,
                                      color: Colors.blue),
                                  title: const Text("Soil Moisture"),
                                  trailing: Text(
                                      "${_irrigationStatus?['soil_moisture'] ?? '--'}%"),
                                ),
                                const SizedBox(height: 20),
                                ElevatedButton(
                                  style: ElevatedButton.styleFrom(
                                    minimumSize:
                                        const Size(double.infinity, 50),
                                    shape: RoundedRectangleBorder(
                                        borderRadius:
                                            BorderRadius.circular(15)),
                                  ),
                                  onPressed: () => Navigator.pop(context),
                                  child: const Text("Done"),
                                )
                              ],
                            ),
                          ),
                        );
                      }
                    },
                  ),
                  _FeatureCard(
                    title: "Disease Scan",
                    subtitle: "AI Health Check",
                    icon: Icons.center_focus_strong_rounded,
                    color: const Color(0xFF4CAF50),
                    onTap: () {
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) => const DiseaseScanScreen()));
                    },
                  ),
                  _FeatureCard(
                    title: "Krishi Assistant",
                    subtitle: "24/7 Expert Help",
                    icon: Icons.chat_bubble_rounded,
                    color: const Color(0xFF9C27B0),
                    onTap: () {
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) =>
                                  const KrishiAssistantScreen()));
                    },
                  ),
                  _FeatureCard(
                    title: "Market Prices",
                    subtitle: "Real-time rates",
                    icon: Icons.trending_up_rounded,
                    color: const Color(0xFFFF9800),
                    onTap: () {
                      ScaffoldMessenger.of(context).showSnackBar(
                        const SnackBar(
                            content:
                                Text("Market data available in full version")),
                      );
                    },
                  ),
                ]),
              ),
            ),

            // Bottom Tip Card
            SliverToBoxAdapter(
              child: Padding(
                padding: const EdgeInsets.all(20),
                child: Container(
                  padding: const EdgeInsets.all(16),
                  decoration: BoxDecoration(
                    color:
                        theme.colorScheme.secondaryContainer.withOpacity(0.5),
                    borderRadius: BorderRadius.circular(20),
                    border:
                        Border.all(color: theme.colorScheme.secondaryContainer),
                  ),
                  child: Row(
                    children: [
                      Icon(Icons.lightbulb_outline,
                          color: theme.colorScheme.onSecondaryContainer),
                      const SizedBox(width: 12),
                      Expanded(
                        child: Text(
                          "Tip: Early irrigation can increase yield by up to 20% this season.",
                          style: GoogleFonts.outfit(
                            fontSize: 14,
                            color: theme.colorScheme.onSecondaryContainer,
                          ),
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildWeatherStatusCard(BuildContext context, dynamic weather) {
    final theme = Theme.of(context);
    return Container(
      padding: const EdgeInsets.all(20),
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: [
            theme.colorScheme.primary,
            theme.colorScheme.primary.withBlue(150),
          ],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
        borderRadius: BorderRadius.circular(24),
        boxShadow: [
          BoxShadow(
            color: theme.colorScheme.primary.withOpacity(0.3),
            blurRadius: 15,
            offset: const Offset(0, 8),
          ),
        ],
      ),
      child: Column(
        children: [
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    weather != null
                        ? "${weather.temperature.toStringAsFixed(1)}°C"
                        : "28°C",
                    style: GoogleFonts.outfit(
                      fontSize: 42,
                      fontWeight: FontWeight.bold,
                      color: Colors.white,
                    ),
                  ),
                  Text(
                    weather != null ? weather.condition : "Sunny",
                    style: GoogleFonts.outfit(
                      fontSize: 18,
                      color: Colors.white.withOpacity(0.9),
                    ),
                  ),
                ],
              ),
              const Icon(
                Icons.wb_sunny_rounded,
                size: 64,
                color: Colors.orangeAccent,
              ),
            ],
          ),
          const SizedBox(height: 20),
          const Divider(color: Colors.white24),
          const SizedBox(height: 12),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              _buildStatusItem(
                Icons.opacity,
                "Soil Moisture",
                weather != null ? "${weather.moisture}%" : "42%",
              ),
              _buildStatusItem(
                Icons.thermostat,
                "Humidity",
                "65%",
              ),
              _buildStatusItem(
                Icons.air,
                "Wind",
                "12 km/h",
              ),
            ],
          ),
        ],
      ),
    );
  }

  Widget _buildStatusItem(IconData icon, String label, String value) {
    return Column(
      children: [
        Icon(icon, color: Colors.white70, size: 20),
        const SizedBox(height: 4),
        Text(
          value,
          style: GoogleFonts.outfit(
            fontSize: 16,
            fontWeight: FontWeight.bold,
            color: Colors.white,
          ),
        ),
        Text(
          label,
          style: GoogleFonts.outfit(
            fontSize: 12,
            color: Colors.white60,
          ),
        ),
      ],
    );
  }
}

class _FeatureCard extends StatelessWidget {
  final String title;
  final String subtitle;
  final IconData icon;
  final Color color;
  final VoidCallback onTap;

  const _FeatureCard({
    required this.title,
    required this.subtitle,
    required this.icon,
    required this.color,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Material(
      color: Colors.transparent,
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(24),
        child: Container(
          padding: const EdgeInsets.all(16),
          decoration: BoxDecoration(
            color: color.withOpacity(0.1),
            borderRadius: BorderRadius.circular(24),
            border: Border.all(color: color.withOpacity(0.2), width: 1.5),
          ),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Container(
                padding: const EdgeInsets.all(12),
                decoration: BoxDecoration(
                  color: color,
                  borderRadius: BorderRadius.circular(16),
                  boxShadow: [
                    BoxShadow(
                      color: color.withOpacity(0.4),
                      blurRadius: 8,
                      offset: const Offset(0, 4),
                    ),
                  ],
                ),
                child: Icon(icon, color: Colors.white, size: 28),
              ),
              const Spacer(),
              Text(
                title,
                style: GoogleFonts.outfit(
                  fontSize: 16,
                  fontWeight: FontWeight.bold,
                  color: theme.colorScheme.onSurface,
                ),
              ),
              const SizedBox(height: 4),
              Text(
                subtitle,
                style: GoogleFonts.outfit(
                  fontSize: 12,
                  color: theme.colorScheme.onSurfaceVariant,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
