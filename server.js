// Libraries
	// HTTP socket (server) requirements
	var app = require('express')();

	// Build of cpp extension
	var game = require('./lib/build/Release/game');

var fs = require('fs');
var config = JSON.parse(fs.readFileSync('config/config.json', 'utf8'));
var port = config.service.port;

// Initialize http server on specified port
app.listen(port, function () {
	console.log('[tic-tac-tree server] listening on  *: ' + port);
});

// Construct the game on the extension and send the results
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

// Server the files as are required by the client
app.get('/*', function(req, res){ 
	var name = "";
	switch(req.originalUrl){
		case "/":
			name = "index.html"; break;
		default:
			name = req.originalUrl; break;
	}
	res.sendFile( config.client.dir + name);
});