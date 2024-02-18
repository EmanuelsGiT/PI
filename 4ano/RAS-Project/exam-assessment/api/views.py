from django.http import HttpResponse, JsonResponse
from django.http.response import responses
from rest_framework.parsers import JSONParser
from django.views.decorators.csrf import csrf_exempt
from django.views.decorators.http import require_http_methods

from api.models import Exam, Response, Question, QuestionScore, ExamScore  # , Question
from api.serializers import (
    ExamSerializer,
    ResponseSerializer,
    QuestionSerializer,
    QuestionScoreSerializer,
    ExamScoreSerializer,
)  # , QuestionSerializer
from api.strategy import (
    MultipleChoiceQuestion,
    TrueOrFalseQuestion,
    SpaceQuestion,
    OpenQuestion,
)
import json
from api.Exceptions import User_Not_Valid
import requests
import jwt

JWT_SECRET = "10152ac15c5c8ac4bc48cb1dea05b0274e0f64577e6c760ed1f4d0e7730e0ad2"


@csrf_exempt
@require_http_methods(["GET", "POST"])
def exam_responses(request, pk):
    """
    Add and Get the list of responses for an exam
    """
    # Get the exam object or return a 404 response if it doesn't exist
    try:
        exam = Exam.objects.get(pk=pk)
    except Exam.DoesNotExist:
        return JsonResponse({"message": "Exam does not exist"}, status=404)

    if request.method == "GET":
        # Query all responses related to the exam
        responses = Response.objects.filter(exam=exam)
        # Serialize the responses and return as JSON response
        serializer = ResponseSerializer(responses, many=True)
        return JsonResponse(serializer.data, status=200, safe=False)
    elif request.method == "POST":
        try:
            exam_response_data = json.loads(request.body.decode("utf-8"))
        except json.JSONDecodeError:
            return JsonResponse({"message": "Invalid JSON data"}, status=400)

        correct_response = []
        for student_response in exam_response_data:
            student_id = student_response["student_id"]
            responses = student_response["responses_data"]

            for data in responses:
                question_id = data["question_id"]
                response_data = data["response_data"]

                # Retrieve the question object
                try:
                    question = Question.objects.get(pk=question_id, exam=exam)
                except Question.DoesNotExist:
                    return JsonResponse(
                        {
                            "message": "Question "
                            + str(question_id)
                            + " does not belong to this exam"
                        },
                        status=401,
                    )

                # Create and save the response associated with the question, exam, and student
                response = Response.objects.create(
                    question=question,  # Use the retrieved question object
                    exam=exam,
                    student_id=student_id,
                    response_data=response_data,
                )

                correct_response.append(response)
        responses_serializer = ResponseSerializer(correct_response, many=True)
        return JsonResponse(responses_serializer.data, status=201, safe=False)


@csrf_exempt
def exam_list(request):
    """
    List all Exams.
    """
    if request.method == "GET":
        exams_list = []

        for exam in Exam.objects.all():
            exam_serializer = ExamSerializer(exam)
            exam_data = exam_serializer.data
            # Get the questions for a specific exam
            questions = Question.objects.filter(exam=exam)
            # Serialize the questions
            questions_serializer = QuestionSerializer(questions, many=True)
            exam_data["questions"] = questions_serializer.data
            exams_list.append(exam_data)
        return JsonResponse(exams_list, status=200, safe=False)
    elif request.method == "POST":
        try:
            data = json.loads(request.body.decode("utf-8"))
        except json.JSONDecodeError:
            return JsonResponse(
                {"message": "Invalid JSON data"}, status=400, safe=False
            )

        # Extract questions from exam data
        questions_data = data.pop("questions", [])
        exam_serializer = ExamSerializer(data=data)

        if exam_serializer.is_valid():
            # Create the exam without questions
            exam = exam_serializer.save()

            # Create a new question associated with the exam:
            question_serializer = QuestionSerializer(data=questions_data, many=True)
            if question_serializer.is_valid():
                question_serializer.save(exam=exam)
                exam_data = exam_serializer.data
                exam_data["questions"] = question_serializer.data
                return JsonResponse(exam_data, status=201, safe=False)
            else:
                exam.delete()  # Delete the exam if questions creation fails
                return JsonResponse(question_serializer.errors, status=400, safe=False)

        return JsonResponse(exam_serializer.errors, status=400, safe=False)


