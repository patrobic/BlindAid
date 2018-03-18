# Test Cases

## Mode Summary
	command				particularity	debug	result
	blindaid -a			realtime		no		good
	blindaid -c			camera only		no		good
	blindaid -t path	control only	yes		good	// does not handle no path
	blindaid -s	path	simulate all	yes
	blindaid -r			record manual		
	blindaid -r 1000	record interval		

	blindaid -d -a		realtime		yes		good
	blindaid -d -c		camera only		yes		good
	blindaid -d -t path	control only	yes		

## Launch by Arguments
### GLOBAL BEHAVIOR
	- loop forever in whatever mode chosen
	- apply all parameters selected

### MODE SELECTION ARGUMENTS
	a: launch realtime mode

	c: launch camera only mode

	t: prompt path, launch glove only mode

	s: prompt path, launch simulation only mode

	r: launch capture only mode, with record enabled

### PARAMETER ARGUMENTS
	d: enable display of color and depth images

	v [index]: increase logging verbosity
	- index provided: set to provided index (0: error, 1: warning, 2: info)
	- index not provided: set to highest level (show all)

	l: disable performance optimizations
	- no parallel threading of depth/deeplearning (1 TL detection per Core iteration)
	- pause between detections/display of images

	p <port>: set bluetooth serial COM port
	- connects to glove on specified port or fails if wrong port

	cc [count]: set consecutive count
	- 0 or not provided: set to 0 (no consecutive behavior)
	- count > 0: only alerted after detected in count frames

	do {fr | hp}: set depth obstacle module to mode
	- fr: set to fixed regions mode (region centered, five equal columns)
	- hp: set to hand position mode (not implemented)

	tl {dl | bd}: set traffic light module to mode
	- dl: set to deep learning mode (4 confidence values + detected value on top left)
	- bd: set to blobdetector mode (no values on top left, circles around light detections)

	coloroff: disable color processing
	- color image not displayed
	- color processing not done
	- no traffic light feedback provided

	depthoff: disable depth processing
	- depth image not displayed
	- depth processing not done
	- no depth obstacle feedback provided

	?: show help, go to menu

### CONNECTION BEHAVIOR
	camera:
	- connect if plugged in
	- warn user and keep reconnecting if not plugged in
	- warn user if disconnected and keep trying to reconnect
	- reconnect if re-plugged in

	glove:
	- connect if plugged in
	- warn user and keep reconnecting if not plugged in
	- warn user if disconnected and keep trying to reconnect
	- reconnect if re-plugged in

## Launch by User Menu
### GLOBAL BEHAVIOR
	- escape in module to return to menu

### MAIN FLAGS
	?: show help, any key to show menu

	m: prompt text, launch provided mode

	q or escape: exit program

### REALTIME MODES
	a: launch realtime mode

	c: launch camera only mode
	- display enabled
	
	t: prompt path, launch glove only mode
	- infinite loop sequence
	- return to menu if invalid path or no files
	- display enabled

	s: prompt path, launch simulation only mode
	- infinite loop sequence
	- return to menu if invalid path or no files
	- display enabled

	r: launch capture only mode, with record enabled
	- 0 or nothing provided: capture on keypress
	- x > 0 provided: captuer every x ms
	- display enabled

### SIMULATION MODES
	o: launch capture only mode, with color disabled
	- pause between each image
	- return to menu if invalid path, no files, or all files done

	l: launch glove only mode, with depth disabled
	- pause between each image
	- pause then return to menu if invalid path, no files, or all files done
