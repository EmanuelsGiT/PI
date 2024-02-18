
<script>
export let question;
export let studentAnswers;
export let mode;

let selectedOptions = [];

function handleChange(event) {
    // Update the selected options array based on user input
    const option = event.target.value;
    if (event.target.checked) {
    selectedOptions = [...selectedOptions, option];
    } else {
    selectedOptions = selectedOptions.filter((selected) => selected !== option);
    }

    // You can log or use the selectedOptions array as needed
    console.log(`Question ${question.questionId} selected options:`, selectedOptions);
}
</script>


<div class="my-4">
    <p class="text-lg font-semibold">{question.description}</p>
    <img src={question.imagePath} alt="Question image" class="w-auto h-auto" />


    {#if mode==="answer"}
        <div class="mt-2">
            {#each Object.entries(question.answers) as [key, answer]}
            <div class="flex items-center space-x-4">
                <label class="flex items-center">
                <input type="checkbox" name={question.questionId} value={key} on:change={handleChange} class="mr-2" />
                <span class="mr-2">{key}</span>

                </label>
            </div>
            {/each}
        </div>
    
    {:else if mode==="view"}
        <div class="mt-2">
            {#each Object.entries(studentAnswers.response_data) as [key, answer]}
            <div class="flex items-center space-x-4">
                <label class="flex items-center">
                <input
                type="checkbox"
                name={`${studentAnswers.questionId}_${key}`}
                value="true"
                bind:checked={answer}
                disabled
                class="mr-2"
                />
                <span class="mr-2">{key}</span>
                </label>
            </div>
            {/each}
        </div>
        <h1>Correção:</h1>
        <div class="mt-2">
            {#each Object.entries(question.answers) as [key, answer]}
            <div class="flex items-center space-x-4">
                <label class="flex items-center">
                <input
                type="checkbox"
                name={`${question.questionId}_${key}`}
                value="true"
                bind:checked={answer}
                disabled
                class="mr-2"
                />
                <span class="mr-2">{key}</span>
                </label>
            </div>
            {/each}
        </div>
        

    {/if}







</div>