@csrf_exempt
def exam_detail(request, pk):
    """
    Retrieve, update or delete a code snippet.
    """
    try:
        exam = Exam.objects.get(pk=pk)
    except Exam.DoesNotExist:
        return JsonResponse({"message": f"Exam {pk} not found"}, status=404)
    if request.method == "GET":
        exam_serializer = ExamSerializer(exam)
        # Get the questions for the exam
        questions = Question.objects.filter(exam=exam)
        # Serialize the questions
        questions_serializer = QuestionSerializer(questions, many=True)
        exam_data = exam_serializer.data
        exam_data["questions"] = questions_serializer.data
        return JsonResponse(exam_data, status=200)
    # Edit without the questions
    elif request.method == "PUT":
        data = JSONParser().parse(request)
        serializer = ExamSerializer(exam, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=200)
        return JsonResponse(serializer.errors, status=400)
    elif request.method == "DELETE":
        exam.delete()
        return JsonResponse({"message": f"Exam {pk} deleted"}, status=204)


@csrf_exempt
def exam_questions(request, pk):
    """
    List all exam questions
    """
    if request.method == "GET":
        # Get the exam object or return a 404 response if it doesn't exist
        try:
            exam = Exam.objects.get(pk=pk)
        except Exam.DoesNotExist:
            return JsonResponse({"message": "Exam does not exist"}, status=404)
        # Query all questions related to the exam
        questions = Question.objects.filter(exam=exam)
        # Serialize the questions and return as JSON response
        serializer = QuestionSerializer(questions, many=True)
        return JsonResponse(serializer.data, status=200, safe=False)
    # Crete the method to edit questions
    elif request.method == "PUT":
        pass


