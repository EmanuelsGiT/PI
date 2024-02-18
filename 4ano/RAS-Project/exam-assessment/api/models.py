from __future__ import annotations

from django.db import models
from enum import Enum


class ExamType(Enum):
    EXAM = "EXAM"
    TEST = "TEST"
    QUIZ = "QUIZ"


class QuestionType(Enum):
    MULTIPLE_CHOICE = "MULTIPLE_CHOICE"  # { "answer": {"0":true,"1":false, "2"(...)} }
    TRUE_FALSE = "TRUE_FALSE"  # { "answer": {"0":true,"1":false,"2"(...)} }
    SPACE = "SPACE"  # { "answer": {"0":"Space1","1":"Space2"}}
    OPEN = "OPEN"  # { "answer": "Lorem ipsum dolor sit amet, qui minim labore adipisicing minim sint cillum sint consectetur cupidatat." }


class Exam(models.Model):
    id = models.BigAutoField(primary_key=True)
    version = models.IntegerField()
    reservation = models.CharField(max_length=100)
    duration = models.IntegerField()
    max_score = models.IntegerField()
    exam_type = models.CharField(max_length=20)
    description = models.CharField(max_length=200)
    subject = models.CharField(max_length=100)

    class Meta:
        unique_together = ("id", "reservation")
        ordering = ["id", "reservation"]


class Question(models.Model):
    exam = models.ForeignKey(
        Exam, related_name="exam_questions", on_delete=models.CASCADE, default=None
    )
    question_id = models.BigAutoField(primary_key=True)
    question_type = models.CharField(max_length=20)
    points = models.FloatField()
    image_path = models.CharField(max_length=100)
    description = models.CharField(max_length=200)
    answer = models.JSONField()  # Resposta Correta

    def __repr__(self):
        return f"Question={self.question_id}, Exam={self.exam.id}, Reservation={self.exam.reservation}, QuestionType={self.question_type}, Points={self.points}, ImagePath={self.image_path}, Description={self.description}, Answer={self.answer}"


class Response(models.Model):
    response_id = models.BigAutoField(primary_key=True)
    question = models.ForeignKey(
        Question, related_name="question_response", on_delete=models.CASCADE
    )
    exam = models.ForeignKey(
        Exam, related_name="exam_response", on_delete=models.CASCADE
    )
    student_id = models.CharField(max_length=100)
    response_data = models.JSONField()  # Resposta Aluno


class QuestionScore(models.Model):
    question_score_id = models.BigAutoField(primary_key=True)
    question = models.ForeignKey(
        Question, related_name="question_score", on_delete=models.CASCADE
    )
    student_id = models.CharField(max_length=100)
    question_score = models.DecimalField(max_digits=5, decimal_places=2)


class ExamScore(models.Model):
    exam_score_id = models.BigAutoField(primary_key=True)
    exam = models.ForeignKey(Exam, related_name="exam_score", on_delete=models.CASCADE)
    student_id = models.CharField(max_length=100)
    exam_score = models.DecimalField(max_digits=5, decimal_places=1)
