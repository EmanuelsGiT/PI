<script>
	import { browser } from '$app/environment';

	if (browser) { // to prevent error window is not defined, because it's SSR
		window.location.href = 'http://localhost:5173/login';
	}
</script>