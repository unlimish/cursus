const http = require('http');
const url = require('url');

if (process.argv.length != 3) {
	console.log('Invalid amount of arguments');
	return;
}

if (isNaN(process.argv[2]) == true) {
	return(console.log('Invalid value. Input port number'))
}

const port = process.argv[2];

try {
	http.createServer(function (req, res ) {
		if (req.method === 'GET') {
			var parsedURL = url.parse(req.url, true);
			var path = parsedURL.pathname;
			var dt = new Date(parsedURL.query.iso);
			if (path === '/api/parsetime')
			{
				var result = {
					hour: dt.getUTCHours(),
					minute: dt.getMinutes(),
					second: dt.getSeconds()
				};
			}
			else if (path === '/api/unixtime') {
				var result = {unixtime: dt.getTime()};
			} else {
				console.log('Invalid api path')
				res.end(null);
			}
			if (result) {
				res.writeHead(200, {'content-type': 'application/json'});
				res.end(JSON.stringify(result));
			}
		} else {
			(console.log('Send request via GET'));
			res.end(null);
		}
	}).listen(port, 'localhost').on("error", err => console.log(err.message));
} catch (error) {
	console.log(error.message);
	return;
}
