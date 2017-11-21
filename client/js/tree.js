var Tree = function () {
	this.draw = function (treeData) {
		treeData.parent = 0;
		var margin = { top: 20, right: 10, bottom: 20, left: 10 },
			width = 706 - margin.right - margin.left,
			height = 500 - margin.top - margin.bottom;

		var i = 0;

		var tree = d3.layout.tree()
			.size([height, width]);

		var diagonal = d3.svg.diagonal()
			.projection(function (d) { return [d.y, d.x]; });
		
		d3.select("#tree-container").html("");
		
		var svg = d3.select("#tree-container").append("svg")
			.attr("width", width + margin.right + margin.left)
			.attr("height", height + margin.top + margin.bottom)
			.call(d3.behavior.zoom().on("zoom", function () {
				svg.attr("transform", "translate(" + d3.event.translate + ")" + " scale(" + d3.event.scale + ")")
			}))
			.append("g")
			.attr("transform", "translate(" + margin.left + "," + margin.top + ")");

		root = treeData;

		update(root);

		function update(source) {
			// Compute the new tree layout.
			var nodes = tree.nodes(root).reverse(),
				links = tree.links(nodes);

			// Normalize for fixed-depth.
			nodes.forEach(function (d) { d.y = d.depth * 180; });

			// Declare the nodes…
			var node = svg.selectAll("g.node")
				.data(nodes, function (d) { return d.id || (d.id = ++i); });

			// Enter the nodes.
			var nodeEnter = node.enter().append("g")
				.attr("class", "node")
				.attr("transform", function (d) {
					return "translate(" + d.y + "," + d.x + ")";
				});

			nodeEnter.append("circle")
				.attr("r", function (d) { return 7; })
				.style("fill", function (d) { 
					switch (d.winner) {
						case 0:
							return "#3674A8"
						case 1:
							return "#36A84B"
						case 2:
							return "#A83636"	
					}
				 });
			
			/*nodeEnter.append("text")
				.attr("x", function (d) {
					return d.children || d._children ?
						(d.value + 4) * -1 : d.value + 4
				})
				.attr("dy", ".35em")
				.attr("text-anchor", function (d) {
					return d.children || d._children ? "end" : "start";
				})
				.text(function (d) { return d.name; })
				.style("fill-opacity", 1);*/

			// Declare the links…
			var link = svg.selectAll("path.link")
				.data(links, function (d) { return d.target.id; });

			// Enter the links.
			link.enter().insert("path", "g")
				.attr("class", "link")
				// .style("stroke", fun kction (d) { return d.target.level; })
				.attr("d", diagonal);
		}
	}
}