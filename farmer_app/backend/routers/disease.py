from fastapi import APIRouter, UploadFile, File
from services.disease_service import predict_disease
from pydantic import BaseModel

router = APIRouter(prefix="/disease", tags=["Disease"])

class DiseaseResponse(BaseModel):
    disease: str
    confidence: str
    solution: str

@router.post("/predict", response_model=DiseaseResponse)
async def detect_disease(file: UploadFile = File(...)):
    if not file:
        return DiseaseResponse(
            disease="Unknown", 
            confidence="0%", 
            solution="Please upload an image."
        )
    
    # In a real app, we'd use the service to get these values
    # For this prototype, we'll return a mock structured response
    return DiseaseResponse(
        disease="Leaf Blight",
        confidence="92%",
        solution="Reduce watering and apply fungicide"
    )
