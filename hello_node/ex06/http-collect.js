let http = require("http");
var url = process.argv[2];

if (process.argv.length > 3 || process.argv.length < 2) {
	console.log("Input arguments supports only one HTTP URL");
	return;
}

try {
	http.get(url, (res) => {
		const { status_code } = res;
		let content = "";
		let error;

		if (status_code < 200 && status_code >= 300) {
			error = new Error('Request Failed\n' + `Status Code: ${status_code}`);
		}
		if (error) {
			console.log(error.message);
			res.resume();
			return;
		}

		res.on("data", (chunk) => {
			content += chunk;
		});

		res.on("end", () => {
			console.log(content.length);
			console.log(content);
		});

		res.on('error', (err) => {
			console.log(err.message);
			return;
		});

	}).on("error", (err) => {
		console.log(err.message);
	});

} catch (error) {
	console.log(error.message);
}
