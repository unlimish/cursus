const net = require('net');
require('date-utils');

if (process.argv.length != 3) {
	console.log('Invalid amount of arguments');
	return;
}

if (isNaN(process.argv[2]) == true) {
	return(console.log('Input valid port number'));
}

var port = process.argv[2];

try {
	net.createServer(function (socket) {
		var dt = new Date().toFormat('YYYY-MM-DD HH24:MI');

		socket.write(`${dt}\r\n`);
		socket.on('error', function (err) {
			return(console.log(err.message));
		})
		socket.end();
	}).listen(port, "localhost").on('error', function (err) {
		return (console.log(err.message));
	});
} catch (error) {
	console.log(error.message);
	return;
}
