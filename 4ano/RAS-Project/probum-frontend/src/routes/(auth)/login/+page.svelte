
<script>

	import { enhance } from "$app/forms";

	import { superForm } from 'sveltekit-superforms/client';
	import Icon from '@iconify/svelte';

	export let data;

	const { form, errors } = superForm(data.form);

	let eyeState = true;
	const eyeToggle = () => {

		const passwordInput = document.getElementById("password");

		if (passwordInput?.type === "password") passwordInput.type = "text";
		else passwordInput.type = "password";

		eyeState = !eyeState;
	}

	let buttonContent = "Sign In";
	let loading = false;

	const submitHandler = () => {

		loading = true;
		buttonContent = "Signing In..."

		return async ({ update }) => {
			await update();
			loading = false;
			buttonContent = "Sign In"
		}
	}

</script>

<svelte:head>
	<title>
		Probum Sign In
	</title>
</svelte:head>

<div class="flex justify-center items-center h-screen flex-col flex-1">

	<div class="card w-1/3 shadow-xl bg-base-100">

		<!-- Card Body (Title, Form, Sign In Button, Continue With)-->
		<div class="card-body">

			<!-- Title -->
			<h1 class="font-bold text-4xl text-center tracking-wider">
				PROBUM
			</h1>

			<h2 class="text-text_base text-center gap-2 text-2xl">Sign In</h2>

			<!-- Card Body and Form -->
			<form method="POST" class="pt-4" use:enhance={submitHandler}>

				<label class="label" for="email">
					<span class="label-text">Insert your email:</span>
				</label>
				<input
					id="email"
					name="email"
					type="text"
					placeholder="Email"
					class="input input-bordered w-full"
					disabled={loading}
					bind:value={$form.email}/>

				{#if $errors.email}
					<small class="text-error">{$errors.email}</small>
				{/if}

				<!-- Password -->
				<label for="password" class="label pt-4">
					<span class="label-text">Insert your password:</span>
				</label>
				<div class="form-control">
					<div class="join">
						<input id="password"
									 name="password"
									 type="password"
									 placeholder="Password"
									 class="input input-bordered w-full join-item"
									 disabled={loading}
						/>

						<button id="passwordIconBtn" type="button" class="btn join-item btn-primary" on:click={eyeToggle}>
							{#if eyeState}
								<Icon icon="mdi:eye-outline" style="font-size: 26px"/>
							{:else}
								<Icon icon="mdi:eye-closed" style="font-size: 26px"/>
							{/if}
						</button>

					</div>
				</div>
				{#if $errors.password}
					<small class="text-error">{$errors.password}</small>
				{/if}

				<label class="label cursor-pointer pt-6 justify-start" for="remember">
					<input id="remember" name="remember" type="checkbox" class="checkbox checkbox-primary checkbox-sm mr-2" />
					<span class="text-md">Remember Me</span>
				</label>
				{#if $errors.general}
					<small class="text-error">{$errors.general}</small>
				{/if}

				<div class="pt-4">
					<button class="btn btn-primary w-full" disabled={loading}>{buttonContent}</button>
				</div>

			</form>

		</div>
	</div>
</div>