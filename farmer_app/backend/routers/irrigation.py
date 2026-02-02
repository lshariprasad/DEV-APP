from fastapi import APIRouter
from pydantic import BaseModel
from services.irrigation_service import irrigation_decision

router = APIRouter(prefix="/irrigation", tags=["Irrigation"])

class IrrigationRequest(BaseModel):
    soil_moisture: float
    temperature: float

class IrrigationResponse(BaseModel):
    status: str
    soil_moisture: float
    temperature: float

@router.post("/analyze", response_model=IrrigationResponse)
async def analyze_irrigation(data: IrrigationRequest):
    status = irrigation_decision(data.soil_moisture, data.temperature)
    return IrrigationResponse(
        status=status,
        soil_moisture=data.soil_moisture,
        temperature=data.temperature
    )

@router.get("/", response_model=IrrigationResponse)
async def get_irrigation_status():
    # Mock data for demonstration
    return IrrigationResponse(
        status="No Irrigation Needed",
        soil_moisture=45.0,
        temperature=28.5
    )
