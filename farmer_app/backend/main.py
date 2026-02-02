from fastapi import FastAPI
from routers import irrigation, disease, chat

app = FastAPI(
    title="Smart Farming API",
    description="Backend for Smart Farming Mobile App",
    version="1.0.0"
)

# Include Routers
app.include_router(irrigation.router)
app.include_router(disease.router)
app.include_router(chat.router)

@app.get("/")
def home():
    return {"message": "Smart Farming API is running"}

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
