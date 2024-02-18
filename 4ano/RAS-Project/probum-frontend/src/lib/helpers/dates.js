export function calculateTimeUntilDate(targetDate) {

	const target = new Date(targetDate);
	const now = new Date();

	const timeDifference = target - now;

	if (target.getDate()     === now.getDate()  &&
		  target.getMonth()    === now.getMonth() &&
			target.getFullYear() === now.getFullYear()
	) {
		return 'today';
	}

	if (timeDifference < 0) {
		return 'expired';
	}

	const days = Math.floor(timeDifference / (1000 * 60 * 60 * 24));

	return `${days} day(s)`;
}

export function formatDate(dateString) {
	const date = new Date(dateString);

	const day = date.getDate().toString().padStart(2, '0');
	const month = (date.getMonth() + 1).toString().padStart(2, '0');
	const year = date.getFullYear().toString();
	const hours = date.getHours().toString().padStart(2, '0');
	const minutes = date.getMinutes().toString().padStart(2, '0');

	return `${day}-${month}-${year} at ${hours}:${minutes}`;
}

