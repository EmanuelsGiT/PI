<script>
  export let mode;
  export let question;
  export let studentAnswers;
  export let userAnswers = Array.from({ length: Object.keys(question.answers).length }, () => []);

  let splitAnswers = question.description.split(/{-\d-}/);
  let i = -1;
  let iAux = -1;

  function handleInput(event, index) {
    userAnswers[index] = event.target.value;
  }
</script>

<style>
  .flex-container {
    display: flex;
    flex-wrap: wrap;
    gap: 8px;
  }

  .word-span {
    margin-right: 8px;
  }

  .input-field {
    flex: 1;
    max-width: 100px; /* Adjust the max-width as needed */
  }
</style>

<img src={question.imagePath} alt="Question image" class="w-auto h-auto" />
<div class="my-4">
  {#if mode === "answer"}
    <div class="flex-container">
      {#each splitAnswers as sa, index (index)}
        {#if sa !== ""}
          <span class="word-span">{sa}</span>
          <input type="text" value={userAnswers[index]} on:input={(e) => handleInput(e, index)} class="input-field border rounded p-1" />
        {/if}
      {/each}
    </div>
  {:else if mode === "view"}
    <div class="flex-container">
      {#each splitAnswers as sa, index (index)}
        {#if sa !== ""}
          <span class="word-span">{sa}</span>
          <input type="text" value={studentAnswers.response_data[index]} class="input-field border rounded p-1" disabled />
        {/if}
      {/each}
    </div>
    <h1>Correção:</h1>
    <div class="flex-container">
      {#each splitAnswers as sa, index (index)}
        {#if sa !== ""}
          <span class="word-span">{sa}</span>
          <input type="text" value={question.answers[index]} class="input-field border rounded p-1" disabled />
        {/if}
      {/each}
    </div>
  {/if}
</div>
