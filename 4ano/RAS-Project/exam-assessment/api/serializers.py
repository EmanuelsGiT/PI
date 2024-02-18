from rest_framework import serializers
from api.models import Exam, Question, Response, QuestionScore, ExamScore


class ExamSerializer(serializers.ModelSerializer):
    class Meta:
        model = Exam
        fields = [
            "id",
            "version",
            "reservation",
            "duration",
            "max_score",
            "exam_type",
            "description",
            "subject",
        ]


class QuestionSerializer(serializers.ModelSerializer):
    class Meta:
        model = Question
        fields = [
            "question_id",
            "question_type",
            "points",
            "image_path",
            "description",
            "answer",
        ]


class ResponseSerializer(serializers.ModelSerializer):
    class Meta:
        model = Response
        fields = [
            "response_id",
            "question",
            "exam",
            "student_id",
            "response_data",
        ]


class QuestionScoreSerializer(serializers.ModelSerializer):
    class Meta:
        model = QuestionScore
        fields = [
            "question_score_id",
            "question",
            "student_id",
            "question_score"
        ]


class ExamScoreSerializer(serializers.ModelSerializer):
    class Meta:
        model = ExamScore
        fields = [
            "exam_score_id",
            "exam",
            "student_id",
            "exam_score"
        ]
