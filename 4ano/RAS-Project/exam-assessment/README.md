# exam-assessment

### Exam Example
```json
{
  "version": 1,
  "reservation": "Reserva2",
  "duration": 90,
  "max_score": 100,
  "exam_type": "EXAM",
  "description": "Trying to create a Exam Example",
  "subject": "Post Test",
  "questions": [
    {
      "question_type": "MULTIPLE_CHOICE",
      "points": 25.0,
      "image_path": "No source",
      "description": "Este é uma questão de escolha múltipla",
      "answer": {
        "0": true,
        "1": false,
        "2": true,
        "3": false
      }
    },
    {
      "question_type": "TRUE_FALSE",
      "points": 25.0,
      "image_path": "No source",
      "description": "Este é uma questão de verdadeiro e falso",
      "answer": {
        "0": true,
        "1": false
      }
    },
    {
      "question_type": "SPACE",
      "points": 25.0,
      "image_path": "No source",
      "description": "Este é uma {-0-} de completar {-1-}",
      "answer": {
        "0": "questão",
        "1": "espaços"
      }
    },
    {
      "question_type": "OPEN",
      "points": 25.0,
      "image_path": "No source",
      "description": "Este é uma questão de resposta aberta",
      "answer": "A mitose é um processo de divisão celular que resulta na formação de duas células filhas geneticamente idênticas."
    }
  ]
}
```
### Response Example

```json
[
  {
    "student_id": 3001,
    "responses_data": [
      {"question_id": 1, "response_data": {"0": true, "1": true, "2": false, "3": false}},
      {"question_id": 2, "response_data": {"0": true, "1": false}},
      {"question_id": 3, "response_data": {"0": "perguntas", "1": "espaços"}},
      {"question_id": 4, "response_data": "Não sei nada."}
    ]
  },
  {
    "student_id": 3002,
    "responses_data": [
      {"question_id": 1, "response_data": {"0": true, "1": false, "2": true, "3": true}},
      {"question_id": 2, "response_data": {"0": true, "1": true}},
      {"question_id": 3, "response_data": {"0": "espaços", "1": ""}},
      {"question_id": 4, "response_data": "Fases da mitose incluem prófase, metáfase, anáfase e telófase, nas quais as células se dividem e formam novas células filhas."}
    ]
  },
  {

    "student_id": 3003,
    "responses_data": [
      {"question_id": 1, "response_data": {"0": true, "1": false, "2": true, "3": false}},
      {"question_id": 2, "response_data": {"0": false, "1": false}},
      {"question_id": 3, "response_data": {"0": "questões", "1": "espaços"}},
      {"question_id": 4, "response_data": "A mitose é um mecanismo de reprodução assexuada em que uma célula mãe se divide em duas células filhas com o mesmo material genético."}

    ]
  }
]
```

### Create an Exam with POST Request

```bash
#curl -X POST http://127.0.0.1:8000/api/exams -d '{
    "version": 1,
    "reservation": "Reserva1",
    "duration": 90,
    "max_score": 200,
    "exam_type": "EXAM",
    "description": "Trying to create using POST Request",
    "subject": "Post Test",
    "questions": [
        {
            "question_type": "MULTIPLE_CHOICE",
            "points": 20.0,
            "image_path": "No source",
            "description": "Este é uma questão de escolha múltipla",
            "answer": {
                "0": true,
                "1": false,
                "2": true,
                "3": false
            }
        },
        {
            "question_type": "TRUE_FALSE",
            "points": 20.0,
            "image_path": "No source",
            "description": "Este é uma questão de verdadeiro e falso",
            "answer": {
                "0": true,
                "1": false
            }
        },
        {
            "question_type": "OPEN",
            "points": 20.0,
            "image_path": "No source",
            "description": "Este é uma questão de resposta aberta",
            "answer": "A mitose é um processo de divisão celular que resulta na formação de duas células filhas geneticamente idênticas."
        }
    ]
}'
```

### Development Logic (Pseudo-Code)

```python
"""
Cada questão tem um ID unico?

Exame 1:
    Questão 1:
    Questão 2:
    ....
    Questão 10:

Exame 2:
    Questão 11:
    ...
    Questão 20:
"""
# Back-End send exam info with all questions
x = [11,12,13,15]


# Front-End randomize the order of the questions and asks for the specific question
visited = []
while len(visited) < len(x):
    _id = random(min(x),max(x)+1)
    if _id not in visited:
        #TODO: Get. ID_questão,ID_test,ID_aluno. -> RESPONSE {ID_questão, ID_test, type, points, image_path, description}
        Display(Response)
        #TODO: Post. Resposta,ID_aluno,ID_test,ID_questão. FORMAT {ID_test,ID_questão,ID_aluno,{"answer":(Por Tipo)} } -> RESPONSE {ID_test,ID_questão,ID_aluno,ok}
        visited.append(_id)

```


## Pedir uma Questão

```bash
curl -X "GET" -H "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3MDQ3NTY2NjcsInN1YiI6InBnNTM4NTEifQ.2nhaFg4IK8tM0fsgBeIeJ1fFAOQixgCsnRHUpOxQyAM" 'http://127.0.0.1:8000/api/question?exam_id=1&question_id=1'  
```

#TODO: ainda vamos tentar alterar isto para usar o body e não o URL


## Resolver um EXAME


### Todos usam JWT token in header

```bash
curl -X "POST" -H "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3MDQ3NTY2NjcsInN1YiI6InBnNTM4NTEifQ.2nhaFg4IK8tM0fsgBeIeJ1fFAOQixgCsnRHUpOxQyAM"
```


### Resposta a uma questão:

```bash
curl -X POST "http://127.0.0.1:8000/api/response" -H "Content-Type: application/json"
```
```json
{                 
    "student_id": "pg53851",
    "exam_id": 1,
    "response":{"question_id": 1, "response_data": {"0": true, "1": false, "2": true, "3": false}}
}'
```

### Guardar todas as respostas: (save, submit and exit the exam)

```bash
curl -X POST "http://127.0.0.1:8000/api/response" -H "Content-Type: application/json"
```
```json
{
   "student_id":"pg53851",
   "exam_id":1,
   "responses":[
      {
         "question_id":1,
         "response_data":{
            "0":true,
            "1":false,
            "2":true,
            "3":false
         }
      },
      {
         "question_id":2,
         "response_data":{
            "0":false,
            "1":false
         }
      },
      {
         "question_id":3,
         "response_data":"A mitose é um mecanismo de reprodução assexuada em que uma célula mãe se divide em duas células filhas com o mesmo material genético."
      }
   ]
}
```