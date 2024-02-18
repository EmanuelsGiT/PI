import json
from django.core.serializers import serialize
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
from django.views import View
from prova.models import Prova, Question
from django.http import JsonResponse

def api_home(request):
    return JsonResponse({'message': 'Welcome to the API home!'})

class ProvaDetailView(View):
    def get(self, request, pk):
        try:
            prova = Prova.objects.get(pk=pk)
            data = json.loads(serialize('json', [prova]))[0]['fields']
            return JsonResponse(data)
        except Prova.DoesNotExist:
            return JsonResponse({'error': 'Prova not found'}, status=404)

    def put(self, request, pk):
        try:
            prova = Prova.objects.get(pk=pk)
            # Extract updated data from request body
            updated_data = json.loads(request.body)
            # Update relevant fields
            prova.version = updated_data.get('version', prova.version)
            prova.reservation = updated_data.get('reservation', prova.reservation)
            # Update other fields similarly
            prova.save()
            return JsonResponse({'message': 'Prova updated successfully'})
        except Prova.DoesNotExist:
            return JsonResponse({'error': 'Prova not found'}, status=404)

    def delete(self, request, pk):
        try:
            prova = Prova.objects.get(pk=pk)
            prova.delete()
            return JsonResponse({'message': 'Prova deleted successfully'})
        except Prova.DoesNotExist:
            return JsonResponse({'error': 'Prova not found'}, status=404)
        
#The @method_decorator is a decorator in Django that allows you to apply a decorator to all methods of a class or only to specific methods. It is commonly used to modify the behavior of class-based views.
@method_decorator(csrf_exempt, name='dispatch')
class ProvaListView(View):
    def get(self, request):
        prova_list = Prova.objects.all()
        data = {'provas': json.loads(serialize('json', prova_list))}
        return JsonResponse(data)

    def post(self, request):
        try:
            new_prova_data = json.loads(request.body)
            new_prova = Prova.objects.create(
                version=new_prova_data['version'],
                reservation=new_prova_data['reservation'],
                duration=new_prova_data['duration'],
                max_score=new_prova_data['max_score'],
                exam_type=new_prova_data['exam_type'],
                description=new_prova_data['description'],
                subject=new_prova_data['subject'],
                questions=new_prova_data['questions'],
                # Set other fields similarly that may be added in the future
            )
            return JsonResponse({'message': 'Prova created successfully'})
        except Exception as e:
            return JsonResponse({'error': str(e)}, status=500)

class QuestionDetailView(View):
    def get(self, request, pk):
        try:
            question = Question.objects.get(pk=pk)
            data = json.loads(serialize('json', [question]))[0]['fields']
            return JsonResponse(data)
        except Question.DoesNotExist:
            return JsonResponse({'error': 'Question not found'}, status=404)

    def put(self, request, pk):
        try:
            question = Question.objects.get(pk=pk)
            # Extract updated data from request body
            updated_data = json.loads(request.body)
            # Update relevant fields
            question.question_id = updated_data.get('question_id', question.question_id)
            question.question_type = updated_data.get('question_type', question.question_type)
            # Update other fields similarly
            question.save()
            return JsonResponse({'message': 'Question updated successfully'})
        except Question.DoesNotExist:
            return JsonResponse({'error': 'Question not found'}, status=404)

    def delete(self, request, pk):
        try:
            question = Question.objects.get(pk=pk)
            question.delete()
            return JsonResponse({'message': 'Question deleted successfully'})
        except Question.DoesNotExist:
            return JsonResponse({'error': 'Question not found'}, status=404)

@method_decorator(csrf_exempt, name='dispatch')
class QuestionListView(View):
    def get(self, request):
        question_list = Question.objects.all()
        data = {'questions': json.loads(serialize('json', question_list))}
        return JsonResponse(data)

    def post(self, request):
        try:
            new_question_data = json.loads(request.body)
            new_question = Question.objects.create(
                question_id=new_question_data['question_id'],
                question_type=new_question_data['question_type'],
                points=new_question_data['points'],
                description=new_question_data['description'],
                answers=new_question_data['answers'],
                # Set other fields similarly that may be added in the future
            )
            return JsonResponse({'message': 'Question created successfully'})
        except Exception as e:
            return JsonResponse({'error': str(e)}, status=500)

class ProvaConsultView(View):
    def get(self, request):
        prova_list = Prova.objects.all()
        data = {'provas': json.loads(serialize('json', prova_list))}
        return JsonResponse(data)
