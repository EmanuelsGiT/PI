<script>

    export let question;

    export let answer;

    export let id;

    const { score, responses } = answer;

</script>

<div class="w-full rounded-lg p-4 my-4">

    <div class="flex flex-row items-center justify-between">
        <header class="text-lg font-bold">
            Question #{id + 1}: <span class="font-normal">{question.description}</span>
        </header>

        <div class="flex flex-row items-center gap-2">
            <div class="badge {`badge badge-neutral`}">{score} / {question.points} points</div>
        </div>
    </div>

    <div class="divider mt-0"></div>

    <div class="flex flex-row justify-evenly">

        <div class="flex-1">
            <p class="mb-2 badge badge-primary">Yours:</p>
            {#each Object.keys(responses.response_data) as opt}

                <div class="form-control pb-2">
                    <label class="cursor-pointer flex items-center gap-2">
                        <input type="checkbox" checked={responses.response_data[opt]} disabled class="checkbox disabled"/>
                        <span>{opt}</span>
                    </label>
                </div>

            {/each}
        </div>

        <div class="flex-1">
            <p class="mb-2 badge badge-secondary">Correct:</p>

            {#each Object.keys(question.answer) as opt}

                <div class="form-control pb-2">
                    <label class="cursor-pointer flex items-center gap-2">
                        <input type="checkbox" checked={question.answer[opt]} disabled class="checkbox disabled" />
                        <span>{opt}</span>
                    </label>
                </div>

            {/each}
        </div>

    </div>

</div>