from abc import ABC, abstractmethod
import spacy


class QuestionType(ABC):
    @abstractmethod
    def evaluate_response(self, response_data, question):
        pass


class MultipleChoiceQuestion(QuestionType):
    def evaluate_response(self, response, question):
        # Calculate the score for the questionns.
        student_response = response.response_data
        correct_response = question.answer
        size_of_answers = len(question.answer)
        count = 0
        for key, answer in correct_response.items():
            if answer == student_response.get(key):
                count += 1

        # Dividir a pontuação por todas as alíneas
        sized_score = question.points / size_of_answers
        # Resultado é igual ao número total de alineas corretas multiplicado
        # pela pontuação de cada alinea
        question_score = sized_score * count
        return question_score


class TrueOrFalseQuestion(QuestionType):
    def evaluate_response(self, response, question):
        # Calculate the score for the question
        student_response = response.response_data
        correct_response = question.answer
        size_of_answers = len(question.answer)
        count = 0
        for key, answer in correct_response.items():
            if answer == student_response.get(key):
                count += 1

        # Dividir a pontuação por todas as alíneas
        sized_score = question.points / size_of_answers
        # Resultado é igual ao número total de alineas corretas multiplicado
        # pela pontuação de cada alinea
        question_score = sized_score * count
        return question_score


class SpaceQuestion(QuestionType):
    def evaluate_response(self, response, question):
        # Calculate the score for the space question
        student_response = response.response_data
        correct_response = question.answer
        size_of_answers = len(question.answer)
        count = 0
        for key, answer in correct_response.items():
            similarity = calculate_similarity(answer, student_response.get(key))
            if similarity >= 0.40:
                count += 1
        sized_score = question.points / size_of_answers
        question_score = count * sized_score
        return question_score


class OpenQuestion(QuestionType):
    def evaluate_response(self, response, question):
        # Calculate the score for the open question
        similarity = calculate_similarity(response.response_data, question.answer)
        if similarity >= 0.85:
            question_score = question.points
        elif similarity < 0.60:
            question_score = 0.0
        else:
            question_score = similarity * question.points

        return question_score


# Auxiliar function to calculate similarity in the openanswers
def calculate_similarity(text1, text2):
    # Load the English spaCy language model
    # nlp = spacy.load("en_core_web_sm")
    # Load the Portuguese spaCy language model
    nlp = spacy.load("pt_core_news_sm")
    # Tokenize the text using spaCy
    doc1 = nlp(text1)
    doc2 = nlp(text2)

    # Calculate the similarity between the two texts (0 to 1)
    similarity = doc1.similarity(doc2)

    return similarity