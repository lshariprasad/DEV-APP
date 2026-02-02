def irrigation_decision(soil_moisture, temperature):
    if soil_moisture < 30:
        return "Irrigation Required"
    elif soil_moisture < 50:
        return "Monitor Soil Moisture"
    else:
        return "No Irrigation Needed"
