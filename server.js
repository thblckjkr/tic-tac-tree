// Libraries
// HTTP socket (server) requirements
var app = require('express')();
	
var fs = require('fs');
var config = JSON.parse(fs.readFileSync('config/config.json', 'utf8'));
var port = config.service.port;

// Files to client
var filesRoute = __dirname + "/client/";

var gamepad = [
	[0, 0, 0],
	[0, 0, 0],
	[0, 0, 0]
]

var game = require('./lib/build/Release/game');
console.log(game.test(gamepad));

/*

// Initialize http server on specified port
app.listen(port, function () {
	console.log('[tic-tac-tree server] listening on  *: ' + port);
});

app.get('/', function (req, res) {
	res.sendFile("index.html", { root: filesRoute });
});

app.get('/css/styles.css', function (req, res) {
	res.sendFile("css/styles.css", { root: filesRoute });
});

app.get('/js/game-client.js', function (req, res) {
	res.sendFile("js/game-client.js", { root: filesRoute });
});
*/