import requests
import re

def is_latin(text: str):
    return re.fullmatch(r"[A-Za-z ]+", text) is not None

def get_valid_name():
    while True:
        r = requests.get("https://randomuser.me/api/?nat=en")
        data = r.json()

        if 'results' not in data or len(data['results']) == 0:
            continue
        u = data['results'][0]
        name = f"{u['name']['last']} {u['name']['first']}"
        if is_latin(name) and len(name) <= 16:
            return name

print(get_valid_name())

