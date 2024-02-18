<script>

    import {examStore} from "$lib/stores/create_store.js";
    import QuestionItem from "$lib/components/create/questions/QuestionItem.svelte";

</script>


<header>
    <h1 class="text-3xl font-bf">Review the Exam</h1>
    <p class="opacity-80">Review and submit the exam, or go back to edit</p>
</header>

<div class="divider mt-0"></div>

<div class="shadow-xl bg-base-200 p-4 rounded-xl">

    <div class="flex flex-col w-full gap-4">

        <section class="flex flex-row justify-between items-center w-full">

            <div class="">
                <p class="text-2xl font-semibold">{$examStore.subject} <span class="text-sm opacity-70 font-normal">(scored to {$examStore.max_score})</span></p>
                <p class="opacity-70">{$examStore.description}</p>
            </div>

            <div class="flex flex-col text-right">
                <p class="opacity-70">Reservation '{$examStore.reservation}'</p>
                <p class="opacity-70">{$examStore.duration} minutes</p>
            </div>

        </section>

        {#each $examStore.questions as question, id}
            <QuestionItem {question} {id} viewOnly={true}/>
        {/each}

    </div>

</div>

