from fastapi import APIRouter
from pydantic import BaseModel
from services.chat_service import get_farming_advice

router = APIRouter(prefix="/chat", tags=["Chat"])

class ChatRequest(BaseModel):
    message: str

class ChatResponse(BaseModel):
    reply: str

@router.post("/", response_model=ChatResponse)
async def chat_with_assistant(data: ChatRequest):
    reply = get_farming_advice(data.message)
    return ChatResponse(reply=reply)
