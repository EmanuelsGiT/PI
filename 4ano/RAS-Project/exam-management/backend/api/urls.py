from django.urls import path
from .views import ProvaDetailView, ProvaListView, QuestionDetailView, QuestionListView, ProvaConsultView, api_home

urlpatterns = [
    path('', api_home, name='api_home'),  # No need for 'api/' prefix here
    path('provas/', ProvaListView.as_view(), name='prova-list'),
    path('provas/<int:pk>/', ProvaDetailView.as_view(), name='prova-detail'),
    path('questions/', QuestionListView.as_view(), name='question-list'),
    path('questions/<int:pk>/', QuestionDetailView.as_view(), name='question-detail'),
    path('provas/', ProvaConsultView.as_view(), name='prova-consult'),
]
