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

## Usage ##

To run the program you can only do 

	node servers.js OR npm run start

The program need's to be previously compiled with

	npm run compile

## How it works ##

Basically, the cpp addon (powered with `nan`) get's a two dimentional array (the gamepad) , and creates a n-ary tree structure with the possible movements.

Then populates it to a v8 Object and then it return's the tree

I don't know how about performance, but it's so great for a homework