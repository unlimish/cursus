const { rejects } = require("assert");
let http = require("http");

if (process.argv.length != 5) {
	console.log("Input 3 HTTP URLs");
	return;
}

try {
	function get_http_data(url) {
		return (new Promise((resolve, reject) => {
			try {
				http.get(url, (res) => {
					const { status_code } = res;
					let content = "";
					let error;
					res.setEncoding("utf8");

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
						resolve(content);
					});

					res.on('error', (err) => {
						reject(err);
					});

				}).on("error", (err) => {
					reject(err);
				});
			} catch(err) {
				reject(err);
			}
		})).catch(err=>{
			return(err.message);
		});
	}
} catch (error) {
	return (error.message);
}
const result = [];
async function main() {
	var arg_i = 2;
	var result_i = 0;
	while(process.argv.length > arg_i) {
		result[result_i] = get_http_data(process.argv[arg_i]);
		arg_i++;
		result_i++;
	}
	var result_amount = result_i;
	result_i = 0;
	while(result_amount > result_i)
		console.log(await result[result_i++]);
};
main();
