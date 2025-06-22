import requests

response = requests.get("https://randomuser.me/api/?nat=ru")
data = response.json()

user = data['results'][0]
first = user['name']['first']
last = user['name']['last']
full_name = f"{last} {first}"

print(full_name)

