<script>

	import NavbarStudent from '$lib/components/navbar/NavbarStudent.svelte';

	export let mode;

</script>

{#if (mode === "lstudent" || mode === "mstudent")}

	<NavbarStudent/>

{:else}

	<p>teacher</p>

{/if}