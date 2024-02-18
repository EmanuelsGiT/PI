<script>

    import { examStore } from "$lib/stores/create_store.js";

    export let ucs;

</script>

<header>
    <h1 class="text-3xl font-bf">Exam Metadata</h1>
    <p class="opacity-80">Fill in the inputs about the exam general information</p>
</header>

<div class="divider mt-0"></div>

<div class="flex flex-row w-full gap-4">

    <div class="flex flex-col gap-2 w-1/5">

        <label class="form-control w-full max-w-xs">
        <span class="label">
            <span class="label-text">Exam Subject</span>
        </span>
            <select class="select select-bordered" bind:value={$examStore.subject}>
                <option disabled selected>Subject</option>
                {#each ucs as u}
                    <option>{u}</option>
                {/each}
            </select>
        </label>

        <label class="form-control w-full max-w-xs">
        <span class="label">
            <span class="label-text">Exam Type</span>
        </span>
            <select class="select select-bordered" bind:value={$examStore.exam_type}>
                <option disabled selected>Type</option>
                <option>EXAM</option>
                <option>WORK ASSIGNMENT</option>
                <option>HOMEWORK</option>
            </select>
        </label>

        <label class="form-control w-full max-w-xs">
        <span class="label">
            <span class="label-text">Exam Duration</span>
        </span>
            <input type="range" min="60" max="180" bind:value={$examStore.duration} class="range range-primary range-sm" step="30" />
            <div class="w-full flex justify-between text-xs px-2 pt-1">
                <span>1h</span>
                <span>1h30</span>
                <span>2h</span>
                <span>2h30</span>
                <span>3h</span>
            </div>
        </label>

        <label class="form-control w-full max-w-xs">
        <span class="label">
            <span class="label-text">Exam Max. Score</span>
        </span>
            <input type="number" class="input input-bordered" placeholder="20" bind:value={$examStore.max_score}/>
        </label>

        <label class="form-control w-full max-w-xs">
        <span class="label">
            <span class="label-text">Exam Date</span>
        </span>
            <div class="join">
                <input class="input input-bordered join-item" type="datetime-local"/>
                <button class="btn join-item btn-primary">Check</button>
            </div>
        </label>

        <label class="form-control w-full">
        <span class="label">
            <span class="label-text">Enrolled List</span>
        </span>
            <input type="file" class="file-input file-input-primary w-full max-w-xs" />
        </label>

    </div>

    <div class="flex-1">

        <label class="form-control">
        <span class="label">
            <span class="label-text">Exam Description</span>
        </span>
            <textarea bind:value={$examStore.description} class="textarea textarea-bordered resize-none" rows="17" placeholder="Exam description"></textarea>
        </label>

    </div>

</div>


