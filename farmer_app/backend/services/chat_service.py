def get_farming_advice(question: str) -> str:
    """
    Simple rule-based chat assistant for farming advice.
    """
    q = question.lower()
    if "water" in q or "irrigation" in q:
        return "It's best to water your crops early in the morning or late in the evening to reduce evaporation."
    elif "pest" in q or "insect" in q:
        return "Try using organic neem oil spray for common pests. If it persists, consult a local expert."
    elif "fertilizer" in q:
        return "Use NPK fertilizers in the ratio recommended for your specific crop. Organic compost is also great!"
    elif "weather" in q:
        return "Always check the local forecast before planning your harvest or irrigation."
    else:
        return "That's an interesting question! For specific advice, please contact the local Krishi Kendra."
