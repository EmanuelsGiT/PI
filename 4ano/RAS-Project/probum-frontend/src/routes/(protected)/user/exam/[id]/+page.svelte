<script>

    import {examStore} from "$lib/stores/create_store.js";

    import Navbar from "$lib/components/navbar/Navbar.svelte";
    import QuestionItemCorrection from "$lib/components/create/questions/QuestionItemCorrection.svelte";

    export let data;

    const { exam, status } = data;

    const stars = Math.ceil((status.exam_score / exam.max_score) * 5);

    const getUserResponses = (id) => {
        for (const question of status.answers) {
            if (question.question_id === id) {
                return question
            }
        }
    }

</script>

<svelte:head>
    <title>
        Exam Details
    </title>
</svelte:head>

<Navbar mode="lstudent"></Navbar>

<div class="w-full px-40 py-4">

    <header class="text-center">
        <h1 class="text-3xl font-bf">Exam Revision</h1>
        <p class="opacity-80">Here you can check out what went wrong (or right) as well as your grade!</p>
    </header>

    <div class="divider mt-0"></div>

    <div class="shadow-xl bg-base-200 p-4 rounded-xl">

        <div class="flex flex-col w-full gap-4">

            <section class="flex flex-row justify-between items-center w-full px-2">

                <div class="">
                    <p class="text-2xl font-semibold">{exam.subject}</p>
                    <p class="opacity-70">{exam.description}</p>
                </div>

                <div class="flex flex-col gap-2 items-center">

                    <div class="rating rating-md">
                        {#each {length: 5} as _, i}
                            {#if i+1 === stars}
                                <input type="radio" name="rating-6" class="mask mask-star-2 bg-orange-400 cursor-default" disabled checked/>
                            {:else}
                                <input type="radio" name="rating-6" class="mask mask-star-2 bg-orange-400 cursor-default" disabled/>
                            {/if}
                        {/each}
                    </div>

                    Grade {status.exam_score}/{exam.max_score}
                </div>


            </section>

            {#each exam.questions as question, id}
                <QuestionItemCorrection {question} answer={{score: status.question_score[question.question_id], responses: getUserResponses(question.question_id)}} {id}/>
            {/each}

        </div>

    </div>

</div>