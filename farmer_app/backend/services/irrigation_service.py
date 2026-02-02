def irrigation_decision(soil_moisture: float, temperature: float) -> str:
    """
    Determines if irrigation is needed based on soil moisture and temperature.
    Logic ported from original utils/irrigation_logic.py
    """
    if soil_moisture < 30:
        return "Irrigation Required"
    elif soil_moisture < 50:
        return "Monitor Soil Moisture"
    else:
        return "No Irrigation Needed"
