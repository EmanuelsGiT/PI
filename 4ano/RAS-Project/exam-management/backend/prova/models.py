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


class Prova(models.Model):
    id = models.AutoField(primary_key=True)
    version = models.IntegerField()
    reservation = models.CharField(max_length=100)
    duration = models.IntegerField()
    max_score = models.IntegerField()
    exam_type = models.CharField(max_length=20)
    description = models.CharField(max_length=200)
    subject = models.CharField(max_length=100)
    questions = models.JSONField()

    class Meta:
        unique_together = ("id", "reservation")
        ordering = ["id", "reservation"]


class Question(models.Model):
    question_id = models.IntegerField()
    question_type = models.CharField(max_length=20)
    points = models.FloatField()
    image_path = models.CharField(max_length=100)
    description = models.CharField(max_length=200)
    answers = models.JSONField()


class Answer(models.Model):
    pass