@csrf_exempt
@require_http_methods(["GET", "POST"])
def exam_correction(request, pk):
    """
    List and Calculate all exam scores
    """
    try:
        # Get the exam object
        exam = Exam.objects.get(pk=pk)
    except Exam.DoesNotExist:
        return JsonResponse({"message": "Exam does not exist"}, status=404)

    if request.method == "GET":
        try:
            # Check if there's an ExamScore record for the specific exam
            exam = Exam.objects.get(pk=pk)
            exam_scores = ExamScore.objects.filter(exam=exam)
            scores_list = []

            for score in exam_scores:
                # Get questions related to the exam
                questions = Question.objects.filter(exam=exam)
                questions_score_dict = dict()

                for question in questions:
                    try:
                        # Retrieve all QuestionScores related to the exam and student
                        question_score = QuestionScore.objects.get(
                            student_id=score.student_id, question=question
                        )
                        questions_score_dict[
                            question_score.question.question_id
                        ] = question_score.question_score
                    except QuestionScore.DoesNotExist:
                        # Handle the case where no QuestionScore exists for the student and question
                        return JsonResponse(
                            {"message": "No scores found for this question."},
                            status=404,
                            safe=False,
                        )

                # Create a response combining ExamScore and QuestionScores data
                response_data = {
                    "student_id": score.student_id,
                    "exam_id": exam.id,
                    "exam_score": score.exam_score,
                    "question_scores": questions_score_dict,
                }
                scores_list.append(response_data)

            return JsonResponse(scores_list, status=200, safe=False)

        except ExamScore.DoesNotExist:
            return JsonResponse(
                {"message": "No correction found for this exam."},
                status=404,
                safe=False,
            )
        except Exam.DoesNotExist:
            return JsonResponse(
                {"message": "No QuestionScores found for the given exam."}, status=404
            )

    elif request.method == "POST":
        try:
            # Get all responses related to the exam
            responses = Response.objects.filter(exam=exam)
            # Get all questions related to the exam
            questions = Question.objects.filter(exam=exam)
            # Initialize variables to track scores
            question_score = 0
            question_score_list = []
            student_score_list = []
            question_serializer_list = []
            grades_list = dict()

            for question in questions:
                # Find the corresponding student response
                student_responses = responses.filter(question=question)
                for response in student_responses:
                    # Compare the student response with the correct answer
                    question_type = question.question_type

                    if question_type == "MULTIPLE_CHOICE":
                        question_score = MultipleChoiceQuestion().evaluate_response(
                            response, question
                        )

                    elif question_type == "TRUE_FALSE":
                        question_score = TrueOrFalseQuestion().evaluate_response(
                            response, question
                        )

                    elif question_type == "SPACE":
                        question_score = SpaceQuestion().evaluate_response(
                            response, question
                        )

                    elif question_type == "OPEN":
                        question_score = OpenQuestion().evaluate_response(
                            response, question
                        )

                    # Round the score
                    rounded_score = round(question_score, 2)

                    # Save the score of the student
                    # question, have the score for the specific question
                    # exam list have all the scores of the exam
                    if response.student_id not in grades_list:
                        grades_list[response.student_id] = {
                            "question": rounded_score,
                            "exam": [rounded_score],
                        }
                    else:
                        grades_list[response.student_id]["question"] = rounded_score
                        grades_list[response.student_id]["exam"].append(rounded_score)

                # Create a question_score-type object record in the database
                for student, list_grades in grades_list.items():
                    question_score = QuestionScore.objects.create(
                        question=question,
                        student_id=student,
                        question_score=list_grades["question"],
                    )
                    question_score_list.append(question_score)

            # Serialize the list of questions scores
            question_serializer = QuestionScoreSerializer(
                question_score_list, many=True
            )
            # Save the serialize objects in a list
            question_serializer_list.append(question_serializer.data)

            # Get the total score of the list of questions grades
            # Create an exam_score-type object record in the database
            for student, list_grades in grades_list.items():
                student_score = ExamScore.objects.create(
                    exam=exam,
                    student_id=student,
                    exam_score=round(sum(list_grades["exam"]), 1),
                )
                # Save the all the objects in a list
                student_score_list.append(student_score)

            # Serialize the list of students' scores
            score_serializer = ExamScoreSerializer(student_score_list, many=True)
            score_final = {
                "exam": score_serializer.data,
                "questions": question_serializer_list,
            }
            return JsonResponse(score_final, status=200, safe=False)
        except Response.DoesNotExist:
            return JsonResponse(
                {"message": "No responses given for this exam."}, status=404, safe=False
            )

        except Question.DoesNotExist:
            return JsonResponse(
                {"message": "No questions found for this exam."}, status=404, safe=False
            )

        except Exception as e:
            return JsonResponse({"error": str(e)}, status=500, safe=False)


@require_http_methods(["GET"])
def exam_students(request, pk):
    """
    List all students that took the exam
    """
    try:
        # Query all unique student IDs who took the specified exam
        student_ids = (
            Response.objects.filter(exam_id=pk)
            .values_list("student_id", flat=True)
            .distinct()
        )

        # Check if any students took the exam
        if student_ids:
            # Convert the student IDs to a list
            student_ids_list = list(student_ids)

            return JsonResponse(student_ids_list, status=200, safe=False)
        else:
            return JsonResponse(
                {"message": "No students found for this exam."}, status=404, safe=False
            )
    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500, safe=False)


@require_http_methods(["GET"])
def student_scores(request, sid):
    """
    List all the scores for a student
    """
    try:
        # Query all scores for the specific student
        exam_scores = ExamScore.objects.filter(student_id=sid)

        # Initialize a list to store the scores
        scores_list = []

        for score in exam_scores:
            # Get the questions related to the exam
            questions = Question.objects.filter(exam=score.exam)
            questions_score_dict = dict()

            for question in questions:
                try:
                    # Retrieve the QuestionScore related to the student and question
                    question_score = QuestionScore.objects.get(
                        student_id=sid, question=question
                    )
                    questions_score_dict[
                        question_score.question.question_id
                    ] = question_score.question_score
                except QuestionScore.DoesNotExist:
                    # Handle the case where no QuestionScore exists for the student and question
                    return JsonResponse(
                        {"message": "No scores found for this question."},
                        status=404,
                        safe=False,
                    )

            # Create a response combining ExamScore and QuestionScores data
            response_data = {
                "student_id": score.student_id,
                "exam_id": score.exam.id,
                "exam_score": score.exam_score,
                "question_scores": questions_score_dict,
            }
            scores_list.append(response_data)

        return JsonResponse(scores_list, status=200, safe=False)
    except ExamScore.DoesNotExist:
        return JsonResponse(
            {"message": "No scores found for this student."}, status=404, safe=False
        )
    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500, safe=False)


