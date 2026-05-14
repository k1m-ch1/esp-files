from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

class Weather(BaseModel):
    temperature: float
    humidity: float

@app.post('/')
async def handle_post_request(weather: Weather):
    return {
        "message": "weather stored successfully",
        "weather": weather
    }

@app.get('/')
async def handle_get_request():
    return {
        "message": "what's going on!"
    }

