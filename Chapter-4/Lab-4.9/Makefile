.PHONY: flash trace watch debug clean

flash:
	platformio run --target ViDBo --environment flash

trace: 
	platformio run --target generate_trace --environment trace
	
watch:
	python3 -m http.server --directory ./lib/verilatorSIM_ViDBo/NexysA7board
	
debug: 
	pio debug -v --environment debug --interface=gdb -- -x .pioinit 

clean:
	platformio run --target fullclean
