<script>
  export let question;
  export let studentAnswers;
  export let mode;
  let v = null;
  console.log(studentAnswers.response_data);

</script>

{#if mode ==="answer"}
<div class="my-4">
  <p class="text-lg font-semibold">{question.description}</p>
  <img src={question.imagePath} alt="Question image" class="w-auto h-auto" />
  
  <div class="grid grid-cols-3 mt-2">
    <div class="col-span-1">
      {#each Object.entries(question.answers) as [key, value]}
        <p>{key}</p>
      {/each}
    </div>
    <div class="col-span-1">
      {#each Object.entries(question.answers) as [key, value]}
        <label class="flex items-center">
          <input
            type="checkbox"
            name={`${question.questionId}_${key}`}
            value="true"
            on:change={() => handleChange(key, true)}
            class="mr-2"
          />
          <span class="text-sm">True</span>
        </label>
      {/each}
    </div>
    <div class="col-span-1">
      {#each Object.entries(question.answers) as [key, value]}
        <label class="flex items-center">
          <input
            type="checkbox"
            name={`${question.questionId}_${key}`}
            value="false"
            on:change={() => handleChange(key, false)}
            class="mr-2"
          />
          <span class="text-sm">False</span>
        </label>
      {/each}
    </div>
  </div>
</div>



{:else if mode === "view"}
  <div class="my-4">
    <p class="text-lg font-semibold">{question.description}</p>
    <img src={question.imagePath} alt="Question image" class="w-auto h-auto" />
    
    
    <div class="grid grid-cols-3 mt-2">
      <div class="col-span-1">
        {#each Object.entries(studentAnswers.response_data) as [key, value]}
          <p>{key}</p>
        {/each}
      </div>
      
      <div class="col-span-1">
        {#each Object.entries(studentAnswers.response_data) as [key, value]}
          <label class="flex items-center">
            <input
              type="checkbox"
              name={`${studentAnswers.questionId}_${key}`}
              value="true"
              bind:checked={value}
              disabled
              class="mr-2"
            />
            <span class="text-sm">True</span>
          </label>
        {/each}
      </div>
      <div class="col-span-1">
        {#each Object.entries(studentAnswers.response_data) as [key, value]}
            {#if value === false?v=true:v=false}{/if}
            <label class="flex items-center">
              <input
                type="checkbox"
                name={`${studentAnswers.questionId}_${key}`}
                value="false"
                bind:checked={v}
                disabled
                class="mr-2"
              />
              <span class="text-sm">False</span>
            </label>
      
        {/each}
      </div>

    </div>

    <h1>Correção</h1>

    <div class="grid grid-cols-3 mt-2">
      <div class="col-span-1">
        {#each Object.entries(question.answers) as [key, _]}
          <p>{key}</p>
        {/each}
      </div>
      
      <div class="col-span-1">
        {#each Object.entries(question.answers) as [key, value]}
          <label class="flex items-center">
            <input
              type="checkbox"
              name={`${question.questionId}_${key}`}
              value="true"
              bind:checked={value}
              disabled
              class="mr-2"
            />
            <span class="text-sm">True</span>
          </label>
        {/each}
      </div>
      <div class="col-span-1">
        {#each Object.entries(question.answers) as [key, value]}
            {#if value === false?v=true:v=false}{/if}
            <label class="flex items-center">
              <input
                type="checkbox"
                name={`${question.questionId}_${key}`}
                value="false"
                bind:checked={v}
                disabled
                class="mr-2"
              />
              <span class="text-sm">False</span>
            </label>
      
        {/each}
      </div>

    </div>
  </div>
    
  {/if}