@require_http_methods(["GET"])
def student_exam_score(request, pk, sid):
    """
    List all the scores from an exam for a student
    """
    try:
        # Get the exam from pk
        exam = Exam.objects.get(pk=pk)

        # Retrieve the ExamScore for the student and exam
        exam_score = ExamScore.objects.get(student_id=sid, exam=exam)

        # Get the questions related to the exam
        questions = Question.objects.filter(exam=exam)
        questions_score_dict = dict()

        for question in questions:
            try:
                # Retrieve the QuestionScore related to the student and question
                question_score = QuestionScore.objects.get(
                    student_id=sid, question=question
                )
                questions_score_dict[
                    question_score.question.question_id
                ] = question_score.question_score
            except QuestionScore.DoesNotExist:
                # Handle the case where no QuestionScore exists for the student and question
                return JsonResponse(
                    {"message": "No scores found for this question."},
                    status=404,
                    safe=False,
                )

        # Create a response combining ExamScore and QuestionScores data
        response_data = {
            "student_id": exam_score.student_id,
            "exam_id": exam.id,
            "exam_score": exam_score.exam_score,
            "question_scores": questions_score_dict,
        }

        return JsonResponse([response_data], status=200, safe=False)
    except ExamScore.DoesNotExist:
        return JsonResponse(
            {"message": "No scores found for this student and exam."},
            status=404,
            safe=False,
        )
    except Exam.DoesNotExist:
        return JsonResponse({"message": "Exam does not exist"}, status=404)


@require_http_methods(["GET"])
def student_exam_responses(request, pk, sid):
    """
    List all the responses from an exam for a student
    """
    try:
        # Get the exam from pk
        exam = Exam.objects.get(pk=pk)
        # Query all responses of the student (sid) for the exam (pk)
        responses = Response.objects.filter(exam=exam, student_id=sid)

        # Create a list to store response information
        response_data = []

        # Iterate over the responses and create dictionaries for each
        for response in responses:
            response_item = {
                "response_id": response.response_id,
                "exam": exam.id,
                "question": response.question_id,
                "response_data": response.response_data,
            }
            response_data.append(response_item)

        return JsonResponse(response_data, status=200, safe=False)

    except Response.DoesNotExist:
        return JsonResponse(
            {"message": "No responses found for this student and exam."},
            status=404,
            safe=False,
        )


@csrf_exempt
@require_http_methods(["PUT"])
def edit_student_exam_score(request, pk, sid):
    """
    Edit a score for a response given by a student
    """
    try:
        try:
            questions_data = json.loads(request.body.decode("utf-8"))
        except json.JSONDecodeError:
            return JsonResponse(
                {"message": "Invalid JSON data"}, status=400, safe=False
            )
        question_serializer_list = []
        exam = Exam.objects.get(pk=pk)
        for data in questions_data:
            # Get the question to update
            question = Question.objects.get(pk=data["question_id"], exam=exam)
            # Get the score of the question
            question_score = QuestionScore.objects.get(
                question=question, student_id=sid
            )
            # Verify if the updated score isn't bigger than the max score for the question
            try:
                float_data = float(data["question_score"])
                if question_score.question_score >= float_data:
                    # Update the score for the question
                    question_score.question_score = float_data
                    # Save the updated question_score
                    question_score.save()
                    # Serialize the updated data
                    question_serializer = QuestionScoreSerializer(question_score)
                    question_serializer_list.append(question_serializer.data)
                else:
                    return JsonResponse(
                        {
                            "message": "Invalid question score. Question score bigger than the max score for this question"
                        },
                        status=400,
                        safe=False,
                    )
            except Exception as e:
                return JsonResponse(
                    {
                        "message": "The question_score field needs to be a float",
                        "error": str(e),
                    },
                    status=500,
                )

        # Get all the questions to calculate the new exam score
        question_scores = QuestionScore.objects.filter(student_id=sid)
        # Calculate the sum of all question scores for that student
        total_score = sum([score.question_score for score in question_scores])
        print(total_score)
        exam_score = ExamScore.objects.get(exam=exam, student_id=sid)

        exam_score.exam_score = total_score
        exam_score.save()
        exam_score_serializer = ExamScoreSerializer(exam_score)
        edited_score = {
            "exam": exam_score_serializer.data,
            "questions": question_serializer_list,
        }
        return JsonResponse(edited_score, status=200)

    except Exam.DoesNotExist:
        return JsonResponse({"message": "Exam does not exist."}, status=404)
    except ExamScore.DoesNotExist:
        return JsonResponse(
            {"message": "ExamScore does not exist for this student and exam."},
            status=404,
        )
    except Question.DoesNotExist:
        return JsonResponse({"message": "Question does not exist."}, status=404)
    except QuestionScore.DoesNotExist:
        return JsonResponse(
            {"message": "QuestionScore does not exist for this student and question."},
            status=404,
        )
    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)


