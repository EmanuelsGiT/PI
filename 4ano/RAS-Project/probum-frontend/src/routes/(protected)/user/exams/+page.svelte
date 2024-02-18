<script>

	import EntryItem from '$lib/components/exam/EntryItem.svelte';
	import EntryFilter from '$lib/components/exam/EntryFilter.svelte';
	import EntryListHeader from '$lib/components/exam/EntryListHeader.svelte';
	import EntryStatistics from '$lib/components/exam/EntryStatistics.svelte';
	import Navbar from '$lib/components/navbar/Navbar.svelte';

	export let data;

	const { user, exams } = data;

	const updateEntries = () => {
		// This is where the filtering occurs. Not to be implemented
	}

</script>

<svelte:head>
	<title>
		Exam Listing
	</title>
</svelte:head>

<div class="flex flex-col h-screen">

	<Navbar mode="lstudent"/>

	<div class="flex w-full flex-1 overflow-y-scroll px-40">

		<div class="flex flex-row-reverse flex-1">

			<!-- Listing Component -->
			<div class="flex flex-col items-center flex-1">

				<!-- Listing Header -->
				<EntryListHeader user={user} exams={exams}/>

				<!-- Listing Items -->
				<div class="w-full flex-1 overflow-y-scroll">
					{#if exams.length > 0}
						{#each exams as exam}
							<EntryItem exam={exam}/>
						{/each}
					{:else}
						<h1 class="text-xl text-neutral opacity-80 ml-4">
							Oops! You don't have exams assigned to your number!
						</h1>
					{/if}
				</div>

			</div>

			<!-- SideBar -->
			<div class="flex flex-col gap-2 w-1/5 ml-4">

				<div class="flex flex-col flex-1">
					<!-- Filter & Sort Menu -->
					<EntryFilter on:filtered={updateEntries}/>

					<!--Statistics -->
					<EntryStatistics {exams}/>
				</div>
			</div>

		</div>

	</div>
</div>
