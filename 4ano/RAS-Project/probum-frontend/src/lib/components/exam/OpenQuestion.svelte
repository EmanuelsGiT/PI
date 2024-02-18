<script>
  
  export let question;
  export let studentAnswers;
  export let mode;
  console.log(studentAnswers.response_data)
  
  let userAnswer = '';
  let canSkip = true;

  let maxWordLen = question.maxWordLen;
  let minWordLen = question.minWordLen;
  function checkWordLen(obj){
    var len = obj.value.split(/[\s]+/);
    if(len.length > maxWordLen){
      alert("You cannot put more than "+maxWordLen+" words in this text area.");
      obj.oldValue = obj.value!=obj.oldValue?obj.value:obj.oldValue;
      obj.value = obj.oldValue?obj.oldValue:"";
      canSkip = true;
      return false;
    }
    else if(len.length < minWordLen && len.length>0){
      canSkip = false;
      alert("You cannot put less than "+minWordLen+" words in this text area.");
      obj.oldValue = obj.value!=obj.oldValue?obj.value:obj.oldValue;
      obj.value = obj.oldValue?obj.oldValue:"";
      return false;
    }
    else if(len.length == 0){
      canSkip = true;
    }
  }
</script>

<div class="my-4">
  <p class="text-lg font-semibold">{question.description}</p>
  <img src={question.imagePath} alt="Question image" class="w-auto h-auto" />
  {#if mode==="answer"}
  
    <textarea
      bind:value={userAnswer}
      class="border rounded p-2 w-full"
      rows="4"
      on:change={checkWordLen(userAnswer)}
      placeholder="Type your answer here..."
    ></textarea>
  {:else if mode==="view"}
    <textarea
      bind:value={studentAnswers.response_data}
      class="border rounded p-2 w-full"
      rows="4"
      disabled
      placeholder="Type your answer here..."
    ></textarea>
    <h1>Correção:</h1>
    <textarea
      bind:value={question.answer}
      class="border rounded p-2 w-full"
      rows="4"
      disabled
      placeholder={question.answer}
    ></textarea>
  {/if}

</div>