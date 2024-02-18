import requests

endpoint = "http://localhost:8000/api/"

# Fetch CSRF token from the server by making a GET request to the login page
response = requests.get(endpoint)

# Check if the CSRF token is present in the cookies
csrf_token = response.cookies.get('csrftoken')

# Include CSRF token in the headers if available
headers = {'X-CSRFToken': csrf_token} if csrf_token else {}

# Make a POST request to create a new Prova instance
prova_data = {
    "version": 1,
    "reservation": "Test Reservation",
    "duration": 60,  # Provide a value for duration
    "max_score": 100,
    "exam_type": "EXAM",
    "description": "Test Prova",
    "subject": "Test Subject",
    "questions": [
        {
            "question_id": 1,
            "question_type": "MULTIPLE_CHOICE",
            "points": 10,
            "description": "Test Question",
            "answers": {"0": "Option A", "1": "Option B", "2": "Option C", "answer": "0"}
        }
    ]
}

prova_response = requests.post(
    f"{endpoint}provas/",
    json=prova_data,
    headers=headers
)

print("Prova creation response:")
print(prova_response.status_code)
print(prova_response.json())

# Make a POST request to create a new Question instance
question_data = {
    "question_id": 2,
    "question_type": "TRUE_FALSE",
    "points": 5,  
    "description": "Another Test Question",
    "answers": {"0": True, "1": False, "answer": "0"}
}

question_response = requests.post(
    f"{endpoint}questions/",
    json=question_data,
    headers=headers
)

print("\nQuestion creation response:")
print(question_response.status_code)
print(question_response.json())
