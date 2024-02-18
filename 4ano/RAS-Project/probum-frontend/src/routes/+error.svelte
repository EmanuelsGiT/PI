<script>

    import { page } from '$app/stores';

    const back = () => {
        window.history.back();
    }

</script>

<div class="h-screen w-full flex flex-col justify-center items-center">

    <h1 class="text-4xl">{$page.status}</h1>
    <p>{$page.error.message}</p>

    <button class="btn btn-sm btn-primary mt-2" on:click={back}>
        Go Back
    </button>

</div>
