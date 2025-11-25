compiler:
	cd build && cmake .. && make -j8

antlr:
	java -jar lib/antlr-4.13.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o src/antlr/ SysYLexer.g4 SysYParser.g4

clean:
	rm -f src/antlr/*.cpp src/antlr/*.h
	rm -f src/antlr/*.interp src/antlr/*.tokens

test:
	python3 run-test.py

.PHONY: antlr clean test
