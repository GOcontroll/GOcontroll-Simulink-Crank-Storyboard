# GOcontroll-Simulink-Crank-Storyboard
A GOcontroll-Simulink extension blockset for working with a Crank Storyboard UI

## Setup

Create a project using the regular [GOcontroll-Simulink](https://github.com/GOcontroll/GOcontroll-Simulink) template.  
Make a copy or a symbolic link of the blockset_crank folder at the root level of this template so it is next to the regular blockset directory:
``` text
.
├── blockset
├── blockset_crank
├── GOcontroll_Linux.slx
├── GOcontroll_Linux_startup.m
├── librarySetup.m
```
Next create a crank_files folder in your project root:
``` text
.
├── blockset
├── blockset_crank
├── crank_files
├── GOcontroll_Linux.slx
├── GOcontroll_Linux_startup.m
├── librarySetup.m
```
This folder will contain your Crank related files, greio.h, greio.a, event descriptions and a Makefile.  
``` text
./crank_files
├── Makefile
├── event_definitions.h
├── crank_header.h
├── crank_lib.a
```
An example Makefile can be found in the example_code folder, An example of the event description file can also be found here.  
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

## Usage

Start matlab in your project and open your simulink model, the librarySetup.m script will now load this addon into your simulink library.  
Your library browser should now show a GOcontroll Crank library.

### Receiving events in Simulink
Place a Crank receive channel block, then attach a function call subsystem to it and have the event be an input to this subsystem.  
Then place any number of Crank deserialize event blocks in this subsystem to get the event info.
### Sending events from Simulink
Place a Crank serialize event block and select the desired event to serialize.

Copy the model from examples to the root of your project, this model is made to work with the ThermostatIO example from Crank.  
This is also the project that the example header file comes from so you can move that to your project aswell.

### Notes

The first startup might take some time as it needs to compile some MEX files.