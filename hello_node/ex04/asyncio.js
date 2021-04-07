var fs = require('fs');
try {
	fs.readFile(process.argv[2], 'utf8', (err, data) => {
		if (err) {
			console.log(err.message);
			return;
		} else {
			console.log(data.toString().split("\n").length - 1);
		}
	})

} catch (error) {
	return (console.log(error.message));
}
