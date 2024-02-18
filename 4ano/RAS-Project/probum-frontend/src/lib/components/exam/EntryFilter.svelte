<script>

	import { createEventDispatcher } from 'svelte';

	let sortBy = "";
	let order = "";

	let filters = {};

	const setDefaults = () => {

		sortBy = "Date";
		order = "Ascending";

		filters = {
			"Today": {
				value: true,
				color: "success"
			},
			"In ? day(s)": {
				value: true,
				color: "warning"
			},
			"Expired": {
				value: true,
				color: "error"
			}
		};
	}

	setDefaults();
	const dispatch = createEventDispatcher();

	const onApply = () => {
		dispatch('filtered', { sortBy, order, filters });
	}

	const onReset = () => {
		setDefaults()
	}

</script>

<section class="flex flex-col bg-base-200 rounded-lg mb-2 shadow-md mr-4 h-fit">

	<!-- Menu -->
	<div class="p-4">

		<header>
			<h1 class="text-lg font-bold">Sort & Filter</h1>
			<div class="divider mt-0"></div>
		</header>

		<div class="flex flex-col">
			<label class="form-control w-full max-w-xs">

				<!-- Sort -->
				<div class="label">
					<span class="label-text">Sort by:</span>
				</div>

				<select class="select select-bordered select-sm" bind:value={sortBy}>
					<option>Date</option>
					<option>Course Name</option>
					<option>Type</option>
					<option>Duration</option>
				</select>

				<div class="label">
					<span class="label-text">Sort order:</span>
				</div>

				<select class="select select-bordered select-sm" bind:value={order}>
					<option selected>Ascending</option>
					<option>Descending</option>
				</select>

				<div class="divider"/>

				<!-- Filters -->
				<div class="flex flex-col gap-2">

					<p class="label-text"> Filter by: </p>

					{#each Object.keys(filters) as f}
						<label class="flex flex-row gap-2 items-center cursor-pointer">
							<input type="checkbox" class="checkbox checkbox-sm checkbox-base-200" bind:checked={filters[f].value}/>
							<span class="label-text"><span class={`badge badge-${filters[f].color}`}>{f}</span></span>
						</label>
					{/each}

				</div>
			</label>

			<!-- Buttons -->
			<div class="mt-6 flex flex-row space-evenly w-full gap-2">
				<button class="btn btn-sm btn-accent w-1/2" on:click={onApply}>Apply</button>
				<button class="btn btn-sm btn-secondary w-1/2" on:click={onReset}>Reset</button>
			</div>

		</div>


	</div>

</section>
