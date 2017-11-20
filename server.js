// Libraries
// HTTP socket (server) requirements
var app = require('express')();
	
var fs = require('fs');
var config = JSON.parse(fs.readFileSync('config/config.json', 'utf8'));
var port = config.service.port;

var gamepad = [
	[1, 0, 0],
	[0, 2, 0],
	[1, 0, 0]
]

var game = require('./lib/build/Release/game');

// Initialize http server on specified port
app.listen(port, function () {
	console.log('[tic-tac-tree server] listening on  *: ' + port);
});

app.get('/api/tree', function (req, res) {
	var tree = game.getTree(gamepad);
	var data = JSON.stringify(tree);

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