def predict_disease(image_bytes: bytes) -> str:
    """
    Prototype disease detection logic.
    Ported from original models/disease_model.py
    In a real app, this would load a ML model and process the image bytes.
    """
    # Simulate processing
    if image_bytes:
        # check size or some property to vary output? 
        # For prototype, we stick to original logic: "if image exists => disease detected (prototype)"
        return "Possible Disease Detected (Prototype)"
    else:
        return "Healthy Crop"
