// Libraries
// HTTP socket (server) requirements
var app = require('express')();
	
var fs = require('fs');
var config = JSON.parse(fs.readFileSync('config/config.json', 'utf8'));
var port = config.service.port;

// Files to client
var filesRoute = __dirname + "/client/";

var gameng = require('./lib/build/Release/game');
gameng.set(function (gamepad) {
	console.log("Response received");
	console.log(gamepad);
})
/*
// Initialize http server on specified port
app.listen(port, function () {
	console.log('[tic-tac-tree server] listening on  *: ' + port);
});

app.get('/', function (req, res) {
	res.sendFile("index.html", { root: filesRoute });
});
*/