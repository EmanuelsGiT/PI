<script>

    import {X} from "lucide-svelte";
    import {examStore} from "$lib/stores/create_store.js";

    export let question;
    export let id;

    export let viewOnly = false;

    const deleteQuestion = () => {
        examStore.update(store => {
            store.questions.splice(id, 1);
            return store;
        });
    };

</script>

<div class="w-full rounded-lg p-4 my-4">

    <div class="flex flex-row items-center justify-between">
        <header class="text-lg font-bold">Question #{id + 1}: <span class="font-normal">{question.description}</span></header>

        <div class="flex flex-row items-center gap-2">
            <div class="badge badge-accent">{question.points} points</div>
            {#if !viewOnly}
                <button class="btn btn-sm btn-outline btn-square" on:click={() => {deleteQuestion()}}>
                    <X size={18}/>
                </button>
            {/if}
        </div>
    </div>

    <div class="divider mt-0"></div>

    {#each Object.keys(question.answer) as opt}

        <div class="form-control pb-2">
            <label class="cursor-pointer flex items-center gap-2">
                <input type="checkbox" checked={question.answer[opt]} disabled class="checkbox disabled" />
                <span>{opt}</span>
            </label>
        </div>

    {/each}

</div>