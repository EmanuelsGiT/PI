<script>

	export let user;
	export let exams;

</script>


<header class="w-full px-4">
	<div class="flex items-center gap-2">
		<h1 class="text-2xl"><span class="font-bold">{user.Name}</span>'s Available Exams</h1>
		<p class="badge badge-outline mt-2">{exams.length} Entries</p>
		<div class="join ml-auto mt-2">
			<button class="join-item btn btn-sm btn-active">1</button>
			<button class="join-item btn btn-sm">2</button>
			<button class="join-item btn btn-sm">3</button>
			<button class="join-item btn btn-sm">4</button>
		</div>
	</div>
	<div class="divider mt-1"></div>
</header>