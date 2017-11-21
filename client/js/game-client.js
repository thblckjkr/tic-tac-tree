/** D3.js dependent game drawe **/
var Game = function () {
	this.contID = "gamepad";
	this.nextTurn = 1;
	this.gamepad =
		[
			[0, 0, 0],
			[0, 0, 0],
			[0, 0, 0]
		];

	this.drawer = new Drawer(this,
		{
			separation: 7,
			width: 500,
			height: 500
		}
	);

	this.init = function () {
		var that = this;
		this.tree = new Tree();
		this.drawer.init();
		this.drawer.draw(this.gamepad, { contID: this.contID });
		//Also set the show function of modals on click
		d3.select("#" + this.contID).selectAll(".layer-item").on('click', function () {
			that.move(this);
		});
	}

	this.move = function (item) {
		var that = this;
		var data = {
			col: $(item.parentNode).attr("col"),
			row: $(item.parentNode).attr("row")
		}

		if (this.gamepad[data.row][data.col] != 0) {
			return;
		}

		this.gamepad[data.row][data.col] = this.nextTurn;

		if (this.IsWinner()) {
			alert("There is a winner!: Winner" + this.getMove(this.IsWinner()));
			this.reset();
		}

		this.drawer.drawMove(this.getMove(this.nextTurn), item, this.gamepad);
		this.nextTurn = (this.nextTurn == 1) ? 2 : 1;
		
		if ($('#draw').is(":checked")) {
		// Asynchronous get&draw all moves from each move
			$.ajax({
				url: "/api/tree",
				data: {
					gamepad: JSON.stringify(that.gamepad),
					next: that.nextTurn
				},
				success: function (response) {
					that.tree.draw(response.tree);
				}
			});
		}
	}

	this.getMove = function (data) {
		var t = "";
		switch (data) {
			case 0:
				t = ""; break;
			case 1:
				t = "X"; break;
			case 2:
				t = "O"; break;
		}
		return t;
	}

	this.IsWinner = function () {
		// Winner by row
		for (var i = 0; i < 3; i++ ){
			if (this.gamepad[i][0] != 0 && this.gamepad[i][0] == this.gamepad[i][1] && this.gamepad[i][1] == this.gamepad[i][2]) {
				winner = this.gamepad[i][0];
				return winner;
			}
		}

		// Winner by col
		for (var i = 0; i < 3; i++ ){
			if (this.gamepad[0][i] != 0 && this.gamepad[0][i] == this.gamepad[1][i] && this.gamepad[1][i] == this.gamepad[1][i]) {
				winner = this.gamepad[0][i];
				return winner;
			}
		}

		if (this.gamepad[0][0] != 0 && this.gamepad[0][0] == this.gamepad[1][1] && this.gamepad[1][1] == this.gamepad[2][2]) {
			winner = this.gamepad[0][0];
			return winner;
		}

		if (this.gamepad[2][0] != 0 && this.gamepad[0][2] == this.gamepad[1][1] && this.gamepad[1][1] == this.gamepad[2][0]) {
			winner = this.gamepad[2][0];
			return winner;
		}

		return false;
	}
	this.reset = function () {
		this.nextTurn = 1;
		this.gamepad = [[0, 0, 0], [0, 0, 0], [0, 0, 0]];
		$("#" + this.contID).html("");
		this.drawer.draw(this.gamepad, { contID: this.contID });
		d3.select("#" + this.contID).selectAll(".layer-item").on('click', function () {
			that.move(this);
		});
	}
}

var Tree = function (options) {
	this.contID = "tree-container" || options.contID;
	
}

// D3.js drawer for the game
var Drawer = function (game, options) {
	options = options || {};
	this.server = options.server || "10.19.9.222";
	this.alive = false;
	this.parentID = "game-container"
	this.contID = "gamepad" || options.contID;
	this.layout = null;
	this.width = options.width || 720;
	this.height = options.height || 720;
	this.separation = options.separation || 0;

	this.init = function (callback) {
		var that = this;
		$('#' + that.parentID).html('<div id="' + that.contID + '" style="width: ' + that.width + 'px; height: ' + that.height + 'px;"></div>');
	}

	this.draw = function (data) {
		//http://jsfiddle.net/1gyjd2xt/4/
		var that = this;
		var svg = d3.select("#" + that.contID).append("svg")
			.attr("width", that.width)
			.attr("height", that.height);

		this.drawLayer(svg, data, null, { x: 0, y: 0, width: that.width, height: that.height, separation: that.separation });
	}

	this.drawLayer = function (svg, layer, next, base) {
		var cols = layer[0].length;
		var rows = layer.length;

		var qty = cols * rows;

		// Calculate width and height
		var width = (base.width - (base.separation * (cols - 1))) / cols;
		var height = (base.height - (base.separation * rows - 1)) / rows;

		var counter = 0;

		for (var r = 0; r < rows; r++) {
			for (var c = 0; c < cols; c++) {
				var pos = {
					x: ((c * width) + (c * base.separation)) + base.x,
					y: ((r * height) + (r * base.separation)) + base.y
				}
				var g = svg.append("g")
					.attr("data", layer[r][c])
					.attr("row", r)
					.attr("col", c);
				
				var rectangle = g.append("rect")
					.attr("x", pos.x)
					.attr("y", pos.y)
					.attr("width", width)
					.attr("height", height)
					.attr("class", "layer-item");

				if (next && layer[r][c]) {
					this.drawLayer(g, next, null, { x: pos.x, y: pos.y, width: width, height: height, separation: 0 })
				}
			}
		}
	}

	this.drawMove = function (move, item, layer) {
		var cols = layer[0].length;
		var rows = layer.length;

		var base = {
			width: this.width,
			height: this.height,
			separation: this.separation
		};

		var width = (base.width - (base.separation * (cols - 1))) / cols;
		var height = (base.height - (base.separation * rows - 1)) / rows;

		var fontSize = (width > height) ? height : width;
		fontSize = fontSize - 4;

		var p = d3.select(item);

		var g = p.select(function () { return this.parentNode });

		g.attr("data", move)
		var pos = {
			x: p[0][0].x.baseVal.value,
			y: p[0][0].y.baseVal.value
		}
		
		var text = g.append("text")
			.attr("class", "layer-text")
			.attr("x", pos.x + (width / 2) - (fontSize / 3))
			.attr("y", pos.y + (height / 2))
			.attr('font-size', '5px')
			.attr("dy", "0.35em")
			.text(move)
			.transition()
				.attr('font-size', '1em')
				.duration(300)
			.transition()
				.attr('font-size', fontSize + 'px')
				.duration(400);
	}
}