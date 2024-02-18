import requests

endpoint = "http://localhost:8000/api/"

# Fetch CSRF token from the server by making a GET request to the login page
response = requests.get(endpoint)

# Check if the CSRF token is present in the cookies
csrf_token = response.cookies.get('csrftoken')

# Include CSRF token in the headers if available
headers = {'X-CSRFToken': csrf_token} if csrf_token else {}

# Make a GET request to retrieve all Provas
prova_list_response = requests.get(
    f"{endpoint}provas/",
    headers=headers
)

print("Prova retrieval response:")
print(prova_list_response.status_code)
print(prova_list_response.json())
