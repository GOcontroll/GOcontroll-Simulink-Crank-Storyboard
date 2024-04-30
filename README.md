# GOcontroll-Simulink-Crank-Storyboard
A GOcontroll-Simulink extension blockset for working with a Crank Storyboard UI

## Setup

Download the addon from the matlab addon explorer.

Create a crank_files folder in your project root:
``` text
.
├── blockset
├── crank_files
├── GOcontroll_Linux.slx
├── GOcontroll_Linux_startup.m
├── librarySetup.m
```
This folder will contain your Crank related files, greio.h, greio.a and event descriptions. You will have to provide these 
``` text
./crank_files
├── event_definitions.h
├── crank_header.h
├── crank_lib.a
```
An example of the event description file can be found in the example_code directory.  
The format of an event in this file is important for the parser and should look like this:
``` h
#define <EVENT_NAME>_EVENT "<event_name>"
#define <EVENT_NAME>_FMT "2u1 field_name1 2u1 field_name2"
typedef struct {
	uint16_t 		field_name1; // type and name can be customized as desired, but need to be on one line
	uint16_t 		field_name2; // allowed types: double, float, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t
} <event_name>_event_t;
```
If an event has no data attached to it you only have to put in the first #define, see the example file.  

It might be nice to split your receive channel events and your send channel events into 2 seperate header files.  
It will make deserializing more efficient.  

## Usage

### Receiving events in Simulink
Place a Crank receive channel block, then attach a function call subsystem to it and have the event be an input to this subsystem.  
Then place any number of Crank deserialize event blocks in this subsystem to get the event info.

### Sending events from Simulink
Place a Crank serialize event block and select the desired event to serialize.

Copy the model from examples to the root of your project, this model is made to work with the ThermostatIO example from Crank.  
This is also the project that the example header file comes from so you can move that to your project aswell.

### Notes

The first startup might take some time as it needs to compile some MEX files.
This blockset is made using 2023b, it might work with 2024a.