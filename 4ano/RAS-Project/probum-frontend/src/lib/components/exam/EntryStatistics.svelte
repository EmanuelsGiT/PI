<script>

	export let exams;

	const applyMetrics = (exams) => {

		let metrics = {};

		for (const e of exams) {
			if (e.uc in metrics) metrics[e.subject] += 1;
			else {
				metrics[e.subject] = 1;
			}
		}

		const sortedMetricEntries = Object.entries(metrics)
			.sort((a, b) => b[1] - a[1]); // Sort in descending order based on the values

		return Object.fromEntries(sortedMetricEntries);

	}

	const examMetrics = applyMetrics(exams);
	const totalSum = Object.values(examMetrics).reduce((acc, currentValue) => acc + currentValue, 0);

</script>

<!-- Statistics -->
<section class="flex flex-col bg-base-200 rounded-lg mb-4 flex-1 mr-4 shadow-md p-4">

	<header>
		<h1 class="text-lg font-bold">Statistics</h1>
		<div class="divider mt-0"></div>
	</header>


	<div class="flex flex-col h-[320px] overflow-y-scroll scrollbar-hide">

		{#each Object.entries(examMetrics) as [uc, count]}
			<div class="w-full">

				<div class="flex flex-row">
					<p class="label-text">{uc}</p>
					<span class="label-text ml-auto pr-2">{count}</span>
				</div>
				<progress class="progress progress-accent w-full" value={(count * 100)/totalSum} max="100"></progress>

			</div>
		{/each}

	</div>

</section>
