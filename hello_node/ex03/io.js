var fs = require('fs');
try {
	var input_texts = fs.readFileSync(process.argv[2], 'utf-8');
} catch (err) {
	console.log(err.message);
	return;
}
var n = 0;

for (let i = 0; input_texts[i]; i++){
	if (input_texts[i] == '\n')
		n++;
}
console.log(n);