@csrf_exempt
@require_http_methods(["GET"])
def get_exam_question(request):
    """
    Get a single question for a specific exam
    """

    # Get the exam id and question id from the request
    id_exam = request.GET.get("exam_id")
    id_question = request.GET.get("question_id")


    # HACK: Auxiliary function to decode the user from the jwt token
    def decode_user(token: str):
        """
        :param token: jwt token
        :return decoded_data: dict with the data of the user
        """
        decoded_data = jwt.decode(jwt=token, key=JWT_SECRET, algorithms=["HS256"])
        return decoded_data

    try:
        # Get the question from id_exam and id_question
        question = Question.objects.filter(exam=id_exam, pk=id_question)
        question = question[0]

        # HACK: I guess this is not the best way to do it
        jwt_token = request.META["HTTP_AUTHORIZATION"].split(" ")[1]
        student = decode_user(jwt_token)
        if not student:
            raise User_Not_Valid("User is not valid")

        ##FIX: Validar que o aluno pode realizar o exame
        student_id = student["sub"]
        # NOTE: Not implemented yet

        response = {
            "exam_id": id_exam,
            "question_id": id_question,
            "question_type": question.question_type,
            "points": question.points,
            "image_path": question.image_path,
            "description": question.description,
        }
        return JsonResponse(response, status=200)

    except Question.DoesNotExist:
        return JsonResponse(
            {"message": "Question does not exist."},
            status=404,
        )
    except User_Not_Valid as e:
        return JsonResponse(
            {"error": str(e)},
            status=500,
        )
    except Exception as e:
        return JsonResponse(
            {"error": str(e)},
            status=500,
        )


def save_response(student_id, exam_id ,student_response):
    """
    Save a single response from a student
    """

    question_id = student_response["question_id"]
    response_data = student_response["response_data"]

    response = None
    try:
        question = Question.objects.get(pk=question_id, exam=exam_id)
        exam = Exam.objects.get(pk=exam_id)
        response = Response.objects.get(
            question=question, exam=exam, student_id=student_id
        )
    except Question.DoesNotExist:
        return (
            {"message": f"Question {str(question_id)} does not belong to this exam"},
            401,
        )
    except Exam.DoesNotExist:
        return ({"message": f"Exam {str(exam_id)} does not exist"}, 401)
    except Response.DoesNotExist:
        # Valid case, but django throws an error if RESPONSE does not exist
        pass
    # Create and save the response associated with the question, exam, and student
    if response is not None:
        response.response_data = response_data
        response.save()
    else:
        Response.objects.create(
            question=question,  # Use the retrieved question object
            exam=exam,
            student_id=student_id,
            response_data=response_data,
        )
    

    return (
        {
            "exam_id": exam_id,
            "question_id": question_id,
            "student_id": student_id,
            "ok": 1,
        },
        200,
    )


