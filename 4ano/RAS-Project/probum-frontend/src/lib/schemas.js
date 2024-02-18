import {z} from "zod";

export const loginSchema = z.object({

	email: z.string().email({message: "Invalid email address."}),
	password: z.string({
		required_error: "Please fill in the password field.",
		invalid_type_error: "Password must be a string."
	}).min(1),
	remember: z.boolean()

});