<script lang="ts">
    import { onMount } from 'svelte';
    import TrueFalseQuestion from './TrueFalseQuestion.svelte';
    import MultipleChoiceQuestion from './MultipleChoiceQuestion.svelte';
    import OpenQuestion from './OpenQuestion.svelte';
    import BlankSpacesQuestion from './BlankSpacesQuestion.svelte';
  
    export let exam: ExamData;
    export let mode: string;
    export let studentAnswers: Record<string, string>;
  
    let currentQuestionIndex = 0;
  
    interface ExamData {
      description: string;
      subject: string;
      duration: number;
      questions: Question[];
    }
  
    interface Question {
      questionId: number;
      type: string;
      points: number;
      imagePath: string;
      description: string;
      answers: Record<string, string>;
    }
  
    function handleSubmit() {
      if (confirm('Are you sure you want to submit the exam?')) {
        // Perform actions when the exam is submitted, e.g., send answers to the server.
        console.log('Exam submitted!');
      }
    }
  
    function handleNextQuestion() {
      if (currentQuestionIndex < exam.questions.length - 1) {
        currentQuestionIndex++;
      }
    }
  
    function handlePrevQuestion() {
      if (currentQuestionIndex > 0) {
        currentQuestionIndex--;
      }
    }
  </script>
  
  <div class="p-8 w-full">
    <h1 class="text-2xl font-bold mb-4">{exam.description}</h1>
    <p class="text-gray-600 mb-2">Subject: {exam.subject}</p>
    <p class="text-gray-600 mb-4">Duration: {exam.duration} minutes</p>
  
    {#if exam.questions.length > 0 && currentQuestionIndex < exam.questions.length}
      <div class="flex justify-between">
        <div>
          <p class="text-lg font-semibold">Question {currentQuestionIndex + 1}:</p>
        </div>
        {#if mode === 'view'}
          <div class="mt-4">
            <p class="text-lg font-semibold">Grade: {exam.questions[currentQuestionIndex].points}</p>
          </div>
        {/if}
      </div>
  
      {#if exam.questions[currentQuestionIndex].type === 'T/F'}
        <TrueFalseQuestion question={exam.questions[currentQuestionIndex]} mode={mode} studentAnswers={studentAnswers[currentQuestionIndex.toString()]} />
      {/if}
      {#if exam.questions[currentQuestionIndex].type === 'Multiple'}
        <MultipleChoiceQuestion question={exam.questions[currentQuestionIndex]} mode={mode} studentAnswers={studentAnswers[currentQuestionIndex.toString()]}/>
      {/if}
      {#if exam.questions[currentQuestionIndex].type === 'Open'}
        <OpenQuestion question={exam.questions[currentQuestionIndex]} mode={mode} studentAnswers={studentAnswers[currentQuestionIndex.toString()]}/>
      {/if}
      {#if exam.questions[currentQuestionIndex].type === 'Spaces'}
        <BlankSpacesQuestion question={exam.questions[currentQuestionIndex]} mode={mode} studentAnswers={studentAnswers[currentQuestionIndex.toString()]}/>
      {/if}
    {/if}
  
    <!-- Navigation buttons -->
    <div class="flex space-x-4">
      <button
        class="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
        on:click={handlePrevQuestion} disabled={currentQuestionIndex === 0}
      >
        Previous Question
      </button>
      <button
        class="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
        on:click={handleNextQuestion} disabled={currentQuestionIndex === exam.questions.length - 1}
      >
        Next Question
      </button>
    </div>
  
    <!-- Submit button -->
    {#if mode === 'answer'}
      <button
        class="mt-4 bg-green-500 hover:bg-green-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
        on:click={handleSubmit}
      >
        Submit Exam
      </button>
    {:else if mode === 'view'}
      <button
        class="mt-4 bg-red-500 hover:bg-red-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
        on:click={() => console.log("leave exam")}
      >
        Leave Exam
      </button>
    {/if}
  </div>
  