@csrf_exempt
@require_http_methods(["POST"])
def respond_exam_question(request):
    """
    Respond to a single question from a specific exam
    """
    if request.method == "POST":
        try:
            student_response = json.loads(request.body.decode("utf-8"))
        except json.JSONDecodeError:
            return JsonResponse({"message": "Invalid JSON data"}, status=400)
        exam_id = student_response["exam_id"]
        student_id = student_response["student_id"]
        response_ = student_response["response"]
        response = save_response(student_id,exam_id,response_)
        return JsonResponse(response[0], status=response[1])


@csrf_exempt
@require_http_methods(["POST"])
def save_and_quit_exam(request):
    """
    Save all question from a specific exam
    """
    if request.method == "POST":
        try:
            student_responses = json.loads(request.body.decode("utf-8"))
        except json.JSONDecodeError:
            return JsonResponse({"message": "Invalid JSON data"}, status=400)
        exam_id = student_responses["exam_id"]
        student_id = student_responses["student_id"]
        student_responses = student_responses["responses"]
        for student_response in student_responses:
            out = save_response(student_id,exam_id,student_response)
            if out[1] != 200:
                return JsonResponse(out[0], status=out[1])

        return JsonResponse({"ok": 1}, status=200)

@csrf_exempt
@require_http_methods(["GET"])
def student_exam_status(request, pk, sid):
    """
    Gets the status of a student in an exam
    """
    try:
        # Get the exam from pk
        exam = Exam.objects.get(pk=pk)
        exam_serializer = ExamSerializer(exam)
        exam_data = exam_serializer.data

        questions = Question.objects.filter(exam=exam)
        # Serialize the questions
        questions_serializer = QuestionSerializer(questions, many=True)
        questions_data = questions_serializer.data
        exam_data["questions"] = questions_data

        # Query all responses of the student (sid) for the exam (pk)
        responses = list(Response.objects.filter(exam=exam, student_id=sid).values_list('question_id', 'response_data'))

        exam_scores = ExamScore.objects.filter(exam=exam, student_id=sid).values_list('exam_score', flat=True)
        if len(exam_scores) > 0:
            exam_score = float(exam_scores[0])
        else:
            exam_score = None

        question_scores = {}
        for qdata in questions_data:
            qid = qdata['question_id']
            qscores = QuestionScore.objects.filter(question=qid, student_id=sid).values_list('question_score', flat=True)

            if len(qscores) > 0:
                question_scores[qid] = qscores[0]
            else:
                question_scores[qid] = None

        status_data = {"exam_score": exam_score, "question_score": question_scores, "answers": responses}
        response_data = {"exam": exam_data, "status": status_data}

        return JsonResponse(response_data, status=200, safe=False)

    except Response.DoesNotExist:
        return JsonResponse(
            {"message": "No responses found for this student and exam."},
            status=404,
            safe=False,
        )
    except ExamScore.DoesNotExist:
        return JsonResponse(
            {"message": "No exame score found for this student and exam."},
            status=404,
            safe=False,
        )
    except Question.DoesNotExist:
        return JsonResponse(
            {"message": "No questions found for this exam."},
            status=404,
            safe=False,
        )
    except QuestionScore.DoesNotExist:
        return JsonResponse(
            {"message": "No question score found for one of the question and student."},
            status=404,
            safe=False,
        )


@csrf_exempt
@require_http_methods(["GET"])
def student_exams(request, sid):
    """
    Lists the exams answered by a student
    """
    try:
        exam_ids = Response.objects.filter(student_id=sid).values_list('exam_id', flat=True).distinct()

        exams = Exam.objects.filter(id__in=exam_ids)
        exams_serializer = ExamSerializer(exams, many=True)
        exams_data = exams_serializer.data

        for i in range(len(exams_data)):
            exams_data[i]['number_questions'] = len(Question.objects.filter(exam_id=exams_data[i]['id']))

        return JsonResponse(exams_data, status=200, safe=False)

    except Response.DoesNotExist:
        return JsonResponse(
            {"message": "No exam responses found for this student."},
            status=404,
            safe=False,
        )
    except Exam.DoesNotExist:
        return JsonResponse(
            {"message": "No exame found."},
            status=404,
            safe=False,
        )
    except Question.DoesNotExist:
        return JsonResponse(
            {"message": "No questions found for this exam."},
            status=404,
            safe=False,
        )
