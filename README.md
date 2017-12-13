# tic-tac-tree

> Not functional yet

Tic Tac Toe game with a tree of possible movements.
The tree it's generated with C++, send across NodeJS and rendered with D3js.

	Latest stable release requirements

	node		v4.4.2
	npm 		v2.15.0
	node-gyp	v3.6.2

## Changelog ##

- v0.0 Initial release

	Creation of files, folders and things

## Interesting things founds ##
In a empty game there are

**116532** ways to win for the one who start
**70008**  ways to win for the one who goes second
**490241** possible movements

## Usage ##

To run the program you can only do 

	node servers.js OR npm run start

The program need's to be previously compiled with

	npm run compile

## How it works ##

Basically, the cpp addon (powered with `nan`) get's a two dimentional array (the gamepad) , and creates a n-ary tree structure with the possible movements.

Then populates it to a v8 Object and then it return's the tree

I don't know how about performance, but it's so great for a homework

Performance benchmarks

```
From:
1 0 0
0 0 0
0 0 0

GameConstruct: 159ms (21380 nodes)
```

```
From:
0 0 0
0 1 0
0 0 0

GameConstruct: 454ms (55505 nodes)
Stringify: 157ms

```