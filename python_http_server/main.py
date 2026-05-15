from fastapi import FastAPI
from pydantic import BaseModel
from datetime import datetime

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
        with open("./weather_data.csv", 'a') as file:
            date = datetime.now().isoformat()
            humidity = round(weather.humidity, 2)
            temperature = round(weather.temperature, 2)
            file.write(f"{date},{humidity},{temperature}\n")
        return {
            "message": "weather stored successfully",
            "date": date,
            "humidity":humidity,
            "temperature":temperature
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

