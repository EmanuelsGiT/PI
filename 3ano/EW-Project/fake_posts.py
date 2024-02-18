import json
from faker import Faker
import random

fake = Faker()

entries = []

# Read IDs from "inquiricoes.json" file
with open('src/data/inquiricoes.json', 'r') as file:
    inquiricoes_data = json.load(file)
    ids = [entry['_id'] for entry in inquiricoes_data]

for _ in range(100):
    entry = {
        "nome": fake.first_name(),
        "descricao": fake.sentence(),
        "data": fake.iso8601(),
        "registo": random.choice(ids),  # Select a random ID from the list of IDs
        "coments": []
    }

    for _ in range(random.randint(0, 5)):
        comment = {
            "username": fake.first_name(),
            "descricao": fake.sentence()
        }
        entry["coments"].append(comment)

    entries.append(entry)

json_data = json.dumps(entries, indent=2)

with open('src/data/posts.json', 'w') as file:
    file.write(json_data)

