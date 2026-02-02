"""
Script to simulate training a disease detection model and converting it to TFLite.
In a real hackathon, this would load a pre-trained MobileNetV2 and fine-tune it.
"""

import tensorflow as tf
import os

def create_and_convert_model(output_dir="."):
    print("Creating prototype model...")
    # diverse dummy model
    model = tf.keras.Sequential([
        tf.keras.layers.Input(shape=(224, 224, 3)),
        tf.keras.layers.Conv2D(16, 3, padding='same', activation='relu'),
        tf.keras.layers.GlobalAveragePooling2D(),
        tf.keras.layers.Dense(2, activation='softmax') # Healthy vs Disease
    ])
    
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    
    # Save generic model
    model_path = os.path.join(output_dir, "disease_model.h5")
    model.save(model_path)
    print(f"Saved Keras model to {model_path}")
    
    # Convert to TFLite
    print("Converting to TFLite...")
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    tflite_model = converter.convert()
    
    tflite_path = os.path.join(output_dir, "disease_model.tflite")
    with open(tflite_path, "wb") as f:
        f.write(tflite_model)
    
    print(f"Saved TFLite model to {tflite_path}")

if __name__ == "__main__":
    create_and_convert_model(output_dir="backend/ml")
