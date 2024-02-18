import csv
import json
import re

# Code 1: CSV to JSON Conversion

data = []

csv_file = "PT-UM-ADB-DIO-MAB-006.CSV"
with open(csv_file, 'r', encoding='utf-8') as file:
    reader = csv.DictReader(file, delimiter=';')
    for row in reader:
        row['_id'] = row.pop('﻿ID')
        data.append(row)

print("CSV convertido para JSON com sucesso!")

# Code 2: Data Processing
def extract_name(unit_title):
    match = re.search(r'de genere de\s+(.+?)(?:,|$)', unit_title)
    if match:
        return match.group(1)
    else:
        return unit_title

def process_entry(entry, data):
    scope_content = entry.get("ScopeContent", "")
    match_filiacao = re.search(r'Filiação:\s(.*?)(?:\s+e|,\w)', scope_content)
    if match_filiacao:
        filiacao = match_filiacao.group(0)
        entry["Filiacao"] = []

        for entry_data in data:
            if "ScopeContent" in entry_data and filiacao in entry_data["ScopeContent"]:
                entry["Filiacao"].append({"Id": entry_data["_id"], "Title": extract_name(entry_data["UnitTitle"])})

    else:
        entry["Filiacao"] = []

    related_material = entry.get("RelatedMaterial", "")
    match_related_material = re.findall(r'Proc\.(\d+)', related_material)
    if match_related_material:
        for match in match_related_material:
            for entry_data in data:
                if "UnitId" in entry_data and entry_data["UnitId"].lstrip("0") == match:
                    entry["Filiacao"].append({"Id": entry_data["_id"], "Title": extract_name(entry_data["UnitTitle"])})
                    break

# Convert CSV to JSON
json_data = json.dumps(data, indent=4, ensure_ascii=False)

def process_json_file(json_data, output_file_path):
    json_data = json.loads(json_data)  # Convert JSON string back to Python object
    for entry in json_data:
        process_entry(entry, json_data)

    with open(output_file_path, "w", encoding="utf-8") as output_file:
        json.dump(json_data, output_file, indent=4, ensure_ascii=False)

    print(f"New data written to: {output_file_path}")

# Example usage
output_json_file = "src/data/inquiricoes.json"
process_json_file(json_data, output_json_file)
