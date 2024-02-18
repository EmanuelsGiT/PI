<script>

    import Icon from '@iconify/svelte';
    import Navbar from '$lib/components/navbar/Navbar.svelte';

	import {Check} from "lucide-svelte";

	import {onMount} from "svelte";
    import {goto} from "$app/navigation";

    export let data;

    const {user, exam} = data;

    let questions = exam.questions;

    const controls = {
        questionIndex: 0,
        answers: {}
    }

    for (const question of questions) {

        const response_data = {...question.answer}

        for (const opt in Object.keys(response_data)) {
            response_data[opt] = false;
        }

        controls.answers[question.question_id] = {question_id: question.question_id, response_data: response_data}
    }

    const next = () => {
        if (controls.questionIndex === exam.questions.length - 1) controls.questionIndex = 0;
        else controls.questionIndex++;
    }

    const prev = () => {
        if (controls.questionIndex === 0) controls.questionIndex = exam.questions.length - 1;
        else controls.questionIndex--;
    }

    const submit = async (event) => {

        event.preventDefault();

		const submission = {
			student_id: user.UId,
			exam_id: exam.id,
			responses: Object.values(controls.answers)
		};

        try {

            const response = await fetch("http://localhost:5173/api/solve",
                {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(submission)
                });

        } catch (err) { console.log(err) }

        await goto("/user/exams");
    }

	let totalTime = exam.duration;
	let elapsedTime = totalTime;

	const startTimer = () => {
		const timer = setInterval(() => {
			elapsedTime--;
			if (elapsedTime >= totalTime) {
				clearInterval(timer);
				submit();
			}
		}, 1000 * 60);
	};

	onMount(() => {
		startTimer();
	})

</script>

<svelte:head>
    <title>
        Exam
    </title>
</svelte:head>

<div class="flex flex-col h-screen">

    <Navbar mode="lstudent"/>

    <div class="flex w-full flex-1 overflow-y-scroll px-40 my-4">

        <div class="flex flex-1 flex-col mx-12 my-8">

            <div class="flex flex-row justify-between items-center outline-2 outline-black h-fit bg-base-100">

                <section>

                    <p class="text-2xl font-semibold">{exam.subject} <span class="text-sm opacity-70 font-normal">(scored to {exam.max_score}
                        )</span></p>
                    <p class="opacity-70">{exam.description}</p>

                </section>

                <div class="flex flex-col-reverse justify-center items-center gap-2">

                    <div>
                        <button on:click={prev} class="btn btn-square btn-primary btn-sm">
                            <Icon icon="mingcute:left-line"></Icon>
                        </button>

                        <button on:click={next} class="btn btn-square btn-primary btn-sm">
                            <Icon icon="mingcute:right-line"></Icon>
                        </button>

                        <button on:click={submit} class="btn btn-accent btn-sm">
                            <Check size={16}/>
                            Submit
                        </button>
                    </div>

                    <span class="font-semibold">
						Question {controls.questionIndex + 1}
					</span>

                </div>

            </div>

			<div class="w-full mt-4 flex flex-row items-center gap-4">
				<div class="flex-1">
					<input type="range" min="0" max={totalTime} bind:value={elapsedTime} class="range range-primary range-xs cursor-auto" disabled/>
				</div>
				<p class="font-semibold pb-1">{elapsedTime} minutes</p>
			</div>

            <div class="">

                {#if exam.questions[controls.questionIndex].question_type === "MULTIPLE_CHOICE"}
                    {@const q=exam.questions[controls.questionIndex]}

                    <div class="flex flex-col-reverse gap-8 items-center">
                        <section class="break-words">
                            <p class="font-semibold"><span class="text-lg font-normal pr-2">{controls.questionIndex + 1}
                                .</span> {q.description} <span class="text-primary">({q.points}v.)</span></p>

                            <p class="mt-2">Select from:</p>
                            {#each Object.keys(q.answer) as opt, i}

							<span class="flex flex-row gap-2 items-center">

								<label class="label cursor-pointer">
									<input type="checkbox" class="checkbox"
                                           bind:checked={controls.answers[q.question_id].response_data[opt]}/>
								</label>

								<span class="break-words">{opt}</span>

							</span>

                            {/each}

                        </section>

                        {#if q.image_path !== "No source"}
                            <img src={q.image_path} alt="question" class="mt-2 w-fit max-w-[800px] rounded-lg">
                        {/if}

                    </div>
                {/if}

            </div>

        </div>

    </div>

</div>

