<script>

    import {Plus, Trash} from 'lucide-svelte';
    import QuestionItem from "$lib/components/create/questions/QuestionItem.svelte";
    import {examStore} from "$lib/stores/create_store.js";

    let questions = [];

    let options = [
        {
            id: 0,
            stat: "#0 A truthful statement!",
            value: true
        }
    ];

    let counter = 1;
    let current = {
        question_type: "MULTIPLE_CHOICE",
        points: 0,
        image_path: "",
        description: "",
        answer: {}
    };

    const newOption = () => {

        options[counter] = {
            id: counter + 1,
            stat: `#${counter} A false statement!`,
            value: false
        }
        counter++;
    }

    const removeOption = (id) => {
        options = options.filter((opt) => {
            return opt.id !== id;
        })
        counter--;
    }

    const getLeftPoints = () => {
        let sum = 0;
        for (const question in questions) {
            sum += question.points;
        }
        return $examStore.max_score - sum;
    }

    const saveQuestion = () => {

        for (const opt of options) {
            current.answer[opt.stat] = opt.value
        }

        examStore.update(store => {
            store.questions = [...store.questions, current];
            return store;
        });

        current = {
            question_type: "MULTIPLE_CHOICE",
            points: 0,
            image_path: "",
            description: "",
            answer: {}
        }

        options = [
            {
                id: 0,
                stat: "#0 A truthful statement!",
                value: true
            }
        ];

        counter = 1;

        const modal = document.getElementById("question_form");
        modal.close();

        console.log("Saved!")
    }

</script>

<header>
    <h1 class="text-3xl font-bf">Exam Questions</h1>
    <p class="opacity-80">Add or edit questions to the exam</p>
</header>

<div class="divider mt-0"></div>

{#each $examStore.questions as question, id}
    <QuestionItem {question} {id}/>
{/each}

<div class="flex flex-row w-full gap-4">

    <button class="btn w-full btn-primary" onclick="question_form.showModal()">
        <Plus color="#150f10" size={20}/>
        <span class="text-md">Add Question</span>
    </button>

    <dialog id="question_form" class="modal">
        <div class="modal-box">

            <h3 class="font-bold text-lg">Question #{questions.length + 1}</h3>

            <div>

                <div class="flex flex-row gap-2">

                    <label class="form-control w-full">
                    <span class="label">
                        <span class="label-text">Question Type</span>
                    </span>
                        <select class="select select-bordered">
                            <option>Multiple Choice</option>
                            <option disabled>Open</option>
                            <option disabled>True or False</option>
                        </select>
                    </label>

                    <label class="form-control">
                        <span class="label">
                            <span class="label-text">Question Points <span class="badge badge-info">{getLeftPoints()}pts. left</span></span>
                        </span>
                        <input max={getLeftPoints()} type="number" class="input input-bordered" placeholder="Enter the statement here" bind:value={current.points}/>
                    </label>

                </div>


                <h3 class="font-bold text-lg mt-4">Question Definition</h3>

                {#if current.question_type === "MULTIPLE_CHOICE"}

                    <div class="">

                        <label class="form-control w-full">
                        <span class="label">
                            <span class="label-text">Question Statement</span>
                        </span>
                            <input type="text" class="input input-bordered" placeholder="Enter the statement here" bind:value={current.description}/>
                        </label>

                        <label class="form-control w-full">
                        <span class="label">
                            <span class="label-text">Image Path (Optional)</span>
                        </span>
                            <input type="text" class="input input-bordered" placeholder="Enter the statement here" bind:value={current.image_path}/>
                        </label>

                        <span class="label">
                                <span class="label-text">Multiple Choice Options</span>
                        </span>

                        {#each options as opt}
                            <div class="form-control pb-2">
                                <label class="cursor-pointer flex items-center gap-2">
                                    <input type="checkbox" bind:checked={opt.value} class="checkbox checkbox-accent" />
                                    <input type="text" class="input input-bordered flex-1" bind:value={opt.stat}/>
                                    <button class="btn btn-neutral btn-circle" on:click={() => {removeOption(opt.id)}}>
                                        <Trash size={18}/>
                                    </button>
                                </label>
                            </div>
                        {/each}

                        <button class="btn btn-sm w-full btn-accent mt-4" on:click={newOption}>
                            <Plus color="#150f10" size={20}/>
                        </button>

                    </div>
                {/if}

            </div>


            <div class="modal-action">
                <form method="dialog">
                    <!-- if there is a button in form, it will close the modal -->
                    <button class="btn">Close</button>
                </form>
                <button class="btn btn-primary" on:click={saveQuestion}>Save</button>
            </div>

        </div>
    </dialog>

</div>


