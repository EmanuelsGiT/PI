<script>

    import Navbar from "$lib/components/navbar/Navbar.svelte";
    import MetadataForm from "$lib/components/create/MetadataForm.svelte";
    import QuestionsForm from "$lib/components/create/QuestionsForm.svelte";
    import SubmitForm from "$lib/components/create/SubmitForm.svelte";

    import {examStore} from "$lib/stores/create_store.js";

    import {goto} from "$app/navigation";

    export let data;

    const { user, ucs } = data;

    let stepControls = {
        currentStep: 0,
        steps: 3,
    }

    let stepState = {
        meta: true,
        questions: false,
        submit: false
    }

    const nextStep = () => {
        if (!(stepControls.currentStep === stepControls.steps - 1))
            stepControls.currentStep++;

        const key = Object.keys(stepState)[stepControls.currentStep]
        stepState[key] = true;
    }

    const prevStep = () => {
        if (!(stepControls.currentStep === 0))
            stepControls.currentStep--;

        const key = Object.keys(stepState)[stepControls.currentStep + 1]
        stepState[key] = false;
    }

    const submitExam = async (event) => {

        event.preventDefault();

        let submission;

        const unsubscribe = examStore.subscribe((store) => {
            submission = store;
        })

        unsubscribe();

        console.log(JSON.stringify(submission))

        try {

        	const response = await fetch("http://localhost:5173/api/create",
            {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(submission)
            });

        } catch (err) { console.log(err) }

        await goto("/");
    }

</script>

<svelte:head>
    <title>
        Exam Creation
    </title>
</svelte:head>

<div class="flex flex-col h-screen gap-2">

    <Navbar mode="mstudent"/>

    <div class="flex flex-col flex-1 w-full items-center px-40 my-4">

        <!-- Form Steps -->
        <ul class="steps w-full mb-4">
            <li class="step {stepState.meta ? 'step-accent' : ''}">Exam Metadata</li>
            <li class="step {stepState.questions ? 'step-accent' : ''}">Exam Composition</li>
            <li class="step {stepState.submit ? 'step-accent' : ''}">Review & Submission</li>
        </ul>


        <!-- Form Part -->
        <div class="w-full shadow-sm rounded-lg flex-1 my-4 p-4">

            {#if stepState.submit}
                <SubmitForm/>
            {:else if stepState.questions}
                <QuestionsForm/>
            {:else}
                <MetadataForm {ucs}/>
            {/if}

        </div>

        <!-- Form Controls -->
        <div class="w-full flex flex-row justify-evenly gap-2 pb-10">

            {#if stepState.submit}
                <button class="btn flex-1" on:click={prevStep}>Previous</button>
                <button class="btn flex-1 btn-primary" on:click={submitExam}>Submit</button>
            {:else}
                <button class="btn flex-1" on:click={prevStep}>Previous</button>
                <button class="btn flex-1 btn-accent" on:click={nextStep}>Next</button>
            {/if}

        </div>

    </div>

</div>

