from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

with open("./key", 'r') as file:
    KEY = file.read()

class Weather(BaseModel):
    key: str
    temperature: float
    humidity: float

@app.post('/')
async def handle_post_request(weather: Weather):
    print(f"your key: {weather.key.strip()}")
    print(f"expected key: {KEY.strip()}")
    if weather.key.strip() == KEY.strip():
        return {
            "message": "weather stored successfully"
        }
    else:
        return {
            "message": "incorrect API key"
        }

@app.get('/')
async def handle_get_request():
    return {
        "message": "what's going on!"
    }

