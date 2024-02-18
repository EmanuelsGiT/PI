from django.urls import path
from django.http import JsonResponse

from api.models import Exam
from api import views

"""
def adicionar_teste(request):
    new_object = Teste(subject='Requisitos e Arquiteturas de Software', duration=90, version=3)

    try:
        new_object.save()  # Save the object to the database
        success = True
    except Exception as e:
        print(f'An exception occurred: {e}')
        success = False

    if success:
        data = new_object.to_dict()
    else:
        data = {}

    return JsonResponse(data)
"""

urlpatterns = [
    path("exams", views.exam_list, name="exams"),
    path("exams/<int:pk>/responses", views.exam_responses, name="exam_responses"),
    path("exams/<int:pk>/questions", views.exam_questions, name="exam_questions"),
    path("exams/<int:pk>/correction", views.exam_correction, name="exam_correction"),
    path("exams/<int:pk>/students", views.exam_students, name="exam_students"),
    path(
        "exams/<int:pk>/students/<str:sid>/score",
        views.student_exam_score,
        name="student_exam_score",
    ),
    path(
        "exams/<int:pk>/students/<str:sid>/responses",
        views.student_exam_responses,
        name="student_exam_responses",
    ),
    path(
        "exams/<int:pk>/students/<str:sid>/edit/score",
        views.edit_student_exam_score,
        name="edit_student_exam_score",
    ),
    path("exams/<int:pk>", views.exam_detail, name="exam_detail"),
    path("students/<str:sid>/scores", views.student_scores, name="student_scores"),
    path(
        "question",
        views.get_exam_question,
        name="get_question",
    ),
    path("responses", views.save_and_quit_exam, name="save_responses"),
    path("response", views.respond_exam_question, name="save_response"),
    path("exams/<int:pk>/students/<str:sid>/status", views.student_exam_status, name="student_exam_status"),
    path("exams/students/<str:sid>", views.student_exams, name="student_exams")
]
