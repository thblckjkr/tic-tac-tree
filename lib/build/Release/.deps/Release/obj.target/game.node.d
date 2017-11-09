cmd_Release/obj.target/game.node := g++ -shared -pthread -rdynamic -m32  -Wl,-soname=game.node -o Release/obj.target/game.node -Wl,--start-group Release/obj.target/game/game.o -Wl,--end-group 
