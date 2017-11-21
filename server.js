// Libraries
// HTTP socket (server) requirements
var app = require('express')();
	
var fs = require('fs');
var config = JSON.parse(fs.readFileSync('config/config.json', 'utf8'));
var port = config.service.port;

var game = require('./lib/build/Release/game');

// Initialize http server on specified port
app.listen(port, function () {
	console.log('[tic-tac-tree server] listening on  *: ' + port);
});

app.get('/api/tree', function (req, res) {
	if (typeof(req.query.gamepad) !== "undefined") {
		gamepad = JSON.parse(req.query.gamepad);	
	} else {
		// Set a near winner if it's not defined
		gamepad = [
			[1, 1, 0],
			[0, 2, 2],
			[0, 0, 0]
		]
	}

	var next = req.query.next;
	
	console.time("GameConstruct");
	var tree = game.getTree(gamepad, next);
	console.timeEnd("GameConstruct");

	console.time("Stringify");
	var data = JSON.stringify(tree);
	console.timeEnd("Stringify");

	res.setHeader('Content-Type', 'application/json');
	res.send(data);
	res.end();
});

app.get('/', function (req, res) {
	res.sendFile("index.html", { root: config.client.dir });
});

app.get('/css/styles.css', function (req, res) {
	res.sendFile("css/styles.css", { root: config.client.dir });
});

app.get('/js/game-client.js', function (req, res) {
	res.sendFile("js/game-client.js", { root: config.client.dir });
});

app.get('/js/tree.js', function (req, res) {
	res.sendFile("js/tree.js", { root: config.client.dir });
});